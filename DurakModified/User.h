#pragma once
#include "Player.h"
#include "drawing.h"
#define nullptr NULL
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_SPACE 32
class User :public Player
{
public:
	User();
	User(string name);
	void setName();
	void setName(string n);
	bool attack(Table &a)override;
	bool defend(Table &a)override;
	void print(int ind_border)const override;
	~User()override;
};
