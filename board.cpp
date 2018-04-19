#include "board.hpp"


//盤面全てを表示
void Board::showBoard() const{
  std::cout << " 0 1 2 3 4 5 6 7 " << std::endl;
  
  for(int i=0;i<8;i++){
    std::cout << i;
    for(int j=0;j<8;j++){
      std::cout << board[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}


//開放度の計算
//打った後で計算するので1少ないはずだが
//相対評価なので問題ない
int Board::getOpenness(int x,int y){
  int openness=0;
  int a[] = {-1,0,1};

  for(auto i : a){
    if((x+i)<1 || (x+i)>6){
      continue;
    }

    for(auto j : a){
      if((y+j)<1 || (y+j)>6){
	continue;
      }

      if(board[x+i][y+j]==' '){
	openness++;
      }
    }
  }
  return openness;
}

//board[x][y]からboard[x2][y2]までをひっくり返す
//返り値はひっくり返した石の開放度の合計
int Board::flip(char myStone,int x,int y,int x2,int y2){
  int openness=0;//開放度
  int dx = x2 - x;
  int dy = y2 - y;
  
  int i = (dx!=0)? dx/abs(dx): 0;
  int j = (dy!=0)? dy/abs(dy): 0; 
  do{
    board[x+i][y+j] = myStone;
    openness += getOpenness(x+i,y+j);
    i += (i!=0)? dx/abs(dx): 0;
    j += (j!=0)? dy/abs(dy): 0;    
  }while(abs(i)<abs(dx) || abs(j)<abs(dy));

  return openness;
}

//返り値は開放度の合計
int Board::setStone(char myStone,int x,int y){
  int openness=0;
  int flag=0;//最後にflag=0ならばどこもひっくり返していない
  char peerStone;
  if(myStone == 'x'){
    peerStone = 'o';
  }else if(myStone == 'o'){
    peerStone = 'x';
  }else{
    std::cout << "Error: Stone" << std::endl;
    return -1;
  }
  
  if(board[x][y]==' '){
    board[x][y] = myStone;
  }else{
    //std::cout << "can not set stone here" << std::endl;
    return -1;
  }
  
  //上を確認
  if(x>1 && board[x-1][y]==peerStone){ 
    for(int i=1;(x-i)>=0;i++){
      if(board[x-i][y]==peerStone){
	continue;
      }else if(board[x-i][y]==myStone){
	openness += flip(myStone,x,y,x-i,y);
	flag=1;
	break;
      }else{
	break;
      }
    }
  }
  
  //下を確認
  if(x<6 && board[x+1][y]==peerStone){ 
    for(int i=1;(x+i)<=7;i++){
      if(board[x+i][y]==peerStone){
	continue;
      }else if(board[x+i][y]==myStone){
	openness += flip(myStone,x,y,x+i,y);
	flag=1;
	break;
      }else{
	break;
      }
    }
  }
  
  //左を確認
  if(y>1 && board[x][y-1]==peerStone){
    for(int i=1;(y-i)>=0;i++){
      if(board[x][y-i]==peerStone){
	continue;
      }else if(board[x][y-i]==myStone){        
	openness += flip(myStone,x,y,x,y-i);
	flag=1;
	break;
      }else{
	break;
      }
    }
  }
  
  //右を確認
  if(y<6 && board[x][y+1]==peerStone){
    for(int i=1;(y+i)<=7;i++){
      if(board[x][y+i]==peerStone){
	continue;
      }else if(board[x][y+i]==myStone){
	openness += flip(myStone,x,y,x,y+i);
	flag=1;
	break;
      }else{
	break;
      }
    }
  }
  
  //左上を確認
  if(x>1 && y>1 && board[x-1][y-1]==peerStone){
    for(int i=1;(x-i)>=0 && (y-i)>=0;i++){
      if(board[x-i][y-i]==peerStone){
	continue;
      }else if(board[x-i][y-i]==myStone){
	openness += flip(myStone,x,y,x-i,y-i);
	flag=1;
	break;
      }else{
	break;
      }
    }
  }
  
  //右下を確認
  if(x<6 && y<6 && board[x+1][y+1]==peerStone){
    for(int i=1;(x+i)<=7 && (y+i)<=7;i++){
      if(board[x+i][y+i]==peerStone){
	continue;
      }else if(board[x+i][y+i]==myStone){
	openness += flip(myStone,x,y,x+i,y+i);
	flag=1;
	break;
      }else{
	break;
      }
    }
  }
  
  //右上を確認
  if(x<6 && y>1 && board[x+1][y-1]==peerStone){
    for(int i=1;(x+i)<=7 && (y-i)>=0;i++){
      if(board[x+i][y-i]==peerStone){
	continue;
      }else if(board[x+i][y-i]==myStone){
	openness += flip(myStone,x,y,x+i,y-i);
	flag=1;
	break;
      }else{
	break;
      }
    }
  }
  
  //左下を確認
  if(x>1 && y<6 && board[x-1][y+1]==peerStone){
    for(int i=1;(x-i)>=0 && (y+i)<=7;i++){
      if(board[x-i][y+i]==peerStone){
	continue;
      }else if(board[x-i][y+i]==myStone){
	openness += flip(myStone,x,y,x-i,y+i);
	flag=1;
	break;
      }else{
	break;
      }
    }
  }
  if(flag==0){
    return -1;
  }  
  return openness;
}


int Board::calcScore(char myStone){
  int score=0;
  char peerStone;
  if(myStone=='x'){
    peerStone = 'o';
  }else if(myStone=='o'){
    peerStone = 'x';
  }else{
    std::cout << "Error:calcScore" << std::endl;
    exit(1);
  }

  const int cornerScore = 50;
  if(board[0][0]==myStone) score+=cornerScore;
  if(board[0][0]==peerStone)  score-=cornerScore;
  
  if(board[7][7]==myStone)  score+=cornerScore;
  if(board[7][7]==peerStone)  score-=cornerScore;
    
  if(board[0][7]==myStone)  score+=cornerScore;
  if(board[0][7]==peerStone)  score-=cornerScore;

  if(board[7][0]==myStone)  score+=cornerScore;
  if(board[7][0]==peerStone)  score-=cornerScore;

  const int sideScore = 5;
  for(int i=1;i<7;i++){
    if(board[0][i]==myStone)  score+=sideScore;
    if(board[0][i]==peerStone)  score-=sideScore;
    if(board[7][i]==myStone)  score+=sideScore;
    if(board[7][i]==peerStone)  score-=sideScore;
  }

  const int generalScore = 1;
  for(int i=1;i<7;i++){
    for(int j=1;j<7;j++){
      if(board[i][j]==myStone)  score+=generalScore;
      if(board[i][j]==peerStone)  score-=generalScore;
    }
  }

  return score;
}

//setStoneの実際には石を置かない関数
int Board::setFakeStone(char myStone,int x,int y) const{
  int flag=0;//最後にflag=0ならばどこもひっくり返していない
  char peerStone;
  if(myStone == 'x'){
    peerStone = 'o';
  }else if(myStone == 'o'){
    peerStone = 'x';
  }else{
    std::cout << "Error: Stone" << std::endl;
  }
  
  if(board[x][y]==' '){
    //board[x][y] = myStone;
  }else{
    //std::cout << "can not set stone here" << std::endl;
    return -1;
  }
  
  //上を確認
  if(x>1 && board[x-1][y]==peerStone){ 
    for(int i=1;(x-i)>=0;i++){
      if(board[x-i][y]==peerStone){
	continue;
      }else if(board[x-i][y]==myStone){
	//flip(myStone,x,y,x-i,y);
	flag=1;
	return 0;
      }else{
	break;
      }
    }
  }
  
  //下を確認
  if(x<6 && board[x+1][y]==peerStone){ 
    for(int i=1;(x+i)<=7;i++){
      if(board[x+i][y]==peerStone){
	continue;
      }else if(board[x+i][y]==myStone){
	//flip(myStone,x,y,x+i,y);
	flag=1;
	return 0;
      }else{
	break;
      }
    }
  }
  
  //左を確認
  if(y>1 && board[x][y-1]==peerStone){
    for(int i=1;(y-i)>=0;i++){
      if(board[x][y-i]==peerStone){
	continue;
      }else if(board[x][y-i]==myStone){
	//flip(myStone,x,y,x,y-i);
	flag=1;
	return 0;
      }else{
	break;
      }
    }
  }
  
  //右を確認
  if(y<6 && board[x][y+1]==peerStone){
    for(int i=1;(y+i)<=7;i++){
      if(board[x][y+i]==peerStone){
	continue;
      }else if(board[x][y+i]==myStone){
	//flip(myStone,x,y,x,y+i);
	flag=1;
	return 0;
      }else{
	break;
      }
    }
  }
  
  //左上を確認
  if(x>1 && y>1 && board[x-1][y-1]==peerStone){
    for(int i=1;(x-i)>=0 && (y-i)>=0;i++){
      if(board[x-i][y-i]==peerStone){
	continue;
      }else if(board[x-i][y-i]==myStone){
	//flip(myStone,x,y,x-i,y-i);
	flag=1;
	return 0;
      }else{
	break;
      }
    }
  }
  
  //右下を確認
  if(x<6 && y<6 && board[x+1][y+1]==peerStone){
    for(int i=1;(x+i)<=7 && (y+i)<=7;i++){
      if(board[x+i][y+i]==peerStone){
	continue;
      }else if(board[x+i][y+i]==myStone){
	//flip(myStone,x,y,x+i,y+i);
	flag=1;
	return 0;
      }else{
	break;
      }
    }
  }
  
  //右上を確認
  if(x<6 && y>1 && board[x+1][y-1]==peerStone){
    for(int i=1;(x+i)<=7 && (y-i)>=0;i++){
      if(board[x+i][y-i]==peerStone){
	continue;
      }else if(board[x+i][y-i]==myStone){
	//flip(myStone,x,y,x+i,y-i);
	flag=1;
	return 0;
      }else{
	break;
      }
    }
  }
  
  //左下を確認
  if(x>1 && y<6 && board[x-1][y+1]==peerStone){
    for(int i=1;(x-i)>=0 && (y+i)<=7;i++){
      if(board[x-i][y+i]==peerStone){
	continue;
      }else if(board[x-i][y+i]==myStone){
	//flip(myStone,x,y,x-i,y+i);
	flag=1;
	return 0;
      }else{
	break;
      }
    }
  }
  if(flag==0){
    return -1;
  }

  return 0;
}



//終盤用の
double Board::calcSolutionForFinal(char myStone,int& x,int& y){
  
  char peerStone;
  if(myStone=='x') peerStone='o';
  if(myStone=='o') peerStone='x';

  if(isEnd()){
    if(countMyStones(myStone)-countMyStones(peerStone)>0){
      return 1.0;
    }else{
      return 0.0;
    }
  }
  
  
  std::vector<int> myX,myY,peerX,peerY;
  int check = canSetStones(myStone,myX,myY);
  int check2;//checkとcheck2はおけるところがあるか確認するよう
  
  Board board2 = *this;//確認
  Board board3 = board2;
  int nextX,nextY;//値は必要ない
  
  std::vector<int> num,num2;//置ける数を格納する

  if(check!=0){//置けるところがあった場合
    auto i = myX.begin();
    for(auto j = myY.begin();j<myY.end();j++){
      board2.setStone(myStone,*i,*j);
      check2 = board2.canSetStones(peerStone,peerX,peerY);
      board3 = board2;
      
      if(check2!=0){//置けるところがあった場合
	auto k = peerX.begin();
	for(auto l = peerY.begin();l<peerY.end();l++){
	  board3.setStone(peerStone,*k,*l);
	  num.push_back(board3.calcSolutionForFinal(myStone,nextX,nextY));
	  
	  board3 = board2;
	  k++;
	}
      }else{//置けるところがなかった場合
	num.push_back(board3.calcSolutionForFinal(myStone,nextX,nextY));
      }

      peerX.clear();
      peerY.clear();
      num2.push_back(*std::min_element(num.begin(),num.end()));
      num.clear();
      board2 = *this;
      i++;
    }
  }else{//TODO自分が置けるところがなかったとき
    return 0;
  }

  auto max = std::max_element(num2.begin(),num2.end());
  int maxIndex = std::distance(num2.begin(),max);
  x = myX[maxIndex];
  y = myY[maxIndex];
  
  return *max;
}
     

int Board::calcSolutionForMiddle(char myStone,int counter,int width,int& x,int& y){
  char peerStone;
  if(myStone=='x') peerStone='o';
  if(myStone=='o') peerStone='x';

  if(counter+width>=30){
    width = 30 - counter;
  }
  
  //置くことのできる箇所の数を返す
  if(width==0){
    //showBoard();
    //std::cout << getScore(myStone) << std::endl;
    return getScore(myStone);
  }
  
  std::vector<int> myX,myY,peerX,peerY;
  int check = canSetStones(myStone,myX,myY);
  int check2;//checkとcheck2はおけるところがあるか確認するよう
  
  Board board2 = *this;//確認
  Board board3 = board2;
  int nextX,nextY;//値は必要ない
  
  std::vector<int> num,num2;//置ける数を格納する

  if(check!=0){//置けるところがあった場合
    auto i = myX.begin();
    for(auto j = myY.begin();j<myY.end();j++){
      
      assert(board2.setFakeStone(myStone,*i,*j)==0);//デバッグ用

      board2.setStone(myStone,*i,*j);
      check2 = board2.canSetStones(peerStone,peerX,peerY);
      board3 = board2;

      
      if(check2!=0){//置けるところがあった場合
	auto k = peerX.begin();
	for(auto l = peerY.begin();l<peerY.end();l++){
	  
	  assert(board3.setFakeStone(peerStone,*k,*l)==0);//デバッグ用

	  board3.setStone(peerStone,*k,*l);
	  num.push_back(board3.calcSolutionForMiddle(myStone,counter+1,width-1,nextX,nextY));
	  
	  board3 = board2;
	  k++;
	}
      }else{//置けるところがなかった場合
	num.push_back(board3.calcSolutionForMiddle(myStone,counter+1,width-1,nextX,nextY));
      }

      peerX.clear();
      peerY.clear();
      num2.push_back(*std::min_element(num.begin(),num.end()));
      num.clear();
      board2 = *this;
      i++;
    }
  }else{//TODO自分が置けるところがなかったとき
    return 0;
  }

  auto max = std::max_element(num2.begin(),num2.end());
  int maxIndex = std::distance(num2.begin(),max);
  x = myX[maxIndex];
  y = myY[maxIndex];
  
  return *max;
}
  
void Board::autoSetStone(char myStone,int counter,int border,int width){
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

//置く場所があればその数を、なければ0をかえす
int Board::canSetStones(char myStone) const{
  int count=0;
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(setFakeStone(myStone,i,j)==0){
	count++;
      }
    }
  }
  return count;
}

//置く場所があればその数を、なければ0をかえす
int Board::canSetStones(char myStone,std::vector<int>& x,std::vector<int>& y){  
  int count=0;
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(setFakeStone(myStone,i,j)==0){
	x.push_back(i);
	y.push_back(j);
	count++;
      }
    }
  }
  return count;
}

