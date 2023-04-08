#pragma once

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string.h>


#pragma comment (lib, "winmm.lib")    //음악
#include <mmsystem.h>;                //음악
#include <Digitalv.h>;                //음악

#include "input.h"
#include "util.h"
//#include "menu.h"
#include "time.h"
#include "game.h"




void playingBgm();
void playingGameBgm();
void stopBgm();


const int playerMoveSpeed = 9;
const int playerJumpSpeed = 10;
const int obsMoveSpeed = 1;

int updateCount = 0;

int hpCount;
double timer;

const double clearTime = 38;

struct obstacle
{
    COORD curPos; // 생성위치
    COORD prePos;
    ULONGLONG time;
    double speed; // 이동속도
    int direction; // 이동방향
    const char* scale = "  ";
};

const int maxObs = 171;

obstacle obs[maxObs];

bool isStart;
bool isCtrl;
bool isQuit;
bool isCredit;

bool isOver;
bool isClear;

bool isLeft;
bool isRight;
bool isSpace;

const ULONGLONG inputDelay = 100;
const ULONGLONG showDelay = 500;
const ULONGLONG jumpDelay = 10;

double velocity;
bool onGround = true;
bool onJump;
bool isCrash;

const double gravity = 0.02;
const double jumpVelocity = -0.3; // 2단 구현되면 0.08
const double doubleJumpVelocity = -0.2;

ULONGLONG previousTime;
ULONGLONG currentTime;
ULONGLONG deltaTime;
ULONGLONG elapsedTime;

SMALL_RECT consoleScreenSize;
SMALL_RECT playerMovableRect;

COORD screenPoint[30];

COORD prePlayerPos;
COORD curPlayerPos;


void playingBgm();
void playingGameBGM();

void gameOver();
void gameClear();

void updatePlayerJump();
void updatePlayerPosY();


void setStart();
void drawTitle();
void showCtrl();
void startGame();
void showCredit();
void updateScreen();
bool quitGame();
void limit(short&, short, short);
void setObs();
void generateObs();
void updateObsMove(int);
void updateUI();
void updateObsPos(int);

void updateObsDraw(int);

void updateCollision(int);