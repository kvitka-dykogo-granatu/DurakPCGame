#pragma once
#include "Card.h"
#include <vector>
#include <random>
class Deck
{
	static const vector<Card> original_deck;
	vector<Card> game_deck;
	Card Trump;
	char TrumpSuit;
public:
	Deck();
	void deckShuffle();
	Card remove();
	const char getTrumpSuit()const;
	Card getTrump()const;
	void setTrump();
	void setTrumpSuit();
	int getCurrentSize()const;
	bool empty();
};

