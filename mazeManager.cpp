//
// Created by noamt on 4/7/19.
//

#include "mazeManager.h"
#include "playerUtils.h"
#include <iostream>


MazeManager::MazeManager(Extractor *ex, Player* pl): extractor(ex), player(pl) {
    max_steps = extractor->getMaxSteps();
    width = extractor->getWidth();
    height = extractor->getHeight();
    start = extractor->getStart();
    end = extractor->getEnd();
    mazeMatrix = extractor->getMazeMatrix();
}


bool MazeManager::manageMaze() {
    Pair current = start;
    
    Pair bm;
    while(steps < max_steps && current != end) {
        Player::Direction move = player->move();
        
        Q.push(move);
        if(move == Player::SET_BM) {
            bm = current;
        } else {
            int x = current[0], y = current[1];
            nextPosition(x, y, move);
            x = x < 0 ? width + x : x % width;
            y = y < 0 ? height + y : y % width;
            if(mazeMatrix[x][y] == '#') {
                player->hitWall();
            } else if(bm == Pair({x, y})) {
                player->hitBookmark();
            } else {
                current = {x, y};
            }
        }
        steps++;
    }
    return current == end;
}