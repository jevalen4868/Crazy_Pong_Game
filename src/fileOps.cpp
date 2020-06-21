//
// Created by jeremyvalenzuela on 6/4/20.
//

#include "fileOps.h"

namespace fs = std::filesystem;

FileOps::FileOps() 
    : _gameDataFile{"pong_game.dat"} {
     
}

FileOps::~FileOps() {    
}

int *FileOps::GetPreviousScore() {
    fs::path dataFilePath{_gameDataFile};
    if (!fs::exists(dataFilePath)) {
        return nullptr;
    }
    int *scores = new int[2];
    ifstream dataFileStream{dataFilePath};
    string line, propName, propValue;
    while (dataFileStream.good() && getline(dataFileStream, line)) {
        istringstream lineStream(line);
        lineStream >> propName;
        lineStream >> propValue;
        if (propName == "PLAYER_1_SCORE") {
            scores[0] = std::stoi(propValue);
        } else if (propName == "PLAYER_2_SCORE") {        
            scores[1] = std::stoi(propValue);
        } 
    }
    dataFileStream.close();
    return scores;
    
}

void FileOps::SaveScore(const int *scores) {    
    fs::path dataFilePath(_gameDataFile);
    ofstream dataFileStream(dataFilePath, std::ios::out);      
    dataFileStream << "PLAYER_1_SCORE " << scores[0] << std::endl;
    dataFileStream << "PLAYER_2_SCORE " << scores[1] << std::endl;
    dataFileStream.close();
}
