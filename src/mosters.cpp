#include "position.h"
#include "monsters.h"
#include "player.h"
Monster::Monster(){
  hp_ = 5;
  attack_ = 1;
  position_ = Position(-1,-1);
}
Monster::~Monster(){

}
void Monster::SetPosition(Position po){
  position_ = po;
}
Position Monster::GetPosition(){
  return position_;
}
void Monster::GetHurt(Player player){
  hp_-=player.GetAttack();
}
bool Monster::IsAlive(){
  if(hp_<=0) return false;
  else return true;
}
