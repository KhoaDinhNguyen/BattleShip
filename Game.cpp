#include "Game.h"

Game::Game(){
    std::string menuCmd{};
    printWelcome();
    do{
        printMenu();
        std::cout << "Please enter your selection (1 - 5): ";
        std::cin >> menuCmd;
        std::cout << std::endl;
        mode = validateMenuCommand(menuCmd);
        menuCommand(mode);
    }while(mode != 5);
    //gamePlay();
}

void Game::gamePlay()
{
    int xDim = 12;
    int yDim = 10;
    int trueShotCnt, shotCnt {}; // The number of total shot
    std::vector<int> shipCnt = {{1,0,0,0,0}};
    Map map(shipCnt, xDim, yDim);
    int shotToClear = map.getShotCnt();
    std::cout << "Number of shot to fully clear the game: " << shotToClear << std::endl;
    this->mapSize = {xDim, yDim};
    bool gameContinue {true}; // T - Continue, F - End
    // Test Command
    // std::cout << "Enter command: ";
    do{ 
        map.showMap();
        std::array<int,2> cmd = gameCommand();
        //std::cout << cmd[0] << " " << cmd[1] << std::endl; // test output
        if(cmd[0] == -1 && cmd[1] == -1){
            gameContinue = false;
            break;
        }
        else{
            trueShotCnt += map.gridShot(cmd[0], cmd[1]);
            shotCnt++;
            //std::cout << "Game is continued!" << std::endl; // test behavior
        }
    }while(gameContinue && map.getShipCnt() > 0);
    if(map.getShipCnt() <= 0){
        // Final congratulation
        std::cout << "The enemy has been defeated!\nYou have successfully defend the earth. For now ...\n";
    }
    // Computation of player accuracy
    if(shotCnt == 0){
        std::cout << "You are quitting the game without making any shot!!!\n\n";
    }
    else if(shotCnt < shotToClear){
        std::cout << "You did not finish off all enemies! Now they are free to roam the world!\n\n";
    }
    else{
        double score = computeAccuracy(shotToClear, shotCnt);
        std::cout << "Your accuracy is: " << std::fixed << std::setprecision(2) << score << "%\n" << std::endl;
    }
}

std::array<int,2> Game::gameCommand(){
    std::string userInput {};
    bool isValid {};
    int i {1};
    do{
        std::cout << "Enter the coordinate that you want to shoot (enter q to quit the game): ";
        std::cin >> userInput;
        isValid = validateCommand(userInput);
        if(!isValid){
            std::cout << "Invalid input. Please try again!\n";
        }
    }while(!isValid);
    if(userInput == "q" || userInput == "Q"){
        return {-1,-1}; // Quit game command
    }
    else{
        // Separating the letter and number part
        char letter = userInput[0];
        std::string strNum = userInput.substr(1);
        int number = std::stoi(strNum); // String to int ()
        // Mapping the data to the grid location
        // Grid location result
        std::array<int,2> result {0, number-1};
        if(letter >= 'a'){
            result[0] = letter - 'a';
        }
        else{
            result[0] = letter - 'A';
        }
        return result; // Return to the location of the grid  
    }
}

bool Game::validateCommand(std::string command){
    int sz = command.size();
    // Size = 1
    if(sz == 1){
        if(command != "q" && command != "Q"){ // If it is not a "quit"
            return false;
        }
    }
    else if(sz == 2){
        // X-direction
        bool test1_1 = 0 <= (command[0] - 'a') && (command[0] - 'a') < mapSize[0];
        bool test1_2 = 0 <= (command[0] - 'A') && (command[0] - 'A') < mapSize[0];
        // Y direction
        bool test2 = 0 < (command[1] - '0') && (command[1] - '0') < mapSize[1]; // Map start with 1
        if(!(test1_1 || test1_2) || !test2){
            return false;
        }
    }
    else if(sz == 3){
        // X-direction
        bool test1_1 = 0 <= (command[0] - 'a') && (command[0] - 'a') < mapSize[0];
        bool test1_2 = 0 <= (command[0] - 'A') && (command[0] - 'A') < mapSize[0];
        // Y direction
        int comb = (command[1] - '0') * 10 + (command[2] - '0');
        bool test2 = 10 <= comb && comb <= mapSize[1];
        if(!(test1_1 || test1_2) || !test2){
            return false;
        }
    }
    else{
        std::cout << "Not here" << std::endl;
        return false;
    }
    return true;
}

double Game::computeAccuracy(int shotToClear, int totalShot){
    // File control
    // std::cout << shotToClear << " " << totalShot << std::endl;
    if(totalShot != 0 && totalShot < shotToClear){
        return (double)(totalShot)/shotToClear * 100.0;        
    }
    else if(totalShot != 0 && totalShot >= shotToClear){
        return (double)(shotToClear)/totalShot * 100.0;
    }
    return 0.0;
}

