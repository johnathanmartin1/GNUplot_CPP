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
        if (data_label.size() < x_data.size())
        {
            for (std::size_t i = 0; i < x_data.size() - data_label.size(); i++)
            {
                data_label.push_back(" ");
            }
        }

        if (data_label.size() > x_data.size())
        {
            for (std::size_t i = 0; i < data_label.size() - x_data.size(); i++)
            {
                data_label.pop_back();
            }
        }
    }
};

#endif