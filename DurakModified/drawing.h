#pragma once
#include <iostream>
#include <windows.h>
#include <string>
using namespace std;
#define WHITE 15
#define RED 12
#define GREY 7

void draw_border(int len, int h, COORD Starting_Pos, char line[], CONSOLE_SCREEN_BUFFER_INFO csbuf_dr, HANDLE hStdOut_dr);
void print_logo(COORD pos, CONSOLE_SCREEN_BUFFER_INFO csbuf_dr, HANDLE hStdOut_dr);
