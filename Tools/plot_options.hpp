#ifndef plot_options
#define plot_options

#include <vector>
#include <string>
#include <cfloat>

#include "options_tooling.hpp"

struct plot_options_general : public options_tools
{
public:
    // Sets the x axis label, accepts data type string.
    std::string x_axis_label = "x";
   
    // Sets the y axis label, accepts data type string.
    std::string y_axis_label = "y";
    
    // Sets the axis label font size.
    double axis_label_fontsize{ 14 };

    // Sets the tics fontsize.
    double axis_tic_fontsize{ 14 };

    // Boolian that turns the legened on or off, accepts boolean true or false, or 1 or 0.
    bool legend{ false };

    //Sets the legend font size
    double legend_fontsize{ 14 };
   
    // Sets the data labels, use label_data("data1", "data2",... etc) function to assign data labels.
    std::vector<std::string> data_label{};
  
    // Sets the title of the plot, accepts strings.
    std::string title{};
   
    // Sets the width of the plotted lines default is 4, accepts decimals.
    double linewidth{ 4 };
    
    // A boolian that turns the grid on or off, set as true or false, or 1 or 0.
    bool grid{ false };
 
    // Sets the minimum range of the plot on the x axis.
    double x_range_min{-1e308};
    
    // Sets the maximum range of the plot on the x axis.
    double x_range_max{1e308};
  
    // Sets the minimum range of the plot on the y axis.
    double y_range_min{ -1e308 };
   
    // Sets the maximum range of plot in the y axis.
    double y_range_max{ 1e308 };

    //sets the border thickness.
    double border_thickness{ 3 };

    //Sets background colour.
    std::string background_colour{ "gray90" };

    virtual void options_print(std::ostream& out) const
    {
        out << "std::string x_axis_label = \"" << x_axis_label << "\"\n"
            << "std::string y_axis_label = \"" << y_axis_label << "\"\n"
            << "double axis_label_fontsize = " << axis_label_fontsize << "\n"
            << "double axis_tic_fontsize = " << axis_tic_fontsize << "\n"
            << "bool legend = " << legend << "\n"
            << "double legend_fontsize = " << legend_fontsize << "\n"
            << "std::vector<std::string> data_label = {";
           
        for (std::size_t i = 0; i < data_label.size(); i++) 
        {   
            out << "\"" << data_label[i];
            if (i + 1 == data_label.size()) 
            { 
                out << "\"}\n"; 
            } 
            else 
            { 
                out << "\", "; 
            } 
        };
        out << "std::string title = \"" << title << "\"\n"
            << "double linewidth = " << linewidth << "\n"
            << "bool grid = " << grid << "\n"
            << "double x_range_min = " << x_range_min << "\n"
            << "double x_range_max = " << x_range_max << "\n"
            << "double y_range_min = " << y_range_min << "\n"
            << "double y_range_max = " << y_range_max << "\n"
            << "double border_thickness = " << border_thickness << "\n"
            << "std::string background_colour = \"" << background_colour << "\"\n";
    }
};



struct two_D_plot_options : public plot_options_general
{
    // Sets the border that you want,
    // sum up the relavent options to slect that combination:
    // 1 Bottom, 2 Left, 4 Top, 8 Right.
    int border{ 15 };

    virtual void options_print(std::ostream& out) const
    {
        out << "int border = " << border << "\n";
    }
};



struct three_D_plot_options : public plot_options_general
{
    // Sets the z axis label
    std::string z_axis_label{ "z" };
    
    // Sets the minimum range of the plot on the z axis.
    double z_range_min{ -1e308 };
    
    // Sets the maximum range of plot in the z axis.
    double z_range_max{ 1e308 };

    // Sets the border that you want,
    // sum up the relavent options to slect that combination:
    // 1 Bottom left front, 2 Bottom left back, 4 Bottom right front, 
    // 8 Bottom right back, 16 Left vertical, 32 Back vertical,
    // 64 Right vertical, 128 Front vertical, 256 Top left back, 
    // 512 Top right back, 1024	Top left front, 2048 Top right front.
    int border{895};

    virtual void options_print(std::ostream& out) const
    {
        out << "std::string z_axis_label = \"" << z_axis_label << "\"\n"
            << "double z_range_min = " << z_range_min << "\n"
            << "double z_range_max = " << z_range_max << "\n"
            << "int border = " << border << "\n";
    }
};



#endif