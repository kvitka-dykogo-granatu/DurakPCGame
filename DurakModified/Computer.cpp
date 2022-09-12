#include "Computer.h"
Computer::Computer() :Player()
{
	name = "Computer";
	iq = 10;//Level:Dummy - with probability of 1 Computer will play the first suitable card to support the attack//(rand() % 9) % 2 == 0
}

void Computer::setIQ(int new_iq)
{
	iq = new_iq;
}

int Computer::getIQ() const
{
	return iq;
}

void Computer::print(int i = 0)const
{
	for (int j = 0; j < getSize(); j++)
	{
		cout << "	**";
	}
	cout << endl;
}


bool Computer::attack(Table &a)
{
	system("cls");
	bool res = 0;
	Card min;	
	min.setPower(25);
	array<Card, 2> tmp;
	if (a.Battle.size() == 0)
	{
		for (int j = 0; j < getSize(); j++)
		{
			if (min.getPower() > hand[j].getPower())
				min = hand[j];
		}
		if ((rand() % 9) - iq == 0)//MegaMind (iq=100) and Clever(iq=10) will get here negative number - so it's false for them, 10% probability for Dummy to get it true (when rand()%9==0)
			min = hand[rand() % (getSize() - 1)];
		tmp[0] = min;
		a.Battle.push_back(tmp);
		remove(min);
		res = 1;
		for (int j = 0; j < getSize(); j++)
		{
			if (min.getPower() == hand[j].getPower())
			{
				tmp[0] = hand[j];
				a.Battle.push_back(tmp);
				remove(hand[j]);
			}
		}
	}
	else {
		for (int i = 0; i < a.Battle.size(); i++)
		{
			min.setPower(25);
			for (int j = 0; j < getSize(); j++)
			{
				if (a.Battle[i][0].getRank() == hand[j].getRank() || a.Battle[i][1].getRank() == hand[j].getRank())
				{
					if (!empty() && a.Battle.size() < a.Battle_max_size) {
						if ((hand[j].getSuit() == a.deck.getTrumpSuit() && ((rand() % 9) % 2 == 0)&&getSize()!=1)||iq == 100)//Computer's IQ 
							continue;
						tmp[0] = hand[j];
						a.Battle.push_back(tmp);
						remove(hand[j]);
						res = 1;
					}
				}
			}
		}
	}
	return res;
}


bool Computer::defend(Table &a)
{	Card min;
	int c_cnt = 0;
	int o_cnt = 0;
	for (int i = 0; i < a.Battle.size()&&!empty(); i++)
	{
		min.setPower(25);
		if (a.Battle[i][1].getPower() == 0)
		{
			c_cnt++;
			for (int j = 0; j < getSize(); j++)
			{
				if (a.Battle[i][0].getPower() < hand[j].getPower()&& (a.Battle[i][0].getSuit()==hand[j].getSuit()||hand[j].getSuit()==a.deck.getTrumpSuit()))
				{
					if (min.getPower() > hand[j].getPower())
						min = hand[j];
				}
			}
			if (min.getPower() != 25) {
				a.Battle[i][1] = min;
				remove(min);
				o_cnt++;
			}

		}
	}
	if(c_cnt == o_cnt)
		return true;
	return false;
}

Computer::~Computer()
{
}
