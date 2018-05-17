#ifndef MONSTER_H_
#define MONSTER_H_
#include <cstdlib>
#include "position.h"
#include "player.h"
class Player;
class Monster{//M represent the Monster
private:
  int hp_;
  int attack_;
  Position position_;
public:
  Monster();
  ~Monster();
  void Rebrith(){hp_ = 5;}
  int GiveExp(){return 5;}
  int GetHp(){return hp_;}
  int GetAttack(){return attack_;}
  void SetPosition(Position po);
  void MoveRandomly();
  Position GetPosition();
  void GetHurt(Player player);
  bool IsAlive();
};
#endif
