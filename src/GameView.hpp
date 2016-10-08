#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include <map>
#include <string>
#include <sstream>

using namespace std;

class GameView {
    public:
        GameView();
        void addCommand(string name, void (*cb)(stringstream*));
        void readInput();
        void readInput(string message);
    private:
        void activateCommand(string name, stringstream* args);
        map<string, void (*)(stringstream*)> commands;
};

#endif
