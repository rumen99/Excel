#ifndef __INT_HPP
#define __INT_HPP
# include "Cell.h"
# include <iostream>
# include <optional>

class Integer : public Cell
{
    private:
    int value;
    public:
    Integer(std::string number);
    std::optional<double> get_value();
    int get_size();
    void print(int sizeCell);
    void print_to_file(std::ostream &os);
    void reset_for_caluclation();

};

#endif