/*
Name:			Andrew Horn
Date:			2/3/2018
Course:			CST211 - Data Structures
Filename:		MGameEngine.h

Overview:		MGameEngine is the engine behind the Minesweeper game. This class contains an MGameBoard
				class, which contains a 2D array filled with Minesweeper Cell objects. This class provides
				the player with gameplay options, and then carries out those instructions, passing them to
				the MGameBoard when appropriate.
*/

#pragma once

#include "MGameBoard.h"
#include "Exception.h"
#include <iostream>
#include <iomanip>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::setfill;
using std::left;
using std::right;
using std::setw;

class MGameEngine
{
private:
	MGameBoard _gameBoard;
	bool _gameOver;
public:
	MGameEngine(int row, int col, int difficulty);
	~MGameEngine();
	void PlayGame();
	const bool IsDone();
	const bool IsDone() const;
	void CheckCell(int row, int col);
	void PrintBoard();
	void cheatMode();
};

inline MGameEngine::MGameEngine(int row, int col, int difficulty)
	: _gameBoard(MGameBoard(row, col, difficulty)), _gameOver(false) {}
//{
//	if (row > 0 && col > 0 && difficulty > 0)
//	{
//		_gameBoard = MGameBoard(row, col, difficulty);
//		_gameOver = false;
//	}
//	else
//		throw Exception("Invalid Parameters");
//}
//	

inline MGameEngine::~MGameEngine() {}

inline void MGameEngine::PlayGame()
{
	int rowChoice = 0;
	int colChoice = 0;
	PrintBoard();

	while (!_gameBoard.isDone() && !_gameOver)
	{
		try
		{
			cout << "Check a Cell!"
				<< "\nRow: ";
			cin >> rowChoice;
			cout << "Column: ";
			cin >> colChoice;

			CheckCell((rowChoice - 1), (colChoice - 1));
		}
		catch (Exception& e)
		{
			cout << e << endl;
		}
	}
	if (_gameBoard.isDone())
	{
		cout << "YOU WIN!" << endl;
		_gameBoard.reveal();
	}
	else
		cout << "GAME OVER!" << endl;
}

inline const bool MGameEngine::IsDone() { return _gameOver; }

inline const bool MGameEngine::IsDone() const { return _gameOver; }

inline void MGameEngine::CheckCell(int row, int col)
{
	if (row >= 0 && row < _gameBoard.getRows())
	{
		if (col >= 0 && col < _gameBoard.getCols())
		{
			_gameOver = _gameBoard.CheckCell(_gameBoard.GetCell(row, col));
			PrintBoard();
		}
		else
			throw Exception("Invalid Column Selection");
	}
	else
		throw Exception("Invalid Row Selection");
}

inline void MGameEngine::PrintBoard()
{
	/* Column Header */
	cout << setw(7) << "Column ";
	for (size_t colHead = 0; colHead < _gameBoard.getCols(); colHead++)
	{
		if (colHead < 9)
			cout << right << setw(2) << std::to_string(colHead + 1) << setw(2) << "";
		else
			cout << right << setw(3) << std::to_string(colHead + 1) << " ";
	}
	cout << endl;

	/* Rows */
	for (size_t row = 0; row < _gameBoard.getRows(); row++)
	{
		cout << left << setw(6) << "Row " + std::to_string(row + 1);
		for (size_t col = 0; col < _gameBoard.getCols(); col++)
		{
			if (_gameBoard.getBoard()[int(row)][(int)col].getHidden())
			{
				cout << "|   ";
			}
			else
			{
				if (_gameBoard.getBoard()[(int)row][(int)col].getMine())
					cout << "| * ";
				else
					cout << "| " << _gameBoard.getBoard()[(int)row][(int)col].getNeighboringMines() << " ";
			}
			if (col == _gameBoard.getCols() - 1)
				cout << "|";
		}
		cout << endl;
	}
}

inline void MGameEngine::cheatMode() { _gameBoard.reveal(); }