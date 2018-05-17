#ifndef POSITION_H_
#define POSITION_H_
#include <vector>
using namespace std;
class Position{
  private:
    static const int max_height_ = 20;
    static const int max_width_ = 80;
    int x_, y_;
  public:
    Position(const Position& t);
    Position(int x = -1,int y = -1);
    bool Changex(int the_x);
    bool Changey(int the_y);
    int Getx();
    int Gety();
    Position UpPosition();
    Position DownPosition();
    Position LeftPosition();
    Position RightPosition();
    Position UpRightPosition();
    Position UpLeftPosition();
    Position DownLeftPosition();
    Position DownRightPosition();
    //Position * getnearerPosition(int x,Position* target);
    int Distance(Position other);
    bool operator==(const Position &other) const{
        return (x_ == other.x_ && y_ == other.y_);
    }

    bool operator!=(const Position &other) const{
        return !(x_ == other.x_ && y_ == other.y_);
    }
    operator bool() const{
        if (x_ == -1 && y_ == -1)
            return false;
        else
            return true;
    }
};
#endif
