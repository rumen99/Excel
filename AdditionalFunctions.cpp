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
            rhs = numbers.top();
            numbers.pop();
            lhs = numbers.top();
            numbers.pop();
            result = perform_operation(lhs, expression[idx++], rhs);
            if (result == std::nullopt)return std::nullopt;
            else numbers.push(result.value());
        }
        idx++;
    }
    result = numbers.top();
    return result;
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

bool isFormula(std::string s)
{
    bool lastoperator = false;
    for(int i = 1; i < s.size(); ++i)
    {
        if(s[i] == ' ') continue;
        if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
        {
            lastoperator = true;
            continue;
        }
        if(s[i] == 'R')
        {
            if(i > 3 && (!lastoperator)) return false;
            lastoperator = false;
            bool fl = true;
            i++;
            while(i < s.size() && s[i] != 'C')
            {
                if(s[i] < '0' || s[i] > '9') return false;
                i++;
            }
            if(i == s.size()) return false;
            i++;
            while(i < s.size() && s[i] >= '0' && s[i] <= '9')i++;
            i--;
            continue;
        }
        if(s[i] >= '0' && s[i] <= '9')
        {
            if(i > 3 && (!lastoperator)) return false;
            lastoperator = false;
            bool point = false;
            while(i < s.size())
            {
                if(s[i] >= '0' && s[i] <= '9') {i++;continue;}
                if(s[i] == '.')
                {
                    if(point) return false;
                    point = true;
                    i++;
                    continue;
                }
                break;
            }
            i--;
            continue;
        }

    }
    return true;
}
