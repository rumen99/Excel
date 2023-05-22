# include "Formula.h"

Formula::Formula(std::string eq)
{
    equation = eq;
    isCalculated = false;
    isNowCalculating = false;
}

void Formula::reset_for_caluclation()
{
    isCalculated = false;
    isNowCalculating = false;
}


std::optional<double> Formula::get_value()
{
    if(isCalculated)
    {
        return value;
    }

    if(isNowCalculating)
    {
        return std::nullopt;
    }

    isNowCalculating = true;
    std::vector < double > vals;
    std::stack <char> operations;
    double tmp,d;
    bool point;
    int last_operation = 0;
    std::string result = "";
    operations.push('(');

    for(int i = 1; i < equation.size(); ++i)
    {
        if(equation[i] == ' ') continue;

        if(equation[i] >= '0' && equation[i] <= '9')
        {
            tmp = get_number(equation,i);
            i--;
            result += std::to_string(tmp);
            result += " ";

        }
        else if(equation[i] == 'R')
        {
            int x = 0, y = 0;
            for(++i; i < equation.size() && equation[i] != 'C'; ++i)
            {
                x = x*10 + (equation[i] - '0');
            }

            for(++i; (i < equation.size()) && (equation[i] >= '0' && equation[i] <= '9'); ++i)
            {
                y = y*10 + (equation[i] - '0');
            }

            std::optional<double> val = Table::get_instance()->get_Cell_value(x,y);
            i--;

            if(val == std::nullopt)
            {
                value = std::nullopt;
                isCalculated = true;
                isNowCalculating = false;
                return std::nullopt;
            }
            
            result += std::to_string(val.value());
            result += " ";

        }

        else if(is_operator(equation[i]))
        {
            if(result.size() == last_operation)
            {
                result += "0 ";
            }

            last_operation = result.size();

            while (operations.top() != '(' && priority(operations.top()) >= priority(equation[i]))
            {
                result += operations.top();
                result += " ";
                operations.pop();
            }

            operations.push(equation[i]);
        }
        
        else if (equation[i] == '(')
        {
            operations.push(equation[i]);
        }
        
        else if (equation[i] == ')')
        {
            while (operations.top() != '(')
            {
                result += operations.top();
                result += " ";
                operations.pop();
            }
            operations.pop();
        }
    }
    while(operations.top() != '(')
    {
        result += operations.top();
        result += " ";
        operations.pop();
    }

    value = RPN(result);
    isCalculated = true;
    isNowCalculating = false;
    return value;
}

int Formula::get_size()
{

    std::optional res = get_value();

    if(res != std::nullopt) return (compress(std::to_string(res.value())).size());
    return 5;
}

void Formula::print(int sz)
{
    std::optional res = get_value();

    if(res != std::nullopt)
    {
        std::cout << compress(std::to_string(res.value()));
        for(int i = get_size(); i < sz; ++i)
            std::cout << " ";
        return ;
    }
    else
    {
        std::cout << "ERROR";
        for(int i = 5; i < sz; i++)
            std :: cout << " ";
        return ;
    }
}

void Formula::print_to_file(std::ostream &os)
{
    os << equation;
    return ;
}