#include<math.h>
#include<stdio.h>
#include<iostream>
#include<vector>
#include<climits>

#include "board.hpp"

int main(){
  Board board;
  int check;
  int x=0,y=0;
  board.showBoard();
  int counter=0;
  
  while(!board.isEnd()){
    if(board.canSetStones('o')!=0){
      do{
	std::cout << "your turn" << std::endl;
	std::cin.clear();
	//std::cin >> x >> y;
	scanf("%d %d",&x,&y);
	
	check = board.setFakeStone('o',x,y);
	if(check==-1){
	  std::cout << "you try to set " << x << "," << y <<",but cannot set Stone here" << std::endl;
	}
      }while(check==-1);
    }else{
      std::cout << "you pass" << std::endl;
    }

    board.setStone('o',x,y);
    board.showBoard();
          
    x=0;
    y=0;

    if(board.canSetStones('x')!=0){
      board.autoSetStone('x',counter);
      board.showBoard();
    }else{
      std::cout << "I pass" << std::endl;
    }
    counter++;
  }
  if(board.whoWin()=='x'){
    std::cout << "you lose" << std::endl;
  }else{
    std::cout << "you win" << std::endl;
  }
  
  return 0;
}
  
