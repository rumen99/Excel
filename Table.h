# include "Cell.h"
# include "String.h"
# include "Int.h"
# include "Double.h"
# include "EmptyCell.h"
# include <vector>
# include <fstream>
# include <iostream>
# include <string>
class table
{
    private:
    std::vector < std::vector <cell*> > t;
    std::vector <int> column_width;

    public:
    bool load(std::istream &is);
    void calc_width();
    void print();

};

std::string compressSpaces(std::string s);
bool isInt(std::string s);
bool isDouble(std::string s);