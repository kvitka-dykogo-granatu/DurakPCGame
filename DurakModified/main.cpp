#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include "Card.h"
#include "Deck.h"
#include "User.h"
#include"Computer.h"
#include"Table.h"
#include "drawing.h"
CONSOLE_SCREEN_BUFFER_INFO csbuf;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//#define GREEN 160
//#define BLUE 159
//#define RED 192
//#define PINK 208
//#define YELLOW 224
//#define INFECTED 240

//#define UNSELECTED 47
//#define SELECTED 44
//char l[6] = { char(218), char(196), char(191), char(179), char(217), char(192) };
//char d_l[6] = { char(201), char(205), char(187), char(186), char(188), char(200) };
//char assist_l[6] = { '.', '-', '.', '|', '\'', '\'' };
char lines[6] = { char(218), char(196), char(191), char(179), char(217), char(192) };
char double_lines[6] = { char(201), char(205), char(187), char(186), char(188), char(200) };


void CompPrint(const Computer &c, const Table&t, COORD pos) {
	char assist_l[6] = { '.', '-', '.', '|', '\'', '\'' };
	COORD label = { static_cast<SHORT>(csbuf.dwMaximumWindowSize.X / 2 - 10), 1 }; COORD curr = pos;
	SetConsoleCursorPosition(hStdOut, label);

	cout << "Now " << t.getStringHod() << " goes " << endl;

	SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
	draw_border(13+ t.getStringHod().length(), 1, { static_cast<SHORT>(label.X - 3), static_cast<SHORT>(label.Y - 1) }, double_lines, csbuf, hStdOut);
	SetConsoleCursorPosition(hStdOut, pos);
	curr.X += 11;
	for (int i = 0; i < c.getSize(); i++) {
		curr.X += 6 + 2;
		draw_border(4, 3, { static_cast<SHORT>(curr.X - 1), static_cast<SHORT>(curr.Y - 2) }, assist_l, csbuf, hStdOut);
	}
	SetConsoleCursorPosition(hStdOut, pos);
	cout << "Computer:	"; c.print(0); cout << endl;
	pos.X -= 7;
	pos.Y += 5;
	SetConsoleCursorPosition(hStdOut, pos);
	char l[3];
	_itoa(t.deck.getCurrentSize(), l, 10);
	cout << "Deck:  ";
	string k = l;
	k += "|";
	cout << k;
	t.deck.getTrump().print();
	SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
	draw_border(14, 1, { static_cast<SHORT>(pos.X -2), static_cast<SHORT>(pos.Y - 1) }, lines, csbuf, hStdOut);
}
//void UserPrint(const User &u, const Computer &c, const Table&t, COORD pos) {
//	pos.Y += 9;
//	SetConsoleCursorPosition(hStdOut, pos);
//	/*cout << u.getName() << ":		"; */
//	u.print(); cout << endl;
//
//}
void TablePrint(const User &u, const Computer &c, const Table&t, COORD pos) {
	CompPrint(c, t,pos);
	cout << endl;
	u.print(-1);

	cin.get();
}
int Round(User &u,Computer &c,Table&t, COORD pos) {
	bool a;
	bool d;
	if (c.empty() && u.empty() && t.deck.empty())
		return 3;
	if (u.empty() && t.deck.empty())
		return 1;
	if (c.empty() && t.deck.empty())
		return 0;
	if (t.getIntHod() == 1)
	{
		do {
			a = u.attack(t);
			pos.X -= 10; pos.Y += 19; SetConsoleCursorPosition(hStdOut, pos);
			cin.get();
			system("cls");
			pos.X += 10; pos.Y -= 19; SetConsoleCursorPosition(hStdOut, pos);
			CompPrint(c, t,pos);
			t.BattlePrint();
			u.print(-1);
			pos.X -= 10; pos.Y += 19; SetConsoleCursorPosition(hStdOut, pos);
			cin.get();
			system("cls");
			pos.X += 10; pos.Y -= 19; SetConsoleCursorPosition(hStdOut, pos);
			//-------------
			d = c.defend(t);
			CompPrint(c, t,pos);
			t.BattlePrint();
			u.print(-1);
		} while (a != 0 && d!=0&&t.Battle.size()<t.Battle_max_size);
		if (d == 0)
		{
			c.take(t);
			u.fill(t.deck);
		}
		else
		{
			for (int i = 0; i < t.Battle.size(); i++)
			{
				t.Otboi.push_back(t.Battle[i][0]);
				if (t.Battle[i][1].getPower() != 0)
					t.Otboi.push_back(t.Battle[i][1]);
			}
			t.changeHod();
		}
		t.Battle.clear();
		if (!t.deck.empty())
		{
			u.fill(t.deck);
			c.fill(t.deck);
		}
		pos.X -= 10; pos.Y += 19; SetConsoleCursorPosition(hStdOut, pos);
		cin.get();
		system("cls");
		pos.X += 10; pos.Y -= 19; SetConsoleCursorPosition(hStdOut, pos);
	}
	else {
		do {
			a = c.attack(t);
			CompPrint(c, t,pos);
			t.BattlePrint();
			u.print(-1);
			//-------------
			d = u.defend(t);
			pos.X -= 10; pos.Y += 19; SetConsoleCursorPosition(hStdOut, pos);
			cin.get();
			system("cls");
			pos.X += 10; pos.Y -= 19; SetConsoleCursorPosition(hStdOut, pos);
			if (d != 0) {
				CompPrint( c, t,pos);
				t.BattlePrint();
				u.print(-1);
				pos.X -= 10; pos.Y += 19; SetConsoleCursorPosition(hStdOut, pos);
				cin.get();
				system("cls");
				pos.X += 10; pos.Y -= 19; SetConsoleCursorPosition(hStdOut, pos);
			}
		} while (a != 0 && d != 0 && t.Battle.size()<t.Battle_max_size);
		if (d == 0)
		{
			u.take(t);
			c.fill(t.deck);
		}
		else
		{
			for (int i = 0; i < t.Battle.size(); i++)
			{
				t.Otboi.push_back(t.Battle[i][0]);
				if (t.Battle[i][1].getPower() != 0)
					t.Otboi.push_back(t.Battle[i][1]);
			}
			t.changeHod();

		}
		t.Battle.clear();
		if (!t.deck.empty())
		{
			u.fill(t.deck);
			c.fill(t.deck);
		}
	}
	TablePrint(u, c, t,pos);
	return 2;
}

