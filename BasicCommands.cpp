# include "CommandLine.h"

void CommandLine::open()
{
    path = cmd[1];
    if(path[0] == '"')
    {
        path = path.substr(1,path.size()-2);
    }
    std :: ifstream input_file(path);

    if(!input_file.is_open())
    {
        std :: cout << "File not found!\n";
        return ;
    }

     if(Table::get_instance()->load(input_file))
     {
        std::cout << "Successfully opened " + path << std::endl;
        loadedFile = true;
     }
     else
     {
        std::cout << "Error while reading the file... Terminating"<<std::endl;
        programTerminated = true;
     }
        

    input_file.close();
}

void CommandLine::close()
{
    if(changes)
    {
        std :: cout << "You have unsaved changes. Do you want to save them [y/N]\n";
        std :: cout << "> ";
        std::string answer;
        getline(std::cin,answer);
        if(answer[0] == 'y' || answer[0] == 'Y') save();
    }
    
    Table::get_instance()->free();

    changes = false;
    loadedFile = false;
    
    std :: cout << "Successfully closed " + path + '\n';

    path = "";
    return ;
}

void CommandLine::save()
{
    std :: ofstream output_file(path);

    if(!output_file.is_open())
    {
        std :: cout << "File cannot be opened\n";
        return ;
    }

    Table::get_instance()->save_to_file(output_file);

    output_file.close();
    changes = false;

    std :: cout << "Successfully saved " + path + '\n';
    return ;
}

void CommandLine::saveas()
{
    if(cmd[1][0] == '"')
    {
        cmd[1] = cmd[1].substr(1,cmd[1].size()-2);
    }
    std :: ofstream output_file(cmd[1]);

    if(!output_file.is_open())
    {
        std :: cout << "File cannot be opened\n";
        return ;
    }

    Table::get_instance()->save_to_file(output_file);

    output_file.close();
    changes = false;

    std :: cout << "Successfully saved another " + cmd[1] + '\n';
    return ;    
}

void CommandLine::help()
{
    std::cout << "The following commands are supported:" << std::endl;
    std::cout << "\topen <file>                    opens <file>" << std::endl;
    std::cout << "\tclose                          closes currently opened file" << std::endl;
    std::cout << "\tsave                           saves the currently open file" << std::endl;
    std::cout << "\tsaveas <file>                  saves the currently open file in <file>" << std::endl;
    std::cout << "\thelp                           prints this information" << std::endl;
    std::cout << "\texit                           exists the program" << std::endl;
    std::cout << "\tprint                          prints the Table to the screen" << std::endl;
    std::cout << "\tedit  R<R>C<C> <value>          changes the value at row <R> and column <C> to <value>" << std::endl;
    return;
}

void CommandLine::exit()
{
    programTerminated = true;

    Table::get_instance()->free();

    std :: cout << "Exiting program...\n";
    return ;
}

void CommandLine::print()
{
    Table::get_instance()->print();

    return ;
}

void CommandLine::edit()
{
    int x = 0, y = 0;
    int i;
    if(cmd[1][0]!='R')
    {
        std :: cout << "Invalid <R><C> format. See help for mor information\n";
        return ;
    }

    for(i = 1; i < cmd[1].size() && cmd[1][i] != 'C'; ++i)
    {
        if(cmd[1][i] < '0' || cmd[1][i] > '9')
        {
            std :: cout << "Invalid <R><C> format. See help for mor information\n";
            return ;
        }
        x = x*10 + (cmd[1][i] - '0');
    }

    if(i == cmd[1].size())
    {
        std :: cout << "Invalid <R><C> format. See help for mor information\n";
        return ;
    }

    for(++i; (i < cmd[1].size()) && (cmd[1][i] >= '0' && cmd[1][i] <= '9'); ++i)
    {
        if(cmd[1][i] < '0' || cmd[1][i] > '9')
        {
            std :: cout << "Invalid <R><C> format. See help for mor information\n";
            return ;
        }
        y = y*10 + (cmd[1][i] - '0');
    }

 
    if(Table::get_instance()->edit(x,y,cmd[2]))
    {
        std :: cout << "Successfully edit the cell.\n";
        changes = true;
        return ;
    }
    else
    {
        std :: cout << "Invalid cell value!\n";
        return ;
    }

    return ;
}