#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>
#include <string>
#include "position.h"
#include "monsters.h"
using namespace std;
class Monster;
class Player{
private:
  int max_hp_[10] = {0,10,20,30,40,50,60,70,80,90};
  int lv_exp_[11] = {0,10,30,60,100,150,200,250,300,400,500};
  int std_attack_[11] = {0,1,2,3,4,5,6,7,8,9,10};
  string name_;
  int hp_;
  bool has_swoll;
  int attack_;
  int lv_;
  int exp_;
  vector <char> item_;
  Position po_;
public:
  Player(string name= "xiaoyan");
  ~Player();
  void GetExp(int exp);
  int ReturnExp(){return exp_;}
  int GetHp(){return hp_;}
  int GetAttack(){return attack_;}
  void UpLever();
  bool HasSwoll(){return has_swoll;}
  int GetLv(){return lv_;}
  std::vector<char> GetItem();
  int GetItemCount();
  void PickUpItem(char c);
  Position GetPosition();
  void SetPosition(Position po);
  void GetHurt(Monster& monster);
  bool IsAlive();
  bool Eat();
};
#endif
