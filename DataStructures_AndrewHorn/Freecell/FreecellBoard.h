#pragma once

#include "Deck.h"
#include "StackArray.h"
#include "TextColor.h"
#include <iostream>
#include <iomanip>  // setw
#include <string>

using std::cout;
using std::endl;
using std::string;

enum STACKS { FREE, HOME, PLAY, RESTART = 8, QUIT };

class FreecellBoard
{
private:
	bool _quit;
	Deck _deck;
	Array<Card> _freeCells;
	Array<StackArray<Card>> _homeCells;
	Array<StackArray<Card>> _playCards;

	void printHeader(string title, int columns);
	void printRow(const Array<Card> &array);
	void printRow(const Array<StackArray<Card>> &stack);
	void init();
protected:
	const Deck& viewDeck();
	const Deck& viewDeck() const;
	const Array<Card>& viewFreeCells();
	const Array<Card>& viewFreeCells() const;
	const Array<StackArray<Card>>& viewHomeCells();
	const Array<StackArray<Card>>& viewHomeCells() const;
	const Array<StackArray<Card>>& viewPlayCards();
	const Array<StackArray<Card>>& viewPlayCards() const;
public:
	FreecellBoard();
	FreecellBoard(const FreecellBoard &copy);
	~FreecellBoard();

	void PrintBoard();
	bool GameOver();
	void PlayCard(int from, int to, int cardIndex);
	bool HasQuit() const;
	void PlayerQuit();
	void Restart();

	Card GetFreeCardCopy(int index);
	bool SetFreeCard(Card &card);
	void PopFreeCard(int index);
	
	Card GetHomeCardCopy(int index);
	bool SetHomeCard(Card &card);
	void PopHomeCard(int index);

	Card GetPlayCardCopy(int index);
	bool SetPlayCard(Card &card);
	void PopPlayCard(int index);
};

inline const Deck& FreecellBoard::viewDeck() { return _deck; }
inline const Deck& FreecellBoard::viewDeck() const { return _deck; }

inline const Array<Card>& FreecellBoard::viewFreeCells() { return _freeCells; }
inline const Array<Card>& FreecellBoard::viewFreeCells() const { return _freeCells; }

inline const Array<StackArray<Card>>& FreecellBoard::viewHomeCells() { return _homeCells; }
inline const Array<StackArray<Card>>& FreecellBoard::viewHomeCells() const { return _homeCells; }

inline const Array<StackArray<Card>>& FreecellBoard::viewPlayCards() { return _playCards; }
inline const Array<StackArray<Card>>& FreecellBoard::viewPlayCards() const { return _playCards; }

inline FreecellBoard::FreecellBoard()
	: _quit(false) { init(); }

inline FreecellBoard::FreecellBoard(const FreecellBoard &copy)
{
	_deck = copy.viewDeck();
	_quit = copy.HasQuit();
	_freeCells = copy.viewFreeCells();
	_homeCells = copy.viewHomeCells();
	_playCards = copy.viewPlayCards();
}

inline FreecellBoard::~FreecellBoard() {}

inline void FreecellBoard::init()
{
	_deck.shuffle(3);

	_freeCells.setLength(4);

	_homeCells.setLength(4);
	for (size_t i = 0; i < 4; i++)
	{
		_homeCells[(int)i] = StackArray<Card>(14);
		_homeCells[(int)i].Push(Card());
	}

	_playCards.setLength(8);
	for (size_t i = 0; i < 8; i++)
	{
		_playCards[(int)i] = StackArray<Card>(14);
		_playCards[(int)i].Push(Card());
	}

	for (size_t card = 0; card < _deck.getLength(); card++)
		_playCards[card % 8].Push(_deck.Deal());

	cout << cyanOnBlack << "Welcome to FREECELL!" << endl
		<< "\nOBJECTIVE: \n- Move all cards into the Home Cells in the correct order." << endl
		<< "\nRULES: \n- Home Cells fill from Ace to King, of the SAME SUIT." << endl
		<< "- Play Cards may be moved to another Play Card position: \n\t- Rank must be ONE less than the current card.\n\t- Must be different color suits." << endl
		<< "- Free Cells and Home Cells will automatically fill from the leftmost available position to the right." << endl
		<< "- Only one card may be placed at a time in any Free Cell." << endl
		<< "- You may only move one card at a time." << endl
		<< "\nENJOY!" << whiteOnBlack << endl;
}

