#include "main.h"

// 창크기 120 * 30


using namespace std;

// 
// drawTitle에서 selectMenu 함수 나누기
// 더블 점프 제대로 구현하기
// drawTitle, drawCtrl, quitGame, gameOver, gameClear ui 꾸미기
// 함수, 변수 이름 정리 
// 파일 분할...
// 타이틀에서 메뉴로 돌아가면 직전 메뉴 위치에 불 들어오게
//

int main()
{
    stopBgm();
    playingBgm();
    setScreenPoint();
    while (true)
    {
      drawTitle();
      if (isStart) startGame();
      if (isCtrl) showCtrl();
      if (isCredit) showCredit();
      if (isQuit && quitGame()) break; 
    }   
    
}



void playingBgm()
{
    int volume = 100;
    DWORD dwVolume = (DWORD)(0xFFFF * volume / 100);
    PlaySound(TEXT("BGM.wav"), NULL,SND_ASYNC | SND_LOOP | SND_NOSTOP);
    waveOutSetVolume(NULL, MAKELONG(dwVolume, dwVolume));
    
}

void playingGameBgm()
{
    int volume = 50;
    DWORD dwVolume = (DWORD)(0xFFFF * volume / 100);
    PlaySound(TEXT("gameBGM.wav"), NULL, SND_ASYNC | SND_LOOP | SND_NOSTOP);
    waveOutSetVolume(NULL, MAKELONG(dwVolume, dwVolume));
}

void stopBgm()
{
    PlaySound(NULL, NULL, NULL);   
}



void drawTitle()
{
    initConsole();
    
    //const int xStart = 10, xControl = 20, xQuit = 30;
    int x = screenPoint[19].X, y = screenPoint[19].Y; // 메뉴 시작 위치

    setColor(0, 10);
    gotoXY(screenPoint[8].X, screenPoint[8].Y);
    printf("3 8 초  버 티 기");
    // 
    //printf("                                             _|        _|      _|        _|                      _|    _|\n");
    //printf("               _|_|_|  _|      _|    _|_|          _|_|_|      _|_|_|    _|    _|_|      _|_|_|  _|  _|  \n");
    //printf("             _|    _|  _|      _|  _|    _|  _|  _|    _|      _|    _|  _|  _|    _|  _|        _|_|    \n");
    //printf("             _|    _|    _|  _|    _|    _|  _|  _|    _|      _|    _|  _|  _|    _|  _|        _|  _|  \n");
    //printf("               _|_|_|      _|        _|_|    _|    _|_|_|      _|_|_|    _|    _|_|      _|_|_|  _|    _|\n");
    //
    //printf("                                    ■         ■       ■         ■                       ■     ■  \n");
    //printf("      ■ ■ ■   ■       ■     ■ ■           ■ ■ ■       ■ ■ ■     ■     ■ ■       ■ ■ ■   ■   ■   \n");
    //printf("    ■     ■    ■     ■    ■     ■   ■   ■     ■       ■     ■   ■   ■     ■   ■         ■ ■     \n");
    //printf("    ■     ■     ■   ■     ■     ■   ■   ■     ■       ■     ■   ■   ■     ■   ■         ■   ■   \n");
    //printf("      ■ ■ ■       ■         ■ ■     ■     ■ ■ ■       ■ ■ ■     ■     ■ ■       ■ ■ ■   ■     ■ \n");

    //gotoXY(xStart, y);
    gotoXY(screenPoint[19].X, screenPoint[19].Y);
    setColor(0, 13);
    printf(" 시 작 ");

    //gotoXY(xControl, y);
    gotoXY(screenPoint[20].X, screenPoint[20].Y);
    setColor(0, 15);
    printf(" 조 작 ");

    //gotoXY(xQuit, y);
    gotoXY(screenPoint[21].X, screenPoint[21].Y);
    setColor(0, 15);
    printf(" 정 보 ");

    gotoXY(screenPoint[22].X, screenPoint[22].Y);
    setColor(0, 15);
    printf(" 종 료 ");

    initTime();
   
    while (true)
    {
        updateTime();
        if (getElapsedTime() >= showDelay)
        {
            static ULONGLONG temp;
            temp += getDeltaTime();
            if (temp >= inputDelay)
            {
                temp -= inputDelay;
                updateInput();
                int caseNum = 19;
                if (x == screenPoint[19].X) caseNum = 19;
                if (x == screenPoint[20].X) caseNum = 20;
                if (x == screenPoint[21].X) caseNum = 21;
                if (x == screenPoint[22].X) caseNum = 22;

                switch (caseNum)
                {
                case 19: // 시작
                    if (isSpace)
                    {
                        isSpace = false;
                        isStart = true;
                        return;
                    }
                    else if (isLeft)
                    {
                        isLeft = false;
                    }
                    else if (isRight)
                    {
                        x = screenPoint[19].X;
                        gotoXY(x, y);
                        setColor(0, 15);
                        printf(" 시 작 ");

                        x = screenPoint[20].X;
                        gotoXY(x, y);
                        setColor(0, 13);
                        printf(" 조 작 ");

                        isRight = false;
                    }
                case 20: // 조작
                    if (isSpace)
                    {
                        isSpace = false;
                        isCtrl = true;
                        return;
                    }
                    else if (isLeft)
                    {
                        x = screenPoint[20].X;
                        gotoXY(x, y);
                        setColor(0, 15);
                        printf(" 조 작 ");

                        x = screenPoint[19].X;
                        gotoXY(x, y);
                        setColor(0, 13);
                        printf(" 시 작 ");

                        isLeft = false;
                    }
                    else if (isRight)
                    {
                        x = screenPoint[20].X;
                        gotoXY(x, y);
                        setColor(0, 15);
                        printf(" 조 작 ");

                        x = screenPoint[21].X;
                        gotoXY(x, y);
                        setColor(0, 13);
                        printf(" 정 보 ");

                        isRight = false;
                    }
                case 21: // 정보
                    if (isSpace)
                    {
                        isSpace = false;
                        isCredit = true;
                        return;
                    }
                    else if (isLeft)
                    {
                        x = screenPoint[21].X;
                        gotoXY(x, y);
                        setColor(0, 15);
                        printf(" 정 보 ");

                        x = screenPoint[20].X;
                        gotoXY(x, y);
                        setColor(0, 13);
                        printf(" 조 작 ");

                        isLeft = false;
                    }
                    else if (isRight)
                    {
                        x = screenPoint[21].X;
                        gotoXY(x, y);
                        setColor(0, 15);
                        printf(" 정 보 ");

                        x = screenPoint[22].X;
                        gotoXY(x, y);
                        setColor(0, 13);
                        printf(" 종 료 ");

                        isRight = false;
                    }
                case 22: // 종료
                    if (isSpace)
                    {
                        isSpace = false;
                        isQuit = true;
                        return;
                    }
                    else if (isLeft)
                    {
                        x = screenPoint[22].X;
                        gotoXY(x, y);
                        setColor(0, 15);
                        printf(" 종 료 ");

                        x = screenPoint[21].X;
                        gotoXY(x, y);
                        setColor(0, 13);
                        printf(" 정 보 ");

                        isLeft = false;
                    }
                    else if (isRight)
                    {
                        isRight = false;
                    }
                }
            }
        }
        
    }
}



