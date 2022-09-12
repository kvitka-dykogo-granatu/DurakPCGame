#include "drawing.h"
void draw_border(int len, int h, COORD Starting_Pos, char line[], CONSOLE_SCREEN_BUFFER_INFO csbuf_dr, HANDLE hStdOut_dr) {
	COORD Pos = Starting_Pos;
	SetConsoleCursorPosition(hStdOut_dr, Pos);
	cout << line[0];
	Pos.X++;

	for (int i = 0; i < len; i++) {
		SetConsoleCursorPosition(hStdOut_dr, Pos);
		cout << line[1];
		Pos.Y = Pos.Y + h + 1;
		SetConsoleCursorPosition(hStdOut_dr, Pos);
		cout << line[1];
		Pos.Y = Starting_Pos.Y;
		Pos.X++;
	}
	SetConsoleCursorPosition(hStdOut_dr, Pos);
	cout << line[2];
	Pos = Starting_Pos;
	Pos.Y = Pos.Y + h + 1;
	SetConsoleCursorPosition(hStdOut_dr, Pos);
	cout << line[5];
	Pos.X = Pos.X + len + 1;
	SetConsoleCursorPosition(hStdOut_dr, Pos);
	cout << line[4];
	Pos = Starting_Pos;
	Pos.Y++;

	for (int j = 0; j < h; j++) {
		SetConsoleCursorPosition(hStdOut_dr, Pos);
		cout << line[3];
		Pos.X = Pos.X + len + 1;
		SetConsoleCursorPosition(hStdOut_dr, Pos);
		cout << line[3];
		Pos.X = Starting_Pos.X;
		Pos.Y++;
	}
}

void print_logo(COORD pos, CONSOLE_SCREEN_BUFFER_INFO csbuf_dr, HANDLE hStdOut_dr) {
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	SetConsoleCursorPosition(hStdOut_dr, { static_cast<SHORT>(csbuf_dr.dwMaximumWindowSize.X / 2 - 20),  1 });
	cout << ".------..------..------..------..------.\n";
	//-------------------------------------------
	SetConsoleCursorPosition(hStdOut_dr, { static_cast<SHORT>(csbuf_dr.dwMaximumWindowSize.X / 2 - 20),  2 });
	cout << "|";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 0); cout << "D";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << ".--. ||";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 12); cout << "U";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << ".--. ||";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 0); cout << "R";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << ".--. ||";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 12); cout << "A";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << ".--. ||";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 0); cout << "K";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << ".--. |\n";
	//-------------------------------------------
	SetConsoleCursorPosition(hStdOut_dr, { static_cast<SHORT>(csbuf_dr.dwMaximumWindowSize.X / 2 - 20),  3 });
	cout << "| :";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 0); cout << "/\\";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << ": || ";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 12); cout << "(\\/)";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << " || :";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 0); cout << "()";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << ": || :";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 12); cout << "/\\";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << ": || :";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 0); cout << "/\\";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << ": | \n";
	//-------------------------------------------

	SetConsoleCursorPosition(hStdOut_dr, { static_cast<SHORT>(csbuf_dr.dwMaximumWindowSize.X / 2 - 20),  4 });
	cout << "| ";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 0); cout << "(__)";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << " || :";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 12); cout << "\\/";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << ": || ";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 0); cout << "()()";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << " || :";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 12); cout << "\\/";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << ": || ";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 0); cout << "(__)";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << " | \n";
	//-------------------------------------------
	SetConsoleCursorPosition(hStdOut_dr, { static_cast<SHORT>(csbuf_dr.dwMaximumWindowSize.X / 2 - 20),  5 });
	cout << "| '--'";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 0); cout << "D";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << "|| '--'";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 12); cout << "U";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << "|| '--'";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 0); cout << "R";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << "|| '--'";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 12); cout << "A";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << "|| '--'";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | 0); cout << "K";
	SetConsoleTextAttribute(hStdOut_dr, BACKGROUND_GREEN | WHITE);
	cout << "|\n";
	SetConsoleCursorPosition(hStdOut_dr, { static_cast<SHORT>(csbuf_dr.dwMaximumWindowSize.X / 2 - 20),  6 });
	cout << "`------'`------'`------'`------'`------'\n";

}

