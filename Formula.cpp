# include "Formula.h"

formula::formula(std::string eq)
{
    equation = eq;
}
bool is_operator(char op)
{
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^');
}

int priority(char op)
{
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    if(op == '^') return 3;
    return 0;
    
}
double get_number(std::string equation, int &i)
{
    double tmp = 0;
    double d = 1;
    bool point = false;
    for(;(i < equation.size()) && ( (equation[i] >= '0' && equation[i] <= '9') || (equation[i] == '.') ); ++i )
    {
        if(equation[i] == '.')
        {
            point = true;
            d = 0.1;
            continue;
        }
        tmp = tmp*(point ? 1 : 10) + d*(equation[i] - '0');
        if(point) d /= 10.0;
    }
    return tmp;   
}

std::optional<double> perform_operation(double lhs, char op, double rhs)
{
    if(op == '+') return lhs+rhs;
    if(op == '-') return lhs-rhs;
    if(op == '*') return lhs*rhs;
    if(op == '^') return pow(lhs,rhs);
    if(op == '/')
    {
        if(rhs != 0) return lhs/rhs;
        return std::nullopt;
    }

    return std::nullopt;
}
std::optional<double> RPN(std::string expression)
{
    double tmp, lhs, rhs;
    std::optional<double> result = 0;
    std::stack<double> numbers;
    int idx = 0;
    while(idx < expression.size())
    {
        while (expression[idx] == ' ')idx++;
        if (expression[idx] >= '0' && expression[idx] <= '9')
        {
            tmp = get_number(expression, idx);
            numbers.push(tmp);
        }
        else
        {
            rhs = numbers.top();
            numbers.pop();
            lhs = numbers.top();
            numbers.pop();
            result = perform_operation(lhs, expression[idx++], rhs);
            if (result.has_value() == false)return std::nullopt;
            else numbers.push(result.value());
        }
        idx++;
    }
    result = numbers.top();
    return result;
}
std::optional<double> formula::get_value() const
{
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
        else if(equation[i] >= 'R')
        {
            int x = 0, y = 0;
            for(++i; i < equation.size() && equation[i] != 'C'; ++i)
            {
                x = x*10 + (equation[i] - '0');
            }

            for(++i; i < equation.size() && (equation[i] >= '0' && equation[i] <= '9'); ++i)
            {
                y = y*10 + (equation[i] - '0');
            }

            // TODO
            result += "1 ";

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
    return RPN(result);



}

int formula::get_size() const
{

    std::optional res = get_value();

    if(res.has_value()) return ((std::to_string(res.value())).size());
    return 5;
}

void formula::print(int sz) const
{
    std::optional res = get_value();

    if(res.has_value())
    {
        std::cout << std::to_string(res.value());
        for(int i = get_size(); i < sz; ++i)
            std::cout << " ";
        return ;
    }else
    {
        std::cout << "ERROR";
        return ;
    }
}

void formula::print_to_file(std::ostream &os) const
{
    os << equation;
    return ;
}