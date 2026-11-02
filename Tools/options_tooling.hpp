#ifndef options_tooling
#define options_tooling



struct options_tools
{
protected:

    /// <summary>
    /// Resizes the label conatainer to match the number of data sets plotted. If the data sets are larger 
    /// than than the number of labels provided then the legend will be published with a empty name. If the number of 
    /// labels is larger than th enumber of data sets the label conatiner will remove the extra and only plotr the
    /// labels from first till the length of the number of data sets.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="data_label">A vector conatining the labels of the data sets.</param>
    /// <param name="x_data">A vector with the data sets to comapre the length</param>
    template <typename T>
    void data_label_sizing(std::vector<std::string>& data_label, const std::vector<std::vector<T>>& x_data)
    {
        std::size_t data_label_size = data_label.size();
        if (data_label_size < x_data.size())
        {
            for (std::size_t i = 0; i < x_data.size() - data_label_size; i++)
            {
                data_label.push_back(" ");
            }
        }

        if (data_label_size > x_data.size())
        {
            for (std::size_t i = 0; i < data_label_size - x_data.size(); i++)
            {
                data_label.pop_back();
            }
        }
    }

    /// <summary>
    /// Resiszes the line style options container to the nuumber of data sets present. Removes line style options if they are more numerous that the data sets
    /// and will select a solid line for every line without a corresponding line style.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="line_style"></param>
    /// <param name="x_data"></param>
    template <typename T>
    void line_style_sizing(std::vector<std::string>& line_style, const std::vector<std::vector<T>>& x_data)
    {
        std::size_t line_style_size = line_style.size();
        if (line_style_size < x_data.size())
        {

            for (std::size_t i = 0; i < x_data.size() - line_style_size; i++)
            {
                line_style.push_back("solid");
            }
        }

        if (line_style_size > x_data.size())
        {
            for (std::size_t i = 0; i < line_style_size - x_data.size(); i++)
            {
                line_style.pop_back();
            }
        }
    }




  /// <summary>
  /// Resiszes the line type options container to the nuumber of data sets present. Removes line type options if they are more numerous that the data sets
  /// and will select a solid line for every line without a corresponding line style.
  /// </summary>
  /// <typeparam name="T"></typeparam>
  /// <param name="line_style"></param>
  /// <param name="x_data"></param>
    template <typename T>
    void line_type_sizing(std::vector<std::string>& line_type, const std::vector<std::vector<T>>& x_data)
    {
        std::size_t line_type_size = line_type.size();
        if (line_type_size < x_data.size())
        {

            for (std::size_t i = 0; i < x_data.size() - line_type_size; i++)
            {
                line_type.push_back("lines");
            }
        }

        if (line_type_size > x_data.size())
        {
            for (std::size_t i = 0; i < line_type_size - x_data.size(); i++)
            {
                line_type.pop_back();
            }
        }
    }

};

#endif