# include "CommandLine.h"



commandLine::commandLine()
{
    cmd.clear();
    loadedFile = false;
    programTerminated = false;   
    changes = false; 
}

void commandLine::run()
{
    while(!programTerminated)
    {
        std::string command;
        std::cout << "> ";

        cmd.clear();
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
    if(tmp!="")cmd.push_back(tmp);
}

void commandLine::execute()
{
    if(cmd.size() == 0)
    {
        return ;
    }

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

        open();
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

        close();
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

        save();
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

        saveas();
        return ;
    }

    if(command == "help")
    {
        if(cmd.size() > 1)
        {
            std :: cout << "Expected few arguments!\n";
            return ;
        }

        help();
        return ;
    }

    if(command == "exit")
    {
        if(cmd.size() > 1)
        {
            std :: cout << "Expected few arguments!\n";
            return ;
        }

        exit();
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

        print();
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

        edit();
        return ;
    }

    std :: cout << "Invalid command! Try help to see available commands!\n";
    return ;
    
}