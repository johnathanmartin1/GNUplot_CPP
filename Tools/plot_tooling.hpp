#ifndef plot_tooling
#define plot_tooling

#include <vector>
#include <string>
#include <type_traits>
#include <variant>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

#include "math_tools.hpp"

//___________________________________________________________________________________________________________________________________________________________________________


struct plot_builder_2D
{
public:
    /// <summary>
    /// Checks that the x and y data are the same size for each data set to be plotted.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="x_data"></param>
    /// <param name="y_data"></param>
    template <typename T>
    void data_size_check(const std::vector<std::vector<T>>& x_data, const std::vector<std::vector<T>>& y_data)
    {
        for (std::size_t i = 0; i < x_data.size(); i++)
        {
            if (x_data[i].size() != y_data[i].size())
            {
                std::cout << "x and y data not the same size!";

                return;
            }
        }
    }





    /// <summary>
    /// Builds the data structure in the correct manner for gnu plot.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="gp"></param>
    /// <param name="x_data"></param>
    /// <param name="y_data"></param>
    template <typename T>
    void gnu_data_builder(std::ofstream& gp, const std::vector<std::vector<T>>& x_data, const std::vector<std::vector<T>>& y_data)
    {
        for (std::size_t i = 0; i < x_data.size(); i++)
        {
            for (std::size_t j = 0; j < x_data[i].size(); j++)
            {
                gp << x_data[i][j] << " " << y_data[i][j] << "\n";
            }

            gp << "\n" << "e\n";

        }
    }

   
    template <typename T = double, typename U>
    void tic_builder_2D(std::ofstream& gp, const std::string tic_axis, const std::vector<U>& layered_figures, const std::vector<std::vector<T>>& x_data, const std::vector<std::vector<T>>& y_data,
        std::vector<double>& xtic_base, std::vector<double>& ytic_base, double& x_range_min, double& x_range_max, double& y_range_min, double& y_range_max, int xtic_decimal_places, int ytic_decimal_places,
    const std::vector<std::string>& xtic_labels, const std::vector<std::string>& ytic_labels,  double xtic_rotation, double ytic_rotation)
    {
        std::vector<double> tics{};
        double* range_min = nullptr;//1e308 max -1e308 min
        double* range_max = nullptr;
        int tic_decimal_places{};
        std::vector<std::string> tic_labels{};
        const std::vector<std::vector<T>>* data = nullptr;
        double rotation{};

        if (tic_axis == "x") { data = &x_data; range_min = &x_range_min; range_max = &x_range_max; tic_decimal_places = xtic_decimal_places; tic_labels = xtic_labels; rotation = xtic_rotation; }
        else if (tic_axis == "y") { data = &y_data; range_min = &y_range_min; range_max = &y_range_max; tic_decimal_places = ytic_decimal_places; tic_labels = ytic_labels; rotation = ytic_rotation; }
        //can add in secondry axis onto this list later on
        
        //tics.clear();

        double max = -std::numeric_limits<double>::infinity();
        double min = std::numeric_limits<double>::infinity();
        double scale{};

        if (!data->empty())
        {
            for (const std::vector<T>& data_pack : *data)
            {
                if (!data_pack.empty())
                {
                    auto [minIt, maxIt] = std::minmax_element(data_pack.begin(), data_pack.end());

                    if (*minIt < min) { min = static_cast<double>(*minIt); }

                    if (*maxIt > max) { max = static_cast<double>(*maxIt); }
                }
            }
        }

        if (!layered_figures.empty())
        {
            tic_builder_layers(tic_axis, layered_figures, min, max);
        }

        std::vector<double> tics_min_max_expanded{};
        if (*range_min == -1e308 and *range_max == 1e308)
        {
            tics_min_max_expanded = tics_min_max_expander(min, max);

            min = tics_min_max_expanded[0];

            max = tics_min_max_expanded[1];
        }
        else if (*range_min == -1e308)
        {
            tics_min_max_expanded = tics_min_max_expander(min, *range_max);

            min = tics_min_max_expanded[0];

            max = tics_min_max_expanded[1];
        }
        else if (*range_max == 1e308)
        {
            tics_min_max_expanded = tics_min_max_expander(*range_min, max);

            min = tics_min_max_expanded[0];

            max = tics_min_max_expanded[1];
        }
        else
        {
            tics_min_max_expanded = tics_min_max_expander(*range_min, *range_max);

            min = *range_min;

            max = *range_max;
        }

        scale = tics_min_max_expanded[2];

        
        

        for (double i = min; i <= max; i += scale)
        {
            tics.push_back(i);
        }
        
        
        tic_label_builder(tic_axis, gp, tics, tic_labels, scale, tic_decimal_places, rotation);

        if (tic_axis == "x") {   xtic_base = tics; x_range_min = *range_min; x_range_max = *range_max; }
        //else if (tic_axis == "y") { ytic_base = tics; y_range_min = *range_min; y_range_max = *range_max; }

    }


