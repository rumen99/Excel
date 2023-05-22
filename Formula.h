#ifndef __Formula_HPP
#define __Formula_HPP

# include "Cell.h"
# include <string>
# include <iostream>
# include <vector>
# include <stack>
# include <optional>
# include <cmath>
# include "Table.h"
# include "AdditionalFunctions.h"
class Formula : public Cell
{
    private:
    std::string equation;
    std::optional<double> value;
    bool isCalculated;
    bool isNowCalculating;
    public:
    Formula(std::string eq);
    std::optional<double> get_value();
    int get_size();
    void print(int sz);
    void print_to_file(std::ostream &os);
    void reset_for_caluclation();
};



#endif