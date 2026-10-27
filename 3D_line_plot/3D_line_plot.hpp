#ifndef ThreeD_line_plot
#define ThreeD_line_plot

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
class plot3D : public three_D_plot_options, public plot_tools, public plot_builder_3D
{
private:
    std::vector<std::vector<T>> x_data;

    std::vector<std::vector<T>> y_data;

    std::vector<std::vector<T>> z_data;




public:
    plot3D(const std::vector<std::vector<T>> x_dat, const std::vector<std::vector<T>> y_dat, const std::vector<std::vector<T>> z_dat) : x_data{ x_dat }, y_data{ y_dat }, z_data{z_dat}
    {
        static_assert(std::is_arithmetic_v<T>, "plot function requires a numeric data type.");
    }

    ~plot3D() { std::cout << "plot deleted\n"; }

    /// <summary>
    /// Displays the plot in an interactive window.
    /// </summary>
    void show()
    {
        if (data_size_check_3D(x_data, y_data, z_data)) { return; };

        std::ofstream gp("plot.gp");

        if (!gp)
        {
            std::cerr << "Could not create plot.gp\n";

            return;
        }

        gp << "set terminal windows\n";

        gp << "set mouse\n";

        gp << "set xlabel '" << x_axis_label << "' font '," << axis_label_fontsize << "'\n";

        gp << "set ylabel '" << y_axis_label << "' font '," << axis_label_fontsize << "'\n";

        gp << "set zlabel '" << z_axis_label << "' font '," << axis_label_fontsize << "'\n";

        gp << "set title \"" << title << "\"\n";

        if (grid == true)
        {
            gp << "set grid\n";
        }

        gp << "set xrange " << range_min_max(x_range_min, x_range_max) << "\n";

        gp << "set yrange " << range_min_max(y_range_min, y_range_max) << "\n";

        gp << "set zrange " << range_min_max(z_range_min, z_range_max) << "\n";

        gnu_plot_builder_3D(gp, x_data);

        gnu_data_builder_3D(gp, x_data, y_data, z_data, x_range_min, x_range_max, y_range_min, y_range_max, z_range_min, z_range_max);
        
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
        if (data_size_check_3D(x_data, y_data, z_data)) { return; };

        std::ofstream gp("plot.gp");

        if (!gp)
        {
            std::cerr << "Could not create plot.gp\n";

            return;
        }

        gp << "set terminal pngcairo size 1200, 800\n";

        gp << "set output '" << name << ".png'\n";

        gp << "set mouse\n";

        gp << "set xlabel '" << x_axis_label << "' font '," << axis_label_fontsize << "'\n";

        gp << "set ylabel '" << y_axis_label << "' font '," << axis_label_fontsize << "'\n";

        gp << "set zlabel '" << z_axis_label << "' font '," << axis_label_fontsize << "'\n";

        gp << "set title \"" << title << "\"\n";

        if (grid == true)
        {
            gp << "set grid xtics ytics ztics\n";
        }

        gp << "set xrange " << range_min_max(x_range_min, x_range_max) << "\n";

        gp << "set yrange " << range_min_max(y_range_min, y_range_max) << "\n";

        gp << "set zrange " << range_min_max(z_range_min, z_range_max) << "\n";

        gnu_plot_builder_3D(gp, x_data);

        gnu_data_builder_3D(gp, x_data, y_data, z_data, x_range_min, x_range_max, y_range_min, y_range_max, z_range_min, z_range_max);

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
    void gnu_plot_builder_3D(std::ofstream& gp, const std::vector<std::vector<T>>& x_data)
    {
        gp << "set xyplane 0\n";

        gp << "set wall x0 fillstyle solid 0.5 fc rgb '" << background_colour << "'\nset wall y1 fillstyle solid 0.5 fc rgb '" << background_colour << "'\nset wall z0 fillstyle solid 0.5 fc rgb '" << background_colour << "'\n";

        gp << "set tics font '," << axis_tic_fontsize << "'\n";
        
        gp << "set border " << border << " lw " << border_thickness << "\n";

        if (legend == true)
        {
            gp << "set key font '," << legend_fontsize << "'\n";

            gp << "splot";

            for (std::size_t i = 0; i < x_data.size(); i++)
            {
                data_label_sizing(data_label, x_data);

                gp << " '-' using 1:2:3 with lines lw " << linewidth << " title '" << data_label[i] << "'";

                data_finishing(gp, i, x_data);
            }
        }
        else
        {
            gp << "set key off\n";

            gp << "splot";

            for (std::size_t i = 0; i < x_data.size(); i++)
            {
                gp << " '-' using 1:2:3 with lines lw " << linewidth;

                data_finishing(gp, i, x_data);
            }

        }
    }
};
#endif