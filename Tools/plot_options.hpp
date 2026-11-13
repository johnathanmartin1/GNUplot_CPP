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

    //Sets the decimal places of the x tic values
    int xtic_decimal_places{};
    
    //Sets the decimal places of the y tic values.
    int ytic_decimal_places{};

    //Sets the tics axis labels when no user defined labels exist will build the tic labels in the object
    std::vector<double> xtic_base{};
    std::vector<double> ytic_base{};
    //Sets the tics axis labels when no user defined labels exist will build the tic labels in the object. If empty will default to the xtic_base.
    std::vector<std::string> xtic_labels{};
    //Sets the tics axis labels when no user defined labels exist will build the tic labels in the object. If empty will default to the ytic_base
    std::vector<std::string> ytic_labels{};

    // Boolian that turns the legened on or off, accepts boolean true or false, or 1 or 0.
    bool legend{ false };

    //Sets the legend orientation. Inputs are "horizontal" or "vertical". Default is "vertical"
    std::string legend_orientation{ "vertical" };

    //Inverts the order of legend elements. Input = "invert". Default ="".
    std::string legend_invert{};

    //Sets the legend font. Default is "Arial"
    std::string legend_font{ "Arial" };

    //Sets the legend font size
    double legend_fontsize{ 14 };

    //Sets the legend order as "line sample - text" or "text-line sample". For line sample-text input "reverse" and text - line sample input an empty string "". Default = "".
    std::string legend_order{};

    //Sets the line sample length. Input a double i.e 1.5., Default = 1.
    double legend_sample_len{ 1 };

    //Sets the vertical spacing between legend elements. Input a double i.e 2.5 Default=1.
    double legend_spacing{ 1 };

    //Sets the legend title. Default = "".
    std::string legend_title{};

    //SEts teh legend title font. Default = "Arial".
    std::string legend_title_font{ "Arial" };

    //Sets the legend tiotle font size. Default = 14.
    double legend_title_fontsize{ 14 };

    //Sets the legened region can be used in conjunction with legend_alignment option: 
    // inside the plot boundary = inside,
    // outside the plot boundary = outside,
    // left margin = lmargin,
    // right margin = rmargin,
    // top margin = tmargin,
    // bottom margin = bmargin.
    std::string legend_region{"inside"};

    //Sets the alignment of the legend within a selected region, if no region selected the default is inside. 
    // X alignment options: "left", "center", "right". Y alignment options: "top", "center", "bottom".
    // Choose X alignment then Y alignment i.e for left alignment, with gnu plot choosing the best y alignment the input strinf is "left" or for center x alignment and bottom y alignment the input string is "center bottom".
    //Default is "top right".
    std::string legend_alignment{"top right"};

    //Sets the legend at chosen graph normalised coordinates "0, 0" being the bottom left corner and "1, 1" being th eupper right corner of the plot. Input example is the string "0.8, 0.9"
    //This will take precedance over legend_region and legend_alignment position options. Default is an empty string "".
    std::string legend_position{};

    //Sets the legend at chosen x and y cooredinates of the diaspalayed axis, input example for a postionat x axis = 10 and y axis = 8 the input is the string "10, 8".
    //This will take precedance over legend_region, legend_alignment and legend_position options. Default is an empty string "".
    std::string legend_position_axis{};

    // Sets the data labels, use label_data("data1", "data2",... etc) function to assign data labels.
    std::vector<std::string> data_label{};
  
    // Sets the title of the plot, accepts strings.
    std::string title{};
    
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
            << "std::string legend_font = \"" << legend_font << "\"\n"
            << "double legend_fontsize = " << legend_fontsize << "\n"
            << "std::string legend_title = \"" << legend_title << "\"\n"
            << "std::string legend_title_font = \"" << legend_title_font << "\"\n"
            << "double legend_title_fontsize = " << legend_title_fontsize << "\n"
            << "std::string legend_orientation = \"" << legend_orientation << "\"\n"
            << "std::string legend_invert = \"" << legend_invert << "\"\n"
            << "std::string legend_order = \"" << legend_order << "\"\n"
            << "double legend_sample_len = " << legend_sample_len << "\n"
            << "doubel legend_spacing = " << legend_spacing << "\n"
            << "std::string legend_region = \"" << legend_region << "\"\n"
            << "std::string legend_alignment = \"" << legend_alignment << "\"\n"
            << "std::string legend position = \"" << legend << "\"\n"
            << "std::string legend_position_axis = \"" << legend_position_axis << "\"\n"
            << "std::vector<std::string> data_label = ";
            list_finisher(out, data_label);
        out << "std::string title = \"" << title << "\"\n"
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

    // Sets the width of the plotted lines default is 4, accepts decimals.
    double linewidth{ 4 };

    //Sets the line type line="line", line with points = "linespoints", points = "points", can manually be placed in a vector or use the line_type function 
    //e.g line_type("lines", "linespoints",...)
    std::vector<std::string> line_type{};

    //Sets the line style. solid line = "solid",  long dashed line = "_", dashed line = "-", dotted line = "." and combinations of each eg ". -"
    //Pass a vector for the different linestyles, or alternativly use the line_style function e.g for two lines fig.line_style =  line_style(1,2,...). 
    std::vector<std::string> line_style{};

    //Sets the line colour
    std::vector<std::string> line_colour{};

    //Sets the point size
    std::vector<double> point_size{ 1 };

    //Sets the point type options are: no point = 0, "+" = 1, "X" = 2, star = 3, unfilled square = 4, filled square = 5, unfilled circle = 6, and filled circle = 7.
    std::vector<int> point_type{};

    virtual void options_print(std::ostream& out) const
    {
        out << "int border = " << border << "\n"
            << "double linewidth = " << linewidth << "\n"
            << "std::vector<std::string> line_style = ";
        list_finisher(out, line_style);
        out << "std::vector<std::string> line_type = ";
        list_finisher(out, line_type);
        out << "std::vector<std::string> line_colour = ";
        list_finisher(out, line_style);
        out << "std::vector<double> point_size = ";
        list_finisher(out, point_size);
        out << "std::vector<std::string>> point_type = ";
        list_finisher(out, point_type);
        
    }
};



