#include "2D_line_plot/2D_line_plot.hpp"
#include "3D_line_plot/3D_line_plot.hpp"



int main() {
    std::vector<double> data { 1,2,3,4,5,6,7,8,9,10 };
    std::vector<double> data2 { 10,20,30,40,50,60,70,80,90,100 };

    std::vector<double> data3{ 1,2,3,4,5,6,7,8,9,10 };
    std::vector<double> data4{ 2,4,6,8,10,12,14,16,18,20 };
    std::vector<double> data5{ 10,20,30,40,50,60,70,80,90,100 };

 
    //plot fig(x_data(data, data2, data), y_data(data3, data4, data5));
    plot fig2(x_data(data), y_data(data4));
    
    fig2.data_label = label_data("Data 1", "Data 2");
    fig2.legend = 1;
    fig2.x_axis_label = "x axis";
    fig2.y_axis_label = "y axis";
    fig2.grid = 1;
    fig2.title = "practice plot";
    fig2.linewidth = 4;
    fig2.x_range_min = -5;
    fig2.x_range_max = 7;
    fig2.y_range_min = -6;
    fig2.y_range_max = 30;
    //fig2.save("C:/Users/johna/Desktop/fig2");
    
    //fig2.show();
    //fig.show();
    //fig.linewidth = 8;
    //fig.save("C:/Users/johna/Desktop/fig1");
   

    plot3D fig3(x_data(data, data2), y_data(data4,data), z_data(data5,data5));
    fig3.grid = 1;
 /*   fig3.x_range_min = 2;
    fig3.z_range_min = 50;
    fig3.y_range_min = 12;
    fig3.x_range_max = 7;
    fig3.z_range_max = 70;
    fig3.y_range_max = 17;*/
    fig3.data_label = label_data("data1", "data2");
    fig3.legend = 1;
    fig3.show();
    fig3.save("C:/Users/johna/Desktop/fig3");

    return 0;
}

