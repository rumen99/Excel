# pragma once
# include "Cell.h"
# include <string>
# include <iostream>
# include <vector>
# include <stack>
# include <optional>
# include <cmath>
# include "table.h"

class formula : public cell
{
    private:
    std::string equation;
    std::optional<double> value;
    bool isCalculated;
    bool isNowCalculating;
    public:
    formula(std::string eq);
    std::optional<double> get_value();
    int get_size();
    void print(int sz);
    void print_to_file(std::ostream &os);
    void reset_for_caluclation();
};

bool is_operator(char op);
int priority(char op);
std::optional<double> RPN(std::string expression);
std::string compress(std::string);