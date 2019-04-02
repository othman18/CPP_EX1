//
//  extractMaze.h
//  CPP_EX1
//
//  Created by othman wattad on 26.03.19.
//  Copyright © 2019 othman wattad. All rights reserved.
//

#ifndef extractMaze_h
#define extractMaze_h

#include <iostream>
#include <fstream>

class Extractor{
    int NUM_ROWS;  // change to const..
    int NUM_COLS;  // change to const..
    int MAX_STEPS;  // change to const..
    char** mazeMatrix=nullptr;
public:
    bool everyThingOkay = true;  // used for debugging
    ~Extractor(){
        if(!mazeMatrix){
            std::cout<<"nothing to delete"<<std::endl;
            return;
        }
        for(int i=0;i<NUM_COLS;i++){
            delete[] mazeMatrix[i];
            mazeMatrix[i] = nullptr;   //should I leave this out?
        }
        delete [] mazeMatrix;
        mazeMatrix = nullptr;   //should I leave this out?
        std::cout<<"deleted maze-matrix"<<std::endl;
    }
    void readFile(const std::string& filename);
    void writeFile(const std::string& filename);
    void createMaze();
    bool checkLine(std::string line, std::string compareWith, int lineNum);
    void printMAze(){
        if(!everyThingOkay)
            return;
        for(int j=0; j<NUM_ROWS;j++){
            for(int i=0; i<NUM_COLS;i++){
                std::cout<<mazeMatrix[i][j];
            }
            std::cout<<std::endl;
        }
    }
};

void mazeInputError(const std::string line, int lineNum);
bool is_number(const std::string& s);
#endif /* extractMaze_h */
