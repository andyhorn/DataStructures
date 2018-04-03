/*
Name:			Andrew Horn
Date:			2/3/2018
Course:			CST211 - Data Structures
Filename:		MCell.h

Overview:		Most basic class in the Minesweeper game. Cell class contains a bool for whether it is
				hidden or has been uncovered, and whether it contains a mine or is a safe space.
				This class is managed by the MGameBoard class, which contains a 2D array filled with Cells.
*/

#pragma once

class MCell
{
private:
	bool _mine;
	bool _hidden;
	size_t _neighborMines;
	size_t _row;
	size_t _col;
public:
	MCell();
	MCell(bool mine);
	~MCell();
	bool getMine();
	bool getMine() const;
	void setMine(bool mine);
	bool getHidden();
	bool getHidden() const;
	void reveal();
	size_t& getNeighboringMines();
	bool HasMine();
	void setRow(size_t row);
	void setCol(size_t col);
	size_t getRow();
	size_t getRow() const;
	size_t getCol();
	size_t getCol() const;
};

inline MCell::MCell()
	: _mine(false), _hidden(true), _neighborMines(0) {}

inline MCell::MCell(bool mine)
	: _mine(mine), _hidden(true), _neighborMines(0) {}

inline MCell::~MCell() {}

inline bool MCell::getMine() { return _mine; }

inline bool MCell::getMine() const { return _mine; }

inline void MCell::setMine(bool mine) { _mine = mine; }

inline bool MCell::getHidden() { return _hidden; }

inline bool MCell::getHidden() const { return _hidden; }

inline bool MCell::HasMine()
{
	_hidden = false;
	return getMine();
}

inline size_t& MCell::getNeighboringMines() { return _neighborMines; }

inline void MCell::reveal() { _hidden = false; }

inline void MCell::setRow(size_t row) { _row = row; }

inline void MCell::setCol(size_t col) { _col = col; }

inline size_t MCell::getRow() { return _row; }

inline size_t MCell::getRow() const { return _row; }

inline size_t MCell::getCol() { return _col; }

inline size_t MCell::getCol() const { return _col; }