int Board::countMyStones(char myStone) const{
  int num=0;
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(board[i][j]==myStone) num++;
    }
  }
  return num;
}

bool Board::isCorner(int i,int j) const{
  if(i==0 && j==0) return true;
  if(i==0 && j==7) return true;
  if(i==7 && j==7) return true;
  if(i==7 && j==0) return true;

  return false;
}

bool Board::isEnd() const{
  int num=0,num2=0,num3=0;
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(board[i][j]==' ') num++;
      if(board[i][j]=='x') num2++;
      if(board[i][j]=='o') num3++;
    }
  }
  if(num==0) return true;
  if(num2==0 || num3==0) return true;

  return false;
}

int Board::getScore(char myStone){
  int score=0;
  static const int CORNER_SCORE=100;
  static const int PRE_CORNER_SCORE = -80;
  char peerStone;
  if(myStone=='x'){
    peerStone='o';
  }else{
    peerStone='x';
  }

  
  if(board[0][0]==myStone) score += CORNER_SCORE;
  if(board[0][0]==peerStone) score -= CORNER_SCORE;
  if(board[0][7]==myStone) score += CORNER_SCORE;
  if(board[0][7]==peerStone) score -= CORNER_SCORE;
  if(board[7][7]==myStone) score += CORNER_SCORE;
  if(board[7][7]==peerStone) score -= CORNER_SCORE;
  if(board[7][0]==myStone) score += CORNER_SCORE;
  if(board[7][0]==peerStone) score -= CORNER_SCORE;     
  if(board[1][1]==myStone) score += PRE_CORNER_SCORE;
  if(board[1][1]==peerStone) score -= PRE_CORNER_SCORE;
  if(board[1][6]==myStone) score += PRE_CORNER_SCORE;
  if(board[1][6]==peerStone) score -= PRE_CORNER_SCORE;
  if(board[6][6]==myStone) score += PRE_CORNER_SCORE;
  if(board[6][6]==peerStone) score -= PRE_CORNER_SCORE;
  if(board[6][1]==myStone) score += PRE_CORNER_SCORE;
  if(board[6][1]==peerStone) score -= PRE_CORNER_SCORE;
  
  score = score + canSetStones(myStone) - canSetStones(peerStone);
  return score;
  
}
//TODO:返り値確認 
void Board::operator=(const Board b){
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      board[i][j] = b.board[i][j];
    }
  }
}

char Board::whoWin() const{
  if((countMyStones('x')-countMyStones('o'))>0){
    return 'x';
  }else{
    return 'o';
  }
}
    
    
