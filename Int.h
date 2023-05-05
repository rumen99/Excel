# include "Cell.h"
# include <iostream>

class integer : public cell
{
    private:
    int value;
    public:
    integer(std::string s);
    double get_value() const;
    int get_size() const;
    void print(int sz) const;

};