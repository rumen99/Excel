# include "EmptyCell.h"

std::optional<double> EmptyCell::get_value()
{
    return (double)0;
}

int EmptyCell::get_size()
{
    return 0;
}

void EmptyCell::print(int sizeCell)
{
    for(int i = 1; i <= sizeCell; ++i)
        std::cout << " ";
    return ;
}

void EmptyCell::print_to_file(std::ostream &os) const
{
    return ;
}

void EmptyCell::reset_for_caluclation()
{
    return ;
}