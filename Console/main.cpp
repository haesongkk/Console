#include "main.h"

using namespace std;

//
// 게임 종료 >> quitGame
// 
// 게임 오버, 게임 클리어 >> startGame
// 크레딧 >> main
// 
// updateUI 제대로 >> updateUI
// hpCount--시 깜빡이는 이벤트 넣기 >> drawPlayer
//  
// +++
// 
// 장애물 설정 다양하게 >> setObs
// 배경음악 넣기
// 더블 점프 제대로 구현하기
// drawTitle, drawCtrl, quitGame, gameOver, gameClear ui 꾸미기
// 함수, 변수 이름 정리 (drawTitle >> titleMenu)
// 파일 분할...
//

int main()
{
    setScreenPoint();
    while (true)
    {
        drawTitle();
        if (isStart) startGame();
        if (isCtrl) drawCtrl();
        if (isQuit) quitGame();
        // if(isCredit) showCredit(); 생성
    }   
}






void drawTitle()
{
    initConsole();

    //const int xStart = 10, xControl = 20, xQuit = 30;
    int x = screenPoint[19].X, y = screenPoint[19].Y; // 메뉴 시작 위치

    setColor(0, 15);
    printf("메인 화면");

    //gotoXY(xStart, y);
    gotoXY(screenPoint[19].X, screenPoint[19].Y);
    setColor(0, 15);
    printf(" 시 작 ");

    //gotoXY(xControl, y);
    gotoXY(screenPoint[20].X, screenPoint[20].Y);
    setColor(0, 15);
    printf(" 조 작 ");

    //gotoXY(xQuit, y);
    gotoXY(screenPoint[21].X, screenPoint[21].Y);
    setColor(0, 15);
    printf(" 종 료 ");

    getKey();
    isLeft = false;
    isSpace = false;
    isRight = false;

    //x = xStart;
    gotoXY(x, y);
    setColor(0, 13);
    printf(" 시 작 ");

    while (true)
    {
        getKey();
        int caseNum = 19;
        if (x == screenPoint[19].X) caseNum = 19;
        if (x == screenPoint[20].X) caseNum = 20;
        if (x == screenPoint[21].X) caseNum = 21;

        switch (caseNum)
        {
        case 19:
            if (isSpace) // 시작
            {
                isSpace = false;
                isStart = true;
                return;
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
        case 20:
            if (isSpace) // 조작
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
                printf(" 종 료 ");

                isRight = false;
            }
        case 21:
            if (isSpace) //종료
            {
                isSpace = false;
                isQuit = true;
                return;
            }
            else if (isLeft)
            {
                x = screenPoint[21].X;
                gotoXY(x, y);
                setColor(0, 15);
                printf(" 종 료 ");

                x = screenPoint[20].X;
                gotoXY(x, y);
                setColor(0, 13);
                printf(" 조 작 ");

                isLeft = false;
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
        //updateScreen();
        updateUI();
        if (hpCount == 0)
        {
            // 게임 오버 화면 만들기 : 점수표시, 메인으로 돌아가기
            // gameOver(); : (점수 표시) 스페이스바 >> quitGame();
            isQuit = true;
            break;
        }
        // if(isClear) gameClear(); : 스페이스바 >> quitGame();
    }
    return;
}

void drawCtrl()
{

    initConsole();
    isCtrl = false;
    printf("조작 방법");

    while (true)
    {
        getKey();
        if (isSpace)
        {
            isSpace = false;
            break;
        }
    }
}

void quitGame()
{
    initConsole();
    isQuit = false;
    gotoXY(0, 0);
    setColor(0, 15);
    printf("게임 종료");

    while (true)
    {
        // 시작화면으로 돌아가기
        // 게임 종료
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






void getKey()
{
    char key = _getch();
    if (key == -32)
    {
        key = _getch();
        if (key == 75) isLeft = true;
        if (key == 77) isRight = true;
    }
    if (key == ' ')
    {
        isSpace = true;
    }
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
        isSpace = true;
    }

}






void initConsole()
{
    // 화면 
    setColor(0, 15);
    system("cls");

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
    //ui 위치 screenPoint로 설정하기!


    // 경과 시간
    static ULONGLONG temp;
    temp += getDeltaTime();
    if (temp >= 10)
    {
        timer += 0.01;
        temp -= 10;
        
    }

    gotoXY(consoleScreenSize.Left, consoleScreenSize.Top);
    setColor(15, 13);
    printf("time : %5.2f", timer);

    // 남은 생명력 기호로 표현하기
 
    gotoXY(consoleScreenSize.Right - 10, consoleScreenSize.Top);
    setColor(15, 13);
    cout << hpCount;

    
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

// 장애물이 맵을 자꾸 지워서 임시로 만든 함수
void updateScreen()
{
    for (int x = playerMovableRect.Left; x <= playerMovableRect.Right; x++)
    {
        gotoXY(x, playerMovableRect.Bottom + 1);
        setColor(0, 15);
        putchar('#');
    }

    for (int x = playerMovableRect.Left - 1; x < playerMovableRect.Right + 1; x++)
    {
        gotoXY(x, playerMovableRect.Top - 1);
        setColor(0, 15);
        putchar(' ');
        gotoXY(x, playerMovableRect.Bottom + 2);
        setColor(0, 15);
        putchar(' ');
    }
    for (int y = playerMovableRect.Top - 1; y < playerMovableRect.Bottom + 1; y++)
    {
        gotoXY(playerMovableRect.Left - 1, y);
        setColor(0, 15);
        putchar(' ');
        gotoXY(playerMovableRect.Right +  1, y);
        setColor(0, 15);
        putchar(' ');
    }
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

    // int 값으로 space 바 누른 횟수 체크
    if (isSpace)
    {
        isSpace = false;
        if (onGround)
        {
            velocity = jumpVelocity;
            onGround = false;
        }
        if (canJump)
        {
            velocity = doubleJumpVelocity;
        }
        
    }
   
    // 공중에 떠있으면 내려오게 만든다.
    curPlayerPos.Y += velocity;
    velocity += gravity;

    if (curPlayerPos.Y <= playerMovableRect.Top)
    {
        curPlayerPos.Y = playerMovableRect.Top;
    }
    if (curPlayerPos.Y >= playerMovableRect.Bottom)
    {
        curPlayerPos.Y = playerMovableRect.Bottom;
        velocity = 0;
        onGround = true;
        canJump = false;
    }
    else if (curPlayerPos.Y > 20)
    {
        canJump = true;
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

    //if(isCrash)

    gotoXY(curPlayerPos.X, curPlayerPos.Y);
    setColor(13, 15);
    //putchar('  ');
    printf("  ");
}





// obs 기본값 설정
void setObs()
{
    // 생성 위치
    for (int i = 0; i < 100; i++)
    {
        if (i % 5 == 0) obs[i].curPos = screenPoint[24];
        if (i % 5 == 1) obs[i].curPos = screenPoint[18];
        if (i % 5 == 3) obs[i].curPos = screenPoint[12];
        if (i % 5 == 2) obs[i].curPos = screenPoint[6];
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
        obs[i].time = i * 1000;
    }
    // 이동 속도
    for (int i = 0; i < 100; i++)
    {
        if (i < 10) obs[i].speed = 20;
        else if (i < 20) obs[i].speed = 20;
        else if (i < 30) obs[i].speed = 10;
        else if (i < 40) obs[i].speed = 5;
        else if (i < 50) obs[i].speed = 1;

    }
        
    // 이동 방향
    for (int i = 0; i < 100; i++)
    {
        obs[i].direction = 0;
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

void updateCollision(int i)
{
    if (obs[i].curPos.X == curPlayerPos.X && obs[i].curPos.Y == curPlayerPos.Y) hpCount--;
    else if (obs[i].curPos.X == prePlayerPos.X && obs[i].curPos.Y == prePlayerPos.Y) hpCount--;
}
