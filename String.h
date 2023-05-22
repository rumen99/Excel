#ifndef __STRING_HPP
#define __STRING_HPP
# include "Cell.h"
# include <string>
# include <iostream>
# include <optional>

class String : public Cell
{
    private:
    std::string value;
    public:
    String(std::string _value);
    std::optional<double> get_value();
    int get_size();
    void print(int sizeCell);
    void print_to_file(std::ostream &os);
    void reset_for_caluclation();
};

#endif