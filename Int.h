# pragma once
# include "Cell.h"
# include <iostream>
# include <optional>
class integer : public cell
{
    private:
    int value;
    public:
    integer(std::string s);
    std::optional<double> get_value();
    int get_size();
    void print(int sz);
    void print_to_file(std::ostream &os);
};