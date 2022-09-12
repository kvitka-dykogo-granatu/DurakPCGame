#pragma once
#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

class Card
{
	string rank="";
	char suit=' ';
	int power=0;
public:
	Card()=default;
	Card(const string &r,char s);
	const string &getRank()const;
	const char getSuit()const;
	void setPower();
	void setPower(int i);
	void setTrumpSuitPower();
	int getPower()const;
	void print()const;
};

