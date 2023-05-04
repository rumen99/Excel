# include "CommandLine.h"
# include <iostream>


commandLine::commandLine()
{
    cmd.clear();
    loadedFile = false;
    programTerminated = false;    
}

void commandLine::run()
{
    while(!programTerminated)
    {
        std::string command;
        std::cout << "> ";

        getline(std::cin,command);
        parse(command);
        execute();
    }

    return ;
}

void commandLine::parse(std::string command)
{
    std::string tmp = "";
    bool quotes = false;
    for(int i = 0; i < command.size(); ++i)
    {
        if(command[i] == ' ' && !quotes)
        {
            if(tmp != "")
                cmd.push_back(tmp);
            tmp = "";
        }
        else if(command[i] == '\"' && (i == 0 || command[i-1] != '\\'))
        {
            if(!quotes) quotes = true;
            else
                {
                    quotes = false;
                    cmd.push_back(tmp);
                    tmp = "";
                }
        }else
        {
            tmp += command[i];
        }
    }
}

void commandLine::execute()
{
    std::string command = cmd[0];
    //command = tolower(command);

    if(command == "open")
    {
        if(cmd.size() == 1)
        {
            std :: cout << "Expected more arguments!\n";
            return;
        }
        if(cmd.size() > 2)
        {
            std :: cout << "Expected few arguments!\n";
            return ;
        }
        if(loadedFile)
        {
            std :: cout << "There is an open file already!\n";
            return ;
        }

        //open(cmd[1]); TODO
        return ;
    }

    if(command == "close")
    {
        if(cmd.size() > 1)
        {
            std :: cout << "Expected few arguments!\n";
            return ;
        }
        if(!loadedFile)
        {
            std :: cout << "There is no open file!\n";
            return ;
        }

        //close(); TODO
        return ;
    }

    if(command == "save")
    {
        if(cmd.size() > 1)
        {
            std :: cout << "Expected few arguments!\n";
            return ;
        }
        if(!loadedFile)
        {
            std :: cout << "There is no open file!\n";
            return ;
        }

        //save(); TODO
        return ;
    }

    if(command == "saveas")
    {
        if(cmd.size() == 1)
        {
            std :: cout << "Expected more arguments!\n";
            return;
        }
        if(cmd.size() > 2)
        {
            std :: cout << "Expected few arguments!\n";
            return ;
        }
        if(!loadedFile)
        {
            std :: cout << "There is no open file!\n";
            return ;
        }

        //saveas(); TODO
        return ;
    }

    if(command == "help")
    {
        if(cmd.size() > 1)
        {
            std :: cout << "Expected few arguments!\n";
            return ;
        }

        //help(); TODO
        return ;
    }

    if(command == "exit")
    {
        if(cmd.size() > 1)
        {
            std :: cout << "Expected few arguments!\n";
            return ;
        }

        //exit(); TODO
        return ;
    }

    if(command == "print")
    {
        if(cmd.size() > 1)
        {
            std :: cout << "Expected few arguments!\n";
            return ;
        }
        if(!loadedFile)
        {
            std :: cout << "There is no open file!\n";
            return ;
        }

        //print(); TODO
        return ;
    }

    if(command == "edit")
    {
        if(cmd.size() < 4)
        {
            std :: cout << "Expected more arguments!\n";
            return ;
        }
        if(!loadedFile)
        {
            std :: cout << "There is no open file!\n";
            return ;
        }

        //edit(); TODO
        return ;
    }

    std :: cout << "Invalid command! Try help to see available commands!\n";
    return ;
    
}