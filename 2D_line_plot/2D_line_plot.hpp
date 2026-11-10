#ifndef TwoD_line_plot
#define TwoD_line_plot

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <variant>
#include <functional>
#include <utility>

#include "Tools/plot_tooling.hpp"
#include "Tools/plot_options.hpp"
#include "Tools/options_tooling.hpp"




/// _________________________________________________________________________________________

/// <summary>
/// creates a plot class that is intialised with data using the x_data(xdata1, xdata2,...) and y_data(ydata1, ydata2,...) functions. 
/// The supplied data must be in a vector container i.e std::vector. E.g plot plot_name(x_data(x values for data set 1 vec, x values for data set 2 vec, ...), y_data(y values for data set 1 vector, y values for data set 2 vec, ...))
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T = double>
class plot : public two_D_plot_options, public plot_tools, public plot_builder_2D
{

public:
    std::vector<std::vector<T>> x_data;

    std::vector<std::vector<T>> y_data;
    
    //Add compatible plot classes that can be layered over the plot class here.
    using compatible_figure_classes = std::variant
        <
        std::reference_wrapper<plot<int>>,
        std::reference_wrapper<plot<double>>,
        std::reference_wrapper<plot<float>>
        >;

    std::vector<compatible_figure_classes> layered_figs;



    //Constructors and Destructor
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    plot(const std::vector<std::vector<T>> x_data_ = {}, const std::vector<std::vector<T>> y_data_ = {}, std::vector<compatible_figure_classes> layered_figs_ = {}) : x_data{ std::move(x_data_) }, y_data{ std::move(y_data_) }, layered_figs{ std::move(layered_figs_) }
    {
        static_assert(std::is_arithmetic_v<T>, "plot function requires a numeric data type.");
    }

    ~plot() { std::cout << "plot deleted\n"; }

    plot(const plot& other) = default;

    plot& operator = (const plot&) = default;

    plot(plot&&) = default;

    plot& operator = (plot&&) = default;

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


    // class functions
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    void plot_data_alignment() 
    {
        data_size_check(x_data, y_data);

        list_sizing_to_data(line_style, x_data, "solid");

        list_sizing_to_data(line_type, x_data, "line");

        list_sizing_to_data(point_size, x_data, 1);

        list_sizing_to_data(data_label, x_data, " ");

        list_sizing_to_data(point_type, x_data, 1);

        list_sizing_to_data(line_colour, x_data, "");
    }
    



    // Displays the plot in an interactive window.
    void show()
    {
        plot_data_alignment();

        layer_plot_data_alignment(layered_figs);

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

        gp << "set title \"" << title << "\"\n";

        if (grid == true)
        {
            gp << "set grid\n";
        }

        gp << "set xrange " << range_min_max(x_range_min, x_range_max) << "\n";

        gp << "set yrange " << range_min_max(y_range_min, y_range_max) << "\n";

        gnu_plot_builder(gp);

        gnu_data_builder(gp, x_data, y_data);

        layer_data_builder(gp, layered_figs);

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
        plot_data_alignment();

        layer_plot_data_alignment(layered_figs);

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

        gp << "set title \"" << title << "\"\n";

        if (grid == true)
        {
            gp << "set grid\n";
        }

        gp << "set xrange " << range_min_max(x_range_min, x_range_max) << "\n";

        gp << "set yrange " << range_min_max(y_range_min, y_range_max) << "\n";

        gnu_plot_builder(gp);

        gnu_data_builder(gp, x_data, y_data);

        layer_data_builder(gp, layered_figs);

        gp << "unset output\n";

        gp.close();

        std::system("gnuplot plot.gp");
    }




    //user callable function to pack extra figure layers on top of base figure
    //takes a two dimenional figures as its arguments.
    template <typename... FIGURES>
    void layer(FIGURES&... figures)
    {
        auto add_one = [this](auto& figure)
            {
                this->layered_figs.emplace_back(std::ref(figure));
            };

        (add_one(figures), ...);
    }

    
    
       
    void with_legend_plot_builder(std::ofstream& gp, std::size_t i) const
    {
        std::string style{};
        if (line_style[i] == "solid") { style = "solid"; }        
        else { style = "\"" + line_style[i] + "\""; }

        std::string point_style{};
        if (line_type[i] == "line") { point_style = ""; }
        else { point_style = " ps " + std::to_string(point_size[i]) + " pt " + std::to_string(point_type[i]); }

        std::string line_colouring{};        
        if (line_colour[i] == "") { line_colouring = ""; }
        else { line_colouring = " lc \"" + line_colour[i] + "\""; }

        gp << " '-' using 1:2 with " << line_type[i] << " dt " << style << " lw " << linewidth << point_style << line_colouring << " title '" << data_label[i] << "'";
        
    }




       
    void without_legend_plot_builder(std::ofstream& gp, std::size_t i) const
    {
        std::string style{};
        if (line_style[i] == "solid") { style = "solid"; }
        else { style = "\"" + line_style[i] + "\""; }

        std::string point_style{};
        if (line_type[i] == "line") { point_style = ""; }        
        else { point_style = " ps " + std::to_string(point_size[i]) + " pt " + std::to_string(point_type[i]); }

        std::string line_colouring{};
        if (line_colour[i] == "") { line_colouring = ""; }        
        else { line_colouring = " lc \"" + line_colour[i] + "\""; }

        gp << " '-' using 1:2 with " << line_type[i] << " dt " << style << " lw " << linewidth << point_style << line_colouring << " ";    
    }