//
//void draw_bond(HANDLE h, COORD t, COORD b) {
//	int lenx = b.X - t.X - 2, leny = b.Y - t.Y;
//	COORD f = t;
//	unsigned char c;
//	SetConsoleCursorPosition(h, f); c = 457; cout << c;
//	f.X++; c = 461;
//	for (int i = 0; i < lenx; i++)cout << c;
//	c = 443; cout << c << endl;
//	c = 442; f = t;
//	f.Y++;
//	for (int i = 0; i < leny - 1; i++) {
//		SetConsoleCursorPosition(h, f);
//		f.Y++;
//		cout << c;
//	}
//	SetConsoleCursorPosition(h, f); f.Y++; c = 456;	cout << c;
//	f.X++; c = 461;
//	for (int i = 0; i < lenx; i++)cout << c;
//	c = 444; cout << c << endl;
//	c = 442; f = b;
//	f.Y--; f.X--;
//	for (int i = leny - 1; i > 0; i--) {
//		SetConsoleCursorPosition(h, f);
//		f.Y--;
//		cout << c;
//	}
//	f = t;
//	f.X += 2;
//	f.Y += 2;
//	SetConsoleCursorPosition(h, f);
//
//}


void show_menu(int current, User u) {

	GetConsoleScreenBufferInfo(hStdOut, &csbuf);
	COORD pos = { 10, 12 };
	SetConsoleTextAttribute(hStdOut, 32);
	system("cls");
	print_logo(pos, csbuf, hStdOut);
	SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
	SetConsoleCursorPosition(hStdOut, { static_cast<SHORT>(csbuf.dwMaximumWindowSize.X / 2 - 11- u.getName().length()/2),  8});
	cout << "Hi, "<<u.getName()<<"! Welcome to DURAK!";
	SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	draw_border(25+ u.getName().length(), 1, { static_cast<SHORT>(csbuf.dwMaximumWindowSize.X / 2 - 13 - u.getName().length() / 2), 7 }, double_lines, csbuf, hStdOut);
	
	if (current % 5 == 0) {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		draw_border(12, 1, { static_cast<SHORT>(pos.X - 2), static_cast<SHORT>(pos.Y - 1) }, lines, csbuf, hStdOut);
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);

	}
	else SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | GREY);
	SetConsoleCursorPosition(hStdOut, pos);
	cout << "Start game";   
	pos.X += 21;

	if (current % 5 == 1) {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		draw_border(18, 1, { static_cast<SHORT>(pos.X - 2), static_cast<SHORT>(pos.Y - 1) }, lines, csbuf, hStdOut);
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
	}
	else SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | GREY);
	SetConsoleCursorPosition(hStdOut, pos);
	cout << "Help/DURAK rules"; 
			 
	pos.X += 24;

	if (current % 5 == 2) {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		draw_border(18, 1, { static_cast<SHORT>(pos.X - 2), static_cast<SHORT>(pos.Y - 1) }, lines, csbuf, hStdOut);
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
	}
	else SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | GREY);
	SetConsoleCursorPosition(hStdOut, pos);
	cout << "  Set new name";  
	pos.X += 28;

	if (current % 5 == 3) {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		draw_border(10, 1, { static_cast<SHORT>(pos.X - 2), static_cast<SHORT>(pos.Y - 1) }, lines, csbuf, hStdOut);
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
	}
	else SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | GREY);
	SetConsoleCursorPosition(hStdOut, pos);
	cout << "Opponent";  //Opponent
	pos.X += 17;

	if (current % 5 == 4) {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		draw_border(6, 1, { static_cast<SHORT>(pos.X - 2), static_cast<SHORT>(pos.Y - 1) }, lines, csbuf, hStdOut);
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
	}
	else SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | GREY);
	SetConsoleCursorPosition(hStdOut, pos);
	cout << "Exit";    

	cout << endl;
	

}
char spaces[1] = { ' ' };


