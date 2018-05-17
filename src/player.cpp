#include "player.h"
#include "position.h"
#include "monsters.h"
#include <string>
using namespace std;
Player::Player(string name){
  name_ = name;
  lv_ = 1;
  hp_ = max_hp_[lv_];
  exp_ = 0;
  has_swoll = false;
  attack_ = std_attack_[lv_];
  po_ = Position(-1,-1);
}
Player::~Player(){
}
void Player::GetExp(int ep){
  exp_ += ep;
  if(exp_>=lv_exp_[lv_]) UpLever();
}
void Player::UpLever(){
  lv_ += 1;
  hp_ = max_hp_[lv_];
  attack_ = std_attack_[lv_];
}
Position Player::GetPosition(){
  return po_;
}
void Player::SetPosition(Position po){
  po_ = po;
}
void Player::GetHurt(Monster& monster){
  hp_-=monster.GetAttack();
}
bool Player::IsAlive(){
  if(hp_<=0) return false;
  else return true;
}
std::vector<char> Player::GetItem(){return item_;}
int Player::GetItemCount(){return item_.size();}
void Player::PickUpItem(char c){
  if(c=='S') has_swoll = true;
  else item_.push_back(c);
}
bool Player::Eat(){
  if(item_.size()){
    hp_+= 2;
    item_.pop_back();
    return true;
  }
  else return false;
}
