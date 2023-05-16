# pragma once
# include "Cell.h"
# include <string>
# include <iostream>
# include <optional>

class doubleNumber : public cell
{
    private:
    std::string value;
    public:
    doubleNumber(std::string s);
    std::optional<double> get_value();
    int get_size();
    void print(int sz);
    void print_to_file(std::ostream &os);
    void reset_for_caluclation();
};