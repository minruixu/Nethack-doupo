#include <cstdlib>
#include <iostream>
#include <cstring>
#include <ctime>
#include <random>
#include "map.h"
#include "room.h"
#include "position.h"
#include "monsters.h"
#include "player.h"
using namespace std;
Map::Map(){
  srand(time(NULL));
  for(int i = 0;i<5;i++) room_[i] = new Room(i);
  for(int i = 0;i<25;i++){
    for(int j = 0;j<81;j++){
      map_[i][j].first = '.';
      map_[i][j].second = 0;
    }
  }
  last_position_ = make_pair('.',2);
  //p = player();
  SetRoomToMap();
  SetDoor();
  AllCorridor();
  SetPlayer();
  SetSwoll();
  SetMonsterToMap();
}
Map::~Map(){
  for(int i = 0;i<5;i++) delete room_[i];
}
void Map::SetRoomToMap(){
  for(int i = 0;i<5;i++){
    for(int _x = po_x_[i]+room_[i]->GetInit_x();_x<po_x_[i]+room_[i]->GetInit_x()+room_[i]->GetWidth();_x++){
      for(int _y = po_y_[i]+room_[i]->GetInit_y();_y<po_y_[i]+room_[i]->GetInit_y()+room_[i]->GetHeight();_y++){
        if(_y==po_y_[i]+room_[i]->GetInit_y()||_y==po_y_[i]+room_[i]->GetInit_y()+room_[i]->GetHeight()-1)
        {map_[_y][_x].first = '-';map_[_y][_x].second = 1;}
        else if(_x==po_x_[i]+room_[i]->GetInit_x()||_x==po_x_[i]+room_[i]->GetInit_x()+room_[i]->GetWidth()-1)
        {map_[_y][_x].first = '|';map_[_y][_x].second = 1;}
        else map_[_y][_x].second = 2;
      }
    }
  }
}
void Map::AllCorridor(){
  SetCorridor(room_[0]->GetDoor(0),room_[1]->GetDoor(0));
  SetCorridor(room_[0]->GetDoor(1),room_[2]->GetDoor(0));
  SetCorridor(room_[1]->GetDoor(1),room_[2]->GetDoor(0));
  SetCorridor(room_[2]->GetDoor(1),room_[3]->GetDoor(0));
  SetCorridor(room_[4]->GetDoor(0),room_[2]->GetDoor(1));
  SetCorridor(room_[3]->GetDoor(1),room_[4]->GetDoor(1));
}
void Map::SetCorridor(Position begin,Position end){
  Position t = begin;
  while(t!=end&&t){
    map_[t.Gety()][t.Getx()].first = '#';
    map_[t.Gety()][t.Getx()].second = 2;
    t = GetCloserPosition(0,'#',t,end);
  }
  map_[t.Gety()][t.Getx()].first = '#';
  map_[t.Gety()][t.Getx()].second = 2;
}
Position Map::GetCloserPosition(int x,char c,Position begin,Position end){
  Position t;
  t = begin.UpPosition();
  if(t==end) return t;
  if((begin.Distance(end)>=t.Distance(end)&&map_[t.Gety()][t.Getx()].second==x)||(begin.Distance(end)>=t.Distance(end)&&map_[t.Gety()][t.Getx()].first=='#')) return t;
  t = begin.DownPosition();
  if(t==end) return t;
  if((begin.Distance(end)>=t.Distance(end)&&map_[t.Gety()][t.Getx()].second==x)||(begin.Distance(end)>=t.Distance(end)&&map_[t.Gety()][t.Getx()].first=='#')) return t;
  t = begin.LeftPosition();
  if(t==end) return t;
  if((begin.Distance(end)>=t.Distance(end)&&map_[t.Gety()][t.Getx()].second==x)||(begin.Distance(end)>=t.Distance(end)&&map_[t.Gety()][t.Getx()].first=='#')) return t;
  t = begin.RightPosition();
  if(t==end) return t;
  if((begin.Distance(end)>=t.Distance(end)&&map_[t.Gety()][t.Getx()].second==x)||(begin.Distance(end)>=t.Distance(end)&&map_[t.Gety()][t.Getx()].first=='#')) return t;
  t = begin.RightPosition();
  if(map_[t.Gety()][t.Getx()].second==x) return t;
  t = begin.DownPosition();
  if(map_[t.Gety()][t.Getx()].second==x) return t;
  t = begin.LeftPosition();
  if(map_[t.Gety()][t.Getx()].second==x) return t;
  t = begin.UpPosition();
  if(map_[t.Gety()][t.Getx()].second==x) return t;
  return Position(-1,-1);
}
void Map::SetDoor(){
  for(int i = 0;i<5;i++){
    map_[room_[i]->GetDoor(0).Gety()][room_[i]->GetDoor(0).Getx()] = make_pair('#',2);
    map_[room_[i]->GetDoor(1).Gety()][room_[i]->GetDoor(1).Getx()] = make_pair('#',2);
  }
}
void Map::SetPlayer(){
  Position po = room_[0]->GetInitPosition();
  po.Changex(po_x_[0]);
  po.Changey(po_y_[0]);
  p_.SetPosition(po);
  last_position_ = map_[po.Gety()][po.Getx()];
  map_[po.Gety()][po.Getx()] = make_pair('@',1);
}
void Map::PlayerWalk(char dir){
  if(dir=='1'){
    if(map_[p_.GetPosition().DownLeftPosition().Gety()][p_.GetPosition().DownLeftPosition().Getx()].first=='M'){
      FightHelper(p_.GetPosition().DownLeftPosition());
    }
    if(p_.GetPosition().DownLeftPosition()&&map_[p_.GetPosition().DownLeftPosition().Gety()][p_.GetPosition().DownLeftPosition().Getx()].second==2){
      WalkHelper(p_.GetPosition(),p_.GetPosition().DownLeftPosition());
      p_.SetPosition(p_.GetPosition().DownLeftPosition());
    }
  }
  else if(dir=='2'){
    if(map_[p_.GetPosition().DownPosition().Gety()][p_.GetPosition().DownPosition().Getx()].first=='M'){
      FightHelper(p_.GetPosition().DownPosition());
    }
    if(p_.GetPosition().DownPosition()&&map_[p_.GetPosition().DownPosition().Gety()][p_.GetPosition().DownPosition().Getx()].second==2){
      WalkHelper(p_.GetPosition(),p_.GetPosition().DownPosition());
      p_.SetPosition(p_.GetPosition().DownPosition());
    }
  }
  else if(dir == '3'){
    if(map_[p_.GetPosition().DownRightPosition().Gety()][p_.GetPosition().DownRightPosition().Getx()].first=='M'){
      FightHelper(p_.GetPosition().DownRightPosition());
    }
    if(p_.GetPosition().DownRightPosition()&&map_[p_.GetPosition().DownRightPosition().Gety()][p_.GetPosition().DownRightPosition().Getx()].second==2){
      WalkHelper(p_.GetPosition(),p_.GetPosition().DownRightPosition());
      p_.SetPosition(p_.GetPosition().DownRightPosition());
    }
  }
  else if(dir == '4'){
    if(map_[p_.GetPosition().LeftPosition().Gety()][p_.GetPosition().LeftPosition().Getx()].first=='M'){
      FightHelper(p_.GetPosition().LeftPosition());
    }
    if(p_.GetPosition().LeftPosition()&&map_[p_.GetPosition().LeftPosition().Gety()][p_.GetPosition().LeftPosition().Getx()].second==2){
      WalkHelper(p_.GetPosition(),p_.GetPosition().LeftPosition());
      p_.SetPosition(p_.GetPosition().LeftPosition());
    }
  }
  else if(dir == '5'){
      ;//alkHelper(p_.GetPosition(),p_.GetPosition());
  }
  else if(dir == '6'){
    if(map_[p_.GetPosition().RightPosition().Gety()][p_.GetPosition().RightPosition().Getx()].first=='M'){
      FightHelper(p_.GetPosition().RightPosition());
    }
    if(p_.GetPosition().RightPosition()&&map_[p_.GetPosition().RightPosition().Gety()][p_.GetPosition().RightPosition().Getx()].second==2){
      WalkHelper(p_.GetPosition(),p_.GetPosition().RightPosition());
      p_.SetPosition(p_.GetPosition().RightPosition());
    }
  }
  else if(dir == '7'){
    if(map_[p_.GetPosition().UpLeftPosition().Gety()][p_.GetPosition().UpLeftPosition().Getx()].first=='M'){
      FightHelper(p_.GetPosition().UpLeftPosition());
    }
    if(p_.GetPosition().UpLeftPosition()&&map_[p_.GetPosition().UpLeftPosition().Gety()][p_.GetPosition().UpLeftPosition().Getx()].second==2){
      WalkHelper(p_.GetPosition(),p_.GetPosition().UpLeftPosition());;
      p_.SetPosition(p_.GetPosition().UpLeftPosition());
    }
  }
  else if(dir == '8'){
    if(map_[p_.GetPosition().UpPosition().Gety()][p_.GetPosition().UpPosition().Getx()].first=='M'){
      FightHelper(p_.GetPosition().UpPosition());
    }
    if(p_.GetPosition().UpPosition()&&map_[p_.GetPosition().UpPosition().Gety()][p_.GetPosition().UpPosition().Getx()].second==2){
      WalkHelper(p_.GetPosition(),p_.GetPosition().UpPosition());
      p_.SetPosition(p_.GetPosition().UpPosition());
    }
  }
  else if(dir == '9'){
    if(map_[p_.GetPosition().UpRightPosition().Gety()][p_.GetPosition().UpRightPosition().Getx()].first=='M'){
      FightHelper(p_.GetPosition().UpRightPosition());
    }
    if(p_.GetPosition().UpRightPosition()&&map_[p_.GetPosition().UpRightPosition().Gety()][p_.GetPosition().UpRightPosition().Getx()].second==2){
      WalkHelper(p_.GetPosition(),p_.GetPosition().UpRightPosition());
      p_.SetPosition(p_.GetPosition().UpRightPosition());
    }
  }
  for(int i = 0;i<5;i++) MonsterWalk(i);
}
void Map::FightHelper(Position po){
  int player_in = -1;
  for(int i = 0;i<5;i++){
    if(room_[i]->Is_In_Room(po)) player_in = i;
  }
  if(player_in == -1) return ;
  else{
    if(room_[player_in]->monster_.IsAlive()){
      p_.GetHurt(room_[player_in]->monster_);
      room_[player_in]->monster_.GetHurt(p_);
      if(!room_[player_in]->monster_.IsAlive()){
        map_[room_[player_in]->monster_.GetPosition().Gety()][room_[player_in]->monster_.GetPosition().Getx()] = make_pair('m',2);
        p_.GetExp(room_[player_in]->monster_.GiveExp());
      }
    }
  }
}
void Map::WalkHelper(Position now,Position then){//leaft and go;
  pair<char,int> t;
  t = map_[then.Gety()][then.Getx()];
  map_[now.Gety()][now.Getx()] = last_position_;
  last_position_ = t;
  map_[then.Gety()][then.Getx()] = make_pair('@',1);
}
void Map::SetMonsterToMap(){
  for(int i = 0;i<5;i++){
    while(!Dropable(room_[i]->monster_.GetPosition())){
      room_[i]->MonsterPositionRanDomly();
    }
    map_[room_[i]->monster_.GetPosition().Gety()][room_[i]->monster_.GetPosition().Getx()]=make_pair('M',1);
  }
}
bool Map::Dropable(Position po){
    if(po&&map_[po.Gety()][po.Getx()]==make_pair('.',2)) return true;
    else return false;
}
void Map::SetSwoll(){
  Position po = room_[4]->GetInitPosition();
  po.Changex(po_x_[4]);
  po.Changey(po_y_[4]);
  map_[po.Gety()][po.Getx()] = make_pair('S',2);
}
void Map::MonsterWalk(int no){
  Position next_po;
  if(room_[no]->monster_.IsAlive()){
  if(room_[no]->Is_In_Room(p_.GetPosition())){
    next_po = GetCloserPosition(2,'.',room_[no]->monster_.GetPosition(),p_.GetPosition());
  }
  else{
    int temp = rand()%4;
    if(temp==0) next_po = room_[no]->monster_.GetPosition().UpPosition();
    else if(temp == 1) next_po = room_[no]->monster_.GetPosition().DownPosition();
    else if(temp == 2) next_po = room_[no]->monster_.GetPosition().LeftPosition();
    else if(temp == 3) next_po = room_[no]->monster_.GetPosition().RightPosition();
  }
  if(room_[no]->Is_In_Room(next_po)&&next_po&&map_[next_po.Gety()][next_po.Getx()] == make_pair('.',2)){
    //pair<char,int> t;
    //t = map_[next_po.Gety()][next_po.Getx()];
    map_[next_po.Gety()][next_po.Getx()] = make_pair('M',1);
    map_[room_[no]->monster_.GetPosition().Gety()][room_[no]->monster_.GetPosition().Getx()] = make_pair('.',2);
    room_[no]->monster_.SetPosition(next_po);
    }
  }
  if(room_[no]->monster_.GetPosition().Distance(p_.GetPosition())<=2){
    FightHelper(p_.GetPosition());
  }
}
void Map::RefreshMonster(){
  for(int i = 0;i<5;i++){
    room_[i]->monster_.Rebrith();
  }
}
bool Map::Pickup(){
  if(strchr("mS",last_position_.first)){
    p_.PickUpItem(last_position_.first);
    last_position_.first = '.';
    return true;
  }
  else return false;
}
