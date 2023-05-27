#ifndef __DOUBLE_HPP
#define __DOUBLE_HPP
# include "Cell.h"
# include <string>
# include <iostream>
# include <optional>

class DoubleNumber : public Cell
{
    private:
    std::string value;
    public:
    DoubleNumber(std::string number);
    ~DoubleNumber();
    std::optional<double> get_value();
    int get_size();
    void print(int sizeCell);
    void print_to_file(std::ostream &os)const;
    void reset_for_caluclation();
};

#endif