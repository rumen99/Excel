# pragma once
# include <fstream>
# include <iostream>
# include <optional>
class cell
{
    public:

    virtual std::optional<double> get_value() = 0;
    virtual int get_size()= 0;
    virtual void print(int sz) = 0;
    virtual void print_to_file(std::ostream &os) = 0;
};