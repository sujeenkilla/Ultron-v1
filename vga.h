#pragma once
#include "stdint.h"

#define MAKE_COLOR(fg, bg) ((fg) | ((bg) << 4))

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GRAY 7
#define DARK_GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define YELLOW 14
#define WHITE 15


#define width 80 //col
#define height 25 //rows

//to access a location formula == at(row,col)= 0xB8000(row*80+col)*2;

void print(const char* s);

void scrollUp();

void newLine();
void reSet();

unsigned short makeEntry(unsigned char c, unsigned char color);