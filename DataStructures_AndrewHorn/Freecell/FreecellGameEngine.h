#pragma once

#include "FreecellBoard.h"
#include <iomanip>

using std::setw;

class FreecellGameEngine
{
private:
	FreecellBoard _board;
public:
	FreecellGameEngine();
	~FreecellGameEngine();
	void PlayGame();
	void PlayCard();
	bool GameOver();
	bool HasQuit();
	bool Quit();
	void Restart();
};

inline FreecellGameEngine::FreecellGameEngine() {}

inline FreecellGameEngine::~FreecellGameEngine() {}

inline void FreecellGameEngine::PlayGame()
{
	while (!GameOver() && !HasQuit())
	{
		_board.PrintBoard();
		PlayCard();
	}
	if (Quit())
		cout << "\nGoodbye!" << endl;
	else
		cout << "\nYou Win!" << endl;
}

inline void FreecellGameEngine::PlayCard()
{
	int from = 0, card = 0, to = 0;
	cout << cyanOnBlack << std::left << setw(10) << "Source:" 
		<< setw(15) << "[1] Free Cell" 
		<< setw(15) << "[2] Home Cell" 
		<< setw(15) << "[3] Play Cards\n"
		<< setw(10) << "Options:" 
		<< setw(15) << "[8] Restart" 
		<< setw(15) << "[9] Quit Game" << "\nSelection: ";
	std::cin >> from;
	std::cin.ignore(256, '\n');
	std::cin.clear();
	if (from > 0 && from < 10)
	{
		if (from == QUIT)
			Quit();
		else if (from == RESTART)
			Restart();
		else
		{
			cout << "Destination: " << setw(15) << "[1] Free Cell" 
				<< setw(15) << "[2] Home Cell"
				<< setw(15) << "[3] Play Cards" << "\nSelection: ";
			std::cin >> to;
			std::cin.ignore(256, '\n');
			std::cin.clear();

			cout << "Card: C";
			std::cin >> card;
			std::cin.ignore(256, '\n');
			std::cin.clear();

			from--;
			to--;
			card--;

			try
			{
				_board.PlayCard(from, to, card);
			}
			catch (Exception &e)
			{
				cout << e << endl;
			}
		}
	}
	else
		cout << "\nInvalid Selection" << endl;
}

inline bool FreecellGameEngine::GameOver() { return _board.GameOver(); }

inline bool FreecellGameEngine::Quit() { _board.PlayerQuit(); return HasQuit(); }

inline bool FreecellGameEngine::HasQuit() { return _board.HasQuit(); }

inline void FreecellGameEngine::Restart() { _board.Restart(); PlayGame(); }