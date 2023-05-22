#include "Int.h"

Integer::Integer(std::string number)
{
    int answer = 0;
    for (int i = 0; i < number.size(); ++i)
    {
        if (i == 0 && number[i] == '-')
            continue;
        answer = answer * 10 + (number[i] - '0');
    }
    if (number[0] == '-')
        answer *= -1;
    value = answer;
}

std::optional<double> Integer::get_value()
{
    return (double)value;
}

int Integer::get_size()
{
    int sizeCell = 0;
    int tmp = value;
    while (tmp)
    {
        sizeCell++;
        tmp /= 10;
    }
    if (value <= 0)
        sizeCell++;
    return sizeCell;
}

void Integer::print(int sizeCell)
{
    int k = get_size();
    for (int i = 1; i <= sizeCell - k; ++i)
        std::cout << " ";
    std::cout << value;
    return;
}

void Integer::print_to_file(std::ostream &os)
{
    os << value;
    return;
}

void Integer::reset_for_caluclation()
{
    return;
}