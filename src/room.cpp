#include <cstdlib>
#include <ctime>
#include <random>
#include "room.h"
#include "position.h"
#include "monsters.h"
Room::Room(int x){
  no_ = x;
  init_y_ = rand()%2+1;
  init_x_ = rand()%4+3;
  height_ = rand()%2+5;
  width_ = rand()%10+8;
  //generate door
  MonsterPositionRanDomly();
  SetDoor(x);
}
Room::~Room(){
  init_x_ = init_y_ = height_ = width_ = 0;
  //delete door[1]
}
Position Room::GetDoor(int n){
  return door_[n];
}
void Room::SetDoor(int no){
  if(no==0){
    door_[0] = Position(po_x_[no]+init_x_+rand()%(width_-5)+3,po_y_[no]+init_y_+height_-1);
    door_[1] = Position(po_x_[no]+init_x_+width_-1,po_y_[no]+init_y_+rand()%(height_-4)+3);
  }
  else if(no == 1){
    door_[0] = Position(po_x_[no]+init_x_+rand()%(width_-4)+3,po_y_[no]+init_y_);
    door_[1] = Position(po_x_[no]+init_x_+width_-1,po_y_[no]+init_y_+rand()%(height_-4)+3);
  }
  else if(no==2){
    door_[0] = Position(po_x_[no]+init_x_,po_y_[no]+init_y_+rand()%(height_-4)+3);
    door_[1] = Position(po_x_[no]+init_x_+width_-1,po_y_[no]+init_y_+rand()%(height_-4)+3);
  }
  else if(no == 3){
    door_[0] = Position(po_x_[no]+init_x_,po_y_[no]+init_y_+rand()%(height_-4)+3);
    door_[1] = Position(po_x_[no]+init_x_+rand()%(width_-5)+4,po_y_[no]+init_y_+height_-1);
  }
  else if(no==4){
    door_[0] = Position(po_x_[no]+init_x_,po_y_[no]+init_y_+rand()%(height_-4)+3);
    door_[1] = Position(po_x_[no]+init_x_+rand()%(width_-5)+4,po_y_[no]+init_y_);
  }
}
Position Room::GetInitPosition(){
  return Position(init_x_+1,init_y_+1);
}
void Room::MonsterPositionRanDomly(){//
  monster_.SetPosition(Position(po_x_[no_]+init_x_+rand()%(width_-1)+1,po_y_[no_]+init_y_+rand()%(height_-1)+1));
}
bool Room::Is_In_Room(Position po){
  return (po.Getx()>po_x_[no_]+init_x_&&po.Getx()<po_x_[no_]+init_x_+width_-1)&&(po.Gety()>po_y_[no_]+init_y_&&po.Gety()<po_y_[no_]+init_y_+height_-1);
}
