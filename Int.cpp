# include "Int.h"

Integer::Integer(std::string s)
{
    int answer = 0;
    for(int i  =0; i < s.size(); ++i)
    {
        answer = answer*10 + (s[i]-'0');
    }
    value = answer;
}

std::optional<double> Integer::get_value()
{
    return (double)value;
}

int Integer::get_size()
{
    int sz = 0;
    int tmp = value;
    while(tmp)
    {
        sz++;
        tmp/=10;
    }
    if(value <= 0) sz++;
    return sz;
}

void Integer::print(int sz)
{
    int k = get_size();
    for(int i = 1; i <= sz-k; ++i)
        std::cout << " ";
    std::cout << value;
    return ;
}

void Integer::print_to_file(std::ostream &os)
{
    os << value;
    return ;
}

void Integer::reset_for_caluclation()
{
    return ;
}