void sub_menu(int current) {
	/*
						COORD secondary_pos = { 51, 15 };
					SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
					SetConsoleCursorPosition(hStdOut, secondary_pos);
					cout << "Choose your opponent:\n"<<endl;
	*/

	GetConsoleScreenBufferInfo(hStdOut, &csbuf);
	COORD subpos = { 55, 18 };
	
	SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	subpos.X += 1;
	if (current % 3 == 0) {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		draw_border(12, 1, { static_cast<SHORT>(subpos.X - 2), static_cast<SHORT>(subpos.Y - 1) }, lines, csbuf, hStdOut);
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);

	}
	else {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN );
		draw_border(12, 1, { static_cast<SHORT>(subpos.X - 2), static_cast<SHORT>(subpos.Y - 1) }, lines, csbuf, hStdOut);
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | GREY); 
	}
	SetConsoleCursorPosition(hStdOut, subpos);
	cout << "YummyDummy";
	subpos.X -= 1;
	subpos.Y += 3;

	if (current % 3 == 1) {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		draw_border(14, 1, { static_cast<SHORT>(subpos.X - 2), static_cast<SHORT>(subpos.Y - 1) }, lines, csbuf, hStdOut);
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
	}
	else {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN);
		draw_border(14, 1, { static_cast<SHORT>(subpos.X - 2), static_cast<SHORT>(subpos.Y - 1) }, lines, csbuf, hStdOut);
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | GREY);
	}
	SetConsoleCursorPosition(hStdOut, subpos);
	cout << "CleverForever";

	subpos.Y += 3;

	subpos.X += 2;
	if (current % 3 == 2) {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		draw_border(10, 1, { static_cast<SHORT>(subpos.X - 2), static_cast<SHORT>(subpos.Y - 1) }, lines, csbuf, hStdOut);
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
	}
	else {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN);
		draw_border(10, 1, { static_cast<SHORT>(subpos.X - 2), static_cast<SHORT>(subpos.Y - 1) }, lines, csbuf, hStdOut);
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | GREY);
	}
	SetConsoleCursorPosition(hStdOut, subpos);
	cout << "MegaMind";
	subpos.X -= 2;
	cout << endl;


}

