# pragma once
# include "Cell.h"
# include <string>
# include <iostream>
# include <optional>
class emptyCell : public cell
{
    private:
    public:
    std::optional<double> get_value();
    int get_size();
    void print(int sz);
    void print_to_file(std::ostream &os);
};