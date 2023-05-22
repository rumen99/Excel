#ifndef __Table_HPP
#define __Table_HPP
# include "Cell.h"
# include "String.h"
# include "Int.h"
# include "Double.h"
# include "EmptyCell.h"
# include "Formula.h"
# include <vector>
# include <fstream>
# include <iostream>
# include <string>
class Table
{
    private:

    static Table* instance;
    std::vector < std::vector <Cell*> > t;
    std::vector <int> column_width;
    size_t numberOfColumns;
    Table();
    
    public:
    

    ~Table();
    bool load(std::istream &is);
    void calc_width();
    void print();
    void save_to_file(std::ostream &os);
    bool edit(int x, int y, std::string curr);
    void free();
    std::vector <int> get_column_width();
    static Table* get_instance();
    std::optional<double> get_Cell_value(int x, int y) const;
};



#endif