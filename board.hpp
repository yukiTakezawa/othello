#ifndef BOARD_HPP
#define BOARD_HPP

#include<iostream>
#include<bitset>
#include<vector>


class Board{

  std::uint64_t black;//black is 'o'
  std::uint64_t white;//while is 'x'
public:
  const static std::uint64_t RIGHT;
  const static std::uint64_t LEFT;
  const static std::uint64_t UP;
  const static std::uint64_t DOWN;
  const static std::uint64_t UPPER_RIGHT;
  const static std::uint64_t UPPER_LEFT;
  const static std::uint64_t LOWER_RIGHT;
  const static std::uint64_t LOWER_LEFT;
  const static char BLACK;
  const static char WHITE;
  const static std::uint64_t DIRECTIONS[8];
    
  Board(){
    black = convertBitBoard(3,4) | convertBitBoard(4,3);
    white = convertBitBoard(3,3) | convertBitBoard(4,4);
  }

  void set(std::uint64_t black2,std::uint64_t white2);

private:
  std::uint64_t getBlack() const;

  std::uint64_t getWhite() const;

  //(col,row)に置けるなら0、おけないなら-1が返る
  int setFakeStone(char myStone,int col,int row) const;

  //置く座標(col,row)を64bitに変換する
  std::uint64_t convertBitBoard(int col,int row) const;

  std::uint64_t transfer(std::uint64_t m,std::uint64_t direction) const;
  
  std::uint64_t getRevPat(char myStone,int col,int row) const;

public:
  //盤面を表示する
  void show() const;

  void setStone(char myStone,int col,int row);

  void operator=(const Board board);
  
  //置く箇所があるならその数を返す
  int canSetStones(char myStone,std::vector<int>& x,std::vector<int>& y);

  //置く箇所があればtrue,なければfalseを返す。
  bool canSetStones(char myStone) const;


  void autoSetStone(char myStone,int counter,int border=25,int width=3);

  int countMyStones(char myStone) const;
  //勝負が終了したかどうか
  bool isEnd() const;
};

#endif