void showCtrl()
{

    initConsole();
    isCtrl = false;
    gotoXY(screenPoint[8].X, screenPoint[8].Y);
    setColor(0, 10);
    printf("조 작");
    gotoXY(screenPoint[7].X, screenPoint[8].Y + 6);
    setColor(0, 10);
    printf("         이 동  :  좌 우  방 향 키");
    gotoXY(screenPoint[7].X, screenPoint[8].Y + 8);
    setColor(0, 10);
    printf("         점 프  :  스 페 이 스 바");
    initTime();
    while (true)
    {
        updateTime();
        if (getElapsedTime() >= showDelay)
        {
            updateInput();
            if (isSpace)
            {
                isSpace = false;
                break;
            }
        }

    }
}

void showCredit()
{
    initConsole();
    isCredit = false;
    gotoXY(screenPoint[8].X, screenPoint[8].Y);
    setColor(0, 10);
    printf(" 정 보 ");
    gotoXY(screenPoint[7].X, screenPoint[8].Y + 6);
    setColor(0, 10);
    printf("                    플 밍  2 반");
    gotoXY(screenPoint[7].X, screenPoint[8].Y + 8);
    setColor(0, 10);
    printf("                     신 해 성");
    initTime();
    while (true)
    {
        updateTime();
        if (getElapsedTime() >= showDelay)
        {
            updateInput();
            if (isSpace)
            {
                isSpace = false;
                break;
            }
        }

    }
}



void startGame()
{
    
    isStart = false;

    initConsole();
    initTime();
    setStart();
    
    setObs();
    drawScreen();

    stopBgm();
    playingGameBgm();

    while (true)
    { 
        updateTime();
        generateObs();
        updateInput();
        updatePlayerMove();
        updateUI();
        if (isOver)
        {
            stopBgm();
            playingBgm();
            gameOver();
            break;
        }
        if (isClear)
        {
            stopBgm();
            playingBgm();
            gameClear();
            break;
        }
    }
    return;
}

