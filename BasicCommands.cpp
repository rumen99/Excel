# include "CommandLine.h"

void commandLine::open()
{
    path = cmd[1];
    std :: ifstream input_file(path);

    if(!input_file.is_open())
    {
        std :: cout << "File not found!\n";
        return ;
    }

    // if(table->load(input_file)) TODO; Successfully opened file.xml

    input_file.close();
}

void commandLine::close()
{
    if(changes)
    {
        std :: cout << "You have unsaved changes. Do you want to save them [y/N]\n";
        std :: cout << "> ";
        char answer;
        std :: cin >> answer;
        if(answer == 'y' || answer == 'Y') save();
    }
    
    //table->free(); TODO
    changes = false;
    loadedFile = false;
    path = "";

    std :: cout << "Successfully closed" + path + '\n';
;
    return ;
}

void commandLine::save()
{
    if(!changes) return ;
    std :: ofstream output_file(path);

    if(!output_file.is_open())
    {
        std :: cout << "File cannot be opened\n";
        return ;
    }

    // table->save_to_file();

    output_file.close();
    changes = false;

    std :: cout << "Successfully saved " + path + '\n';
    return ;
}

void commandLine::saveas()
{
    std :: ofstream output_file(cmd[1]);

    if(!output_file.is_open())
    {
        std :: cout << "File cannot be opened\n";
        return ;
    }

    // table->save_to_file(output_file);

    output_file.close();
    changes = false;

    std :: cout << "Successfully saved another " + cmd[1] + '\n';
    return ;    
}

void commandLine::help()
{
    std::cout << "The following commands are supported:" << std::endl;
    std::cout << "\topen <file>                    opens <file>" << std::endl;
    std::cout << "\tclose                          closes currently opened file" << std::endl;
    std::cout << "\tsave                           saves the currently open file" << std::endl;
    std::cout << "\tsaveas <file>                  saves the currently open file in <file>" << std::endl;
    std::cout << "\thelp                           prints this information" << std::endl;
    std::cout << "\texit                           exists the program" << std::endl;
    std::cout << "\tprint                          prints the table to the screen" << std::endl;
    std::cout << "\tedit  <R> <C> <value>          changes the value at row <R> and column <C> to <value>" << std::endl;
    return;
}

void commandLine::exit()
{
    programTerminated = true;

    //table->free(); TODO

    std :: cout << "Exiting program...\n";
    return ;
}

void commandLine::print()
{
    // table->print(); TODO

    return ;
}

void commandLine::edit()
{
    //int x = get_num(cmd[1]);
    //int y = get_num(cmd[2]);

    // if(table->edit(x,y,cmd[3])); TODO; Successfully or not;

    return ;
}