#ifndef options_tooling
#define options_tooling



struct options_tools
{
protected:


    // finshes of the list printing for option variables
    template <typename T>
    void list_finisher(std::ostream& out, const std::vector<T> list) const
    {
        out << "{";
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