    template <typename U>
    void tic_builder_layers(const std::string& tic_axis, const std::vector<U>& layered_figures, double& min, double& max)
    {
        for (const auto& figure : layered_figures)
        {
            std::visit([&](const auto& wrapped_fig)
                {
                    const auto& fig = wrapped_fig.get();

                    auto inspect = [&](const auto& nested_data)
                        {
                            for (const auto& data_pack : nested_data)
                            {
                                if (data_pack.empty()) continue;

                                const auto [min_it, max_it] = std::minmax_element(data_pack.begin(), data_pack.end());

                                min = std::min(min, static_cast<double>(*min_it));

                                max = std::max(max, static_cast<double>(*max_it));
                            }

                        };

                    if (tic_axis == "x") inspect(fig.x_data);

                    else if (tic_axis == "y") inspect(fig.y_data);



                }, figure);
        }
    }


    //Expands the tic labels according to the magnitude of the scale of the data so that the range end points will be at 
    std::vector<double> tics_min_max_expander(double min, double max)
    {

        double order{};

        double difference = max - min;
        if (difference == 0.0) {
            std::cout << "Axis has zero differnce between intial and final range\n\n";
        }
        else
        {
            order = std::floor(std::log10(std::abs(difference)));
        }

        double scale = std::pow(10, order);

        if (difference / scale <= 5) { scale = 5 * scale / 10; }
        if (difference / scale <= 4) { scale = 4 * scale / 10; }
        if (difference / scale <= 3) { scale = 3 * scale / 10; }
        if (difference / scale <= 2) { scale = 2 * scale / 10; }
        if (difference / scale <= 1) { scale = 1 * scale / 10; }

        double end_range = std::ceil(max / scale) * scale;

        double start_range = std::floor(min / scale) * scale;

        std::vector<double> min_max_range{ start_range, end_range, scale };

        return min_max_range;

    }

    //Produces the gnu plot string for the tic labels
    void tic_label_builder(const std::string tic_axis, std::ofstream& gp,  std::vector<double>& tic_base, const std::vector<std::string>& tic_labels, double scale, int tic_decimal_places, double rotation)
    {
        if (scale < 1 and tic_decimal_places == 0) { tic_decimal_places = static_cast<int>(std::ceil(std::abs(std::log10(scale)))); }
        
        gp << "set ";
        
        if (tic_axis == "x") { gp << "xtics "; }
        else if (tic_axis == "y") { gp << "ytics "; }
        else if (tic_axis == "x2") { gp << "x2tics "; }
        else if (tic_axis == "y2") { gp << "y2tics "; }

        gp << "(";

        for (std::size_t i = 0; i < tic_base.size(); i++)
        {
            if (tic_labels.empty())
            {
                gp << "\"" << round_to_places(tic_base[i], tic_decimal_places) << "\" " << tic_base[i];
            }
            else
            {
                std::string label = (i + 1 > tic_labels.size()) ? "" : tic_labels[i];
 
                gp << "\"" << label << "\" " << tic_base[i];
            }
            
            if (i + 1 == tic_base.size())
            {
                gp << ") rotate by "<< rotation << "right\n";
            }
            else
            {
                gp << ", ";
            }
        }
    }

    

};


//____________________________________________________________________________________________________________________________________________________________________________


