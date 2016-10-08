#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

class GameState {
    public:
        GameState();
        GameState(int w, int h, int mines);
        bool getHasLost();
        char getTileAdjacent(int x, int y);
        bool getTileRevealed(int x, int y);
        int getWidth();
        int getHeight();
        void revealTile(int x, int y);
    private:
        int width;
        int height;
        char *tiles;
        bool lost;
        bool coordsInGame(int x, int y);
        void plantMines(int number);
        void sweepFrom(int x, int y);
};

#endif
