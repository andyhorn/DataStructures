/*
Name:			Andrew Horn
Date:			2/3/2018
Course:			CST211 - Data Structures
Filename:		Minesweeper.cpp

Overview:		Provides the main function that drives the Minesweeper game. A Minesweeper engine is 
				instantiated in main, and the engine drives all actual gameplay.
*/

#include "stdafx.h"
#include "MGameEngine.h"

int main()
{
	int boardSize = 0;
	int difficulty = 0;
	bool replay = true;
	char playAgain = 'Y';
	MGameEngine *game = nullptr;

	cout << "WELCOME TO MINESWEEPER!\n\n" << endl;

	do
	{
		bool cheat = false;
		cout << "Select a size: \n[1] 5x5\n[2] 10x10\n[3] 15x15\nSelection: ";
		cin >> boardSize;
		cout << "Choose your difficulty:\n[1]Easy\n[2]Medium\n[3]Hard\n[4]Expert\nSelection: ";
		cin >> difficulty;

		try
		{
			if ((boardSize > 0 && boardSize < 4) && ((difficulty > 0 && difficulty < 5) || difficulty == 99))
			{
				//bool cheat = false;
				if (difficulty == 99)
				{
					cheat = true;
					difficulty = 2;
				}
				cout << "Thank you! Let's begin!\n\n" << endl;
				switch (boardSize)
				{
				case 1: game = new MGameEngine(5, 5, difficulty);
					if (cheat)
						game->cheatMode();
					game->PlayGame();
					break;
				case 2: game = new MGameEngine(10, 10, difficulty);
					if (cheat)
						game->cheatMode();
					game->PlayGame();
					break;
				case 3: game = new MGameEngine(15, 15, difficulty);
					if (cheat)
						game->cheatMode();
					game->PlayGame();
					break;
				}
				cout << "Play again? Y/N: ";
				cin >> playAgain;
				if (toupper(playAgain) != 'Y')
					replay = false;
			}
			else
			{
				cout << "Invalid Parameters\nTry again." << endl;
				replay = true;
			}
		}
		catch (Exception e)
		{
			cout << e;
		}
			
	} while (replay);	
	cout << "Goodbye!" << endl;
	delete game;
    return 0;
}

