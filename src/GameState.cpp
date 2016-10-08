#include <stdlib.h>
#include "GameState.hpp"

using namespace std;

/*
Tile States:
0-8: Revealed; X mines adjacent
-1: Unrevealed; no mine on tile
-2: Unrevealed; mine on tile
*/

GameState::GameState()
{
    
}

GameState::GameState(unsigned int w, unsigned int h, unsigned int mines)
{
    width = w;
    height = h;
    tiles = new char[width * height];
    setUpNewGame(mines);
}

bool GameState::getHasLost()
{
    return lost;
}

char GameState::getTileAdjacent(unsigned int x, unsigned int y)
{
    if (coordsInGame(x, y)) {
        return tiles[y * width + x];
    }
    return 0;
}

bool GameState::getTileRevealed(unsigned int x, unsigned int y)
{
    if (coordsInGame(x, y) && tiles[y * width + x] < 0) {
        return false;
    }
    return true;
}

void GameState::setUpNewGame(unsigned int mines)
{
    for (int i = 0, m = width * height; i < m; ++i) {
        tiles[i] = -1;
    }
    plantMines(mines);
}

void GameState::revealTile(unsigned int x, unsigned int y)
{
    if (coordsInGame(x, y)) {
        char tile = tiles[y * width + x];
        if (tile == -2) {
            lost = true;
        } else if (tile == -1) {
            sweepFrom(x, y);
        }
    }
}

bool GameState::coordsInGame(unsigned int x, unsigned int y)
{
    return x < width && y < height;
}

void GameState::plantMines(unsigned int number)
{
    int size = width * height;
    
    while (number > 0) {
        tiles[rand() % size] = -2;
        --number;
    }
}

void GameState::sweepFrom(unsigned int ox, unsigned int oy)
{
    char adjacentCount = 0;
    char v;
    for (unsigned int x = ox - 1; x <= ox + 1; ++x) {
        for (unsigned int y = oy - 1; y <= oy + 1; ++y) {
            if (!(x == ox && y == oy) && coordsInGame(x, y)) {
                v = tiles[y * width + x];
                if (v == -2) {
                    adjacentCount += 1;
                }
            }
        }
    }
    
    if (adjacentCount == 0) {
        for (unsigned int x = ox - 1; x <= ox + 1; ++x) {
            for (unsigned int y = oy - 1; y <= oy + 1; ++y) {
                if (!(x == ox && y == oy) && coordsInGame(x, y)) {
                    v = tiles[y * width + x];
                    if (v == -1) {
                        sweepFrom(x, y);
                    }
                }
            }
        }
    }
    
    tiles[oy * height + ox] = adjacentCount;
}
