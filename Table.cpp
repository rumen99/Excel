# include "Table.h"

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
        std::cout << '\n';
    }
}