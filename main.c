#include <stdio.h>
#include <Windows.h>

#define width 30
#define height 25

// Structure for the left and right rackets
typedef struct {
    int x, y; // Position of the racket
    int w;    // Width of the racket
} TRaket;

// Structure for the ball
typedef struct {
    int x, y; // Position of the ball
    int dx, dy; // Direction of the ball
} TBall;

TRaket Lracket; // Left racket
TRaket Rracket; // Right racket

TBall ball; // Ball

char mas[height][width]; // Game field

int player1Score = 0; // Player 1's score
int player2Score = 0; // Player 2's score

// Function prototypes
void init();
void show();

void initRacket();
void PutRacket();

void moveLeftRacket(int y);
void moveRightRacket(int y);

void initBall();
void PutBall();

void moveBall();
void updateBall();

void setcur(int x, int y);

// Main function
int main() {
    // Initialize rackets and ball
    initRacket();
    initBall();

    do {
        setcur(0, 0); // Set cursor position

        init(); // Initialize the game field
        PutRacket(); // Put the rackets on the field
        PutBall(); // Put the ball on the field
        show(); // Display the game field

        updateBall(); // Update the ball's position

        // Display scores
        printf("Player 1 Score: %d\n", player1Score);
        printf("Player 2 Score: %d\n", player2Score);

        // Check for winning conditions
        if (player1Score >= 21) {
            printf("Player 1 wins!\n");
            break;
        }
        else if (player2Score >= 21) {
            printf("Player 2 wins!\n");
            break;
        }

        // Move the rackets based on keyboard input
        if (GetKeyState('A') < 0) moveLeftRacket(Lracket.y - 1);
        if (GetKeyState('Z') < 0) moveLeftRacket(Lracket.y + 1);

        if (GetKeyState('K') < 0) moveRightRacket(Rracket.y - 1);
        if (GetKeyState('M') < 0) moveRightRacket(Rracket.y + 1);

        Sleep(10); // Pause for a short duration
    } while (GetKeyState(VK_ESCAPE) >= 0); // Loop until ESC key is pressed

    return 0;
}

// Initialize the game field
void init() {
    // Draw top and bottom boundaries
    for (int i = 0; i < width; i++) {
        mas[0][i] = '-';  // Top boundary
        mas[height - 1][i] = '-';  // Bottom boundary
    }

    // Draw left and right boundaries and empty space inside
    for (int i = 1; i < height - 1; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) {
                mas[i][j] = '|';  // Left and right boundaries
            }
            else {
                mas[i][j] = ' ';  // Empty space inside the field
            }
        }
    }
}

// Initialize the rackets
void initRacket() {
    // Initialize left racket
    Lracket.w = 3;
    Lracket.x = 1;
    Lracket.y = height / 2 - Lracket.w / 2;

    // Initialize right racket
    Rracket.w = 3;
    Rracket.x = width - 2;
    Rracket.y = height / 2 - Rracket.w / 2;
}

// Initialize the ball
void initBall() {
    ball.x = width / 2;
    ball.y = height / 2;
    ball.dx = 1;
    ball.dy = 1;
}

// Put the rackets on the game field
void PutRacket() {
    // Put left racket on the field
    for (int i = Lracket.y; i < Lracket.y + Lracket.w; i++) {
        mas[i][Lracket.x] = '#';
    }

    // Put right racket on the field
    for (int i = Rracket.y; i < Rracket.y + Rracket.w; i++) {
        mas[i][Rracket.x] = '#';
    }
}

// Put the ball on the game field
void PutBall() {
    mas[ball.y][ball.x] = 'O';
}

// Move the left racket
void moveLeftRacket(int y) {
    Lracket.y = y;

    // Prevent racket from going out of bounds
    if (Lracket.y < 1) {
        Lracket.y = 1;
    }

    if (Lracket.y + Lracket.w >= height) {
        Lracket.y = height - 1 - Lracket.w;
    }
}

// Move the right racket
void moveRightRacket(int y) {
    Rracket.y = y;

    // Prevent racket from going out of bounds
    if (Rracket.y < 1) {
        Rracket.y = 1;
    }

    if (Rracket.y + Rracket.w >= height) {
        Rracket.y = height - 1 - Rracket.w;
    }
}

// Move the ball
void moveBall() {
    ball.x += ball.dx;
    ball.y += ball.dy;
}

// Update the ball's position and check for collisions
void updateBall() {
    moveBall(); // Move the ball

    // Reflect the ball if it hits top or bottom boundary
    if (ball.y <= 0 || ball.y >= height - 1) {
        ball.dy = -ball.dy;
    }

    // Reflect the ball if it hits left or right boundary
    if (ball.x <= 0 || ball.x >= width - 1) {
        ball.dx = -ball.dx;
    }

    // Reflect the ball and update score if it hits left racket
    if (ball.x == Lracket.x + 1 && ball.y >= Lracket.y && ball.y < Lracket.y + Lracket.w) {
        ball.dx = -ball.dx;
        player1Score++;
    }

    // Reflect the ball and update score if it hits right racket
    if (ball.x == Rracket.x - 1 && ball.y >= Rracket.y && ball.y < Rracket.y + Rracket.w) {
        ball.dx = -ball.dx;
        player2Score++;
    }
}

// Display the game field
void show() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", mas[i][j]);
        }
        printf("\n");
    }
}

// Set cursor position
void setcur(int x, int y) {
    COORD coord;

    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
