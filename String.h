# include "Cell.h"
# include <string>
# include <iostream>
class String : public cell
{
    private:
    std::string value;
    public:
    String(std::string s);
    double get_value() const;
    int get_size() const;
    void print(int sz) const;
    void print_to_file(std::ostream &os) const;
};