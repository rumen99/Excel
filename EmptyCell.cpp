# include "EmptyCell.h"

double emptyCell::get_value() const
{
    return (double)0;
}
int emptyCell::get_size() const
{
    return 0;
}
void emptyCell::print(int sz) const
{
    for(int i = 1; i <= sz; ++i)
        std::cout << " ";
    return ;
}