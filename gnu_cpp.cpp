#include "GNU_C++.hpp"


int main() {
    std::vector<double> data { 1,2,3,4,5,6,7,8,9,10 };
    std::vector<double> data2 { 10,20,30,40,50,60,70,80,90,100 };

    std::vector<double> data3{ 1,2,3,4,5,6,7,8,9,10 };
    std::vector<double> data4{ 2,4,6,8,10,12,14,16,18,20 };
    std::vector<double> data5{ 10,20,30,40,50,60,70,80,90,100 };

 
    plot fig(x_data(data, data2, data), y_data(data3, data4, data5));
    fig.data_label = label_data("Data 1", "Data 2", "Data 3");

    fig.line_style = line_style(".", "solid");
    fig.legend = 1;
    fig.line_colour = line_colour("green");
    fig.line_type = line_type("points", "line", "linespoints");
    //fig.line_type = line_type("points", "points", "points");
    fig.point_size = point_size(3);
    fig.point_type = point_type(5, 6, 7);
    //fig.show();
    //fig.save("test");
    //std::cout << fig;

    plot fig1(x_data(data5), y_data(data5));
    fig1.data_label = label_data("fig1 data");
    //fig1.line_colour = line_colour("green");
    fig1.line_type = line_type("linespoints");
    fig1.point_type = point_type(7);
    
    std::cout << fig.layered_figs.size()<<"\n";
    fig.layer(fig1);
    std::cout << fig.layered_figs.size()<<"\n";
    //fig.show();

    plot fig3;
    fig3.layer(fig, fig1);
    fig3.legend = 1;
    fig3.legend_region = "lmargin";
    fig3.legend_region = "bmargin";
    fig3.legend_region = "tmargin";
    
    fig3.legend_alignment = "center";
    fig3.legend_position = "0.5, 0.5";
    fig3.legend_position_axis = "10,10";
    fig3.show();
    std::cout << fig3;
    //fig3.save("test");

    //plot3D fig3(x_data(data, data2), y_data(data4,data), z_data(data5,data5));
    //fig3.grid = 1;
    //fig3.data_label = label_data("data1", "data2");
    //fig3.line_style = line_style(".-", ".");
    //fig3.line_type = line_type("linespoints", "linespoints");
    //fig3.point_size = point_size( 3,5.5 );
    //fig3.point_type = point_type(5, 2);
    //fig3.legend = 1;
    //fig3.line_colour = line_colour("red", "red");
    //fig3.legend_fontsize = 20;
    //fig3.axis_label_fontsize = 20;
    //fig3.axis_tic_fontsize = 20;
    //fig3.show();
    ////fig3.save("C:/Users/johna/Desktop/fig3");
    //std::cout << fig3;

    return 0;
}

