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
    /*!
    @param equation Запазва самата формула
    @param value Стойността на клетката
    @param isCalculated Ако веднъж е пресметнато няма да го изчислява наново докато не се редактира файлът
    @param isNowCalculating В случай на циклична връзка между формулите ще бъде true, когато е изивикан метода get_value 
    */
    std::string equation;
    std::optional<double> value;
    bool isCalculated;
    bool isNowCalculating;
    public:
    Formula(std::string _equation);
    std::optional<double> get_value();
    int get_size();
    void print(int sizeCell);
    void print_to_file(std::ostream &os) const;
    void reset_for_caluclation();
};



#endif