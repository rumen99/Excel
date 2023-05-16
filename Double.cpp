# include "Double.h"
doubleNumber::doubleNumber(std::string s)
{
    value = s;
}
std::optional<double> doubleNumber::get_value()
{
    double ans = 0;
    bool point = 0;
    double d = 1;
    for(int i = 0; i < value.size(); i++)
    {
        if(i==0 && (value[i] == '+' || value[i] == '-')) continue;
        if(!point && (value[i] >= '0' && value[i] <= '9' )) ans = ans*10 + (value[i]-'0');
        if(value[i] == '.') point = 1;
        if(point && (value[i] >= '0' && value[i] <= '9' )) ans = ans + (value[i]-'0')*d;
        if(point) d = d/10;
    }
    if(value[0] == '-')ans = -ans;
    return ans;
}

int doubleNumber::get_size()
{
    return value.size();
}

void doubleNumber::print(int sz)
{
    for(int i = 1; i <= sz-value.size(); i++)
    {
        std::cout << " ";
    }
    std::cout << value ;
    return ;
}

void doubleNumber::print_to_file(std::ostream &os)
{
    os << value;
    return ;
}