void Game::printMenu(){
    std::cout << "Menu: \n";
    std::map<int, std::string> modeMap = {
        {1, "Instructions"},
        {2, "View Example Map"},
        {3, "New Game"},
        {4, "Hall of Fame"},
        {5, "Quit"}
    };
    for(int i = 1; i <= modeMap.size(); i++){
        std::cout << std::setw(3) << i << " : " << modeMap.at(i) << std::endl;
    }
}

void Game::menuCommand(int cmd){
    switch (cmd)    {
    case 1:
        std::cout << "Instruction\n" << std::endl;
        break;
    case 2:
        //std::cout << "Example\n" << std::endl;
        newRecord(30.0);
        break;
    case 3:
        gamePlay();
        break;
    case 4:
        //std::cout << "Congrat!\n" << std::endl;
        printHOF(processHOF());
        break;
    case 5:
        std::cout << "Thank you for playing the game! See you again ...\n";
        mode = 5;
        break;    
    default:
        std::cout << "Error!!!" << std::endl;
        mode = 5;
        break;
    }
}

void Game::printWelcome(){
    std::ifstream ifs{};
    std::string line{};
    ifs.open("welcome_text.txt");
    while(getline(ifs, line)){
        std::cout << line << std::endl;
    }
    ifs.close();
}

void Game::printHOF(std::vector<std::pair<std::string, double>> hof){
    // ...
    int size = hof.size();
    // Print hall of fame
    std::cout << "HALL OF FAME\n";
    std::cout << "+------+-------------+----------+\n";
    std::cout << "| Rank | Player Name | Accuracy |\n";
    std::cout << "+------+-------------+----------+\n";
    for(int i = 0; i < size; i++){
        //std::cout << hof[i].first << " " << hof[i].second << std::endl; // test
        std::cout << std::setw(3) << std::left << "|";
        std::cout << std::setw(2) << std::right << i + 1;
        std::cout << std::setw(3) << std::right << "|";
        std::cout << std::setw(13) << std::left << " " + hof[i].first; // Player name
        std::cout << "|";
        std::cout << std::setw(8) << std::right << std::fixed << std::setprecision(2) << hof[i].second << "% "; // Score
        std::cout << "|\n";
    }
    std::cout << "+------+-------------+----------+\n\n";
}

std::vector<std::pair<std::string, double>> Game::processHOF(){
    std::ifstream ifs{};
    ifs.open("hof.txt");
    std::vector<std::pair<std::string, double>> hofVector{};
    std::string inputStr {};
    while(getline(ifs, inputStr)){
        std::string name{}, score{};
        int idx = inputStr.find(',');
        name = inputStr.substr(0, idx);
        score = inputStr.substr(idx + 1);
        double numScore = std::stod(score);
        hofVector.push_back(std::make_pair(name, numScore));
    }
    ifs.close();
    return hofVector;
}

int Game::validateMenuCommand(std::string cmd){
    bool validCmd {false};
    do{
        if(cmd.size() == 1){
            int cmdValue = cmd[0] - '0';
            if(0 < cmdValue && cmdValue <= 5){
                return cmdValue;
            }
            else{
                std::cout << "Invalid menu command! Please try again with options 1 - 5.\n\n";
                printMenu();                
                std::cout << "Please enter your selection (1 - 5): ";
                std::cin >> cmd;
                std::cout << std::endl;
            }
        }
        else{
            std::cout << "Invalid menu command! Please try again with options 1 - 5.\n\n";
            printMenu();                
            std::cout << "Please enter your selection (1 - 5): ";
            std::cin >> cmd;
            std::cout << std::endl;
        }
    }while(!validCmd);
    return 0;
}

void Game::newRecord(double score){
    std::vector<std::pair<std::string, double>> oldRecord{processHOF()};
    bool recordChange{};
    std::vector<std::pair<std::string, double>>::iterator it {oldRecord.begin()};
    int size = oldRecord.size();
    int idx = size - 1;
    if(size < 10){
        for(idx; idx >= 0; idx--){
            if(score <= oldRecord[idx].second){
                break;
            }
        }
        oldRecord.insert(it + idx, std::make_pair("name", score));
        recordChange = true;
    }
    else{
        for(idx; idx >= 0; idx--){
            if(score <= oldRecord[idx].second){
                break;
            }
        }
        if(idx >= 0){
            oldRecord.insert(it + idx, std::make_pair("name", score));
            recordChange = true;
        }
        else{
            recordChange = false;
        }
    }
    if(recordChange){
        std::ofstream ofs{};
        ofs.open("hof2.txt");
        for(int i = 0; i < oldRecord.size(); i++){
            ofs << oldRecord[i].first + "," << std::fixed << std::setprecision(2) << score << std::endl;
        }
        ofs.close();
    }
}

Game::~Game(){
}
