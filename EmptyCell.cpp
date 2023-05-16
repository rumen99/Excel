# include "EmptyCell.h"

std::optional<double> emptyCell::get_value()
{
    return (double)0;
}
int emptyCell::get_size()
{
    return 0;
}
void emptyCell::print(int sz)
{
    for(int i = 1; i <= sz; ++i)
        std::cout << " ";
    return ;
}

void emptyCell::print_to_file(std::ostream &os)
{
    return ;
}