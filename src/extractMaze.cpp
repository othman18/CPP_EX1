//
//  extractMaze.cpp
//  CPP_EX1
//
//  Created by othman wattad on 26.03.19.
//  Copyright © 2019 othman wattad. All rights reserved.
//


/*
 TODO:
 add bad maze file header writer
 add bad maze in maze writer
 current path
 spaces in words or in numbers
 
 continue current maze structure so that it will add the chars to the matrix now
 
 
 can catch:
 empty file
 words written with all caps
 lines without any nums
 unvalid nums and or words
 
 */
#include "extractMaze.h"

void Extractor::checkForValidInput(){}



void Extractor::createMaze(){
    if(!(MAX_STEPS && NUM_COLS && NUM_ROWS)){
        std::cerr<<"haven't created maze yet"<<std::endl;
        everyThingOkay = false;
        return;
    }
    mazeMatrix = new char*[NUM_COLS];
    int counter = 0;
    for(int i=0; i<NUM_COLS;i++){
        mazeMatrix[i] = new char[NUM_ROWS];
        for(int j=0;j<NUM_ROWS;j++){
            mazeMatrix[i][j] = ' ';
            counter++;
        }
    }
    std::cout<<"created maze-matrix"<<std::endl;
}

void Extractor::readFile(const std::string& fileName){
    //with the given path create the matrix and extract relevant info.
    
    std::string line;
    if(fileName[0] == '/'){
        std::cout<<"abs path was given"<<std::endl;
    }else{
        std::cout<<"current path was given"<<std::endl;
        // change the fileName to include the current path ... can't find the right path atm
        std::cerr<<"haven't implemented this yet"<<std::endl;
        everyThingOkay = false;
        return;
    }
    
    std::ifstream fin(fileName);
    
    if (fin.is_open()){
        
        int lineCounter = 1;
        while(lineCounter < 5){
            std::getline(fin, line);
            switch(lineCounter){
                case 2:
                    checkLine(line, "maxsteps",lineCounter);
                    break;
                case 3:
                    checkLine(line, "rows",lineCounter);
                    break;
                case 4:
                    checkLine(line, "cols",lineCounter);
                    break;
            }
            lineCounter++;
        }
        
        createMaze();
        //        lineCounter = 0;    // reset lineCounter for the matrix construction
        int rowCounter = 0, poundCounter=0,atCounter=0,colCounter=0;
        char currentChar;
        while(std::getline(fin, line)){
            //          std::cout << line << '\n';
            for(int i = 0; i<line.length();i++){
                currentChar = line[i];
                
                if(currentChar == '\r' || currentChar == '\n'){
                    continue;   //ignore
                }else if(currentChar == 9){
                    std::cerr<<"Wrong character in maze: TAB in row "<<lineCounter<<", col "<<i<<std::endl;
                    everyThingOkay=false;
                    return;
                }else if(!(currentChar == '#'||currentChar == ' '||
                           currentChar == '@'||currentChar == '$')){
                    //forbiden chars
                    std::cerr<<"Wrong character in maze: TAB in row "<<lineCounter<<", col "<<i<<std::endl;
                    everyThingOkay=false;
                    return;
                }else{
                    if(currentChar == '@'){
                        atCounter++;
                        if(atCounter > 1){
                            std::cerr<<"More than one @ in maze"<<std::endl;
                            everyThingOkay=false;
                            return;
                            
                        }
                    }else if(currentChar == '$'){
                        poundCounter++;
                        if(poundCounter > 1){
                            std::cerr<<"More than one $ in maze"<<std::endl;
                            everyThingOkay=false;
                            return;
                        }
                    }
                    // add to mazeMatrix
                    mazeMatrix[colCounter][rowCounter] = currentChar;
//                    std::cout<<colCounter<<" col"<<std::endl;
                    colCounter++;
                }
            }
//            std::cout<<rowCounter<<" row"<<std::endl;
            if(line.length()==0)
                colCounter++;  //in case the maze has a row that is completly empty
            colCounter = 0;
            rowCounter++;
            lineCounter++;
        }
        fin.close();
    }else
        std::cerr <<"Command line argument for maze: "<< fileName <<" doesn't lead to a maze file or leads to a file that cannot be opened"<<std::endl;
};

bool Extractor::checkLine(const std::string line, std::string compareWith, int lineNum){
    //check line's validity and extract the relevant information
    
    std::string tmpLine = line;
    int intValue = 0;
    //remove whitespace
    tmpLine.erase(remove_if(tmpLine.begin(), tmpLine.end(), isspace), tmpLine.end());
    
    std::string::size_type delimiter_pos = tmpLine.find('=');
    std::string name = tmpLine.substr(0,delimiter_pos);    //steps||rows||cols
    std::string value = tmpLine.substr(delimiter_pos+1);   //int value
    
    if(!is_number(value)){
        //check if value is a number
        mazeInputError(line, lineNum);
        everyThingOkay = false;
        std::cerr<<"error checkLine 1"<<std::endl;
        return false;
    }
    
    try{
        //convert value to int
        intValue = std::stoi(value);
    }
    catch (std::invalid_argument const &e){
        mazeInputError(line, lineNum);
        everyThingOkay = false;
        std::cerr<<"error checkLine 2"<<std::endl;
        return false;
    }
    
    std::transform(name.begin(), name.end(), name.begin(), tolower);    //convert name to lower case
    
    if(name.compare(compareWith)){
        mazeInputError(line, lineNum);
        everyThingOkay = false;
        std::cerr<<"error checkLine 3"<<std::endl;
        return false;
    }
    //everything checks out
    
    if(!name.compare("maxsteps"))
        MAX_STEPS = intValue;
    else if (!name.compare("rows"))
        NUM_ROWS = intValue;
    else if (!name.compare("cols"))
        NUM_COLS = intValue;
    return true;
}

void mazeInputError(const std::string line, int lineNum){
    std::string errorName;
    switch (lineNum) {
        case 2:
            errorName = "MaxSteps";
            break;
        case 3:
            errorName = "Rows";
            break;
        case 4:
            errorName = "Cols";
            break;
    }
    std::cerr << "expected in line "<<lineNum<<" - "<< errorName <<" = <num>" << '\n'<<
    "got: "<<line<<std::endl;
}

bool is_number(const std::string& s){
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

