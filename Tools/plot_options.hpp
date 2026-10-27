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


};



struct two_D_plot_options : public plot_options_general
{
    int border{ 15 };
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
};



#endif