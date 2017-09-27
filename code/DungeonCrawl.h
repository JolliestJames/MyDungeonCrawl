#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>

using namespace std;

class DungeonCrawl
{
	private:
		char Player, Traps, Move, Goal;
		char **Field;
		int xPos, yPos, Rows, Columns;
		string Status;

	public:
		DungeonCrawl(char p, char t, char g);
		void MakePlayer(char p);
		void SetTraps(char t);
		void PrintField();
		void MovePlayer(char m);		
		void CheckStatus();
		void Game();
		void DeallocateField();
};

void DungeonCrawl::DeallocateField()
{
	for(int i = 0; i < Rows; i++)
	{
		delete Field[i];
	}
	delete Field;
}

void DungeonCrawl::CheckStatus()
{
	if(Status == "dead")
	{
		cout << "You stepped on a trap, now you're " << Status << "! Game over.\n\n";
	}
	else if(Status == "Victory!")
	{
		cout << Status << " You made it through the dungeon!\n";
	}
	else if(Status == "quit")
	{
		cout << "You " << Status << ". Wow...\n";
	}
	else
	{
		cout << "You carry on through the dungeon. What's your next move?\n";
		cout << "Enter <w> to move up, <s> to move down, <a> to move left, <d> to move right, and <q> to quit: ";
	}
}

void DungeonCrawl::MakePlayer(char p)
{
	Player = p;
	Field[yPos][xPos] = Player;
}

void DungeonCrawl::SetTraps(char t)
{
	Traps = t;
	int r, c;
	srand(time(NULL));
	int numTraps = rand()%30+15;

	for(int i = 0; i < numTraps; i++)
	{
		r = rand()%Rows;
		c = rand()%Columns;
		if(Field[r][c] != Player && Field[r][c] != Goal)
		{
			Field[r][c] = Traps;	
		}
	}
}

void DungeonCrawl::PrintField()
{
	cout << endl;

	for(int i = 0; i < Rows; i++)
	{
		for(int j = 0; j < Columns; j++)
		{
			cout << Field[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

DungeonCrawl::DungeonCrawl(char p, char t, char g)
{
	xPos = 0;
	yPos = 0;
	Status = "Continue";
	srand(time(NULL));
	Rows = rand() % 20+10;
	srand(time(NULL));
	Columns = rand() % 20+10;
	Goal = g;

	Field = new char*[Rows];

	for(int i = 0; i < Rows; i++)
	{
		Field[i] = new char[Columns];
	}

	for(int i = 0; i < Rows; i++)
	{
		for(int j = 0; j < Columns; j++)
		{
			Field[i][j] = '.';
		}
	}

	Field[Rows-1][Columns-1] = Goal;

	MakePlayer(p);
	SetTraps(t);	
}


void DungeonCrawl::MovePlayer(char m)
{
	Move = m;
	bool MoveIsValid = true;
	
	if(Move == 'd' && xPos != Columns-1)
	{
		xPos += 1;
	}
	else if(Move == 'a' && xPos != 0)
	{
		xPos -= 1;
	}
	else if(Move == 'w' && yPos != 0)
	{
		yPos -= 1;
	}
	else if(Move == 's' && yPos != Rows-1)
	{
		yPos += 1;
	}
	else if(Move == 'q')
	{
		Status = "quit";
	}
	else
	{
		cout << "Not a valid move! Try again\n";
		MoveIsValid = false;
	}

	if(Field[yPos][xPos] == Traps)
	{
		Status = "dead";
		Field[yPos][xPos] = Player;
	}
	else if(Field[yPos][xPos] == Goal)
	{
		Status = "Victory!";
		Field[yPos][xPos] = Player;
	}
	else
	{
		Field[yPos][xPos] = Player;
	}

	if(Move == 'd')
	{
		Field[yPos][xPos - 1] = '.';
	}
	else if(Move == 'a')
	{
		Field[yPos][xPos + 1] = '.';
	}
	else if(Move == 'w')
	{
		Field[yPos + 1][xPos] = '.';
	}
	else if(Move == 's')
	{
		Field[yPos - 1][xPos] = '.';
	}
}

void DungeonCrawl::Game()
{

	char m;

	cout << "Welcome to Dungeon Crawl. Reach the " << Goal << " to win!" << endl;

	PrintField();

	cout << "Enter <w> to move up, <s> to move down, <a> to move left, <d> to move right, and <q> to quit: ";

	while(Status == "Continue")
	{
		cin >> m;
		
		MovePlayer(m);
		
		PrintField();

		CheckStatus();
	}
	DeallocateField();
}
