#pragma once

enum RANK { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, NULLRANK };
enum SUIT { SPADES, HEARTS, CLUBS, DIAMONDS, NULLSUIT };

class Card
{
private:
	size_t _rank;
	size_t _suit;
	char _cRank;
	char _cSuit;
public:
	Card();
	Card(size_t rank, size_t suit, char cRank, char cSuit);
	Card(const Card &copy);
	~Card();

	Card& operator=(const Card &rhs);
	bool operator==(const Card &rhs);
	size_t GetRank();
	size_t GetRank() const;
	char GetCharRank();
	char GetCharRank() const;
	void setRank(size_t rank, char cRank);
	size_t GetSuit();
	size_t GetSuit() const;
	char GetCharSuit();
	char GetCharSuit() const;
	void setSuit(size_t suit, char cSuit);
};

inline Card::Card()
	: _suit(NULLSUIT), _rank(NULLRANK), _cRank('\0'), _cSuit('\0') {}

inline Card::Card(size_t rank, size_t suit, char cRank, char cSuit)
	: _rank(rank), _suit(suit), _cRank(cRank), _cSuit(cSuit)  {}

inline Card::Card(const Card &copy)
	: _rank(copy.GetRank()), _suit(copy.GetSuit()), _cRank(copy.GetCharRank()), _cSuit(copy.GetCharSuit()) {}

inline Card::~Card() {}

inline Card& Card::operator=(const Card &rhs)
{
	_rank = rhs.GetRank();
	_suit = rhs.GetSuit();
	_cRank = rhs.GetCharRank();
	_cSuit = rhs.GetCharSuit();
	return *this;
}

inline bool Card::operator==(const Card &rhs)
{
	return (_rank == rhs.GetRank() && _suit == rhs.GetSuit());
}

inline size_t Card::GetRank() { return _rank; }
inline size_t Card::GetRank() const { return _rank; }
inline char Card::GetCharRank() { return _cRank; }
inline char Card::GetCharRank() const { return _cRank; }

inline void Card::setRank(size_t rank, char cRank) { _rank = rank; _cRank = cRank; }

inline size_t Card::GetSuit() { return _suit; }
inline size_t Card::GetSuit() const { return _suit; }
inline char Card::GetCharSuit() { return _cSuit; }
inline char Card::GetCharSuit() const { return _cSuit; }

inline void Card::setSuit(size_t suit, char cSuit) { _suit = suit; _cSuit = cSuit; }