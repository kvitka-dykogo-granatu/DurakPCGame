#pragma once
#include "Deck.h"
#include<array>
struct Table
{
	Deck deck;
	vector<Card>Otboi;
	vector<array<Card,2>>Battle;
	const int Battle_max_size = 6;
	bool hod;
	void setHod(int u, int c)
	{
		if (u < c)
			hod = 1;// "User"
		else
			hod = 0;// "Computer"
	}
	string getStringHod()const
	{
		string tmp;
		hod ? tmp = "User" : tmp = "Computer";
		return tmp;
	}
	int getIntHod()const
	{
		return hod;
	}
	void changeHod()
	{
		if (hod==0)
			hod = 1;
		else
			hod = 0;
	}
	void BattlePrint()const
	{
		cout << "			";
		for (int i = 0; i < Battle.size(); i++)
		{
			Battle[i][0].print();
			cout << " / ";
			if(Battle[i][1].getPower()!=0)
				Battle[i][1].print();
			cout << "	";
		}
		cout << endl;
		/* //CARDS ON THE BATTLE TABLE
			CONSOLE_SCREEN_BUFFER_INFO csbuf_table;
		HANDLE hStdOut_table = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hStdOut_table, &csbuf_table);
		char assist_l[6] = { '.', '-', '.', '|', '\'', '\'' };
		COORD pos = { csbuf_table.dwMaximumWindowSize.X / 2 - 40, 12 };
		cout << "			";
		pos.X += 19;
		SetConsoleCursorPosition(hStdOut_table, pos);
		for (int i = 0; i < Battle.size(); i++)
		{
			pos.X += 6 + 2;
			Battle[i][0].print();
			draw_border(4, 3, { static_cast<SHORT>(pos.X - 1), static_cast<SHORT>(pos.Y - 2) }, assist_l, csbuf_table, hStdOut_table);
			cout << "  /";
			if(Battle[i][1].getPower()!=0)
				Battle[i][1].print();
			cout << "  ";
		}
		cout << endl;
		*/
	}
};