bool quitGame() 
{
    // bool bySelect 만들어서 종료 선택했을 경우와 게임 후 나오는 화면 구분

    initConsole();

    isQuit = false;
    int x = screenPoint[19].X, y = screenPoint[19].Y;

    gotoXY(screenPoint[19].X, screenPoint[19].Y);
    setColor(0, 13);
    printf(" 메 인 으 로 ");

    gotoXY(screenPoint[21].X, screenPoint[21].Y);
    setColor(0, 15);
    printf(" 나 가 기 ");

    isQuit = false;
    gotoXY(screenPoint[7].X, screenPoint[7].Y);
    setColor(0, 10);
    printf("      게 임 을  종 료 하 시 겠 습 니 까 ?");

    initTime();

    while (true)
    {
        updateTime();
        if (getElapsedTime() >= showDelay)
        {
            updateInput();
            
            int caseNum;
            if (x == screenPoint[19].X) caseNum = 19;
            if (x == screenPoint[21].X) caseNum = 21;

            switch (caseNum)
            {
            case 19:
                if (isSpace)
                {
                    isSpace = false;
                    return false;
                }
                if (isRight) 
                {
                    isRight = false;

                    x = screenPoint[19].X;
                    gotoXY(x, y);
                    setColor(0, 15);
                    printf(" 메 인 으 로 ");

                    x = screenPoint[21].X;
                    gotoXY(x, y);
                    setColor(0, 13);
                    printf(" 나 가 기 ");
                }
            case 21:
                if(isSpace)
                {
                    isSpace = false;
                    return true;
                }
                if (isLeft)
                {
                    isLeft = false;

                    x = screenPoint[21].X;
                    gotoXY(x, y);
                    setColor(0, 15);
                    printf(" 나 가 기 ");

                    x = screenPoint[19].X;
                    gotoXY(x, y);
                    setColor(0, 13);
                    printf(" 메 인 으 로 ");
                }

            }
        }
    }
}



void gameOver()
{

    

    initConsole();
    isOver = false;

    gotoXY(screenPoint[8].X, screenPoint[8].Y);
    setColor(0, 10);
    printf("게임 오버\n");
    gotoXY(screenPoint[8].X, screenPoint[8].Y + 2);
    printf("time : %5.2f\n", timer);

    initTime();

    while (true)
    {
        updateTime();
        if (getElapsedTime() >= showDelay)
        {
          updateInput();
          if (isSpace)
          {
              isSpace = false;
              isQuit = true;
              break;
          }
        }
    }
}

void gameClear()
{
    initConsole();
    isClear = false;

    gotoXY(screenPoint[8].X, screenPoint[8].Y);
    setColor(0, 10);
    printf("클리어!");

    initTime();

    while (true)
    {
        updateTime();
        if (getElapsedTime() >= showDelay)
        {
            updateInput();
            if (isSpace)
            {
                isSpace = false;
                isQuit = true;
                break;
            }
        }
    }
}





void initTime()
{
    currentTime = previousTime = GetTickCount64();
    elapsedTime = 0;
}

void updateTime()
{
    previousTime = currentTime;
    currentTime = GetTickCount64();

    deltaTime = currentTime - previousTime;
    elapsedTime += deltaTime;
}

ULONGLONG getDeltaTime()
{
    return deltaTime;
}

ULONGLONG getElapsedTime()
{
    return elapsedTime;
}



void updateInput()
{
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        isLeft = true;
    }

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        isRight = true;
    }
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        //if (!isSpace) isSpace = true;
        //else isSpace = false;
        isSpace = true; 
    } 

}



