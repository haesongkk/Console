#pragma once

#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "input.h"
#include "util.h"
//#include "menu.h"
#include "time.h"
#include "game.h"

const int playerMoveSpeed = 1;
const int obsMoveSpeed = 1;

int updateCount = 0;

int hpCount;
double timer;

struct obstacle
{
    COORD pos; // 생성위치
    ULONGLONG time;
    double speed; // 이동속도
    int direction; // 이동방향
};

obstacle obs[100];

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

COORD screenPoint[30];

COORD prePlayerPos;
COORD curPlayerPos;

void setStart();
void drawTitle();
void drawCtrl();
void startGame();
void updateScreen();
void quitGame();
void limit(short&, short, short);
void setObs();
void generateObs();
void updateObsMove(int);
void updateUI();
void updateObsPos(int);

void updateObsDraw(int);

void updateCollision(int);