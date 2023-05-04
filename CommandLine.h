# include <vector>
# include <cstring>
# include <string>
# include <fstream>
# include <iostream>
class commandLine
{
    private:

    std::vector <std::string> cmd;
    bool programTerminated;
    bool loadedFile;
    bool changes;
    std::string path;
    //Table* table;

    public:

    commandLine();
    void run();
    void parse(std::string command);
    void execute();

    void open();
    void close();
    void save();
    void saveas();
    void help();
    void exit();
    void print();
    void edit();
};