struct three_D_plot_options : public plot_options_general
{
    //Sets the tics axis labels when no user defined labels exist will build the tic labels in the object
    std::vector<double> ztic_base{};

    //Sets the z tic axis labels using the inputted data when no user defined ones are given 
    std::vector<std::string> ztic_labels{};

    // Sets the z axis label
    std::string z_axis_label{ "z" };
    
    // Sets the minimum range of the plot on the z axis.
    double z_range_min{ -1e308 };
    
    // Sets the maximum range of plot in the z axis.
    double z_range_max{ 1e308 };

    // Sets the width of the plotted lines default is 4, accepts decimals.
    double linewidth{ 4 };

    //Sets the line style. solid line = "solid",  long dashed line = "_", dashed line = "-", dotted line = "." and combinations of each eg ". -"
    //Pass a vector for the different linestyles, or alternativly use the line_style function e.g for two lines fig.line_style =  line_style(1,2,...). 
    std::vector<std::string> line_style{};

    //Sets the line type line="line", line with points = "linespoints", points = "points", can manually be placed in a vector or use the line_type function 
    //e.g line_type("lines", "linespoints",...)
    std::vector<std::string> line_type{};

    //Sets the line colour
    std::vector<std::string> line_colour{};

    //Sets the point size.
    std::vector<double> point_size{ 1 };

    //Sets the point type options are: no point = 0, "+" = 1, "X" = 2, star = 3, unfilled square = 4, filled square = 5, unfilled circle = 6, and filled circle = 7.
    std::vector<int> point_type{};

    // Sets the border that you want,
    // sum up the relavent options to slect that combination:
    // 1 Bottom left front, 2 Bottom left back, 4 Bottom right front, 
    // 8 Bottom right back, 16 Left vertical, 32 Back vertical,
    // 64 Right vertical, 128 Front vertical, 256 Top left back, 
    // 512 Top right back, 1024	Top left front, 2048 Top right front.
    int border{895};

    void options_print(std::ostream& out) const
    {
        out << "std::string z_axis_label = \"" << z_axis_label << "\"\n"
            << "double z_range_min = " << z_range_min << "\n"
            << "double z_range_max = " << z_range_max << "\n"
            << "double linewidth = " << linewidth << "\n"
            << "std::vector<std::string> line_style = ";
        list_finisher(out, line_style);
        out << "std::vector<std::string> line_type = ";
        list_finisher(out, line_type);
        out << "std::vector<std::string> line_colour = ";
        list_finisher(out, line_style);
        out << "double point_size = ";
        list_finisher(out, point_size);
        out << "std::vector<std::string>> point_type = ";
        list_finisher(out, point_type);
        out << "int border = " << border << "\n";
    }

    
};



#endif