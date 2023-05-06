# include "Cell.h"
# include <string>
# include <iostream>
class emptyCell : public cell
{
    private:
    public:
    double get_value() const;
    int get_size() const;
    void print(int sz) const;
    void print_to_file(std::ostream &os) const;
};