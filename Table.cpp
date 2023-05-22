# include "Table.h"

Table* Table::instance = nullptr;

Table* Table::get_instance()
{
    if(instance == nullptr) instance = new Table();
    return instance;
}

Table::Table()
{
    numberOfColumns = 0;
}


bool Table::load(std::istream &is)
{
    Cell* tmp;
    std::vector <Cell*> row;
    std::string curr;
    int roww = 0;
    int col = 0;

    while((is.peek() != EOF))
    {
        curr  = "";
        while((is.peek() != EOF) && is.peek()!=',' && is.peek() != '\n')
        {
            curr += is.get();
        }
        curr = compressSpaces(curr);

        if(curr.size() == 0)
        {
            tmp = new EmptyCell();
        }
        
        else if(curr[0] == '\"')
        {
            tmp = new String(curr);
        }

        else if(isInt(curr))
        {
            tmp = new Integer(curr);
        }

        else if(isDouble(curr))
        {
            tmp = new DoubleNumber(curr);
        }
        
        else if(curr[0] == '=')
        {
            if(!isFormula(curr))
            {
                std :: cout << "Error: row " << roww + 1 << ", col " << col + 1 << ", " << curr << " is invalid Formula!!\n";
                return false;
            }
            tmp = new Formula(curr);
        }

        else 
        {
            std :: cout << "Error: row " << roww + 1 << ", col " << col + 1 << ", " << curr << " is unknown data type!!\n";
            return false;
        }
        
        row.push_back(tmp);
        col++;

        if((is.peek() != EOF) && is.peek()==',')
        {
            is.get();
            continue;
        }
        else
        {
            if((is.peek() != EOF)) is.get();
            t.push_back(row);
            col = 0;
            roww++;
            row.clear();
        }
    }

    return true;
}

void Table::calc_width()
{
    for(int i = 0; i < t.size(); ++i)
    {
        for(int j = 0; j < t[i].size(); ++j)
        {
            t[i][j] -> reset_for_caluclation();
        }
    }

    column_width.clear();

    for(int i = 0; i < t.size(); ++i)
    {
        numberOfColumns = std::max(numberOfColumns, (size_t)t[i].size());

        for(int j = 0; j < t[i].size(); ++j)
        {
            if(column_width.size()==j)column_width.push_back(t[i][j]->get_size());
            else
                column_width[j] = std::max(column_width[j], t[i][j]->get_size());
        }
    }
}

void Table::print()
{
    calc_width();
    Cell* empty = new EmptyCell();

    for(int i = 0; i < t.size(); ++i)
    {
        for(int j = 0; j < t[i].size(); ++j)
        {
            t[i][j]->print(column_width[j]);
            std::cout << " | ";
        }
        for(int j = t[i].size(); j < numberOfColumns; ++j)
        {
            empty->print(column_width[j]);
            std::cout << " | ";
        }
        std::cout << std::endl;
    }
}

void Table::save_to_file(std::ostream &os)
{
    for(int i = 0; i < t.size(); ++i)
    {
        for(int j = 0; j < t[i].size(); ++j)
        {
            t[i][j] -> print_to_file(os);
            if(j + 1 < t[i].size())
                os << ", "; 
        }
        os << '\n';
    }
}

Table::~Table()
{
    for(int i = 0; i < t.size(); ++i)
    {
        for(int j = 0; j < t[i].size(); ++j)
        {
            delete t[i][j];
        }
    }
    t.clear();
}

void Table::free()
{
    column_width.clear();
    numberOfColumns = 0;
    instance = nullptr;
}

std::optional<double> Table::get_Cell_value(int x, int y) const
{
    x--;
    y--;
    if(x>=t.size()) return 0;
    if(y>=t[x].size()) return 0;
    return t[x][y]->get_value();
}

bool Table::edit(int x, int y, std::string curr)
{
    x--;
    y--;
    Cell *tmp;
    
    curr = compressSpaces(curr);
    if(curr.size() == 0)
    {
        tmp = new EmptyCell();
    }
    
    else if(curr[0] == '\"')
    {
        tmp = new String(curr);
    }

    else if(isInt(curr))
    {
        tmp = new Integer(curr);
    }

    else if(isDouble(curr))
    {
        tmp = new DoubleNumber(curr);
    }
    else if(curr[0] == '=')
    {
        if(!isFormula(curr))
        {
            return false;
        }
        tmp = new Formula(curr);
    }

    else 
    {
        return false;
    }


    if(x >= t.size())
    {
        std::vector <Cell*> row;
        while(t.size() <= x)
            t.push_back(row);
    }

    if(y >= t[x].size())
    {
        
        while(t[x].size() <= y)
        {
            Cell* emptyCell = new EmptyCell();
            t[x].push_back(emptyCell);
        }
            
    }
    
    delete t[x][y];
    t[x][y] = tmp;

    calc_width();
    return true;
}