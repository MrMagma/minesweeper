#include <stdlib.h>
#include "GameState.hpp"

using namespace std;

/*
Tile States:
0-8: Revealed; X mines adjacent
-1: Unrevealed; no mine on tile
-2: Unrevealed; mine on tile
9: Revealed; mine on tile
*/

GameState::GameState()
{
    
}

GameState::GameState(int w, int h, int mines)
{
    width = w;
    height = h;
    tiles = new char[width * height];
    for (int i = 0, m = width * height; i < m; ++i) {
        tiles[i] = -1;
    }
    plantMines(mines);
}

bool GameState::getHasLost()
{
    return lost;
}

char GameState::getTileAdjacent(int x, int y)
{
    if (coordsInGame(x, y)) {
        return tiles[y * width + x];
    }
    return 0;
}

int GameState::getWidth()
{
    return width;
}

int GameState::getHeight()
{
    return height;
}

bool GameState::getTileRevealed(int x, int y)
{
    if (coordsInGame(x, y) && tiles[y * width + x] < 0) {
        return false;
    }
    return true;
}

void GameState::revealTile(int x, int y)
{
    if (coordsInGame(x, y)) {
        char tile = tiles[y * width + x];
        if (tile == -2) {
            tiles[y * width + x] = 9;
            lost = true;
        } else if (tile == -1) {
            sweepFrom(x, y);
        }
    }
}

bool GameState::coordsInGame(int x, int y)
{
    return x >= 0 && y >= 0 && x < width && y < height;
}

void GameState::plantMines(int number)
{
    int size = width * height;
    
    while (number > 0) {
        tiles[rand() % size] = -2;
        --number;
    }
}

void GameState::sweepFrom(int ox, int oy)
{
    char adjacentCount = 0;
    char v;
    for (int x = ox - 1; x <= ox + 1; ++x) {
        for (int y = oy - 1; y <= oy + 1; ++y) {
            if (!(x == ox && y == oy) && coordsInGame(x, y)) {
                v = tiles[y * width + x];
                if (v == -2) {
                    adjacentCount += 1;
                }
            }
        }
    }
    
    tiles[oy * height + ox] = adjacentCount;
    
    if (adjacentCount == 0) {
        for (int x = ox - 1; x <= ox + 1; ++x) {
            for (int y = oy - 1; y <= oy + 1; ++y) {
                if (!(x == ox && y == oy) && coordsInGame(x, y)) {
                    if (tiles[y * width + x] == -1) {
                        sweepFrom(x, y);
                    }
                }
            }
        }
    }
}
