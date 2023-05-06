# include "String.h"

String::String(std::string s)
{
    for(int i = 1; i < s.size()-1; ++i)
    {
        if(s[i]!='\\' || s[i-1] == '\\') value+=s[i];
    }
}
double String::get_value() const
{
    double answer = 0;
    double d = 1;
    bool point = false;

    for(int i = 0; i < value.size(); i++)
    {
        if(i == 0 && (value[i] == '+' || value[i] == '-') ) continue;
        if(!point && value[i] == '.')
        {
            point = true;
            d /= 10.0;
            continue;
        }
        else if(value[i] >= '0' && value[i] <= '9')
        {
            answer = answer*(point ? 1 : 10) + d*(value[i]-'0');
            if(point) d /= 10.0;
        }
        else
        {
            return 0.0;
        }

    }

    return answer;
}

int String::get_size() const
{
    return value.size();
}

void String::print(int sz) const
{
    std :: cout << value;
    for(int i = 0; i < sz-get_size();++i)
        std :: cout << " ";

}

void String::print_to_file(std::ostream &os) const
{
    os << '"';
    for(int i = 0; i < value.size(); ++i)
    {
        if(value[i] == '"' || value[i] == '\\')
        {
            os << "\\"; 
        }
        os << value[i];
    }
    os << '"';
    return ;
}