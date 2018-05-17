#include <curses.h>
#include <ncurses.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <random>
#include <ctime>
#include "window.h"
#include "player.h"
#include "map.h"
using namespace std;
int main(){//using terminal 24*80
  long long game_time=1;
  char com;
  Window * e = new Window;
  Map map;
  e->PrintAction("Welcome to the wrold of Douqi.\n\
                  You are XiaoYan,once a talent.\n\
                  now you need to train yourself in the monsters Mountains\n\
                  For the promise three years later\n\
                  you need to be stronger.\n\
                  To reach 10 Lv!");
  com = getchar();
  e->PrintMap(map);
  while(true){
    if(map.p_.GetLv()>=10){
      e->PrintAction("Finally you reach Lv 10\n\
                      Now, you need to go into the Mountains\n\
                      So that you can get stronger faster.");
      break;
    }
    if(game_time%180==0) map.RefreshMonster();
    if(!map.p_.IsAlive()){
      e->PrintAction("Game Over!Press any key to continue.");
      break;
    }
    if(strchr("q",com)){
      e->PrintAction("Press any key to continue.");
      break;
    }
    if(strchr("123456789",com)){
      map.PlayerWalk(com);
      e->PrintMap(map);
    }
    else if(strchr(",",com)){
      if(map.Pickup()){
        e->PrintMap(map);
        e->PrintAction("Succeefully pick up.");
      }
      else e->PrintAction("Nothing is there.");
      //pick up something
    }
    else if(com == 'b'){

      e->PrintBag(map.p_);
      //view the bag
    }
    else if(com == 'd'){
      getchar();
    }
    else if(com == 'e'){
      if(map.p_.Eat()){
        e->PrintMap(map);
        e->PrintAction("You eat the meat.");
      }
      else {
        e->PrintMap(map);
        e->PrintAction("There is nothing to eat.");
      }
    }
    else {
      e->PrintMap(map);
      e->PrintAction("Never mind,");
    }
    //e->PrintMap(map);
    //com = getchar();
    //e->PrintAction(to_string(game_time));
    e->PrintInformation(map.p_);
    e->CursorFollow(map.p_.GetPosition());
    //getchar();
    com = getchar();
    game_time++;
  }
  getchar();
  delete e;
  return 0;
}
