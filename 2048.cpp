#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>

using namespace std;

class myPair{
public:
	int x;
	int y;
	myPair(int a, int b){
		x=a;
		y=b;
	}
};



class Board{
public:
	int board[4][4];
	void start();
	void print();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	bool addNum();
	bool merged[4][4];
	bool noUp();
	bool noDown();
	bool noLeft();
	bool noRight();
	int score;

	myPair** emptySquares(){
		myPair** squares=new myPair*[17];
		int size = 0;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if (this->board[i][j]==0){
					squares[size]=new myPair(i,j);
					size++;
				}
			}
		}
		squares[size]=NULL;
		return squares;
	}

	
};
//return a null-terminated array of myPair objects
//that represents all of the empty squares on board b

int main(){
	string input;
	string again;
	bool gameOver = false;

	Board grid;
	grid.start();
	grid.print();


	do{
		if(grid.noUp()&&grid.noRight() && grid.noDown() && grid.noLeft()){
			gameOver = true;
			cout << "GAME OVER" << endl << "Play Again? ";
			getline(cin, again);
			if(again == "yes"){
				continue;
			}

		}
		else{
			cout << "Enter direction: ";
			getline(cin, input);

			if(input == "w"){
				if(grid.noUp() == true){
					continue;
				}
				else {
					grid.moveUp();
				}
			}

			else if(input == "s"){
				if(grid.noDown() == true){
					continue;
				}
				else{
					grid.moveDown();
				}
			}

			else if(input == "a"){
				if(grid.noLeft() == true){
					continue;
				}
				else{
					grid.moveLeft();
				}

			}

			else if(input == "d") {
				if(grid.noRight() == true){
					continue;
				}
				else{
					grid.moveRight();
				}
			}
			else{
				continue;
			}

			grid.addNum();
			grid.print();
		}
	}while(!gameOver);


	system("pause");
	return 0;

}



void Board::start() {
	srand(time(NULL));
	int firstRow, firstCol, secondRow, secondCol;

	for(int i = 0; i < 4; i++){
		for(int j=0; j<4; j++){
			board[i][j] = 0;
			merged[i][j] = false;
		}
	}

	firstRow = rand()%4;
	firstCol = rand()%4;

	secondRow = rand()%4;
	secondCol = rand()%4;

	while(firstRow == secondRow && firstCol == secondCol) {
		secondRow = rand()%4;
		secondCol = rand()%4;
	}

	board[firstRow][firstCol] = 2;
	board[secondRow][secondCol] = 2;

	cout << "Controls: w - up, a - left, s - down, d - right" << endl;
}





void Board::print(){

	for(int i = 0; i < 4; i++){
		for(int j=0; j < 4; j++){
			if(board[j][i]==0){
				printf("%6c",'_');
			}
			else{
				printf("%6d", board[j][i]);
			}
		}
		cout << endl<<endl;
	}

}

/*
for row in board:
for square in row:
if(square is occupied):
if(above square is clear):
move square all the way up
else:
for all squares above square:
if (square is not occupied) move up
else if square is occupied by the same thing: combine them
else don't move up

*/

void Board::moveUp() {


	for( int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			merged[i][j] = false;
			if(board[i][j] != 0){
				for(int k = j-1; k>=0; k--){
					if(board[i][0] == 0){
						board[i][0] = board[i][j];
						board[i][j] = 0;
					}
					else{

						if(board[i][j-1] != 0 && board[i][j-1] != board[i][k]){
							break;
						}


						else if(board[i][k] == board[i][j] && merged[i][k] == false){
							board[i][k] = board[i][j] * 2;
							board[i][j] = 0;
							merged[i][k] = true;
							break;
						}
						else if(board[i][k]!=0&&k!=j-1){
							board[i][k+1]=board[i][j];
							board[i][j]=0;
							break;
						}


					}
				}
			}
		}
	}
}

