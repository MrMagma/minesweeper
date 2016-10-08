#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

class GameState {
    public:
        GameState();
        GameState(unsigned int w, unsigned int h, unsigned int mines);
        bool getHasLost();
        char getTileAdjacent(unsigned int x, unsigned int y);
        bool getTileRevealed(unsigned int x, unsigned int y);
        void revealTile(unsigned int x, unsigned int y);
        void setUpNewGame(unsigned int mines);
    private:
        unsigned int width;
        unsigned int height;
        char *tiles;
        bool lost;
        bool coordsInGame(unsigned int x, unsigned int y);
        void plantMines(unsigned int number);
        void sweepFrom(unsigned int x, unsigned int y);
};

#endif