    /// <summary>
    /// builds the plot option for the gnu plot.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="gp"></param>
    /// <param name="x_data"></param>
    /// <param name="options"></param>
    void gnu_plot_builder(std::ofstream& gp) const
    {
        gp << "set object 1 rectangle from graph 0,0 to graph 1,1 behind fc rgb '" << background_colour << "' fs solid 0.5\n";

        gp << "set tics font '," << axis_tic_fontsize << "'\n";

        gp << "set border " << border << " lw " << border_thickness << "\n";

        if (legend == true)
        {
            gp << "set key font '," << legend_fontsize << "'\n";

            gp << "plot";

            for (std::size_t i = 0; i < x_data.size(); i++)
            {
                with_legend_plot_builder(gp, i);
                
                if (layered_figs.empty() and i+1 == x_data.size())
                {
                    gp << " ";
                }
                else
                {
                    gp << ", ";
                }
            }

            layer_builder(gp, layered_figs);
            
            gp << "\n";
        }
        else
        {
            gp << "set key off\n";

            gp << "plot";

            for (std::size_t i = 0; i < x_data.size(); i++)
            {
                without_legend_plot_builder(gp, i);
                
                if (layered_figs.empty() and i+1 == x_data.size())
                {
                    gp << " ";
                }
                else
                {
                    gp << ", ";
                }
            }
            
            layer_builder(gp, layered_figs);
            
            gp << "\n";

        }
    }

 



    //builds the layers of the added plot classes with the legend data
    void gnu_plot_builder_layer_legend(std::ofstream& gp, const bool is_last_layer) const
    {

            for (std::size_t i = 0; i < x_data.size(); i++)
            {
                with_legend_plot_builder(gp, i);
                if (is_last_layer and i + 1 == x_data.size())
                {
                    gp << " ";
                }
                else
                {
                    gp << ", ";
                }
            }
        
       
    }




    //builds the layers of the added plot classes without the legend labels
    void gnu_plot_builder_layer(std::ofstream& gp, const bool is_last_layer) const
    {

            for (std::size_t i = 0; i < x_data.size(); i++)
            {
                without_legend_plot_builder(gp, i);
                if (is_last_layer and i + 1 == x_data.size())
                {
                    gp << " ";
                }
                else
                {
                    gp << ", ";
                }

            }
        
    }




    //ensures any data that plot classes that are layered on have the data checked and labels managed
    void layer_plot_data_alignment(std::vector<compatible_figure_classes>& layered_figs)
    {
        if (layered_figs.empty())
        {
            return;
        }

        for (std::size_t i = 0; i < layered_figs.size(); i++)
        {
            std::visit
            (
                [&](auto& wrapped_fig)
                {
                    auto& fig = wrapped_fig.get();

                    fig.plot_data_alignment();
                }, layered_figs[i]
            );
        }
    }




    /// <summary>
    /// Builds the layers of the added plots into the gnu plot terminal.
    /// </summary>
    void layer_builder(std::ofstream& gp, const std::vector<compatible_figure_classes>& layered_figs) const
    {
        if (layered_figs.empty())
        {
            return;
        }
        
        for (std::size_t i=0; i< layered_figs.size(); i++)
        {
            const bool is_last_layer = (i + 1 == layered_figs.size());
            
            std::visit
            (
                [&](const auto& wrapped_fig)
                {   
                    const auto& fig = wrapped_fig.get();

                    if (legend == true)
                    {
                        fig.gnu_plot_builder_layer_legend(gp, is_last_layer);
                    }
                    else
                    {
                        fig.gnu_plot_builder_layer(gp, is_last_layer);
                    }
                }, layered_figs[i]
            );
           
        }
    }




    /// <summary>
    /// Builds the data for plotting the layers onto the figures data list in gnu plot format.
    /// </summary>
    /// <param name="gp"></param>
    /// <param name="layered_figs"></param>
    void layer_data_builder(std::ofstream& gp, const std::vector<compatible_figure_classes>& layered_figs)
    {
        if (layered_figs.empty())
        {
            return;
        }
        for (std::size_t i = 0; i < layered_figs.size(); i++)
        {
            std::visit
            (
                [&](const auto& wrapped_fig)
                {
                    const auto& fig = wrapped_fig.get();

                    gnu_data_builder(gp, fig.x_data, fig.y_data);
                }, layered_figs[i]
                    );
        }

    }




    //Joins the options_print virtual functins from the plot options to print out all applicable
    //options and current values for the plot class.
    void options_print(std::ostream& out) const
    {
        out << "Plot Options and Current Values:\n\n";
        plot_options_general::options_print(out);
        two_D_plot_options::options_print(out);
        out << "\n\n";
    }


};



template <typename T>
std::ostream& operator << (std::ostream& out, const plot<T>& plt)
{
    plt.options_print(out);

    return out;
}



#endif