#pragma once
#include "Player.h"
#include<time.h>
class Computer :public Player
{
	int iq;
public:
	Computer();
	void setIQ(int new_iq);
	int getIQ()const;
	void print(int i)const override;
	bool attack(Table &a)override;
	bool defend(Table &a)override;
	~Computer()override;
};

