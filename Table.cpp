# include "Table.h"

table* table::instance = nullptr;

table* table::get_instance()
{
    if(instance == nullptr) instance = new table();
    return instance;
}

table::table()
{
    numberOfColumns = 0;
}

std::string compressSpaces(std::string s)
{
    std :: string ans = "";
    int i = 0;
    while( i < s.size() && ( s[i] == ' ' || s[i] == '\t') ) i++;
    int last = s.size()-1;
    while( last >= 0 && ( s[last] == ' ' || s[last] == '\t') ) last--;
    while(i <= last)
    {
        ans += s[i];
        ++i;
    }
    return ans;
}

bool isInt(std::string s)
{
    for(int i = 0; i < s.size(); ++i)
    {
        if(s[i] >= '0' && s[i] <= '9')continue;
        if(i == 0 && (s[i]=='+' || s[i] == '-')) continue;
        return false;
    }

    return true;
}

bool isDouble(std::string s)
{
    bool point = false;
    for(int i = 0; i < s.size(); ++i)
    {
        if(s[i] >= '0' && s[i] <= '9')continue;
        if(i == 0 && (s[i]=='+' || s[i] == '-')) continue;
        if(i!=0 && (!point) && s[i]=='.'){point = true; continue;}
        return false;
    }

    return point;
}

bool isFormula(std::string s)
{
    bool lastoperator = false;
    for(int i = 1; i < s.size(); ++i)
    {
        if(s[i] == ' ') continue;
        if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
        {
            if(lastoperator) return false;
            lastoperator = true;
            continue;
        }
        if(s[i] == 'R')
        {
            if(i > 3 && (!lastoperator)) return false;
            lastoperator = false;
            bool fl = true;
            i++;
            while(i < s.size() && s[i] != 'C')
            {
                if(s[i] < '0' || s[i] > '9') return false;
                i++;
            }
            if(i == s.size()) return false;
            i++;
            while(i < s.size() && s[i] >= '0' && s[i] <= '9')i++;
            i--;
            continue;
        }
        if(s[i] >= '0' && s[i] <= '9')
        {
            if(i > 3 && (!lastoperator)) return false;
            lastoperator = false;
            bool point = false;
            while(i < s.size())
            {
                if(s[i] >= '0' && s[i] <= '9') {i++;continue;}
                if(s[i] == '.')
                {
                    if(point) return false;
                    point = true;
                    i++;
                    continue;
                }
                break;
            }
            i--;
            continue;
        }

    }
    return true;
}
bool table::load(std::istream &is)
{
    cell* tmp;
    std::vector <cell*> row;
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
            tmp = new emptyCell();
        }
        
        else if(curr[0] == '\"')
        {
            tmp = new String(curr);
        }

        else if(isInt(curr))
        {
            tmp = new integer(curr);
        }

        else if(isDouble(curr))
        {
            tmp = new doubleNumber(curr);
        }else if(curr[0] == '=')
        {
            if(!isFormula(curr))
            {
                std :: cout << "Error: row " << roww + 1 << ", col " << col + 1 << ", " << curr << " is invalid formula!!\n";
                return false;
            }
            tmp = new formula(curr);
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
        }else
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

void table::calc_width()
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

void table::print()
{
    calc_width();
    cell* empty = new emptyCell();
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

void table::save_to_file(std::ostream &os)
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

void table::free()
{
    for(int i = 0; i < t.size(); ++i)
    {
        for(int j = 0; j < t[i].size(); ++j)
        {
            delete t[i][j];
        }
    }
    t.clear();
    column_width.clear();
    numberOfColumns = 0;
    instance = nullptr;
}

std::optional<double> table::get_cell_value(int x, int y) const
{
    x--;
    y--;
    if(x>=t.size()) return 0;
    if(y>=t[x].size()) return 0;
    return t[x][y]->get_value();
}

bool table::edit(int x, int y, std::string curr)
{
    x--;
    y--;
    cell *tmp;
    
    curr = compressSpaces(curr);
    if(curr.size() == 0)
    {
        tmp = new emptyCell();
    }
    
    else if(curr[0] == '\"')
    {
        tmp = new String(curr);
    }

    else if(isInt(curr))
    {
        tmp = new integer(curr);
    }

    else if(isDouble(curr))
    {
        tmp = new doubleNumber(curr);
    }
    else if(curr[0] == '=')
    {
        if(!isFormula(curr))
        {
            return false;
        }
        tmp = new formula(curr);
    }

    else 
    {
        return false;
    }


    if(x >= t.size())
    {
        std::vector <cell*> row;
        while(t.size() <= x)
            t.push_back(row);
    }
    if(y >= t[x].size())
    {
        
        while(t[x].size() <= y)
        {
            cell* emptycell = new emptyCell();
            t[x].push_back(emptycell);
        }
            
    }
    
    

    delete t[x][y];
    
    t[x][y] = tmp;

    calc_width();
    return true;
}