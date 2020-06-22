//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_FILE_OPS_H
#define PONG_GAME_FILE_OPS_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

using std::string;
using std::ofstream;
using std::ifstream;
using std::istringstream;

// As long as file data retrievals are short and sweet we can use these helper methods to contain
// of all the file management logic.
class FileOps {
public:
    FileOps();
    ~FileOps();
    // retrieves the previous score of the app from the existing file.
    int *GetPreviousScore();
    // saves 2 scores passed to file.
    void SaveScore(const int *scores);
private:
    // name of the game data file written to.
    string _gameDataFile{};
};


#endif//PONG_GAME_RENDERER_H
