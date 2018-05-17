#include "position.h"
#include <vector>
using namespace std;
Position::Position(int x,int y){
  x_ = x;
  y_ = y;
}
Position::Position(const Position& t){
  x_ = t.x_;
  y_ = t.y_;
}
bool Position::Changex(int tx){
  if(x_+tx>=0&&x_+tx<max_width_){
    x_ = x_+tx;
    return true;
  }
  else return false;
}
bool Position::Changey(int ty){
  if(y_+ty>=0&&y_+ty<max_height_){
    y_ = y_+ty;
    return true;
  }
  else return false;
}
int Position::Getx(){
  return x_;
}
int Position::Gety(){
  return y_;
}
Position Position::UpPosition(){
  if(x_>2){
    return Position(x_,y_-1);
  }
  else return Position(-1,-1);
}
Position Position::DownPosition(){
  if(y_<max_height_-1) return Position(x_,y_+1);
  else return Position(-1,-1);
}
Position Position::LeftPosition(){
  if(x_>2) return Position(x_-1,y_);
  else return Position(-1,-1);
}
Position Position::RightPosition(){
  if(x_<max_width_-1) return Position(x_+1,y_);
  else return Position(-1,-1);
}
Position Position::UpRightPosition(){
  if(y_>2&&x_<max_width_-1)
    return Position(x_+1,y_-1);
  else return Position(-1,-1);
}
Position Position::UpLeftPosition(){
  if(y_>2&&x_>0)
    return Position(x_-1,y_-1);
  else return Position(-1,-1);
}
Position Position::DownLeftPosition(){
  if(y_<max_height_-1&&x_>0)
    return Position(x_-1,y_+1);
  else return Position(-1,-1);
}
Position Position::DownRightPosition(){
  if(y_<max_height_-1&&x_<max_width_-1)
    return Position(x_+1,y_+1);
  else return Position(-1,-1);
}
int Position::Distance(Position other){
  return (this->x_-other.Getx())*(this->x_-other.Getx())+(this->y_-other.Gety())*(this->y_-other.Gety());
}
