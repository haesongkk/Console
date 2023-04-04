#include "main.h"

using namespace std;

struct obstacle
{
    COORD Pos; // 생성위치
    int time; // 생성시간
    double speed; // 이동속도
    int direction; // 이동방향
    obstacle(int initX, int initY, int initTime, double initSpeed, int initDirection)
    {
        Pos.X = initX, Pos.Y = initY;
        time = initTime;
        speed = initSpeed;
        direction = initDirection;
    }

    void move()
    {
        switch (direction)
        {
        case(0): // 오른쪽
            Pos.X ++;
            break;
        case(1): // 왼쪽
            Pos.X --;
            break;
        case(2): // 아래
            Pos.Y ++;
            break;
        case(3): // 위
            Pos.Y --;
            break;
        }
    }

    void draw()
    {
        gotoXY(Pos.X, Pos.Y);
        setColor(15, 0);
        printf("  ");
    }

    bool timer()
    {
        static ULONGLONG elapsedTime;
        elapsedTime += getDeltaTime();
        
        if (time <= elapsedTime) return true;
        else return false;
    }

    void generate()
    {
        while (timer())
        {
            draw();
            move();
            Sleep(speed);
        }
    }
};

void generateObstacles()
{
    // 생성위치, 생성시간, 이동속도, 이동방향
    obstacle test(0, 10, 0, 1, 0);
    test.generate();
}




int main()
{
    generateObstacles();
    //while (true)
    //{
    //    drawTitle();
    //    if (isStart) startGame();
    //    if (isCtrl) drawCtrl();
    //    if (isQuit) quitGame();
    //    
    //}
    
}


void initTime()
{
    currentTime = previousTime = GetTickCount64();
}

void updateTime()
{
    previousTime = currentTime;
    currentTime = GetTickCount64();

    deltaTime = currentTime - previousTime;
}

ULONGLONG getDeltaTime()
{
    return deltaTime;
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
        updateTime();
        updateInput();
        updatePlayerMove();
    }
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
    static ULONGLONG elapsedTime;
    elapsedTime += getDeltaTime();
    
    while (elapsedTime >= playerMoveSpeed)
    {
        updatePlayerPos();
        elapsedTime -= playerMoveSpeed;
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
