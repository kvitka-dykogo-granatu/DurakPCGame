#include "Player.h"

int Player::start_check()
{
	int minTrumpPower = 25;
	for (int i = 0; i < getSize(); i++)
	{
		if (hand[i].getPower() < minTrumpPower&&hand[i].getPower() > 15)
			minTrumpPower = hand[i].getPower();
	}
	return minTrumpPower;
}

Player::Player(string n)
{
	name = n;
}

int Player::getSize()const
{
	return hand.size();
}

const string &Player::getName()const
{
	return name;
}

bool Player::attack(Table &a)
{
	return 0;
}


bool Player::defend(Table &a)
{
	cout << "Defend" << endl;
	return 0;
}


void Player::addFromDeck(Deck &deck)
{
	hand.push_back(deck.remove());
}

void Player::add(Card card)
{
	hand.push_back(card);
}

void Player::fill(Deck &deck)
{
	for (int i = getSize(); i<original_size&& !deck.empty(); i++)
	{
		addFromDeck(deck);
	}
}

void Player::take(Table &a)
{
	for (int i = 0; i < a.Battle.size(); i++)
	{
		add(a.Battle[i][0]);
		if (a.Battle[i][1].getPower() != 0)
			add(a.Battle[i][1]);
	}
}

void Player::remove(Card card)
{
	for (int i = 0; i < getSize(); i++)
	{
		if (hand[i].getSuit() == card.getSuit()&& hand[i].getRank() == card.getRank())
		{
			hand.erase(hand.begin() + i);
			return;
		}
	}
}

bool Player::empty()
{
	if (hand.size() == 0)
		return true;
	return false;
}


void Player::print(int i=0) const
{
	cout << "Player" << endl;
}

Player::~Player()
{
}

