#ifndef TwoD_line_plot
#define TwoD_line_plot

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <type_traits>

#include "Tools/plot_tooling.hpp"
#include "Tools/plot_options.hpp"


/// _________________________________________________________________________________________

/// <summary>
/// creates a plot class that is intialised with data using the x_data(xdata1, xdata2,...) and y_data(ydata1, ydata2,...) functions. 
/// The supplied data must be in a vector container i.e std::vector. E.g plot plot_name(x_data(x values for data set 1 vec, x values for data set 2 vec, ...), y_data(y values for data set 1 vector, y values for data set 2 vec, ...))
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
class plot : public two_D_plot_options, public plot_tools, public plot_builder_2D
{
private:
    std::vector<std::vector<T>> x_data;

    std::vector<std::vector<T>> y_data;

public:
    plot(const std::vector<std::vector<T>> x_dat, const std::vector<std::vector<T>> y_dat) : x_data{ x_dat }, y_data{ y_dat }
    {
        static_assert(std::is_arithmetic_v<T>, "plot function requires a numeric data type.");
    }

    ~plot() { std::cout << "plot deleted\n"; }

    /// <summary>
    /// Displays the plot in an interactive window.
    /// </summary>
    void show()
    {
        std::ofstream gp("plot.gp");

        if (!gp)
        {
            std::cerr << "Could not create plot.gp\n";

            return;
        }

        gp << "set terminal windows\n";

        gp << "set mouse\n";

        gp << "set xlabel \"" << x_axis_label << "\"\n";

        gp << "set ylabel \"" << y_axis_label << "\"\n";

        gp << "set title \"" << title << "\"\n";

        if (grid == true)
        {
            gp << "set grid\n";
        }

        gp << "set xrange " << range_min_max(x_range_min, x_range_max) << "\n";

        gp << "set yrange " << range_min_max(y_range_min, y_range_max) << "\n";

        data_size_check(x_data, y_data);

        gnu_plot_builder(gp, x_data);

        gnu_data_builder(gp, x_data, y_data);

        gp << "pause mouse close\n";

        gp.close();

        std::system("gnuplot plot.gp");

    }

    /// <summary>
    /// Saves the plot as a png file.
    /// </summary>
    /// <param name="name">file location and name to be saved as, i.e "C:/users/documnets/my_plot", take note you must use foward slashes as reverse slash will not work</param>
    void save(std::string name)
    {
        std::ofstream gp("plot.gp");

        if (!gp)
        {
            std::cerr << "Could not create plot.gp\n";

            return;
        }

        gp << "set terminal pngcairo size 1200, 800\n";

        gp << "set output '" << name << ".png'\n";

        gp << "set mouse\n";

        gp << "set xlabel \"" << x_axis_label << "\"\n";

        gp << "set ylabel \"" << y_axis_label << "\"\n";

        gp << "set title \"" << title << "\"\n";

        if (grid == true)
        {
            gp << "set grid\n";
        }

        gp << "set xrange " << range_min_max(x_range_min, x_range_max) << "\n";

        gp << "set yrange " << range_min_max(y_range_min, y_range_max) << "\n";

        data_size_check(x_data, y_data);

        gnu_plot_builder(gp, x_data);

        gnu_data_builder(gp, x_data, y_data);

        gp << "unset output\n";

        gp.close();

        std::system("gnuplot plot.gp");
    }







    protected:


    /// <summary>
    /// builds the plot option for the gnu plot.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="gp"></param>
    /// <param name="x_data"></param>
    /// <param name="options"></param>
    template <typename T>
    void gnu_plot_builder(std::ofstream& gp, const std::vector<std::vector<T>>& x_data)
    {
        if (legend == true)
        {

            gp << "plot";

            for (std::size_t i = 0; i < x_data.size(); i++)
            {
                data_label_sizing(data_label, x_data);

                gp << " '-' using 1:2 with lines lw " << linewidth << " title '" << data_label[i] << "'";

                data_finishing(gp, i, x_data);
            }
        }
        else
        {
            gp << "set key off\n";

            gp << "plot";

            for (std::size_t i = 0; i < x_data.size(); i++)
            {
                gp << " '-' using 1:2 with lines lw " << linewidth << " ";

                data_finishing(gp, i, x_data);
            }

        }
    }

};



#endif