void setScreenPoint()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    consoleScreenSize.Left = csbi.srWindow.Left;
    consoleScreenSize.Right = csbi.srWindow.Right;
    consoleScreenSize.Bottom = csbi.srWindow.Bottom;
    consoleScreenSize.Top = csbi.srWindow.Top;

    playerMovableRect.Left = consoleScreenSize.Left + 2;
    playerMovableRect.Right = consoleScreenSize.Right - 2;
    playerMovableRect.Bottom = consoleScreenSize.Bottom - 2;
    playerMovableRect.Top = consoleScreenSize.Top + 2;

    //위
    screenPoint[0] = { playerMovableRect.Left,playerMovableRect.Top };
    screenPoint[1] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 1,playerMovableRect.Top };
    screenPoint[2] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 2,playerMovableRect.Top };
    screenPoint[3] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 3,playerMovableRect.Top };
    screenPoint[4] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 4,playerMovableRect.Top };
    screenPoint[5] = { playerMovableRect.Right,playerMovableRect.Top };

    screenPoint[6] = { playerMovableRect.Left,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 1 };
    screenPoint[7] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 1,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 1 };
    screenPoint[8] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 2,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 1 };
    screenPoint[9] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 3,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 1 };
    screenPoint[10] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 4,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 1 };
    screenPoint[11] = { playerMovableRect.Right,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 1 };

    screenPoint[12] = { playerMovableRect.Left,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 2 };
    screenPoint[13] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 1,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 2 };
    screenPoint[14] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 2,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 2 };
    screenPoint[15] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 3,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 2 };
    screenPoint[16] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 4,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 2 };
    screenPoint[17] = { playerMovableRect.Right,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 2 };

    screenPoint[18] = { playerMovableRect.Left,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 3 };
    screenPoint[19] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 1,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 3 };
    screenPoint[20] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 2,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 3 };
    screenPoint[21] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 3,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 3 };
    screenPoint[22] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 4,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 3 };
    screenPoint[23] = { playerMovableRect.Right,(playerMovableRect.Top + playerMovableRect.Bottom) / 4 * 3 }; //23

    //아래
    screenPoint[24] = { playerMovableRect.Left,playerMovableRect.Bottom };
    screenPoint[25] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 1,playerMovableRect.Bottom };
    screenPoint[26] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 2,playerMovableRect.Bottom };
    screenPoint[27] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 3,playerMovableRect.Bottom };
    screenPoint[28] = { (playerMovableRect.Left + playerMovableRect.Right) / 5 * 4,playerMovableRect.Bottom };
    screenPoint[29] = { playerMovableRect.Right,playerMovableRect.Bottom };

}

void initConsole()
{
    // 화면 
    system("cls");
    setColor(0, 15);

    // 커서 숨기기
    HANDLE consonleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO consoleCursor;
    consoleCursor.bVisible = 0;
    consoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consonleHandle, &consoleCursor);
}

// 보라색 13 하얀색 15 검정색 0
void setColor(int backColor, int textColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (backColor << 4) + textColor);
}

