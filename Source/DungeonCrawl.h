#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

//Creating class(game) DungeonCrawl
class DungeonCrawl{
	
	private:
		char Player, Traps, Move, Goal;
		char **Field;
		int xPos, yPos, Rows, Columns;
		string Status;

	public:
		//Constructor takes player character, traps, # of traps, and size of field
		DungeonCrawl(char p, char t, char g);
		char MakePlayer(char p);
		char SetTraps(char t);
		void PrintField();
		bool MovePlayer(char m);		
		void CheckStatus();
		void Game();
		void ClearField();
};

void DungeonCrawl::ClearField(){

	for(int i = 0; i < Rows; i++){
		delete Field[i];
	}

	delete Field;
}

//Checks to see if the player died, won, or quit
void DungeonCrawl::CheckStatus(){
	
	if(Status == "dead"){
		cout << "You stepped on a trap, now you're " << Status << "! Game over.\n\n";
	}else if(Status == "Victory!"){
		cout << Status << " You made it through the dungeon!\n";
	}else if(Status == "quit"){
		cout << "You " << Status << ". Wow...\n";
	}else{
		cout << "You carry on through the dungeon. What's your next move?\n";
		cout << "Enter <w> to move up, <s> to move down, <a> to move left, <d> to move right, and <q> to quit: ";
	}
		
}

//Creating player and inserting them into the board
char DungeonCrawl::MakePlayer(char p){
	
	Player = p;

	Field[yPos][xPos] = Player;

}

//Setting traps
char DungeonCrawl::SetTraps(char t){

	Traps = t;

	int r, c;

	srand(time(NULL));
	int numTraps = rand()%30+15;

	for(int i = 0; i < numTraps; i++){
		r = rand()%Rows;
		c = rand()%Columns;
		if(Field[r][c] != Player && Field[r][c] != Goal){
			Field[r][c] = Traps;	
		}
	}
}

//Printing the game/field
void DungeonCrawl::PrintField(){

	cout << endl;

	for(int i = 0; i < Rows; i++){
		for(int j = 0; j < Columns; j++){
			cout << Field[i][j];
		}cout << endl;
	}cout << endl;

}

//Initializing game
DungeonCrawl::DungeonCrawl(char p, char t, char g){
		
	xPos = 0;
	yPos = 0;
	Status = "Continue";
	srand(time(NULL));
	Rows = rand() % 20+10;
	srand(time(NULL));
	Columns = rand() % 20+10;
	Goal = g;

	//Allocating the rows and columns of the field	
	Field = new char*[Rows];

	for(int i = 0; i < Rows; i++){
		Field[i] = new char[Columns];
	}

	//Setting all parts of the board to '.'
	for(int i = 0; i < Rows; i++){
		for(int j = 0; j < Columns; j++){
			Field[i][j] = '.';
		}
	}

	//Setting goal
	Field[Rows-1][Columns-1] = Goal;

	MakePlayer(p);
	SetTraps(t);
	
}


bool DungeonCrawl::MovePlayer(char m){

	Move = m;

	if(Move == 'd' && xPos != Columns-1){
		xPos += 1;
	}else if(Move == 'a' && xPos != 0){
		xPos -= 1;
	}else if(Move == 'w' && yPos != 0){
		yPos -= 1;
	}else if(Move == 's' && yPos != Rows-1){
		yPos += 1;
	}else if(Move == 'q'){
		Status = "quit";
	}else{
		cout << "Not a valid move! Try again\n";
		return 0;
	}

	if(Field[yPos][xPos] == Traps){
		Status = "dead";
		Field[yPos][xPos] = Player;
	}else if(Field[yPos][xPos] == Goal){
		Status = "Victory!";
		Field[yPos][xPos] = Player;
	}else{
		Field[yPos][xPos] = Player;
	}

	if(Move == 'd'){
		Field[yPos][xPos - 1] = '.';
	}else if(Move == 'a'){
		Field[yPos][xPos + 1] = '.';
	}else if(Move == 'w'){
		Field[yPos + 1][xPos] = '.';
	}else if(Move == 's'){
		Field[yPos - 1][xPos] = '.';
	}
}

void DungeonCrawl::Game(){

	char m;

	cout << "Welcome to Dungeon Crawl. Reach the " << Goal << " to win!" << endl;

	PrintField();

	cout << "Enter <w> to move up, <s> to move down, <a> to move left, <d> to move right, and <q> to quit: ";

	while(Status == "Continue"){
	
		cin >> m;
		
		MovePlayer(m);
		
		PrintField();

		CheckStatus();
	
	}ClearField();
	
}
