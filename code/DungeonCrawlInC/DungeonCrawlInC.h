#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <stdint.h>

using namespace std;

struct DungeonCrawlGameState
{
	char Player, Traps, Move, Goal;
	char **Field;
	int XPos, YPos, Rows, Columns, Status; 
};

static void
DungeonCrawlSetTraps
(
	DungeonCrawlGameState *GameState
)
{
	int r, c;
	srand(time(NULL));
	int numTraps = (int)rand()%30+15;
	for(int i = 0; i < numTraps; i++)
	{
		r = rand()%(GameState->Rows);
		c = rand()%(GameState->Columns);
		
		if(GameState->Field[r][c] != GameState->Player && GameState->Field[r][c] != GameState->Goal)
		{
			GameState->Field[r][c] = GameState->Traps;	
		}
	}
}

static void
DungeonCrawlCreateGame
(
	DungeonCrawlGameState *GameState, char g, char p, char t
)
{
	GameState->Goal = g;
	GameState->Traps = t;
	GameState->Player = p;
	
	GameState->XPos = 0;
	GameState->YPos = 0;
	GameState->Status = true;
	srand(time(NULL));
	GameState->Rows = rand() % 20+10;
	srand(time(NULL));
	GameState->Columns = rand() % 20+10;
	
	GameState->Field = (char **)malloc(GameState->Rows*sizeof(int));

	for(int i = 0; i < GameState->Rows; i++)
	{
		GameState->Field[i] = (char *)malloc(GameState->Columns*sizeof(int));
	}

	for(int i = 0; i < GameState->Rows; i++)
	{
		for(int j = 0; j < GameState->Columns; j++)
		{
			GameState->Field[i][j] = '.';
		}
	}

	GameState->Field[GameState->Rows-1][GameState->Columns-1] = GameState->Goal;
	GameState->Field[GameState->YPos][GameState->XPos] = GameState->Player;
	DungeonCrawlSetTraps(GameState);
}

static void 
DungeonCrawlPrintField(DungeonCrawlGameState *GameState)
{
	cout << endl;

	for(int i = 0; i < GameState->Rows; i++)
	{
		for(int j = 0; j < GameState->Columns; j++)
		{
			cout << GameState->Field[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

static void 
DungeonCrawlDeallocateField(DungeonCrawlGameState *GameState)
{
	for(int i = 0; i < GameState->Rows; i++)
	{
		free(GameState->Field[i]);
	}

	free(GameState->Field);
}

static void
DungeonCrawlProcessStatus(DungeonCrawlGameState *GameState)
{
	if(GameState->Status == 1)
	{
		cout << "You stepped on a trap, now you're dead! Game over.\n\n";
	}
	else if(GameState->Status == 2)
	{
		cout << "Victory! You made it through the dungeon!\n";
	}
	else if(GameState->Status == 3)
	{
		cout << "You quit. Wow...\n";
	}
	else
	{
		cout << "You carry on through the dungeon. What's your next move?\n";
		cout << "Enter <w> to move up, <s> to move down, <a> to move left, <d> to move right, and <q> to quit: ";
	}	
}

static int
DungeonCrawlMovePlayer(DungeonCrawlGameState *GameState, char m)
{
	GameState->Move = m;

	if(GameState->Move == 'd' && GameState->XPos != GameState->Columns-1)
	{
		GameState->XPos += 1;
	}
	else if(GameState->Move == 'a' && GameState->XPos != 0)
	{
		GameState->XPos -= 1;
	}
	else if(GameState->Move == 'w' && GameState->YPos != 0)
	{
		GameState->YPos -= 1;
	}
	else if(GameState->Move == 's' && GameState->YPos != GameState->Rows-1)
	{
		GameState->YPos += 1;
	}
	else if(GameState->Move == 'q')
	{
		//3 = Quit
		GameState->Status = 3;
	}
	else
	{
		cout << "Not a valid move! Try again\n";
		return(0);
	}

	if(GameState->Field[GameState->YPos][GameState->XPos] == GameState->Traps)
	{
		//1 = Gameover
		GameState->Status = 1;
		GameState->Field[GameState->YPos][GameState->XPos] = GameState->Player;
	}
	else if(GameState->Field[GameState->YPos][GameState->XPos] == GameState->Goal)
	{
		//2 = Victory
		GameState->Status = 2;
		GameState->Field[GameState->YPos][GameState->XPos] = GameState->Player;
	}
	else
	{
		GameState->Field[GameState->YPos][GameState->XPos] = GameState->Player;
	}

	if(GameState->Move == 'd')
	{
		GameState->Field[GameState->YPos][GameState->XPos - 1] = '.';
	}
	else if(GameState->Move == 'a')
	{
		GameState->Field[GameState->YPos][GameState->XPos + 1] = '.';
	}
	else if(GameState->Move == 'w')
	{
		GameState->Field[GameState->YPos + 1][GameState->XPos] = '.';
	}
	else if(GameState->Move == 's')
	{
		GameState->Field[GameState->YPos - 1][GameState->XPos] = '.';
	}
	return(1);
}
