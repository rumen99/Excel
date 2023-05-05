# include "Cell.h"
# include <string>
# include <iostream>


class doubleNumber : public cell
{
    private:
    std::string value;
    public:
    doubleNumber(std::string s);
    double get_value() const;
    int get_size() const;
    void print(int sz) const;
};