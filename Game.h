#include <iostream>
#include "Map.h"
#include <map>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <utility>

// DIFFERENT GAME MODES AND OPERATIONS OF EACH MODE

class Game{
    public:
        Game();
        void gamePlay();
        std::array<int,2> gameCommand();
        bool validateCommand(std::string );
        double computeAccuracy(int, int);
        void printMenu();
        void menuCommand(int );
        void printWelcome();
        void printHOF(std::vector<std::pair<std::string, double>> );
        void newRecord(double );
        std::vector<std::pair<std::string, double>> processHOF(); 
        int validateMenuCommand(std::string );
        ~Game();
    private:    
        int mode; // 1 - Intro, 2 - Instruction, 3 - Gameplay, 4 - HOF, 5 - Quit
        std::array<int,2> mapSize {}; // Only use in mode 3        
};