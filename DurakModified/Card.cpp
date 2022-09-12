#include "Card.h"
CONSOLE_SCREEN_BUFFER_INFO csb;
HANDLE hSO = GetStdHandle(STD_OUTPUT_HANDLE);
Card::Card(const string &r, char s)
{
	rank = r;
	suit = s;
	if (isdigit(rank[0]))
		power = stoi(rank);
	else
	{
		switch (rank[0])
		{
		case 'J':power = 11; break;
		case 'Q':power = 12; break;
		case 'K':power = 13; break;
		case 'A':power = 14; break;
		}
	}
}

const string& Card::getRank() const
{
	return rank;
}

const char Card::getSuit() const
{
	return suit;
}

void Card::setPower()
{
	if (isdigit(rank[0]))
		power = stoi(rank);
	else
	{
		switch (rank[0])
		{
		case 'J':power = 11; break;
		case 'Q':power = 12; break;
		case 'K':power = 13; break;
		case 'A':power = 14; break;
		}
	}
}

void Card::setPower(int i)
{
	power = i;
}

void Card::setTrumpSuitPower()
{
	power += 10;
}

int Card::getPower() const
{
	return power;
}

void Card::print()const
{
	GetConsoleScreenBufferInfo(hSO, &csb);
	SetConsoleTextAttribute(hSO, BACKGROUND_GREEN | 15);
	cout << rank;
	if(suit == (char)3 ||suit == (char)4)
		SetConsoleTextAttribute(hSO, BACKGROUND_GREEN | 12);
	else
		SetConsoleTextAttribute(hSO, BACKGROUND_GREEN | 0);
	cout << suit;
	SetConsoleTextAttribute(hSO, BACKGROUND_GREEN | 15);

}

