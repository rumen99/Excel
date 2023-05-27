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
/*!
Синглетон за таблицата
*/
class Table
{
    private:
    /*!
    @param table съдържа рефернции към отделните клетки
    @param column_width вектор от ширините на всички колони
    */
    static Table* instance;
    std::vector < std::vector <Cell*> > table;
    std::vector <int> column_width;
    size_t numberOfColumns;
    Table();
    
    public:
    

    ~Table();
    bool load(std::istream &is);
    /*!
    Изчислява дължините на всички колони преди метода print
    */
    void calc_width();
    void print();
    /*!
    Запазва информация за клетките в съответния файл
    */
    void save_to_file(std::ostream &os) const;
    /*!
    Сменя клетката
    @param x редът на клетката
    @param y колоната на клетката
    @param curr съдържанието на клетката

    */
    bool edit(int x, int y, std::string curr);
    void free();
    /*!
    @return вектор от широчините на колоните. За Тестване.
    */
    std::vector <int> get_column_width();
    static Table* get_instance();
    /*!
    @return стойността на клетката на съответния ред и колона
    @param x редът на клетката
    @param y колоната на клетката
    */
    std::optional<double> get_Cell_value(int x, int y) const;
};



#endif