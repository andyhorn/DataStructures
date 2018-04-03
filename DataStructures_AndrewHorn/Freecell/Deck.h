#pragma once

#include "Card.h"
#include "Array.h"
#include "Exception.h"
#include <stdlib.h> // random
#include <time.h>   // random seed

class Deck
{
private:
	Array<Card> _deck;
	size_t _dealIndex;
	char _suit[4] = { 'S','H','C','D' };
	char _rank[13] = { 'A','2','3','4','5','6','7','8','9','T','J','Q','K' };
public:
	Deck();
	Deck(const Deck &copy);
	~Deck();

	void init();
	void copyDeck(const Deck &copy);
	void shuffle(int shuffles);
	size_t getLength();
	size_t getLength() const;

	Deck& operator=(const Deck &rhs);
	Card& operator[](int index);
	Card& operator[](int index) const;
	const Card& Deal();
};

inline Deck::Deck()
{
	init();
}

inline Deck::Deck(const Deck &copy)
{
	copyDeck(copy);
}

inline Deck::~Deck() {}

inline void Deck::init()
{
	_deck.setLength(52);
	_dealIndex = 51;

	size_t index = 0;
	for (size_t suit = SPADES; suit <= DIAMONDS; suit++)
		for (size_t rank = ACE; rank <= KING; rank++)
		{
			_deck[(int)index].setSuit(suit, _suit[suit]);
			_deck[(int)index].setRank(rank, _rank[rank]);
			
			index++;
		}
}

inline void Deck::copyDeck(const Deck &copy)
{
	_deck.setLength((int)copy.getLength());
	_dealIndex = getLength() - 1;

	for (size_t i = 0; i < _deck.getLength(); i++)
	{
		_deck[(int)i].setRank(copy[(int)i].GetRank(), copy[(int)i].GetCharRank());
		_deck[(int)i].setSuit(copy[(int)i].GetSuit(), copy[(int)i].GetCharSuit());
	}
}

inline void Deck::shuffle(int shuffles)
{
	srand((unsigned int)time(0));
	for (size_t shuffle = 0; shuffle < shuffles; shuffle++)
	{
		for (size_t swap = 0; swap < getLength(); swap++)
		{
			int randomOne = rand() % 52;
			int randomTwo = rand() % 52;
			Card temp = _deck[randomOne];
			_deck[randomOne] = _deck[randomTwo];
			_deck[randomTwo] = temp;
		}
	}
}

inline size_t Deck::getLength() { return _deck.getLength(); }
inline size_t Deck::getLength() const { return _deck.getLength(); }

inline Deck& Deck::operator=(const Deck &rhs) { copyDeck(rhs); }

inline Card& Deck::operator[](int index) 
{
	if (index >= 0 && index < _deck.getLength())
		return _deck[index];
	else
		throw Exception("Exception: Out of Range!");
}
inline Card& Deck::operator[](int index) const 
{
	if (index >= 0 && index < _deck.getLength())
		return _deck[index];
	else
		throw Exception("Exception: Out of Range!");
}

inline const Card& Deck::Deal()
{
	if (_dealIndex < 0)
		_dealIndex = getLength() - 1;

	return _deck[(int)_dealIndex--];
}