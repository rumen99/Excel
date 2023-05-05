# include "Int.h"
integer::integer(std::string s)
{
    int answer = 0;
    for(int i  =0; i < s.size(); ++i)
    {
        answer = answer*10 + (s[i]-'0');
    }
    value = answer;
}
double integer::get_value() const
{
    return (double)value;
}
int integer::get_size() const
{
    int sz = 0;
    int tmp = value;
    while(tmp)
    {
        sz++;
        tmp/=10;
    }
    if(value < 0) sz++;
    return sz;
}
void integer::print(int sz) const
{
    int k = get_size();
    for(int i = 1; i <= sz-k; ++i)
        std::cout << " ";
    std::cout << value;
    return ;
}