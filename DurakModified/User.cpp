#include "User.h"
CONSOLE_SCREEN_BUFFER_INFO csbuf_user;
HANDLE hStdOut_user = GetStdHandle(STD_OUTPUT_HANDLE);


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

				
		}
	} while (!stop && a.Battle.size() < a.Battle_max_size && !empty());
	return res;

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
									
									unbeaten_curr++;
								}
								

							}
							if(unbeaten_prev==unbeaten_curr&& unbeaten_prev!=0)
								return false;
							unbeaten_prev = unbeaten_curr;
							unbeaten_curr = 0;
						
						}

						default:break;
						}

					}
				}
	
			} while (c_cnt != o_cnt);
		}
		errors = 0;
	}
	return true;

	
}



User::~User()
{
}



