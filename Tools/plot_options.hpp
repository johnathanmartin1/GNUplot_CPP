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
    
    // Boolian that turns the legened on or off, accepts boolean true or false, or 1 or 0.
    bool legend{ false };
   
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


};



struct two_D_plot_options : public plot_options_general
{

};



struct three_D_plot_options : public plot_options_general
{
    std::string z_axis_label = "z";
    /// <summary>
    /// Sets the minimum range of the plot on the z axis.
    /// </summary>
    double z_range_min{ -1e308 };
    /// <summary>
    /// Sets the maximum range of plot in the z axis.
    /// </summary>
    double z_range_max{ 1e308 };
};



#endif