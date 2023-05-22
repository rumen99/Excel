#include "String.h"

String::String(std::string _value)
{
    for (int i = 1; i < _value.size() - 1; ++i)
    {
        if (_value[i] != '\\' || _value[i - 1] == '\\')
            value += _value[i];
    }
}

std::optional<double> String::get_value()
{
    double answer = 0;
    double unit = 1;
    bool point = false;

    for (int i = 0; i < value.size(); i++)
    {
        if (i == 0 && (value[i] == '+' || value[i] == '-'))
            continue;
        if (!point && value[i] == '.')
        {
            point = true;
            unit /= 10.0;
            continue;
        }
        else if (value[i] >= '0' && value[i] <= '9')
        {
            answer = answer * (point ? 1 : 10) + unit * (value[i] - '0');
            if (point)
                unit /= 10.0;
        }
        else
        {
            return 0.0;
        }
    }

    if (value[0] == '-')
        answer *= -1;
    return answer;
}

int String::get_size()
{
    return value.size();
}

void String::print(int sizeCell)
{
    std ::cout << value;
    for (int i = 0; i < sizeCell - get_size(); ++i)
        std ::cout << " ";
}

void String::reset_for_caluclation()
{
    return;
}

void String::print_to_file(std::ostream &os)
{
    os << '"';
    for (int i = 0; i < value.size(); ++i)
    {
        if (value[i] == '"' || value[i] == '\\')
        {
            os << "\\";
        }
        os << value[i];
    }
    os << '"';
    return;
}