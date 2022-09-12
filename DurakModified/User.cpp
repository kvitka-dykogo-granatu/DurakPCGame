#include "User.h"
CONSOLE_SCREEN_BUFFER_INFO csbuf_user;
HANDLE hStdOut_user = GetStdHandle(STD_OUTPUT_HANDLE);
//char l[6] = { char(218), char(196), char(191), char(179), char(217), char(192) };
//char d_l[6] = { char(201), char(205), char(187), char(186), char(188), char(200) };


User::User():Player()
{
}

User::User(string name):Player(name)
{
}

void User::setName()
{
	cout << "Enter your name:";
	string n;
	getline(cin, name);
}

void User::setName(string n)
{
	name=n;
}
void User::print(int ind_border=-1)const
{
	char assist_l[6] = { '.', '-', '.', '|', '\'', '\'' };
	GetConsoleScreenBufferInfo(hStdOut_user, &csbuf_user);
	COORD curr= { csbuf_user.dwMaximumWindowSize.X / 2 - 40, 15 };

	SetConsoleCursorPosition(hStdOut_user,curr);
	DWORD cCharsWritten;
	SetConsoleTextAttribute(hStdOut_user, BACKGROUND_GREEN | WHITE);
	FillConsoleOutputCharacter(hStdOut_user, ' ', 600, curr, &cCharsWritten);

	curr.Y+=2;
	SetConsoleCursorPosition(hStdOut_user, curr);

	cout << getName() << ":		";
	for (int i = 0; i < getSize(); i++)
	{
		hand[i].print();
		cout << "	";
		
	}
	curr.X += 11;
	for (int i = 0; i < getSize(); i++) {
		curr.X += 6+2;
		draw_border(hand[i].getRank().length() + 3, 3, { static_cast<SHORT>(curr.X - 1), static_cast<SHORT>(curr.Y - 2) }, assist_l, csbuf_user, hStdOut_user);
	}
	curr.X = csbuf_user.dwMaximumWindowSize.X / 2 - 40;
	if (ind_border >= 0 && ind_border < getSize())
	{
		curr.X += 6 + 13 + 8 * ind_border;
		SetConsoleTextAttribute(hStdOut_user, BACKGROUND_GREEN | RED);
		draw_border(hand[ind_border].getRank().length()+3, 3, { static_cast<SHORT>(curr.X - 1), static_cast<SHORT>(curr.Y - 2) }, assist_l, csbuf_user, hStdOut_user);
		SetConsoleTextAttribute(hStdOut_user, BACKGROUND_GREEN | WHITE);
	}
	cout << endl;
}

