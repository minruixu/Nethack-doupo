#ifndef ROOM_H_
#define ROOM_H_
#include "position.h"
#include "monsters.h"
#include <cstdlib>
#include <ctime>
#include <random>
class Room{
  private:
    int no_;
    int po_x_[5] = {1,3,25,53,53};
    int po_y_[5] = {2,12,8,3,12};
    int init_x_,init_y_;
    int height_;
    int width_;
    Position door_[2];
  public:
    Monster monster_;
    Room(int x);
    ~Room();
    int GetHeight(){return height_;}
    int GetWidth(){return width_;}
    int GetInit_x(){return init_x_;}
    int GetInit_y(){return init_y_;}
    Position GetDoor(int n);
    void SetDoor(int no);
    Position GetInitPosition();
    void MonsterPositionRanDomly();
    bool Is_In_Room(Position po);
};
#endif
