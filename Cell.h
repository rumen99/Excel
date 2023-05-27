#ifndef __CELL_HPP
#define __CELL_HPP

# include <fstream>
# include <iostream>
# include <optional>

/*!
Абстрактен клас, наследен от всички типове клетки, поддържани до момента
*/
class Cell
{
    public:

    /*!
    @return Стойността на клетката след необходимото преобразуване в тип double или при невалидна формула - ERROR!
    */
    virtual std::optional<double> get_value() = 0;
    /*!
    @return дължината на "текста", който ще се визуализира при евентуално извикване на командата print
    */
    virtual int get_size()= 0;
    /*!
    @param sizeCell размерът на клетката.
    Визуализира на екрана клетката, форматирана според стандартите на MS EXCEL отляво или  отдясно.
    */
    virtual void print(int sizeCell) = 0;
    /*!
    Извиква се след команда edit. Необходимо заради зависимостите между клетки чрез формули.
    */
    virtual void reset_for_caluclation() = 0;
    /*!
    Записва информация за клетката.
    */
    virtual void print_to_file(std::ostream &os)const = 0;
};

#endif