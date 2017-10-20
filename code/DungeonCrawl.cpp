#include <iostream>
#include "DungeonCrawl.h"

using namespace std;

int main()
{
	char c, t, g;

	cout << "What letter of the alphabet represents you the best? ";
	cin >> c;

	cout << "What letter of the alphabet are you afraid of most? ";
	cin >> t;

	while(t == c)
	{
		cout << "Are you afraid of yourself? This isn't a psychological horror game. Enter something else: ";
		cin >> t;
	}

	cout << "What letter are you most attracted to? ";
	cin >> g;

	while(g == t || g == c)
	{
		if(g==t)
		{
			cout << "That's really weird. I think you should pick a different letter: ";
			cin >> g;
		}
		else if(g==c)
		{
			cout << "You're most attracted to yourself? Get out of here, me too!\n\nSeriously though, pick a different letter: ";
			cin >> g;
		}
	}

	DungeonCrawl newGame(c, t, g);

	newGame.Game();
	
	return(0);
}