bool User::attack(Table &a)
{
	GetConsoleScreenBufferInfo(hStdOut_user, &csbuf_user);
	SetConsoleTextAttribute(hStdOut_user, BACKGROUND_GREEN | 7);
	COORD poss = { 10, 22 };
	//for (int i = 0; i < csbuf_user.dwMaximumWindowSize.X; i++)
	//{
	//	/*tempor = (char)i % 4 + 3;
	//	if(tempor==3|| tempor==4)
	//		SetConsoleTextAttribute(hStdOut_user, BACKGROUND_GREEN | 12);
	//	else
	//		SetConsoleTextAttribute(hStdOut_user, BACKGROUND_GREEN | 0);*/
	//	cout << (char)(i % 4 + 3);
	//}
	////	COORD poss = { csbuf_user.dwMaximumWindowSize.X / 2 - 50, 21 };
	//SetConsoleTextAttribute(hStdOut_user, BACKGROUND_GREEN | 7);
	//poss.Y += 2;
	string g;
	bool stop = 0;
	bool k = 0;
	bool res = 0;
	int printed_rows = 0;
	int card_n;
	int flag;
	int key, current;
	poss.X = csbuf_user.dwMaximumWindowSize.X / 2 - 50;
	do {
		SetConsoleCursorPosition(hStdOut_user, poss);
		cout << "Choose a card for attack, and press 'Enter'" << endl;
		poss.Y++; printed_rows++; SetConsoleCursorPosition(hStdOut_user, poss);
		cout << "Or just press 'Space' if you don't want to attack anymore (possible after at least 1 attack): ";
		poss.Y++; printed_rows++; SetConsoleCursorPosition(hStdOut_user, poss);
		card_n = 0;
		flag = 1;
		current = getSize() * 20;
		print(0);
		while (flag) {
			if (_kbhit()) {
				key = _getch();
				switch (key) {
					case KEY_ESC:
						flag = 0;
						break;
					case KEY_ARROW_LEFT:
						current--;
						print(current % getSize());
						break;
					case KEY_ARROW_RIGHT:
						current++;
						print(current % getSize());
						break;
					case KEY_ENTER: {
						for (int i = 0; i < getSize(); i++) {
							card_n = current % getSize();
							if (card_n == i)break;
						}
						if (a.Battle.size() > 0) {//if we can compare rank with other cards on the table
							for (int i = 0; i < a.Battle.size(); i++)
							{
								if (a.Battle[i][0].getRank() == hand[card_n].getRank() || a.Battle[i][1].getRank() == hand[card_n].getRank())
								{
									k = 1;
									break;
								}
							}
							if (k == 0)
							{
								SetConsoleCursorPosition(hStdOut_user, poss);
								cout << "Cards' rank doesn't match! Change the card or finish your choice by pressing 'Enter'";
								poss.Y++; printed_rows++; SetConsoleCursorPosition(hStdOut_user, poss);
								continue;
							}

						}
						array<Card, 2> tmp;
						tmp[0] = hand[card_n];
						a.Battle.push_back(tmp);//putting on board
						remove(hand[card_n]);//removing from hand
						res = 1;
						poss.Y++; printed_rows++; SetConsoleCursorPosition(hStdOut_user, poss);
						cout << "Got it!" << endl;
						poss.Y++; printed_rows++; SetConsoleCursorPosition(hStdOut_user, poss);
						print(current % getSize());
						k = 0;
					}break;
					case KEY_SPACE: {
						if (!a.Battle.empty()) {//if there is at least 1 card on the table
							stop = 1;
							flag = 0;
						}
					}

					default:break;
				}
				
			}
			/*else
			{
				if (a.Battle.size() == 0)
				{
					cout << "Choose any card to attack!" << endl;
					g = "empty";
				}
			}
			k = 0;
			m = 1;*/

				
		}
	} while (!stop && a.Battle.size() < a.Battle_max_size && !empty());
	return res;
		//if (g.size() != 0) {//if not Enter
		//	for (int i = 0; i < g.size(); ++i)//check if it is a number
		//		if (!isdigit(g.c_str()[i]))
		//			m = 0;
		//	if (!m)
		//		cout << "Error! It's not a number!" << endl;
		//	else
		//		if (getSize() <= stoi(g) - 1)//check if it matches the size of the hand_deck
		//			cout << "Error! It's not a suitable number!" << endl;
		//		else {
		//			j = stoi(g) - 1;
		//	 
		//	if (a.Battle.size()>0) {//if we can compare rank with other cards on the table
		//		for (int i = 0; i < a.Battle.size(); i++)
		//		{
		//			if (a.Battle[i][0].getRank() == hand[j].getRank() || a.Battle[i][1].getRank() == hand[j].getRank())
		//			{
		//				k = 1;
		//				break;
		//			}
		//		}	
		//		if(k==0)
		//			{
		//				cout << "Cards' rank doesn't match! Change the card or finish your choice by pressing 'Enter'" << endl;
		//				continue; 
		//			}
		//		
		//	}
		//	array<Card, 2> tmp;
		//	tmp[0] = hand[j];
		//	a.Battle.push_back(tmp);
		//	remove(hand[j]);
		//	res = 1;
		//	
		//	cout << "Got it!" << endl;
		//	poss.Y++; printed_rows++; SetConsoleCursorPosition(hStdOut_user, poss);
		//	}

		//}
		//else
		//{
		//	if (a.Battle.size() == 0)
		//	{
		//		cout << "Choose any card to attack!" << endl;
		//		g = "empty";
		//	}
		//}
		//k = 0;
		//m = 1;
}

