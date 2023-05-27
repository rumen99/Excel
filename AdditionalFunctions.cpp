#include "AdditionalFunctions.h"

std::string compress(std::string S)
{
    bool fl = false;
    for(int i = 0; i < S.size(); ++i)
    {
        if(S[i]=='.')fl = true;
    }

    if(!fl)return S;

    while(S[S.size()-1]=='0')
    {
        S.pop_back();
    }

    if(S[S.size()-1]=='.')S.pop_back();
    return S;
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
        if(rhs != 0.0)
        {
            return lhs/rhs;
        }
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
            if(numbers.empty()) return std::nullopt;
            rhs = numbers.top();
            numbers.pop();
            if(numbers.empty()) return std::nullopt;
            lhs = numbers.top();
            numbers.pop();
            result = perform_operation(lhs, expression[idx++], rhs);
            if (result == std::nullopt)return std::nullopt;
            else numbers.push(result.value());
        }
        idx++;
    }
    if(numbers.empty()) return std::nullopt;
    result = numbers.top();
    if(numbers.size()!=1) return std::nullopt;
    return result;
}

bool isRPN(std::string expression)
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
            if(numbers.empty()) return false;
            rhs = numbers.top();
            numbers.pop();
            if(numbers.empty()) return false;
            lhs = numbers.top();
            numbers.pop();
            result = perform_operation(lhs, expression[idx++], rhs);
            if (result == std::nullopt)return false;
            else numbers.push(result.value());
        }
        idx++;
    }
    if(numbers.empty()) return false;
    result = numbers.top();
    if(numbers.size()!=1) return false;
    return true;
}

std::string compressSpaces(std::string s)
{
    std :: string ans = "";
    int i = 0;
    while( i < s.size() && ( s[i] == ' ' || s[i] == '\t') ) i++;
    int last = s.size()-1;
    while( last >= 0 && ( s[last] == ' ' || s[last] == '\t') ) last--;
    while(i <= last)
    {
        ans += s[i];
        ++i;
    }
    return ans;
}

bool isInt(std::string s)
{
    for(int i = 0; i < s.size(); ++i)
    {
        if(s[i] >= '0' && s[i] <= '9')continue;
        if(i == 0 && (s[i]=='+' || s[i] == '-')) continue;
        return false;
    }

    return true;
}

bool isDouble(std::string s)
{
    bool point = false;
    for(int i = 0; i < s.size(); ++i)
    {
        if(s[i] >= '0' && s[i] <= '9')continue;
        if(i == 0 && (s[i]=='+' || s[i] == '-')) continue;
        if(i!=0 && (!point) && s[i]=='.'){point = true; continue;}
        return false;
    }

    return point;
}

bool isFormula(std::string equation)
{
    std::vector<double> vals;
    std::stack<char> operations;
    double tmp, unit;
    bool point;
    int last_operation = 0;
    std::string result = "";
    operations.push('(');

    for (int i = 1; i < equation.size(); ++i)
    {
        if (equation[i] == ' ')
            continue;

        if (equation[i] >= '0' && equation[i] <= '9')
        {
            tmp = get_number(equation, i);
            i--;
            result += std::to_string(tmp);
            result += " ";
        }
        else if (equation[i] == 'R')
        {
            int x = 0, y = 0;
            for (++i; i < equation.size() && equation[i] != 'C'; ++i)
            {
                x = x * 10 + (equation[i] - '0');
            }

            for (++i; (i < equation.size()) && (equation[i] >= '0' && equation[i] <= '9'); ++i)
            {
                y = y * 10 + (equation[i] - '0');
            }

            std::optional<double> val = 1;
            i--;


            result += std::to_string(val.value());
            result += " ";
        }

        else if (is_operator(equation[i]))
        {
            if (result.size() == last_operation)
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
    while (operations.top() != '(')
    {
        result += operations.top();
        result += " ";
        operations.pop();
    }
    return isRPN(result);

}