void gotoXY(int x, int y)
{
    COORD cur = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void limit(short& n, short min, short max)
{
    if (n < min) n = min;
    if (n > max) n = max;
}



void setStart()
{
    hpCount = 3;
    timer = 0;
    isCrash = false;
}



void updateUI()
{
    // 경과 시간
    static ULONGLONG temp;
    temp += getDeltaTime();
    if (temp >= 10)
    {
        timer += 0.01;
        temp -= 10;
    }

    gotoXY(consoleScreenSize.Left + 1, consoleScreenSize.Top + 1);
    setColor(0, 15);
    printf("time : %5.2f", timer);

    // 남은 생명력 기호로 표현하기
    if (hpCount == 3)
    {
        gotoXY(consoleScreenSize.Right - 5, consoleScreenSize.Top + 1);
        setColor(0, 15);
        printf("O O O");
    }
    if (hpCount == 2)
    {
        gotoXY(consoleScreenSize.Right - 5, consoleScreenSize.Top + 1);
        setColor(0, 15);
        printf("X O O");
    }
    if (hpCount == 1)
    {
        gotoXY(consoleScreenSize.Right - 5, consoleScreenSize.Top + 1);
        setColor(0, 15);
        printf("X X O");
    }
    
    if (timer >= clearTime) isClear = true;
    if (hpCount == 0) isOver = true;

}



void drawScreen()
{
    for (int x = playerMovableRect.Left; x <= playerMovableRect.Right; x++)
    {
        gotoXY(x, playerMovableRect.Bottom + 1);
        setColor(15, 15);
        putchar(' ');
    }
    curPlayerPos.X = (playerMovableRect.Right + playerMovableRect.Left) / 2;
    curPlayerPos.Y = playerMovableRect.Bottom;
    prePlayerPos.X = (playerMovableRect.Right + playerMovableRect.Left) / 2;
    prePlayerPos.Y = playerMovableRect.Bottom;
    drawPlayer(true);
}



void updatePlayerMove()
{
    static ULONGLONG time = 0;
    time += getDeltaTime();
    
    while (time >= playerMoveSpeed)
    {
        updatePlayerPos();
        time -= playerMoveSpeed;
    }
}

void updatePlayerPos()
{
    prePlayerPos = curPlayerPos;

    // 공중에 떠있으면 내려오게 만든다.
    curPlayerPos.Y += velocity;
    velocity += gravity;
    if (curPlayerPos.Y <= 12)
    {
        velocity -= jumpVelocity;
    }
    
    if (curPlayerPos.Y <= playerMovableRect.Top)
    {
        curPlayerPos.Y = playerMovableRect.Top;
    }
    if (curPlayerPos.Y >= playerMovableRect.Bottom)
    {
        curPlayerPos.Y = playerMovableRect.Bottom;
        velocity = 0;
        onGround = true;
        onJump = false;
    }
    

    //static bool boo = true;
    //static ULONGLONG time = 0;
    //if (boo == false)
    //{
    //    time += getDeltaTime();
    //}
    //
    //if (time >= 200)
    //{
    //    time = 0;
    //    boo = true;
    //}
    //

    //if (isSpace)
    //{
    //    isSpace = false;
    //    // 땅에 있을 경우 점프
    //    if (onGround && boo)
    //    {
    //        boo = false;
    //        velocity += jumpVelocity;
    //        onGround = false;
    //    }
    //    // 공중에 있을 경우 더블점프
    //    if (!onGround && boo)
    //    {
    //        boo = false;
    //        onJump = true;
    //        velocity += doubleJumpVelocity;
    //    }
    //}


    if (isSpace)
    {
        isSpace = false;
        if (onGround)
        {
            velocity += jumpVelocity;
            onGround = false;
        }
 }

    if (isRight)
    {
        isRight = false;
        curPlayerPos.X++;
        limit(curPlayerPos.X, playerMovableRect.Left, playerMovableRect.Right);
    }
    if (isLeft)
    {
        isLeft = false;
        curPlayerPos.X--;
        limit(curPlayerPos.X, playerMovableRect.Left, playerMovableRect.Right);
    }

    if ((prePlayerPos.X != curPlayerPos.X) || (prePlayerPos.Y != curPlayerPos.Y))
    {
        drawPlayer(false);
    }
    else drawPlayer(true);
    

}

void drawPlayer(bool isClear)
{
    if (!isClear)
    {
        gotoXY(prePlayerPos.X, prePlayerPos.Y);
        setColor(0, 15);
        //putchar('  ');
        printf("  ");
    }

    if (isCrash)
    {
        static ULONGLONG temp;
        temp += getDeltaTime();
        if (temp < 200)
        {
            gotoXY(curPlayerPos.X, curPlayerPos.Y);
            setColor(10, 15);
            printf("  ");
        }
        else if (temp < 400)
        {
            gotoXY(curPlayerPos.X, curPlayerPos.Y);
            setColor(13, 15);
            printf("  ");

        }
        else if (temp < 600)
        {
            gotoXY(curPlayerPos.X, curPlayerPos.Y);
            setColor(10, 15);
            printf("  ");
        }
        else if (temp < 800)
        {
            gotoXY(curPlayerPos.X, curPlayerPos.Y);
            setColor(13, 15);
            printf("  ");
        }
        else if (temp < 1000)
        {
            gotoXY(curPlayerPos.X, curPlayerPos.Y);
            setColor(10, 15);
            printf("  ");
        }

        if (temp >= 1000)
        {
            temp -= 1000;
            isCrash = false;
        }
    }

    else
    {
        gotoXY(curPlayerPos.X, curPlayerPos.Y);
        setColor(13, 15);
        //putchar('  ');
        printf("  ");
    }
}



// obs 기본값 설정
void setObs()
{
    
     // 초코비 원샷하기
    {
        obs[0].time = 350;
        obs[0].curPos.X = screenPoint[1].X-10;
        obs[0].curPos.Y = screenPoint[1].Y;
        obs[0].speed = 30;
        obs[0].direction = 2;
        obs[0].scale = "                                             ";

        obs[1].time = 550;
        obs[1].curPos.X = screenPoint[3].X;
        obs[1].curPos.Y = screenPoint[1].Y;
        obs[1].speed = 20;
        obs[1].direction = 2;
        obs[1].scale = "                                             ";

        obs[2].time = 750;
        obs[2].curPos.X = screenPoint[1].X;
        obs[2].curPos.Y = screenPoint[1].Y;
        obs[2].speed = 20;
        obs[2].direction = 2;
        obs[2].scale = "                                             ";                                 
    }


    // 상자를 머리위로 높이들어서
    for (int i = 3; i < 11; i++)
    {

        if (i == 8 || i == 9)
        {
            obs[i].speed = 1;
        }
        else
        {
            obs[i].speed = 10;
        }

        obs[i].time = 1500;
        obs[i].curPos = screenPoint[13];
        obs[i].direction = i % 8;
        obs[i].scale = "  ";
 
    }
    for (int i = 11; i < 19; i++)
    {

        if (i == 16 || i == 17)
        {
            obs[i].speed = 1;
        }
        else
        {
            obs[i].speed = 10;
        }

        obs[i].time = 2100;
        obs[i].curPos = screenPoint[20];
        obs[i].direction = i % 8;
        obs[i].scale = "  ";

    }
    for (int i = 20; i < 28; i++)
    {

        if (i == 24 || i == 25)
        {
            obs[i].speed = 1;
        }
        else
        {
            obs[i].speed = 10;
        }

        obs[i].time = 2700;
        obs[i].curPos = screenPoint[16];
        obs[i].direction = i % 8;
        obs[i].scale = "  ";

    }
    
    // 전주
    for (int i = 28; i < 56; i++)
    {
        obs[i].time = (i - 28) * 720 + 4200;
        obs[i].curPos = screenPoint[24];
        obs[i].speed = 10;
        obs[i].direction = 0;
        obs[i].scale = "  ";
    }

    // 마음속의 외침
    for (int i = 56; i < 78; i++)
    {
        obs[i].time = (i - 56) * 25 + 9500;
        obs[i].curPos.Y = screenPoint[0].Y;
        obs[i].speed = 100;
        obs[i].direction = 2;
        obs[i].scale = "  ";

        obs[56].curPos.X = screenPoint[2].X;
        obs[57].curPos.X = screenPoint[2].X + 2;
        obs[58].curPos.X = screenPoint[2].X + 4;
        obs[59].curPos.X = screenPoint[2].X + 6;
        obs[60].curPos.X = screenPoint[2].X + 8;

        obs[61].curPos.X = screenPoint[4].X;
        obs[62].curPos.X = screenPoint[4].X + 2;
        obs[63].curPos.X = screenPoint[4].X + 4;
        obs[64].curPos.X = screenPoint[4].X + 6;
        obs[65].curPos.X = screenPoint[4].X + 8;

        obs[66].curPos.X = screenPoint[1].X;
        obs[67].curPos.X = screenPoint[1].X + 2;
        obs[68].curPos.X = screenPoint[1].X + 4;
        obs[69].curPos.X = screenPoint[1].X + 6;
        obs[70].curPos.X = screenPoint[1].X + 8;

        obs[71].curPos.X = screenPoint[3].X;
        obs[72].curPos.X = screenPoint[3].X + 2;
        obs[73].curPos.X = screenPoint[3].X + 4;
        obs[74].curPos.X = screenPoint[3].X + 6;
        obs[75].curPos.X = screenPoint[3].X + 8;

        obs[76].curPos.X = screenPoint[2].X + 8;
        obs[77].curPos.X = screenPoint[2].X;
    }

    // 짱돌
    for (int i = 78;i < 82; i++)
    {
        
        obs[i].time = (i - 78) * 200 + 15700;
        obs[i].curPos.Y = screenPoint[1].Y;
        obs[i].speed = 10;
        obs[i].direction = 2;
        obs[i].scale = "    ";
    
        obs[78].curPos.X = screenPoint[1].X;
        obs[79].curPos.X = screenPoint[3].X;
        obs[80].curPos.X = screenPoint[2].X;
        obs[81].curPos.X = screenPoint[4].X;
    }
    for (int i = 82; i < 86; i++)
    {

        obs[i].time = (i - 82) * 200 + 17100;
        obs[i].curPos.Y = screenPoint[1].Y;
        obs[i].speed = 10;
        obs[i].direction = 2;
        obs[i].scale = "    ";

        obs[82].curPos.X = screenPoint[1].X + 8;
        obs[83].curPos.X = screenPoint[3].X + 8;
        obs[84].curPos.X = screenPoint[2].X + 8;
        obs[85].curPos.X = screenPoint[4].X + 8;
    }
    for (int i = 86; i < 90; i++)
    {

        obs[i].time = (i - 86) * 200 + 18500;
        obs[i].curPos.Y = screenPoint[1].Y;
        obs[i].speed = 10;
        obs[i].direction = 2;
        obs[i].scale = "    ";

        obs[86].curPos.X = screenPoint[1].X;
        obs[87].curPos.X = screenPoint[3].X + 4;
        obs[88].curPos.X = screenPoint[2].X + 4;
        obs[89].curPos.X = screenPoint[4].X + 8;
    }

    // 맷돌
    for (int i = 90; i < 98; i += 2)
    {
        obs[i].time = (i - 90) * 100 + 21500;
        obs[i+1].time = (i - 90) * 100 + 21500;

        obs[i].curPos.X = screenPoint[18].X;
        obs[i+1].curPos.X = screenPoint[18].X;

        obs[i].speed = 10;
        obs[i+1].speed = 10;

        obs[i].direction = 0;
        obs[i+1].direction = 0;

        obs[i].scale = "    ";
        obs[i+1].scale = "    ";

        obs[90].curPos.Y = screenPoint[18].Y;
        obs[91].curPos.Y = screenPoint[18].Y + 1;

        obs[92].curPos.Y = screenPoint[6].Y;
        obs[93].curPos.Y = screenPoint[6].Y + 1;

        obs[94].curPos.Y = screenPoint[18].Y;
        obs[95].curPos.Y = screenPoint[18].Y + 1;

        obs[96].curPos.Y = screenPoint[6].Y;
        obs[97].curPos.Y = screenPoint[6].Y + 1;
    }
    for (int i = 98; i < 105; i += 2)
    {
        obs[i].time = (i - 98) * 100 + 22900;
        obs[i + 1].time = (i - 98) * 100 + 22900;

        obs[i].curPos.X = screenPoint[18].X;
        obs[i + 1].curPos.X = screenPoint[18].X;

        obs[i].speed = 10;
        obs[i + 1].speed = 10;

        obs[i].direction = 0;
        obs[i + 1].direction = 0;

        obs[i].scale = "    ";
        obs[i + 1].scale = "    ";

        obs[98].curPos.Y = screenPoint[18].Y + 2;
        obs[99].curPos.Y = screenPoint[18].Y + 3;

        obs[100].curPos.Y = screenPoint[12].Y + 2;
        obs[101].curPos.Y = screenPoint[12].Y + 3;

        obs[102].curPos.Y = screenPoint[18].Y + 2;
        obs[103].curPos.Y = screenPoint[18].Y + 3;

        obs[104].curPos.Y = screenPoint[12].Y + 2;
        obs[105].curPos.Y = screenPoint[12].Y + 3;
    }
    for (int i = 106; i < 120; i++)
    {
        obs[i].time = 25000;
        obs[i].curPos.X = screenPoint[23].X - 40;
        obs[i].speed = 10;
        obs[i].direction = 1;
        obs[i].scale = "                                       ";

        obs[i].curPos.Y = screenPoint[23].Y - i + 106 ;
    }

    // 초코비 2트
    {
        obs[120].time = 25200;
        obs[120].curPos.X = screenPoint[1].X;
        obs[120].curPos.Y = screenPoint[1].Y;
        obs[120].speed = 20;
        obs[120].direction = 2;
        obs[120].scale = "                                             ";

        obs[121].time = 25400;
        obs[121].curPos.X = screenPoint[3].X;
        obs[121].curPos.Y = screenPoint[1].Y;
        obs[121].speed = 20;
        obs[121].direction = 2;
        obs[121].scale = "                                             ";

        obs[122].time = 25600;
        obs[122].curPos.X = screenPoint[1].X;
        obs[122].curPos.Y = screenPoint[1].Y;
        obs[122].speed = 20;
        obs[122].direction = 2;
        obs[122].scale = "                                             ";
    }
   
    // 아원츄베이베
    for (int i = 123; i < 131; i++)
    {
        obs[i].time = (i - 123) * 100 + 27000;
        obs[i].speed = 10;
        obs[i].direction = 4;
        obs[i].scale = "  ";

        obs[123].curPos = screenPoint[12];
        obs[124].curPos = screenPoint[6];
        obs[125].curPos = screenPoint[1];
        obs[126].curPos = screenPoint[2];
        obs[127].curPos = screenPoint[6];
        obs[128].curPos = screenPoint[12];
        obs[129].curPos = screenPoint[2];
        obs[130].curPos = screenPoint[1];
    }

    // 아니쥬베이베
    for (int i = 131; i < 139; i++)
    {
        obs[i].time = (i - 131) * 100 + 28500;
        obs[i].speed = 10;
        obs[i].direction = 6;
        obs[i].scale = "  ";

        obs[131].curPos = screenPoint[3];
        obs[132].curPos = screenPoint[4];
        obs[133].curPos = screenPoint[11];
        obs[134].curPos = screenPoint[17];
        obs[135].curPos = screenPoint[4];
        obs[136].curPos = screenPoint[3];
        obs[137].curPos = screenPoint[17];
        obs[138].curPos = screenPoint[11];
    }

    // 알러뷰베이베
    for (int i = 139; i < 171; i += 2)
    {
        obs[i].time = (i - 139) * 100 + 30000;
        obs[i + 1].time = (i + 1 - 139) * 100 + 30000;
        obs[i].speed = 10;
        obs[i + 1].speed = 10;
        
        obs[i].direction = 6;
        obs[i + 1].direction = 4;

        obs[i].scale = "  ";
        obs[i + 1].scale = "  ";

        obs[139].curPos = screenPoint[3];
        obs[141].curPos = screenPoint[4];
        obs[143].curPos = screenPoint[11];
        obs[145].curPos = screenPoint[17];
        obs[147].curPos = screenPoint[4];
        obs[149].curPos = screenPoint[3];
        obs[151].curPos = screenPoint[17];
        obs[153].curPos = screenPoint[11];
        obs[155].curPos = screenPoint[3];
        obs[157].curPos = screenPoint[4];
        obs[159].curPos = screenPoint[11];
        obs[161].curPos = screenPoint[17];
        obs[163].curPos = screenPoint[4];
        obs[165].curPos = screenPoint[3];
        obs[167].curPos = screenPoint[17];
        obs[169].curPos = screenPoint[11];

        obs[140].curPos = screenPoint[12];
        obs[142].curPos = screenPoint[6];
        obs[144].curPos = screenPoint[1];
        obs[146].curPos = screenPoint[2];
        obs[148].curPos = screenPoint[6];
        obs[150].curPos = screenPoint[12];
        obs[152].curPos = screenPoint[2];
        obs[154].curPos = screenPoint[1];
        obs[156].curPos = screenPoint[12];
        obs[158].curPos = screenPoint[6];
        obs[160].curPos = screenPoint[1];
        obs[162].curPos = screenPoint[2];
        obs[164].curPos = screenPoint[6];
        obs[166].curPos = screenPoint[12];
        obs[168].curPos = screenPoint[2];
        obs[170].curPos = screenPoint[1];
    }


    for (int i = 0; i < maxObs; i++)
    {
        obs[i].prePos = obs[i].curPos;
    }
}

// obs 생성 시간 적용
void generateObs()
{
    ULONGLONG time = getElapsedTime();

    for (int i = 0; i < maxObs; i++)
    {
        if (time >= obs[i].time)
        {
            updateObsMove(i);
        }
    }

}

// obs 이동 속도 적용 &  & 다른 obs 함수들 호출
void updateObsMove(int i)
{
    static ULONGLONG time;
    time += getDeltaTime();

    if (time >= obs[i].speed)
    {
        updateObsPos(i);
        updateObsDraw(i);
        updateCollision(i);
        time -= obs[i].speed;
    }

}

// obs 이동 방향 적용 : 오른쪽 0 왼쪽 1 아래 2 위 3
void updateObsPos(int i)
{
    obs[i].prePos = obs[i].curPos;

    switch (obs[i].direction)
    {
    case(0):
        obs[i].curPos.X++;
        break;
    case(1):
        obs[i].curPos.X--;
        break;
    case(2):
        obs[i].curPos.Y++;
        break;
    case(3):
        obs[i].curPos.Y--;
        break;
    case(4):
        obs[i].curPos.X++;
        obs[i].curPos.Y++;
        break;
    case(5):
        obs[i].curPos.X++;
        obs[i].curPos.Y--;
        break;
    case(6):
        obs[i].curPos.X--;
        obs[i].curPos.Y++;
        break;
    case(7):
        obs[i].curPos.X--;
        obs[i].curPos.Y--;
        break;
    }
}

// obs 생성 위치 적용 & draw 
void updateObsDraw(int i)
{
    // 이전 위치 삭제

    if (obs[i].prePos.Y > playerMovableRect.Bottom)
    {
        obs[i].prePos.Y = playerMovableRect.Top;
    }

    gotoXY(obs[i].prePos.X, obs[i].prePos.Y);
    setColor(0, 0);
    printf("%s", obs[i].scale);
   

    // 화면 벗어나면 끝
    if (obs[i].curPos.X >= playerMovableRect.Right)
    {
        obs[i].curPos.X = playerMovableRect.Right;
        return;
    }
    if (obs[i].curPos.X <= playerMovableRect.Left)
    {
        obs[i].curPos.X = playerMovableRect.Left;
        return;
    }
    if (obs[i].curPos.Y > playerMovableRect.Bottom)
    {
        //obs[i].prePos.Y = playerMovableRect.Bottom + 1;
        obs[i].curPos.Y = playerMovableRect.Bottom + 1;
        
    }
    if (obs[i].curPos.Y <= playerMovableRect.Top)
    {
        obs[i].curPos.Y = playerMovableRect.Top;
        return;
    }
    


    // 현재 위치 표시
    gotoXY(obs[i].curPos.X, obs[i].curPos.Y);
    setColor(15, 0);
    printf("%s", obs[i].scale);
    

   
}

// obs와 플레이어 충돌 감지
void updateCollision(int i)
{

    
    if (!isCrash)
    {
      
        for (int k = 0; k < strlen(obs[i].scale); k++)
        {
            if (obs[i].curPos.X + k == curPlayerPos.X && obs[i].curPos.Y == curPlayerPos.Y)
            {
                hpCount--;
                isCrash = true;
            }
            
        }
   
        
    }
}
