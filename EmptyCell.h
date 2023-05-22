#ifndef __EmptyCell_HPP
#define __EmptyCell_HPP
# include "Cell.h"
# include <string>
# include <iostream>
# include <optional>
class EmptyCell : public Cell
{
    private:
    public:
    std::optional<double> get_value();
    int get_size();
    void print(int sizeCell);
    void print_to_file(std::ostream &os);
    void reset_for_caluclation();
};

#endif