#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>

#include "input.h"
#include "util.h"
//#include "menu.h"
#include "time.h"
#include "game.h"

const int playerMoveSpeed = 1;

int updateCount = 0;
int updatePlayerCount = 0;


bool isStart;
bool isCtrl;
bool isQuit;

bool isLeft;
bool isRight;
bool isSpace;

bool isJumping;
int jumpCount = 0;
int jumpHeight = 3;

ULONGLONG previousTime;
ULONGLONG currentTime;
ULONGLONG deltaTime;

SMALL_RECT consoleScreenSize;
SMALL_RECT playerMovableRect;

COORD prePlayerPos;
COORD curPlayerPos;


void drawTitle();

void drawCtrl();

void startGame();

void quitGame();

void limit(short&, short, short);