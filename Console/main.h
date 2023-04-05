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

bool isStart;
bool isCtrl;
bool isQuit;

bool isLeft;
bool isRight;
bool isSpace;


double velocity;
bool onGround = true;
bool canJump;
bool doubleJumpAvailable = true;

const double gravity = 0.01;
const double jumpVelocity = -0.03;
const double doubleJumpVelocity = -0.02;

ULONGLONG previousTime;
ULONGLONG currentTime;
ULONGLONG deltaTime;
ULONGLONG elapsedTime;

SMALL_RECT consoleScreenSize;
SMALL_RECT playerMovableRect;

COORD prePlayerPos;
COORD curPlayerPos;


void drawTitle();

void drawCtrl();

void startGame();

void quitGame();

void limit(short&, short, short);