inline void FreecellBoard::printHeader(string title, int columns)
{
	int titleLen = 0, totalLen = 0, padding = 0;
	titleLen = (int)title.length();
	totalLen = columns * 7;
	padding = (totalLen - titleLen) / 2;

	cout << "\n\n";
	for (size_t i = 0; i < padding - 2; i++)
		cout << " ";
	cout << blueOnWhite << " " << title << " " << whiteOnBlack << endl;

	for (size_t k = 0; k < columns; k++)
		cout << "|  C" << k + 1 << "  ";
	cout << "|" << endl;

	for (size_t l = 0; l < columns; l++)
		cout << "-------";
	cout << "-" << endl;
}

inline void FreecellBoard::printRow(const Array<Card> &array)
{
	int columns = array.getLength();
	for (size_t i = 0; i < columns; i++)
	{
		cout << whiteOnBlack << "|" << blackOnWhite << " ";
		if (array[(int)i].GetRank() != NULLRANK)
		{
			if (!(array[(int)i].GetSuit() % 2))
			{
				cout << blackOnWhite << array[(int)i].GetCharRank() << "  "
					<< array[(int)i].GetCharSuit() << " ";
			}
			else
			{
				cout << redOnWhite << array[(int)i].GetCharRank() << "  "
					<< array[(int)i].GetCharSuit() << " ";
			}
		}
		else
		{
			cout << blackOnWhite << "     ";
		}
	}
	cout << whiteOnBlack << "|\n" << endl;
}

inline void FreecellBoard::printRow(const Array<StackArray<Card>> &array)
{
	int columns = array.getLength();
	for (size_t i = 0; i < columns; i++)
	{
		cout << whiteOnBlack << "|" << blackOnWhite << " ";
		if (array[(int)i].Peek().GetRank() != NULLRANK)
		{
			if (!(array[(int)i].Peek().GetSuit() % 2))
			{
				cout << blackOnWhite << array[(int)i].Peek().GetCharRank() << "  "
					<< array[(int)i].Peek().GetCharSuit()  << " ";
			}
			else
			{
				cout << redOnWhite << array[(int)i].Peek().GetCharRank() << "  "
					<< array[(int)i].Peek().GetCharSuit()  << " ";
			}
		}
		else
		{
			cout << blackOnWhite <<  "     ";
		}
	}
	cout << whiteOnBlack << "|\n" << endl;
}

inline void FreecellBoard::PrintBoard()
{

	printHeader("FREE CELLS", 4);
	printRow(_freeCells);
		
	printHeader("HOME CELLS", 4);
	printRow(_homeCells);

	printHeader("PLAY CARDS", 8);
	printRow(_playCards);
}

inline bool FreecellBoard::GameOver()
{
	return (_homeCells[0].Peek().GetRank() == KING
		&& _homeCells[1].Peek().GetRank() == KING
		&& _homeCells[2].Peek().GetRank() == KING
		&& _homeCells[3].Peek().GetRank() == KING);
}

inline void FreecellBoard::PopFreeCard(int index)
{
	Card nullCard;
	_freeCells[index] = nullCard;
}

inline Card FreecellBoard::GetFreeCardCopy(int index)
{
	if (index >= 0 && index < _freeCells.getLength())
	{
		if (_freeCells[index].GetRank() != NULLRANK)
		{
			return _freeCells[index];
		}
		else
			throw Exception("\nNo card available.");
	}
	else
		throw Exception("\nOut of range!");
}

inline bool FreecellBoard::SetFreeCard(Card &card)
{
	bool placed = false;
	for (size_t i = 0; i < 4 && !placed; i++)
	{
		if (_freeCells[(int)i].GetRank() == NULLRANK)
		{
			_freeCells[(int)i] = card;
			placed = true;
		}
	}
	if (!placed)
		throw Exception("\nUnable to place card, all positions full.");

	return placed;
}

