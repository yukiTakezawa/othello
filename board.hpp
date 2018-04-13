#ifndef BOARD_HPP
#define BOARD_HPP

#include<math.h>

#include<climits>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<algorithm>
#include<numeric>

class Board{
  
public:
  char board[8][8];
  
  Board(){
    //盤を初期化する
    for(int i=0;i<8;i++){
      for(int j=0;j<8;j++){
	board[i][j] = ' ';
      }
    }
    board[3][3] = 'x';
    board[4][4] = 'x';
    board[3][4] = 'o';
    board[4][3] = 'o';
  }
  
  //盤面全てを表示
  void showBoard();

  //開放度の計算
  int getOpenness(int x,int y);
  
  //board[x][y]からboard[x2][y2]までをひっくり返す
  //返り値は開放度の合計
  int flip(char myStone,int x,int y,int x2,int y2);
  
  int setStone(char myStone,int x,int y);

  //setStoneの実際には石を置かないバージョン
  int setFakeStone(char myStone,int x,int y);
  
  //盤上の優勢度の点数を計算する
  int calcScore(char myStone);

  //次に打つべき手を計算しx,yに代入する
  //counterは現在何番目の手順か
  //widthはゲーム木の高さ
  int calcSolutionForMiddle(char myStone,int counter,int width,int& x,int& y);

  int calcSolutionForMiddle2(char myStone,int counter,int width,int& x,int& y);
  
  double calcSolutionForFinal(char myStone,int& x,int& y);

  void autoSetStone(char myStone,int counter,int border=25,int width=2);
  //石の個数を数える
  int countMyStones(char myStone);

  int canSetStones(char myStone);

  //置く箇所があるならその数を返す
  int canSetStones(char myStone,std::vector<int>& x,std::vector<int>& y);
  
  //board[i][j]が角だったらtrueを返す
  bool isCorner(int i,int j);

  //全ての石を置きおわったらtrueを返す
  bool isEnd();
  
  void operator=(const Board b);

  int getScore(char myStone);

  //勝った方の石を返す
  char whoWin();
};

#endif