void Game(User u, Computer c) {
	Table t;
	
	SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
	//int prev_str = 1;
	//a.X = 0; a.Y = 0;
	//b.X = csbuf.srWindow.Right;
	//b.Y = csbuf.srWindow.Bottom;
	//m.X = csbuf.srWindow.Right / 2;
	//m.Y = 2;
	//lb.X = 2;
	//lb.Y = prev_str;
	system("cls");
	COORD pos = { csbuf.dwMaximumWindowSize.X / 2-40, 7 };
	u.fill(t.deck);
	c.fill(t.deck);
	t.setHod(u.start_check(), c.start_check());
	TablePrint(u, c, t,pos);

	int k = 2;
	do {
		k = Round(u, c, t, pos);
	} while (k == 2);
	system("cls");
	pos = { csbuf.dwMaximumWindowSize.X / 2 - 7, 12 };
	SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
	SetConsoleCursorPosition(hStdOut, pos);
	if (k == 3)
		cout << "	Draw!" << endl;
	else {
		if (k == 1)
			cout << u.getName() << " wins!" << endl;
		else
			cout << "Computer wins!" << endl;
	}
	pos.X -= 15;
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	cout << "Press any key to return to the main menu..." << endl;
	draw_border(48, 2, { static_cast<SHORT>(pos.X - 2), static_cast<SHORT>(pos.Y - 2) }, double_lines, csbuf, hStdOut);

	cin.get();

}

void choose_opponent(Computer c) {
	sub_menu(0);
	int flag = 1;
	int key, current = 200;
	while (flag) {
		if (_kbhit()) {
			key = _getch();
			switch (key) {
			case KEY_ESC:
				flag = 0;
				break;
			case KEY_ARROW_UP:
				current--;
				sub_menu(current);
				break;
			case KEY_ARROW_DOWN:
				current++;
				sub_menu(current);
				break;
			case KEY_ENTER:
				if (current % 3 == 0) {
					c.setIQ(0);
					sub_menu(current);
				}

				if (current % 3 == 1) {
					c.setIQ(10);
					sub_menu(current);
				}
				if (current % 3 == 2) {
					c.setIQ(100);
					sub_menu(current);

				}
				flag = 0;
				break;
			default:
				break;
			}
		}
	}
}



void main_menu() {
	User u("Newbie");
	Computer c;
	show_menu(0,u);
	
	int flag = 1;
	int key, current = 200;
	COORD h2 = { static_cast<SHORT>(csbuf.dwMaximumWindowSize.X / 2 - 4), 17 };
	while (flag) {
		if (_kbhit()) {
			key = _getch();
			switch (key) {
			case KEY_ESC:
				flag = 0;
				break;
			case KEY_ARROW_LEFT:
				current--;
				show_menu(current,u);
				break;
			case KEY_ARROW_RIGHT:
				current++;
				show_menu(current,u);
				break;
			case KEY_ENTER:
				// Game itself
				if (current % 5 == 0) { 
					Game(u,c); 
					show_menu(0, u);
				}

				if (current % 5 == 1) {
			
					SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
					SetConsoleCursorPosition(hStdOut, { 0, 14 });
					cout << "\n						Standart rules of 'DURAK':\n" << endl;
					cout << "\t- At the start the deck is shuffled, the Trump is chosen and you and your opponent get 6 cards from the deck " << endl;
					cout << "\t- You can't see Computer's cards unless they're on the board, 'in game' " << endl;
					cout << "\t- Every round if you lack some cards to 6, you get some from the deck" << endl;
					cout << "\t- Each turn you or Computer choose cards to attack (up to 4 of the same nominal)" << endl;
					cout << "\t  and the opponent has to defend with cards of the same suit and higher nominal, or use a Trump card" << endl;
					cout << "\t- To choose the card you can type its position in your hand" << endl;
					cout << "\t- If the player doesn't have appropriate cards to defend, he takes everything on board in his hands" << endl;
					cout << "\t- The one who doesn't have any cards when the deck is over is the winner" << endl;
					cout << "\n\t						Good luck!";
					draw_border(110, 12, { static_cast<SHORT>(h2.X - 50), static_cast<SHORT>(h2.Y - 3) }, lines, csbuf, hStdOut);
				}
				if (current % 5 == 2) {
					h2.X -= 8;
					SetConsoleCursorPosition(hStdOut, h2);
					u.setName();
					h2.X += 8;
					
					
				}

				//Opponent
				if (current % 5 == 3) {

					COORD secondary_pos = { 51, 15 };
					SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | WHITE);
					SetConsoleCursorPosition(hStdOut, secondary_pos);
					cout << "Choose your opponent:\n"<<endl;
					choose_opponent(c);
					
				}
				if (current % 5 == 4) { 
					SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN | FOREGROUND_GREEN);
					exit(0); 
				}
				break;
			default:
				break;
			}
		}
	}
	system("pause");
}


int main()
{
	SetConsoleTitle(L" DURAK ");
	srand(time(0));
	main_menu();
	system("pause");
}

