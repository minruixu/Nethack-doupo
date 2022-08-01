#include <ncurses.h>
#include <curses.h>
#include <string>
#include <cstring>
#include <iostream>
#include "position.h"
#include "map.h"
#include "player.h"
#include "window.h"
using namespace std;
Window::Window(){
  initscr();
  noecho();
  //cbreak();
  keypad(stdscr,TRUE);
}
Window::~Window(){
  endwin();
}
void Window::PrintAction(std::string s){
  mvprintw(0,0,"%s",s.c_str());
  refresh();
}
void Window::PrintMap(Map & m){
  erase();
  for(int i = 1;i<24;i++){
    for(int j = 0;j<80;j++){
      //if(m._map[i][j].second!=0) cout << m._map[i][j].first;
      if(m.map_[i][j].second!=0) mvaddch(i,j,m.map_[i][j].first);
    }
  }
  refresh();
}
void Window::CursorFollow(Position t){
  move(t.Gety(),t.Getx());
  refresh();
}
void Window::PrintInformation(Player player){
  mvprintw(21,0,"lv:%d",player.GetLv());
  mvprintw(21,15,"hp:%d",player.GetHp());
  mvprintw(21,30,"exp:%d",player.ReturnExp());
  mvprintw(21,45,"attack:%d",player.GetAttack());
  //mvprintw(23,0,"");
  refresh();
}
void Window::PrintBag(Player player){
  erase();
  int i,l=0;
  if(player.HasSwoll()){
    mvprintw(l,0,"Swoll - the weapon increase your attack");
    l++;
  }
  std::vector<char> item = player.GetItem();
  for(i=0;i<player.GetItemCount();i++,l++){
    if(strchr("m",item[i]))
    mvprintw(l,0,"Meat - a thing to eat to recover HP");
    else mvprintw(l,0,"Unknown - Something unexpected");
  }
  refresh();
}