void Board::moveDown(){

	for( int i = 0; i < 4; i++){
		for(int j = 3; j >= 0; j--){
			merged[i][j] = false;
			if(board[i][j] != 0){

				for(int k = j+1; k<4; k++){

					if(board[i][3] == 0){
						board[i][3] = board[i][j];
						board[i][j] = 0;
					}

					else{
						if(board[i][j+1] !=0 && board[i][j+1] != board[i][k]){
							break;
						}
						else if(board[i][k] == board[i][j] && merged[i][k] == false){
							board[i][k] = board[i][j] * 2;
							board[i][j] = 0;
							merged[i][k] = true;
							break;
						}
						else if(board[i][k]!=0&&k!=j+1){
							board[i][k-1]=board[i][j];
							board[i][j] = 0;
							break;
						}
					}
				}
			}
		}
	}
}


void Board::moveLeft(){
	for( int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			merged[i][j] = false;
			if(board[i][j] != 0){
				for(int k = i-1; k>=0; k--){
					if(board[0][j] == 0){
						board[0][j] = board[i][j];
						board[i][j] = 0;
					}
					else{

						if(board[i-1][j] != 0 && board[i-1][j] != board[k][j]){
							break;
						}

						else if(board[k][j] == board[i][j] && merged[k][j] == false){
							board[k][j] = board[i][j] * 2;
							board[i][j] = 0;
							merged[k][j] = true;
							break;
						}

						else if(board[k][j]!=0&&k!=i-1){
							board[k+1][j]=board[i][j];
							board[i][j]=0;
							break;
						}

					}
				}
			}
		}
	}
}

void Board::moveRight(){
	for( int i = 3; i >= 0 ; i--){
		for(int j = 0; j <4; j++){
			merged[i][j] = false;
			if(board[i][j] != 0){

				for(int k = i+1; k<4; k++){

					if(board[3][j] == 0){
						board[3][j] = board[i][j];
						board[i][j] = 0;
					}

					else{
						if(board[i+1][j] !=0 && board[i+1][j] != board[k][j]){
							break;
						}
						else if(board[k][j] == board[i][j] && merged[k][j] == false){
							board[k][j] = board[i][j] * 2;
							board[i][j] = 0;
							merged[k][j] = true;
							break;
						}
						else if(board[k][j]!=0&&k!=i+1){
							board[k-1][j]=board[i][j];
							board[i][j] = 0;
							break;
						}
					}
				}
			}
		}
	}
}

bool Board::addNum(){
	srand(time(NULL));
	myPair** squares=emptySquares();
	int size;
	int randNum;
	for(size=0;squares[size]!=NULL;size++){
		;
	}
	randNum = rand()%size;
	myPair* square=squares[randNum];
	board[square->x][square->y]=((rand()%2)+1)*2;
	return true;
}

bool Board::noUp(){
	bool gotZero;
	int last;
	for(int i=0;i<4;i++){
		gotZero=false;
		last=0;
		for(int j=0;j<4;j++){
			if(board[i][j]==0){
				gotZero=true;
				last=0;
			}
			else{
				if(gotZero){
					return false;
				}
				else if(board[i][j]==last){
					return false;
				}
				last=board[i][j];
			}
		}	
	}
	return true;
}

bool Board::noDown(){
	bool gotZero;
	int last;
	for(int i=0;i<4;i++){
		gotZero=false;
		last=0;
		for(int j=3;j>=0;j--){
			if(board[i][j]==0){
				gotZero=true;
				last=0;
			}
			else{
				if(gotZero){
					return false;
				}
				else if(board[i][j]==last){
					return false;
				}
				last=board[i][j];
			}
		}	
	}
	return true;
}

bool Board::noLeft(){
	bool gotZero;
	int last;
	for(int i=0;i<4;i++){
		gotZero=false;
		last=0;
		for(int j=0;j<4;j++){
			if(board[j][i]==0){
				gotZero=true;
				last=0;
			}
			else{
				if(gotZero){
					return false;
				}
				else if(board[j][i]==last){
					return false;
				}
				last=board[j][i];
			}
		}	
	}
	return true;
}

bool Board::noRight(){
	bool gotZero;
	int last;
	for(int i=0;i<4;i++){
		gotZero=false;
		last=0;
		for(int j=3;j>=0;j--){
			if(board[j][i]==0){
				gotZero=true;
				last=0;
			}
			else{
				if(gotZero){
					return false;
				}
				else if(board[j][i]==last){
					return false;
				}
				last=board[j][i];
			}
		}	
	}
	return true;
}