struct plot_builder_3D
{
protected:
    /// <summary>
    /// Checks that the x, y and z data are the same size for each data set to be plotted.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="x_data">x plotting data.</param>
    /// <param name="y_data">y plotting data.</param>
    /// <param name="z_data">z plotting data<\param>
    template <typename T>
    bool data_size_check_3D(const std::vector<std::vector<T>>& x_data, const std::vector<std::vector<T>>& y_data, const std::vector<std::vector<T>>& z_data)
    {
        for (std::size_t i = 0; i < x_data.size(); i++)
        {
            if (x_data[i].size() != y_data[i].size())
            {
                std::cerr << "x and y data not the same size in data set " << i + 1 << "\n";

                return true;
            }
        }

        for (std::size_t i = 0; i < x_data.size(); i++)
        {
            if (x_data[i].size() != z_data[i].size())
            {
                std::cerr << "x and z data not the same size in data set " << i + 1 << "\n";

                return true;
            }
        }

        for (std::size_t i = 0; i < x_data.size(); i++)
        {
            if (y_data[i].size() != z_data[i].size())
            {
                std::cerr << "y and z data not the same size in data set " << i + 1 << "\n";

                return true;
            }
        }
        return false;
    }




    /// <summary>
  /// Builds the data structure in the correct manner for gnu plot.
  /// </summary>
  /// <typeparam name="T"></typeparam>
  /// <param name="gp"></param>
  /// <param name="x_data"></param>
  /// <param name="y_data"></param>
    template <typename T>
    void gnu_data_builder_3D(std::ofstream& gp, const std::vector<std::vector<T>>& x_data, const std::vector<std::vector<T>>& y_data, const std::vector<std::vector<T>>& z_data,
        double x_min, double x_max, double y_min, double y_max, double z_min, double z_max)
    {
        for (std::size_t i = 0; i < x_data.size(); i++)
        {
            for (std::size_t j = 0; j < x_data[i].size(); j++)
            {
                const auto x = x_data[i][j]; //these three statements cut the plot off when it falls out of range as set xrange etc doesnt cut the lines in 3d plot in gnu for some reason!!!
                
                if (x < x_min || x > x_max)
                
                    continue;
                
                const auto y = y_data[i][j];
                
                if (y < y_min || y > y_max)
                
                    continue;
                
                const auto z = z_data[i][j];
                
                if (z < z_min || z > z_max)
                
                    continue;
                
                gp << x<< " " << y << " " << z << "\n";
            }

            gp  << "e\n";

        }
    }

  
};



//__________________________________________________________________________________________________________________________________________________________________________________________

/// <summary>
/// General plottting tools for handling the plotting data that are common across all plot types.
/// </summary>
struct plot_tools
{


public:
    /// <summary>
  /// Assigns the min and max of th ex and y axis if chosen if not it reverst back top teh gnu plot auto range utilising [*:*] for min man ranges.
  /// </summary>
  /// <param name="options"></param>
  /// <param name="axis"></param>
  /// <returns></returns>
    std::string range_min_max(const double range_min, const double range_max)
    {
        std::string min{};
        std::string max{};
        
        {
            min = (range_min == -1e308) ? "*" : std::to_string(range_min);
            max = (range_max == 1e308) ? "*" : std::to_string(range_max);
        }
        
        return "[" + min + ":" + max + "]";

    }




    /// <summary>
    /// Does the finishing of the plot data lines for gnuplot accounting for if there aree more than one set of data.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="gp"> The gnuplot instance.</param>
    /// <param name="i"> The curent iteration of the data conatiner.</param>
    /// <param name="x_data"> The x_data conatiner</param>
    template <typename T>
    void data_finishing(std::ofstream& gp, const std::size_t i, const std::vector<std::vector<T>>& x_data)
    {
        if (i + 1 < x_data.size())
        {
            gp << ", ";
        }

        else
        {
            gp << "\n";
        }
    }

   
    template <typename U, typename T>
    void list_sizing_to_data(std::vector<U>& list, const std::vector<std::vector<T>>& x_data, const std::type_identity_t<U>&& default_value)
    {
        std::size_t list_size = list.size();
        if (list_size < x_data.size())
        {
            for (std::size_t i = 0; i < x_data.size() - list_size; i++)
            {
                list.push_back(default_value);
            }
        }

        if (list_size > x_data.size())
        {
            for (std::size_t i = 0; i < list_size - x_data.size(); i++)
            {
                list.pop_back();
            }
        }
    }


    
    

};


























#endif