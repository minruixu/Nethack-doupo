#ifndef MAP_H_
#define MAP_H_
#include "room.h"
#include "position.h"
#include "player.h"
#include "monsters.h"
class Map{
  /*
  0,don't print
  1,can't walk
  2,can walk
  */
  private:
    //pair<char,int> _map[25][81];
    Room * room_[5];
    int po_x_[5] = {1,3,25,53,53};
    int po_y_[5] = {2,12,8,3,12};
    pair<char,int> last_position_;
  public:
    Player p_;
    pair<char,int> map_[25][82];
    Map();
    ~Map();
    void SetRoomToMap();
    Position GetCloserPosition(int x,char c,Position begin,Position end);
    void SetCorridor(Position begin,Position end);
    void SetDoor();
    void AllCorridor();
    void SetPlayer();
    void PlayerWalk(char dir);
    void WalkHelper(Position now,Position then);
    void FightHelper(Position po);
    void RefreshMonster();
    void SetMonsterToMap();
    bool Dropable(Position po);
    void MonsterWalk(int no);
    bool Pickup();
    void SetSwoll();
};
#endif