bool User::defend(Table &a)
{
	GetConsoleScreenBufferInfo(hStdOut_user, &csbuf_user);
	SetConsoleTextAttribute(hStdOut_user, BACKGROUND_GREEN | 7);
	COORD poss = { csbuf_user.dwMaximumWindowSize.X / 2 - 50, 22 };

	string g;
	int c_cnt = 0;
	int o_cnt = 0;
	int errors = 0;
	bool m = 1;
	int printed_rows = 0;
	int flag;
	int current;
	int card_n;
	int key;
	int unbeaten_prev = 0;
	int unbeaten_curr = 0;

	for (int i = 0; i < a.Battle.size()&&!empty(); i++)
	{
		if (a.Battle[i][1].getPower() == 0)
		{
			c_cnt++;
			SetConsoleCursorPosition(hStdOut_user, poss);
			SetConsoleTextAttribute(hStdOut_user, BACKGROUND_GREEN | 7);
			cout << "Choose a card to defend, or double press 'Space' to take" << endl;
			poss.Y++; printed_rows++; SetConsoleCursorPosition(hStdOut_user, poss);
			do {
				card_n = 0;
				flag = 1;
				current = getSize() * 20;
				print(0);
				while (flag) {
					if (_kbhit()) {
						key = _getch();
						switch (key) {
						case KEY_ESC:
							flag = 0;
							break;
						case KEY_ARROW_LEFT:
							current--;
							print(current % getSize());
							break;
						case KEY_ARROW_RIGHT:
							current++;
							print(current % getSize());
							break;
						case KEY_ENTER: {
							for (int i = 0; i < getSize(); i++) {
								card_n = current % getSize();
								if (card_n == i)break;
							}

							if (a.Battle[i][0].getPower() < hand[card_n].getPower() && (a.Battle[i][0].getSuit() == hand[card_n].getSuit() || hand[card_n].getSuit() == a.deck.getTrumpSuit()))
							{
								a.Battle[i][1] = hand[card_n];
								remove(hand[card_n]);
								o_cnt++;
								SetConsoleCursorPosition(hStdOut_user, poss);
								cout << "Got it!" << endl;
								poss.Y++; printed_rows++; SetConsoleCursorPosition(hStdOut_user, poss);
							}
							else
							{
								SetConsoleCursorPosition(hStdOut_user, poss);
								cout << "Error! Try another card or take!" << endl;
								poss.Y++; printed_rows++; SetConsoleCursorPosition(hStdOut_user, poss);
								errors++;
								if (errors >= 3)
								{
									SetConsoleCursorPosition(hStdOut_user, poss);
									cout << "It seems that you don't know what to do. Maybe it's better to take cards?";
									poss.Y++; printed_rows++; SetConsoleCursorPosition(hStdOut_user, poss);
								}
							}
						}break;
						case KEY_SPACE: {
							flag = 0;
							for (int i = 0; i < a.Battle.size(); i++){
								if (!a.Battle[i][1].getPower())
								{
									/*SetConsoleCursorPosition(hStdOut_user, poss);
									cout << "There are some unbeaten cards on the table!" << endl;
									poss.Y++; printed_rows++; SetConsoleCursorPosition(hStdOut_user, poss);*/
									unbeaten_curr++;
								}
								

							}
							if(unbeaten_prev==unbeaten_curr&& unbeaten_prev!=0)
								return false;
							unbeaten_prev = unbeaten_curr;
							unbeaten_curr = 0;
							
						/*
							flag = 0;
							space_cnt++;
							if (a.Battle.size() == 1 && !a.Battle[0][1].getPower())
								return false;
							else {
								for (int i = 1; i < a.Battle.size(); i++)
								{
									if (!a.Battle[i][1].getPower() && a.Battle[i][0].getRank() == a.Battle[i - 1][0].getRank() && space_cnt > a.Battle.size())
										return false;
								}
							}*/
						}
									  /*break;
						case KEY_BACKSPACE: {
							flag = 0;
							
							if (a.Battle.size() == 1 && !a.Battle[0][1].getPower())
								return false;
						}*/
						default:break;
						}

					}
				}
	
			} while (c_cnt != o_cnt);
		}
		errors = 0;
		/*if (a.Battle[i][1].getPower() == 0)
		{
			c_cnt++;
			do {
				SetConsoleCursorPosition(hStdOut_user, poss);
				cout << "Choose the card to defend (numbers from 1 to " << getSize() << ") or press 'Enter' to take" << endl;
				getline(cin, g);
				if (g.size() != 0) {
					for (int i = 0; i<g.size(); ++i)
						if (!isdigit(g.c_str()[i]))
							m = 0;
					if (!m)
						cout << "Error! It's not a number!" << endl;
					else
						if (getSize() <= stoi(g) - 1)
							cout << "Error! It's not a suitable number!" << endl;
						else {
							j = stoi(g) - 1;


							if (a.Battle[i][0].getPower() < hand[j].getPower() && (a.Battle[i][0].getSuit() == hand[j].getSuit() || hand[j].getSuit() == a.deck.getTrumpSuit()))
							{
								a.Battle[i][1] = hand[j];
								remove(hand[j]);
								o_cnt++;
								cout << "Got it!" << endl;
							}
							else
							{
								cout << "Error! Try another card or take!" << endl;
								errors++;
								if (errors >= 5)
									cout << "It seems that you don't know what to do. Maybe it's better to take cards?";
							}
						}
				}
				else
					return false;
			} while (c_cnt != o_cnt);
		}
		errors = 0;*/
	}
	return true;

	
}



User::~User()
{
}



