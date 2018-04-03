/*
Name:			Andrew Horn
Date:			2/3/2018
Course:			CST211 - Data Structures
Filename:		MGameBoard.h

Overview:		Provides class implementation for a Minesweeper Game Board. Contains a 2D array of 
				Minesweeper Cell objects, and manages the board. Receives instructions from the 
				Minesweeper game engine (MGameEngine), and operates on individual Cells.
*/

#pragma once

#include "Array2D.h"
#include "DList.h"
#include "ForwardIterator.h"
#include "ListIterator.h"
#include "MCell.h"
#include <stdlib.h>
#include <time.h>

class MGameBoard
{
private:
	Array2D<MCell> _board;
	//DList<MCell*> _neighbors;
	//ForwardIterator<MCell*> _cellIterator;
	size_t _numMines;
	size_t _rows;
	size_t _cols;
	size_t _uncovered;
	void initialize(int difficulty);
	DList<MCell*>* getNeighborCells(int row, int col);
public:
	MGameBoard(int row, int col, int difficulty);
	~MGameBoard();
	bool CheckCell(MCell &cell);
	MCell& GetCell(int row, int col);
	MCell& GetCell(int row, int col) const;
	const int getMines();
	const int getMines() const;
	size_t getRows();
	size_t getRows() const;
	size_t getCols();
	size_t getCols() const;
	bool isDone();
	void reveal();
	Array2D<MCell>& getBoard();
};

inline MGameBoard::MGameBoard(int row, int col, int difficulty)
	: _board(Array2D<MCell>(row, col)),	_rows(row), _cols(col), _uncovered(0) { initialize(difficulty); }

inline MGameBoard::~MGameBoard() {}

inline void MGameBoard::initialize(int difficulty)
{
	if (difficulty > 0)
	{
		// Randomly place mines until mineCount == 0
		srand((int)time(NULL));
		_numMines = (_rows * _cols) / (10 / difficulty);
		size_t mineCount = _numMines;
		while (mineCount > 0)
		{
			size_t mineRow = rand() % _rows;
			size_t mineCol = rand() % _cols;
			if (_board[(int)mineRow][(int)mineCol].getMine() != true)
			{
				_board[(int)mineRow][(int)mineCol].setMine(true);
				mineCount--;
			}
		}

		for (size_t row = 0; row < _rows; row++)
			for (size_t col = 0; col < _cols; col++)
			{
				_board[(int)row][(int)col].setRow(row);
				_board[(int)row][(int)col].setCol(col);
				if (_board[(int)row][(int)col].getMine())
				{
					ForwardIterator<MCell*> cellIterator;
					DList<MCell*> *temp = getNeighborCells((int)row, (int)col);
					cellIterator = temp->getHead();

					while (!(cellIterator.IsDone())) // while not at tail
					{
						cellIterator.GetCurrent()->getNeighboringMines() += 1;
						cellIterator.MoveNext();
					}
					cellIterator.GetCurrent()->getNeighboringMines() += 1; // get tail

					cellIterator = nullptr;
					temp->Purge();
					delete temp;
				}
			}
	}
	else
		throw Exception("Invalid Difficulty");
}

inline bool MGameBoard::CheckCell(MCell &cell) 
{ 
	if (!cell.getMine()) // if not a mine
	{
		_uncovered++;
		if (cell.getNeighboringMines() == 0) // and no mines nearby
		{
			DList<MCell*> *neighborList = getNeighborCells((int)cell.getRow(), (int)cell.getCol());
			ForwardIterator<MCell*> cellIterator;
			cellIterator = neighborList->getHead();

			while (!cellIterator.IsDone())
			{
				if (cellIterator.GetCurrent()->getNeighboringMines() == 0 // if also 0 mines nearby
					&& cellIterator.GetCurrent()->getHidden() // and still hidden
					&& !cellIterator.GetCurrent()->getMine()) // and not a mine
				{
					(*cellIterator)->reveal(); // reveal
					CheckCell(*(*cellIterator)); // and check its neighbors
				}

				cellIterator.MoveNext();
			}

			cellIterator = nullptr;
			neighborList->Purge();
			delete neighborList;
		}
	}
	return cell.getMine(); 
}

inline MCell& MGameBoard::GetCell(int row, int col) { _board[row][col].reveal(); return _board[row][col]; }

inline MCell& MGameBoard::GetCell(int row, int col) const { _board[row][col].reveal(); return _board[row][col]; }

inline DList<MCell*>* MGameBoard::getNeighborCells(int row, int col)
{
	DList<MCell*> *cellList = new DList<MCell*>;
	// Need to clean this up, a little verbose.

	if (row != 0)
	{
		cellList->Append(&_board[row - 1][col]); // above neighbor
	}
	if (col != 0)
	{
		cellList->Append(&_board[row][col - 1]); // left neighbor
	}
	if (row < _rows - 1)
	{
		cellList->Append(&_board[row + 1][col]); // bottom neighbor
	}
	if (col < _cols - 1)
	{
		cellList->Append(&_board[row][col + 1]); // right neighbor
	}
	if (row != 0 && col != 0)
	{
		cellList->Append(&_board[row - 1][col - 1]); // top-left neighbor
	}
	if (row != 0 && col < _cols - 1)
	{
		cellList->Append(&_board[row - 1][col + 1]); // top-right neighbor
	}
	if (row < _rows - 1 && col < _cols - 1)
	{
		cellList->Append(&_board[row + 1][col + 1]); // bottom-right neighbor
	}
	if (row < _rows - 1 && col != 0)
	{
		cellList->Append(&_board[row + 1][col - 1]); // bottom-left neighbor
	}

	return cellList;
}

inline const int MGameBoard::getMines() { return static_cast<int>(_numMines); }

inline const int MGameBoard::getMines() const { return static_cast<int>(_numMines); }

inline size_t MGameBoard::getRows() { return _rows; }

inline size_t MGameBoard::getRows() const { return _rows; }

inline size_t MGameBoard::getCols() { return _cols; }

inline size_t MGameBoard::getCols() const { return _cols; }

inline bool MGameBoard::isDone() { return (_uncovered >= ((_rows * _cols) - _numMines)); }

inline void MGameBoard::reveal()
{
	for (size_t row = 0; row < _rows; row++)
		for (size_t col = 0; col < _cols; col++)
			_board[(int)row][(int)col].reveal();

	cout << "Number of mines: " << _numMines << endl;
}

inline Array2D<MCell>& MGameBoard::getBoard() { return _board; }