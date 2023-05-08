# include "Cell.h"
# include <iostream>
# include <optional>
class integer : public cell
{
    private:
    int value;
    public:
    integer(std::string s);
    std::optional<double> get_value() const;
    int get_size() const;
    void print(int sz) const;
    void print_to_file(std::ostream &os) const;
};