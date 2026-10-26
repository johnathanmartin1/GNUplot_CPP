#ifndef plot_tooling
#define plot_tooling

#include <vector>
#include <string>




//stand alone functions for user arguments

/// <summary>
/// A function for packing the x data for plotting functions.
/// </summary>
/// <typeparam name="...ARGS"></typeparam>
/// <param name="...args">Input vectors for the x data that will be packaged for plotting.</param>
/// <returns>A single vector containing vectors of the x data.</returns>
template <typename ...ARGS>
std::vector<std::vector<double>> x_data(ARGS& ...args) 
{    
    std::vector<std::vector<double>> x_dat;

    (x_dat.push_back(args), ...);

    return x_dat;
}




/// <summary>
/// A function for packing the y data for plotting functions.
/// </summary>
/// <typeparam name="...ARGS"></typeparam>
/// <param name="...args">Input vectors for the y data that will be packaged for plotting.</param>
/// <returns>A single vector containing vectors of the y data.</returns>
template < typename ...ARGS>
std::vector<std::vector<double>> y_data(ARGS& ...args) 
{
    std::vector<std::vector<double>> y_dat;

    (y_dat.push_back(args), ...);

    return y_dat;
}




/// <summary>
/// A function for packing the z data for plotting functions.
/// </summary>
/// <typeparam name="...ARGS"></typeparam>
/// <param name="...args">Input vectors for the z data that will be packaged for plotting.</param>
/// <returns>A single vector containing vectors of the z data.</returns>
template < typename ...ARGS>
std::vector<std::vector<double>> z_data(ARGS& ...args)
{
    std::vector<std::vector<double>> z_dat;
    
    (z_dat.push_back(args), ...);

    return z_dat;    
}

    

    
/// <summary>
/// A packing function for the data labels.
/// </summary>
/// <typeparam name="...ARGS"></typeparam>
/// <param name="...args">Input strings seperated by commas.</param>
/// <returns>A vector containing labels of the plotted data.</returns>
template <typename ...ARGS>
std::vector<std::string> label_data(ARGS& ...args) {

    std::vector<std::string> labels;
    
    (labels.push_back(args), ...);

    return labels;    
}


//___________________________________________________________________________________________________________________________________________________________________________


struct plot_builder_2D
{
protected:
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
protected:
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
};


























#endif