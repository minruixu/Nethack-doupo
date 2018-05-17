#ifndef WINDOW_H_
#define WINDOW_H_
#include <ncurses.h>
#include <curses.h>
#include <string>
#include "position.h"
#include "player.h"
#include "map.h"
class Window{
  private:
    int height_ = 24;
    int width_ = 80;
    int x_=0,y_=0;
  public:
    Window();
    ~Window();
    void PrintAction(std::string s);
    void PrintMap(Map & _map);
    void CursorFollow(Position t);
    void PrintInformation(Player player);
    void PrintBag(Player player);
};

#endif
