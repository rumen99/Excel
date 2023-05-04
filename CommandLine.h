# include <vector>
# include <cstring>
# include <string>

class commandLine
{
    private:

    std::vector <std::string> cmd;
    bool programTerminated;
    bool loadedFile;
    std::string path;

    public:

    commandLine();
    void run();
    void parse(std::string command);
    void execute();
};