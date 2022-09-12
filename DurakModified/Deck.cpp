#include "Deck.h"
const vector<Card> Deck::original_deck = {
Card("6", (char)3), Card("7", (char)3), Card("8", (char)3), Card("9", (char)3), Card("10", (char)3), Card("J", (char)3), Card("Q", (char)3), Card("K", (char)3), Card("A", (char)3),
Card("6", (char)4), Card("7", (char)4), Card("8", (char)4), Card("9", (char)4), Card("10", (char)4), Card("J", (char)4), Card("Q", (char)4), Card("K", (char)4), Card("A", (char)4),
Card("6", (char)5), Card("7", (char)5), Card("8", (char)5), Card("9", (char)5), Card("10", (char)5), Card("J", (char)5), Card("Q", (char)5), Card("K", (char)5), Card("A", (char)5),
Card("6", (char)6), Card("7", (char)6), Card("8", (char)6), Card("9", (char)6), Card("10", (char)6), Card("J", (char)6), Card("Q", (char)6), Card("K", (char)6), Card("A", (char)6)
};
Deck::Deck()
{
	game_deck = original_deck;
	random_device rd;
	mt19937 gen;
	gen.seed(rd());
	shuffle(game_deck.begin(), game_deck.end(), gen);	
	Trump = game_deck.front();
	TrumpSuit = game_deck.front().getSuit();
	for (int i = 0; i < game_deck.size(); i++)
	{
		if (game_deck[i].getSuit() == TrumpSuit)
			game_deck[i].setTrumpSuitPower();
	}
}

void Deck::deckShuffle()
{
	random_device rd;
	mt19937 gen;
	gen.seed(rd());
	shuffle(game_deck.begin(), game_deck.end(), gen);
}

Card Deck::remove()
{
	Card top = game_deck.back();
	game_deck.pop_back();
	return top;
}

const char Deck::getTrumpSuit()const
{
	return Trump.getSuit();
}

Card Deck::getTrump()const
{
	return Trump;
}

void Deck::setTrump()
{
	Trump = game_deck.front();
}

void Deck::setTrumpSuit()
{
	TrumpSuit = game_deck.front().getSuit();
}

int Deck::getCurrentSize()const
{
	return game_deck.size();
}

bool Deck::empty()
{
	if(getCurrentSize())
		return false;
	return true;
}
