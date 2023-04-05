#include "main.h"

using namespace std;

struct obstacle
{
    COORD pos; // 생성위치
    
    double speed; // 이동속도
    int direction; // 이동방향

    // 생성자
    obstacle(int initX, int initY, double initSpeed, int initDirection)
    {
        pos.X = initX; pos.Y = initY;
        speed = initSpeed;
        direction = initDirection;
    }

    // 오른쪽 0 왼쪽 1 아래 2 위 3
    void move()
    {
        switch (direction)
        {
        case(0):
            pos.X++;
            break;
        case(1):
            pos.X--;
            break;
        case(2):
            pos.Y++;
            break;
        case(3):
            pos.Y--;
            break;
        }
    }

    void draw()
    {
        // 이전 위치 삭제
        switch (direction)
        {
        case(0): // 오른쪽
            gotoXY(pos.X - 1, pos.Y);
            setColor(0, 0);
            printf("  ");

            break;
        case(1): // 왼쪽
            gotoXY(pos.X + 1, pos.Y);
            setColor(0, 0);
            printf("  ");
            break;
        case(2): // 아래
            gotoXY(pos.X, pos.Y - 1);
            setColor(0, 0);
            printf("  ");
            break;
        case(3): // 위
            gotoXY(pos.X, pos.Y + 1);
            setColor(0, 0);
            printf("  ");
            break;
        }

        // 화면 벗어나면 끝
        if (pos.X >= consoleScreenSize.Right) return;
        if (pos.X <= consoleScreenSize.Left) return;
        if (pos.Y >= consoleScreenSize.Bottom) return;
        if (pos.Y <= consoleScreenSize.Top) return;

        // 현재 위치 표시
        gotoXY(pos.X, pos.Y);
        setColor(15, 0);
        printf("  ");
    }
};

//bool isCollision()
//{
//
//    if (obs.pos.X == curPlayerPos.X && obs.pos.Y == curPlayerPos.Y) return true;
//
//    return false;
//}


int main()
{
    //generateObstacles();
    while (true)
    {
        drawTitle();
        if (isStart) startGame();
        if (isCtrl) drawCtrl();
        if (isQuit) quitGame();
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

void drawTitle()
{
    initConsole();

    const int xStart = 10, xControl = 20, xQuit = 30;
    int x = xStart, y = 5; // 메뉴 시작 위치

    setColor(0, 15);
    printf("메인 화면");

    gotoXY(xStart, y);
    setColor(0, 15);
    printf(" 시 작 ");

    gotoXY(xControl, y);
    setColor(0, 15);
    printf(" 조 작 ");

    gotoXY(xQuit, y);
    setColor(0, 15);
    printf(" 종 료 ");

    getKey();
    isLeft = false;
    isSpace = false;
    isRight = false;

    x = xStart;
    gotoXY(x, y);
    setColor(0, 13);
    printf(" 시 작 ");

    while (true)
    {
        getKey();

        switch (x)
        {
        case xStart:
            if (isSpace) // 시작
            {
                isSpace = false;
                isStart = true;
                return;
            }
            else if (isRight)
            {
                x = xStart;
                gotoXY(x, y);
                setColor(0, 15);
                printf(" 시 작 ");

                x = xControl;
                gotoXY(x, y);
                setColor(0, 13);
                printf(" 조 작 ");

                isRight = false;
            }
        case xControl:
            if (isSpace) // 조작
            {
                isSpace = false;
                isCtrl = true;
                return;
            }
            else if (isLeft)
            {
                x = xControl;
                gotoXY(x, y);
                setColor(0, 15);
                printf(" 조 작 ");

                x = xStart;
                gotoXY(x, y);
                setColor(0, 13);
                printf(" 시 작 ");

                isLeft = false;
            }
            else if (isRight)
            {
                x = xControl;
                gotoXY(x, y);
                setColor(0, 15);
                printf(" 조 작 ");

                x = xQuit;
                gotoXY(x, y);
                setColor(0, 13);
                printf(" 종 료 ");

                isRight = false;
            }
        case xQuit:
            if (isSpace) //종료
            {
                isSpace = false;
                isQuit = true;
                return;
            }
            else if (isLeft)
            {
                x = xQuit;
                gotoXY(x, y);
                setColor(0, 15);
                printf(" 종 료 ");

                x = xControl;
                gotoXY(x, y);
                setColor(0, 13);
                printf(" 조 작 ");

                isLeft = false;
            }
        }

    }
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

void startGame()
{
    initConsole();
    initTime();
    isStart = false;
    setMovableMap();
    drawScreen();
    
    while (true)
    {
        gotoXY(0, 0);
        cout << elapsedTime;
        updateTime();
        updateInput();
        updatePlayerMove();
        //updateObstacles();
        //updateUI();
        //if(isQuit) break;
    }
    //quitGame();
}

void setMovableMap()
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

    gotoXY(curPlayerPos.X, curPlayerPos.Y);
    setColor(13, 15);
    //putchar('  ');
    printf("  ");
}

void limit(short& n, short min, short max)
{
    if (n < min) n = min;
    if (n > max) n = max;
}

void quitGame()
{
    initConsole();
    isQuit = false;
    printf("게임 종료");
}
