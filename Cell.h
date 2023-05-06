# pragma once
# include <fstream>
# include <iostream>
class cell
{
    public:

    virtual double get_value() const = 0;
    virtual int get_size() const = 0;
    virtual void print(int sz) const = 0;
    virtual void print_to_file(std::ostream &os) const = 0;
};