inline void FreecellBoard::PlayCard(int from, int to, int cardIndex)
{
	if (from != QUIT)
	{
		Card temp;
		bool placed = false;

		switch (from)
		{
		case FREE: temp = GetFreeCardCopy(cardIndex);
			break;
		case HOME: temp = GetHomeCardCopy(cardIndex);
			break;
		case PLAY: temp = GetPlayCardCopy(cardIndex);
			break;
		default:
			throw Exception("\nInvalid \"From\" selection.");
		}

		switch (to)
		{
		case FREE: placed = SetFreeCard(temp);
			break;
		case HOME: placed = SetHomeCard(temp);
			break;
		case PLAY: placed = SetPlayCard(temp);
			break;
		default:
			throw Exception("\nInvalid \"To\" selection.");
		}

		if (placed)
		{
			switch (from)
			{
			case FREE: PopFreeCard(cardIndex);
				break;
			case HOME: PopHomeCard(cardIndex);
				break;
			case PLAY: PopPlayCard(cardIndex);
				break;
			}
			cout << "\nCard placed!" << endl;
		}
		else
			throw Exception("\nError: Unable to place card.");
	}
}

inline bool FreecellBoard::HasQuit() const { return _quit; }

inline void FreecellBoard::PlayerQuit() { _quit = true; }

inline void FreecellBoard::Restart() 
{
	_freeCells.setLength(0);
	_homeCells.setLength(0);
	_playCards.setLength(0);
	_deck.init();
	init();
}

inline void FreecellBoard::PopHomeCard(int index) { _homeCells[index].Pop(); }

inline Card FreecellBoard::GetHomeCardCopy(int index)
{
	if (index >= 0 && index < _homeCells.getLength())
	{
		if (_homeCells[index].Peek().GetRank() != NULLRANK)
		{
			return _homeCells[index].Peek();
		}
		else
			throw Exception("\nNo card available.");
	}
	else
		throw Exception("\nError: Out of Range!");
}

inline bool FreecellBoard::SetHomeCard(Card &card)
{
	bool placed = false;
	for (size_t i = 0; i < 4 && !placed; i++)
		if ((_homeCells[(int)i].Peek().GetRank() == (card.GetRank() - 1))
			&& (_homeCells[(int)i].Peek().GetSuit() == card.GetSuit())
				|| ((_homeCells[(int)i].Peek().GetSuit() == NULLSUIT)
			&& (card.GetRank() == ACE)))
		{
			_homeCells[(int)i].Push(card);
			placed = true;
		}
	if (!placed)
		throw Exception("\nUnable to place card, no valid options exist.");

	return placed;
}

inline void FreecellBoard::PopPlayCard(int index) { _playCards[index].Pop(); }

inline Card FreecellBoard::GetPlayCardCopy(int index)
{
	if (index >= 0 && index < _playCards.getLength())
	{
		if (_playCards[index].Peek().GetRank() != NULLRANK)
		{
			return _playCards[index].Peek();
		}
		else
			throw Exception("\nNo card available.");
	}
	else
		throw Exception("\nOut of Range!");
}

inline bool FreecellBoard::SetPlayCard(Card &card)
{
	Array<size_t> columns;
	bool found = false, placed = false;
	size_t choice = 0;

	for (size_t i = 0; i < 8; i++)
	{
		if ((_playCards[(int)i].Peek().GetRank() == card.GetRank() + 1)
			&& (_playCards[(int)i].Peek().GetSuit() % 2 != card.GetSuit() % 2))
		{
			columns.setLength(columns.getLength() + 1);
			columns[columns.getLength() - 1] = i;
			found = true;
		}
	}
	if (found)
	{
		if (columns.getLength() > 1)
		{
			cout << "In which column would you like to place your card?";
			for (size_t i = 0; i < columns.getLength(); i++)
				cout << " " << columns[(int)i] + 1 << ",";
			cout << endl;
			std::cin >> choice;
			choice--;

			bool valid = false;
			for (size_t check = 0; check < columns.getLength(); check++)
				if (columns[(int)check] == choice)
					valid = true;
			if (valid)
			{
				_playCards[(int)choice].Push(card);
				placed = valid;
			}
			else
				throw Exception("\nInvalid selection.");
		}
		else
		{
			_playCards[(int)columns[0]].Push(card);
			placed = true;
		}
	}
	else
		throw Exception("\nUnable to place card, no valid options exist.");

	return placed;
}