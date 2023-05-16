#ifndef __ADDITIONALFUNCTIONS_HPP
#define __ADDITIONALFUNCTIONS_HPP
# include <string>
# include <iostream>
# include <vector>
# include <stack>
# include <optional>
# include <cmath>

bool is_operator(char op);
int priority(char op);
std::optional<double> RPN(std::string expression);
double get_number(std::string equation, int &i);
std::string compress(std::string);


std::string compressSpaces(std::string s);
bool isInt(std::string s);
bool isDouble(std::string s);
bool isFormula(std::string s);

#endif