#ifndef options_tooling
#define options_tooling

#include <algorithm>
#include <cmath>
#include <type_traits>



struct options_tools
{
protected:


    // finshes of the list printing for option variables
    template <typename T>
    void list_finisher(std::ostream& out, const std::vector<T>& list) const
    {
        out << "{";
        if (list.empty())
        {
            out << "}\n";
        }
        else
        {
            for (std::size_t i = 0; i < list.size(); i++)
            {
                out << "\"" << list[i];
                if (i + 1 >= list.size())
                {
                    out << "\"}\n";
                }
                else
                {
                    out << "\", ";
                }
            }
        }
    }


    //Creates the legend gnu plot string based on class defined plot option variables
    void legend_builder(std::ofstream& gp, const std::string& legend_font, double legend_fontsize, const std::string& legend_region, const std::string& legend_alignment, const std::string& legend_position, const std::string& legend_position_axis,
    const double& legend_sample_len, const double& legend_spacing, const std::string& legend_order, const std::string& legend_title, const std::string& legend_title_font, const double& legend_title_fontsize, const std::string& legend_orientation,
        const std::string& legend_invert) const
    {
        gp << "set key font '"<< legend_font << ", " << legend_fontsize << "'\n";
        gp << "set key spacing " << legend_spacing << "\n";
        gp << "set key samplen " << legend_sample_len << "\n";
        gp << "set key title '" << legend_title << "' font '" << legend_title_font << ", " << legend_title_fontsize << "'\n";
        gp << "set key " << legend_order << "\n";
        gp << "set key " << legend_orientation << "\n";
        gp << "set key " << legend_order << "\n";
        gp << "set key " << legend_invert << "\n";

        if (!legend_position_axis.empty()) 
        {
            gp << "set key at " << legend_position_axis << "\n";
        }
        else if (!legend_position.empty())
        {
            gp << "set key at graph " << legend_position << "\n";
        }
        else
        {
            gp << "set key " << legend_region << " " << legend_alignment << "\n";
        }
    }
    



};






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
/// A function for packing the xtic labels for plotting functions.
/// </summary>
/// <typeparam name="...ARGS"></typeparam>
/// <param name="...args">Input a comma seperated list of strings to match up to the xtics.</param>
/// <returns>A single vector of user defined x tic labels.</returns>
template <typename ...ARGS>
std::vector<std::string> xtic_labels(ARGS& ...args)
{
    std::vector<std::string> xtic_labels;

    (xtic_labels.push_back(args), ...);

    return xtic_labels;
}




/// <summary>
/// A function for packing the ytic labels for plotting functions.
/// </summary>
/// <typeparam name="...ARGS"></typeparam>
/// <param name="...args">Input a comma seperated list of strings to match up to the ytics.</param>
/// <returns>A single vector of user defined y tic labels.</returns>
template <typename ...ARGS>
std::vector<std::string> ytic_labels(ARGS& ...args)
{
    std::vector<std::string> ytic_labels;

    (ytic_labels.push_back(args), ...);

    return ytic_labels;
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

template <typename ...ARGS>
std::vector<std::string> line_style(ARGS ...args)
{
    std::vector<std::string> line_styles;

    (line_styles.push_back(args), ...);

    return line_styles;
}

template <typename ...ARGS>
std::vector<std::string> line_type(ARGS ...args)
{
    std::vector<std::string> line_types;

    (line_types.push_back(args), ...);

    return line_types;
}


template <typename ...ARGS>
std::vector<double> point_size(ARGS ...args)
{
    std::vector<double> point_size;
    
    (point_size.push_back(args), ...);

    return point_size;
}


template <typename ...ARGS>
std::vector<int> point_type(ARGS ...args)
{
    std::vector<int> point_type;

    (point_type.push_back(args), ...);

    return point_type;
}

template <typename ...ARGS>
std::vector<std::string> line_colour(ARGS ...args)
{
    std::vector<std::string> line_colour;

    (line_colour.push_back(args), ...);

    return line_colour;
}
#endif