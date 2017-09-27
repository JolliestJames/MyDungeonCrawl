#include <iostream>
#include <stdio.h>
#include "DungeonCrawl.h"

using namespace std;

int main(void)
{
	char Player, Trap, Goal;
	
	DungeonCrawlGameState *GameState = {};	

	cout << "What letter of the alphabet represents you the best? ";
	cin >> Player;

	cout << "What letter of the alphabet are you afraid of most? ";
	cin >> Trap;

	while(Trap == Player)
	{
		cout << "Are you afraid of yourself? This isn't a psychological horror game. Enter something else: ";
		cin >> Trap;
	}

	cout << "What letter are you most attracted to? ";
	cin >> Goal;

	while(Goal == Trap || Goal == Player)
	{
		if(Goal == Trap)
		{
			cout << "That's really kinky. I think you should pick a different letter: ";
			cin >> Goal;
		}
		else if(Goal == Player)
		{
			cout << "You're most attracted to yourself? Get the fuck out of here, me too!\n\nSeriously though, pick a different letter: ";
			cin >> Goal;
		}
	}
	
	DungeonCrawlCreateGame(GameState, Goal, Player, Trap);
	
	char Move;
	
	cout << "Welcome to Dungeon Crawl. Reach the " << Goal << " to win!" << endl;

	DungeonCrawlSetTraps(GameState);
	DungeonCrawlPrintField(GameState);

	cout << "Enter <w> to move up, <s> to move down, <a> to move left, <d> to move right, and <q> to quit: ";

	while(GameState->Status == 1)
	{
		cin >> Move;
		
		DungeonCrawlMovePlayer(GameState, Move);
		
		DungeonCrawlPrintField(GameState);

		DungeonCrawlProcessStatus(GameState);
	}
	
	DungeonCrawlDeallocateField(GameState);
}
