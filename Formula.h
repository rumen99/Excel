# include "Cell.h"
# include <string>
# include <iostream>
# include <vector>
# include <stack>
# include <optional>
# include <cmath>
class formula : public cell
{
    private:
    std::string equation;
    double value;
    public:
    formula(std::string eq);
    std::optional<double> get_value() const;
    int get_size() const;
    void print(int sz) const;
    void print_to_file(std::ostream &os) const;
};

bool is_operator(char op);
int priority(char op);
std::optional<double> RPN(std::string expression);