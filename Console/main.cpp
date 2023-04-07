#include "main.h"

using namespace std;

// 
// drawTitle에서 selectMenu 함수 나누기
//  
// +++
// 
// 장애물 설정 다양하게 >> setObs
// 배경음악 넣기
// 
// 더블 점프 제대로 구현하기
// drawTitle, drawCtrl, quitGame, gameOver, gameClear ui 꾸미기
// 함수, 변수 이름 정리 
// 파일 분할...
// 타이틀에서 메뉴로 돌아가면 직전 메뉴 위치에 불 들어오게
//

int main()
{
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



void drawTitle()
{
    initConsole();

    //const int xStart = 10, xControl = 20, xQuit = 30;
    int x = screenPoint[19].X, y = screenPoint[19].Y; // 메뉴 시작 위치

    setColor(0, 10);
    gotoXY(0, screenPoint[8].Y);
    // printf("장 애 물  피 하 기");
    // 
    printf("                                             _|        _|      _|        _|                      _|    _|\n");
    printf("               _|_|_|  _|      _|    _|_|          _|_|_|      _|_|_|    _|    _|_|      _|_|_|  _|  _|  \n");
    printf("             _|    _|  _|      _|  _|    _|  _|  _|    _|      _|    _|  _|  _|    _|  _|        _|_|    \n");
    printf("             _|    _|    _|  _|    _|    _|  _|  _|    _|      _|    _|  _|  _|    _|  _|        _|  _|  \n");
    printf("               _|_|_|      _|        _|_|    _|    _|_|_|      _|_|_|    _|    _|_|      _|_|_|  _|    _|\n");
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
    printf("                 플 밍  2 반");
    gotoXY(screenPoint[7].X, screenPoint[8].Y + 8);
    setColor(0, 10);
    printf("                   신 해 성");
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

    while (true)
    { 
        updateTime();
        generateObs();
        updateInput();
        updatePlayerMove();
        updateUI();
        if (isOver)
        {
            gameOver();
            break;
        }
        if (isClear)
        {
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
        setColor(0, 15);
        putchar('#');
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
            setColor(4, 15);
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
            setColor(4, 15);
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
            setColor(4, 15);
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
    // 생성 위치
    for (int i = 0; i < 100; i++)
    {
        if (i % 5 == 0) obs[i].curPos = screenPoint[24];
        if (i % 5 == 1) obs[i].curPos = screenPoint[11];
        if (i % 5 == 3) obs[i].curPos = screenPoint[12];
        if (i % 5 == 2) obs[i].curPos = screenPoint[23];
        if (i % 5 == 4) obs[i].curPos = screenPoint[0];
    }
    for (int i = 0; i < 100; i++)
    {
        obs[i].prePos = obs[i].curPos;
    }
    // 생성 시간
    for (int i = 0; i < 100; i++)
    {
        //
        obs[i].time = i * 300;
    }
    // 이동 속도
    for (int i = 0; i < 100; i++)
    {
        if (i < 10) obs[i].speed = 10;
        else if (i < 20) obs[i].speed = 20;
        else if (i < 30) obs[i].speed = 10;
        else if (i < 40) obs[i].speed = 5;
        else if (i < 50) obs[i].speed = 1;

    }
        
    // 이동 방향
    for (int i = 0; i < 100; i++)
    {
        if (i % 2 == 0) obs[i].direction = 0;
        if (i % 2 == 1) obs[i].direction = 1;
    }
}

// obs 생성 시간 적용
void generateObs()
{
    ULONGLONG time = getElapsedTime();

    for (int i = 0; i < 100; i++)
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
    }
}

// obs 생성 위치 적용 & draw
void updateObsDraw(int i)
{
    // 이전 위치 삭제

    gotoXY(obs[i].prePos.X, obs[i].prePos.Y);
    setColor(0, 0);
    printf("  ");


    // 화면 벗어나면 끝
    if (obs[i].curPos.X > consoleScreenSize.Right) return;
    if (obs[i].curPos.X < consoleScreenSize.Left) return;
    if (obs[i].curPos.Y > consoleScreenSize.Bottom) return;
    if (obs[i].curPos.Y < consoleScreenSize.Top) return;

    // 현재 위치 표시
    gotoXY(obs[i].curPos.X, obs[i].curPos.Y);
    setColor(15, 0);
    printf("  ");


   
}

// obs와 플레이어 충돌 감지
void updateCollision(int i)
{
    if (!isCrash)
    {
        if (obs[i].curPos.X == curPlayerPos.X && obs[i].curPos.Y == curPlayerPos.Y)
        {
            hpCount--;
            isCrash = true;
        }
        else if (obs[i].curPos.X == prePlayerPos.X && obs[i].curPos.Y == prePlayerPos.Y)
        {
            hpCount--;
            isCrash = true;
        }
    }
}
