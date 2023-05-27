
# include <vector>
# include <cstring>
# include <string>
# include <fstream>
# include <iostream>
# include "Table.h"

class CommandLine
{
    private:
    /*!
    @param cmd отделните аргументи от командата
    @param programTerminated  При грешка по време на зареждането на файл или команда exit
    @param changes Указва ни дали са правени промени по файлът и дали е необходимо запазване на файла отново
    @param path Пътят до заредения файл
    */
    std::vector <std::string> cmd;
    bool programTerminated;
    bool loadedFile;
    bool changes;
    std::string path;

    public:
    CommandLine();
    /*!
    Прочита съответната команда
    */
    void run();
    /*!
    обработва въведената команда и я разделя.
    */
    void parse(std::string command);
    /*!
    Извиква метода за съответната команда
    */
    void execute();

    void open();
    void close();
    void save();
    void saveas();
    void help();
    void exit();
    void print();
    void edit();
    void clear_command();
};