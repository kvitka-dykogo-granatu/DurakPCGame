#pragma once
#include<array>
#include <conio.h>
#include "Card.h"
#include "Deck.h"
#include"Table.h"

class Player
{
protected:
	string name;
	static const int original_size = 6;
	vector <Card> hand;
public:
	int start_check();
	Player()=default;
	Player(string n);
	int getSize()const;
	const string &getName()const;
	void addFromDeck(Deck &deck);
	void add(Card card);
	void fill(Deck &deck);
	void take(Table &a);
	void remove(Card card);
	bool empty();
	virtual bool attack(Table &a);
	virtual bool defend(Table &a);
	virtual void print(int i)const;
	virtual~Player() = 0;
};

