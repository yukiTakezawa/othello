#include "Board.hpp"

const std::uint64_t Board::RIGHT = 0x7f7f7f7f7f7f7f7f;
const std::uint64_t Board::LEFT = 0xfefefefefefefefe;
const std::uint64_t Board::UP = 0xffffffffffffff00;
const std::uint64_t Board::DOWN = 0x00ffffffffffffff;
const std::uint64_t Board::UPPER_RIGHT = 0x7f7f7f7f7f7f7f00;
const std::uint64_t Board::UPPER_LEFT = 0xfefefefefefefe00;
const std::uint64_t Board::LOWER_RIGHT = 0x007f7f7f7f7f7f7f;
const std::uint64_t Board::LOWER_LEFT = 0x00fefefefefefefe;
const char Board::BLACK = 'o';
const char Board::WHITE = 'x';
const std::uint64_t Board::DIRECTIONS[] = {RIGHT,LEFT,UP,DOWN,UPPER_RIGHT,UPPER_LEFT,LOWER_RIGHT,LOWER_LEFT};

void Board::set(std::uint64_t black2,std::uint64_t white2){
  black = black2;
  white = white2;
}

std::uint64_t Board::getBlack() const{
  return black;
}

std::uint64_t Board::getWhite() const{
  return white;
}

void Board::show() const{
  int rank=1;
  std::uint64_t pos = (std::uint64_t)1<<63;
  
  std::cout << "  a b c d e f g h" << std::endl;
  for(int i=0;i<64;i++){
    if(i%8==0) std::cout << rank++;

    if((black & pos)!=0) std::cout << " o";
    else if((white & pos)!=0) std::cout << " x";
    else std::cout << "  ";

    if(i%8==7) std::cout << std::endl;
    pos >>= 1;
  }
}

std::uint64_t Board::convertBitBoard(int col,int row) const{
  return (std::uint64_t)1 << ((7-col)*8+(7-row));
}

std::uint64_t Board::transfer(std::uint64_t m,std::uint64_t direction) const{
  if(direction==RIGHT) return (m>>1) & direction;
  if(direction==LEFT) return (m<<1) & direction;
  if(direction==UP) return (m<<8) & direction;
  if(direction==DOWN) return (m>>8) & direction;
  if(direction==UPPER_RIGHT) return (m<<7) & direction;
  if(direction==UPPER_LEFT) return (m<<9) & direction;
  if(direction==LOWER_RIGHT) return (m>>9) & direction;
  if(direction==LOWER_LEFT) return (m>>7) & direction;

  return 0;
}

int Board::setFakeStone(char myStone,int col,int row) const{
  if(getRevPat(myStone,col,row)==0){
    return -1;
  }
  return 0;
}

std::uint64_t Board::getRevPat(char myStone,int col,int row) const{
  std::uint64_t m = convertBitBoard(col,row);//着手箇所
  std::uint64_t rev = 0;

  std::uint64_t myBoard,peerBoard;
  if(myStone==BLACK){
    myBoard = black;
    peerBoard = white;
  }else{
    myBoard = white;
    peerBoard = black;
  }
  
  if(((myBoard | peerBoard) & m)!=0)//既に石が置いてある時
    return rev;

  std::uint64_t tmpRev = 0;
  std::uint64_t mask;
  for(auto direction : DIRECTIONS){
    mask = transfer(m,direction);
    while(mask!=0 && (mask & peerBoard)!=0){
      tmpRev |= mask;
      mask = transfer(mask,direction);
    }
    if((mask & myBoard)==0){//peerStoneがなければおけない
      tmpRev = 0;
    }else{
      rev |= tmpRev;
      tmpRev = 0;
    }
  }
  return rev;
}


void Board::setStone(char myStone,int col,int row){
  std::uint64_t mov = convertBitBoard(col,row);
  std::uint64_t rev = getRevPat(myStone,col,row);
  
  if(myStone==BLACK && rev!=0){
    black ^= mov | rev;
    white ^= rev;
  }if(myStone==WHITE && rev!=0){
    white ^= mov | rev;
    black ^= rev;
  }
}

void Board::operator=(const Board board){
  set(board.getBlack(),board.getWhite());
}

//置く箇所があるならその数を返す
int Board::canSetStones(char myStone,std::vector<int>& x,std::vector<int>& y){
  int counter = 0;
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(setFakeStone(myStone,i,j)==-1)
	continue;
      else{
	x.push_back(i);
	y.push_back(j);
	++counter;
      }
    }
  }
  return counter;
}

bool Board::canSetStones(char myStone) const{
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(setFakeStone(myStone,i,j)==0)
	return true;
    }
  }
  return false;
}

bool Board::isEnd() const{
  bool canSetBlack = canSetStones(BLACK);
  bool canSetWhite = canSetStones(WHITE);

  return (!canSetBlack && canSetBlack) || (canSetBlack && !canSetWhite);
}

int Board::countMyStones(char myStone){


}

void autoSetStone(char myStone,int counter,int border=25,int width=3){
  if(counter>30){
    std::exit(1);
  }
  
  int x,y;
  if(counter<border){
    calcSolutionForMiddle(myStone,counter,width,x,y);
    setStone(myStone,x,y);
  }else{
    fprintf(stderr,"calcSolutionForFinal\n");
    calcSolutionForFinal(myStone,x,y);
    setStone(myStone,x,y);
  }
}



