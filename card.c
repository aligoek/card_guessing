#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void easyMode();
void mediumMode();
void hardMode();

int main() {
    int difficulty;

    printf("Welcome to the Card Guessing Game!\n");
    printf("Select difficulty: (Easy: 1, Medium: 2, Hard: 3)\nSelection: ");
    scanf("%d", &difficulty);

    if (difficulty == 1) {
        easyMode();
    } else if (difficulty == 2) {
        mediumMode();
    } else if (difficulty == 3) {
        hardMode();
    } else {
        printf("INVALID SELECTION.\n");
    }

    system("pause");

    return 0;
}

void hardMode() {
    system("color 1");

    int counter = 0;
    int gameBoard[8][8];
    int isGameFinished = 0;
    int pcMemoryValues[16];
    int pcMemoryRows[16];
    int pcMemoryCols[16];
    int i, j, k, m;
    int assignedNumber = 1;
    int pcGuesses = 0;
    int playerGuesses = 0;
    int receivedRow, receivedColumn;
    int playerTurn = 1;
    int pcTurn = 0;
    int receivedRow2, receivedColumn2;
    int playerCorrectGuesses = 0;
    int pcCorrectGuesses = 0;
    int pcRow, pcColumn, pcRow2, pcColumn2;
    int memoryIndex = 0;
    int isPairFound;

    srand(time(NULL));

    for (i = 0; i < 16; i++) {
        pcMemoryValues[i] = 0;
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            gameBoard[i][j] = -1;
        }
    }

    while (assignedNumber < 33) {
        k = rand() % 8;
        m = rand() % 8;

        if (gameBoard[k][m] == -1) {
            gameBoard[k][m] = assignedNumber;
            counter++;
            if (counter % 2 == 0) {
                assignedNumber++;
            }
        }
    }

    printf("\n                GAME BOARD\n");
    printf("  ");
    for (j = 0; j < 8; j++) {
        printf("   %d. ", j + 1);
    }
    printf("\n");
    for (i = 0; i < 8; i++) {
        printf("%d.", i + 1);
        for (j = 0; j < 8; j++) {
            printf(" |%2d| ", gameBoard[i][j]);
        }
        printf("\n");
    }

    printf("\n\nGAME STARTING..\n");
    sleep(6);

    while (isGameFinished == 0) {

        while (playerTurn == 1) {
            sleep(2);
            system("CLS");
            printf("Current Game Board Status:\n");

            printf("  ");
            for (j = 0; j < 8; j++) {
                printf("  %d. ", j + 1);
            }
            printf("\n");
            for (i = 0; i < 8; i++) {
                printf("%d.", i + 1);
                for (j = 0; j < 8; j++) {
                    if (gameBoard[i][j] != -1)
                        printf(" |*| ");
                    else
                        printf(" |-| ");
                }
                printf("\n");
            }

            printf("Current Turn: Player\n");
            printf("Enter row and column to reveal (e.g., 1 2): ");
            scanf("%d %d", &receivedRow, &receivedColumn);

            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    if (i == receivedRow - 1 && j == receivedColumn - 1) {
                        if (gameBoard[receivedRow - 1][receivedColumn - 1] != -1)
                            printf("|%3d|", gameBoard[receivedRow - 1][receivedColumn - 1]);
                        else
                            printf("| x |");
                    } else if (gameBoard[i][j] == -1) {
                        printf("| - |");
                    } else {
                        printf("| * |");
                    }
                }
                printf("\n");
            }

            printf("Current Turn: Player\n");
            printf("Enter row and column for the second card: ");
            scanf("%d %d", &receivedRow2, &receivedColumn2);

            playerGuesses++;

            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    if ((i == receivedRow2 - 1) && (j == receivedColumn2 - 1)) {
                        if (gameBoard[receivedRow2 - 1][receivedColumn2 - 1] != -1)
                            printf("|%3d|", gameBoard[receivedRow2 - 1][receivedColumn2 - 1]);
                        else
                            printf("| x |");
                    } else if (gameBoard[i][j] == -1) {
                        printf("| - |");
                    } else {
                        printf("| * |");
                    }
                }
                printf("\n");
            }

            if (((gameBoard[receivedRow - 1][receivedColumn - 1] == gameBoard[receivedRow2 - 1][receivedColumn2 - 1]) && ((receivedRow - 1 != receivedRow2 - 1) || (receivedColumn - 1 != receivedColumn2 - 1))) && gameBoard[receivedRow - 1][receivedColumn - 1] != -1) {
                gameBoard[receivedRow - 1][receivedColumn - 1] = -1;
                gameBoard[receivedRow2 - 1][receivedColumn2 - 1] = -1;
                playerCorrectGuesses++;
                playerTurn = 1;
                pcTurn = 0;
                printf("\nCongratulations, you found a pair!\n");

                if (playerCorrectGuesses + pcCorrectGuesses == 32) {
                    if (playerCorrectGuesses > pcCorrectGuesses) {
                        printf("Player Wins! Total guesses: %d\nTotal correct guesses: %d\n", playerGuesses, playerCorrectGuesses);
                    } else if (pcCorrectGuesses > playerCorrectGuesses) {
                        printf("PC Wins! Total PC guesses: %d\nTotal PC correct guesses: %d\n", pcGuesses, pcCorrectGuesses);
                    } else {
                        printf("GAME ENDS IN A DRAW...\n");
                    }
                    isGameFinished = 1;
                    playerTurn = 0;
                }

            } else {
                printf("\nIncorrect match.\n");
                playerTurn = 0;
                pcTurn = 1;

                pcMemoryValues[memoryIndex] = gameBoard[receivedRow - 1][receivedColumn - 1];
                pcMemoryRows[memoryIndex] = receivedRow - 1;
                pcMemoryCols[memoryIndex] = receivedColumn - 1;
                memoryIndex++;
                if (memoryIndex == 16) {
                    memoryIndex = 0;
                }
                pcMemoryValues[memoryIndex] = gameBoard[receivedRow2 - 1][receivedColumn2 - 1];
                pcMemoryRows[memoryIndex] = receivedRow2 - 1;
                pcMemoryCols[memoryIndex] = receivedColumn2 - 1;
                memoryIndex++;
                if (memoryIndex == 16) {
                    memoryIndex = 0;
                }
            }
        }

        while (pcTurn == 1) {
            isPairFound = 0;
            sleep(2);
            system("CLS");
            printf("\nCurrent Turn: PC\n");

            for (i = 0; i < 16; i++) {
                for (j = i + 1; j < 16; j++) {
                    if (((pcMemoryValues[i] != 0 && pcMemoryValues[i] == pcMemoryValues[j]) && (pcMemoryRows[j] != pcMemoryRows[i] || pcMemoryCols[j] != pcMemoryCols[i]))) {
                        if (gameBoard[pcMemoryRows[i]][pcMemoryCols[i]] != -1 && gameBoard[pcMemoryRows[j]][pcMemoryCols[j]] != -1) {
                            pcRow = pcMemoryRows[i];
                            pcColumn = pcMemoryCols[i];
                            pcRow2 = pcMemoryRows[j];
                            pcColumn2 = pcMemoryCols[j];
                            pcMemoryValues[i] = 0;
                            pcMemoryRows[i] = 0;
                            pcMemoryCols[i] = 0;
                            pcMemoryValues[j] = 0;
                            pcMemoryRows[j] = 0;
                            pcMemoryCols[j] = 0;
                            isPairFound = 1;
                            break;
                        }
                    }
                }
                if (isPairFound) break;
            }

            if (isPairFound == 0) {
                do {
                    pcRow = rand() % 8;
                    pcColumn = rand() % 8;
                } while (gameBoard[pcRow][pcColumn] == -1);

                do {
                    pcRow2 = rand() % 8;
                    pcColumn2 = rand() % 8;
                } while (gameBoard[pcRow2][pcColumn2] == -1 || (pcRow == pcRow2 && pcColumn == pcColumn2));
            }

            pcGuesses++;
            pcTurn = 0;
            playerTurn = 1;

            printf("PC's first guess:\n");
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    if (i == pcRow && j == pcColumn) {
                        if (gameBoard[pcRow][pcColumn] != -1) {
                            printf("|%3d|", gameBoard[pcRow][pcColumn]);
                        } else {
                            printf("| x |");
                        }
                    } else if (gameBoard[i][j] == -1) {
                        printf("| - |");
                    } else {
                        printf("| * |");
                    }
                }
                printf("\n");
            }

            printf("PC's second guess:\n");
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    if (i == pcRow2 && j == pcColumn2) {
                        if (gameBoard[pcRow2][pcColumn2] != -1) {
                            printf("|%3d|", gameBoard[pcRow2][pcColumn2]);
                        } else {
                            printf("| x |");
                        }
                    } else if (gameBoard[i][j] == -1) {
                        printf("| - |");
                    } else {
                        printf("| * |");
                    }
                }
                printf("\n");
            }

            if (((gameBoard[pcRow][pcColumn] == gameBoard[pcRow2][pcColumn2]) && ((pcRow != pcRow2) || (pcColumn != pcColumn2))) && gameBoard[pcRow][pcColumn] != -1) {
                gameBoard[pcRow][pcColumn] = -1;
                gameBoard[pcRow2][pcColumn2] = -1;
                pcCorrectGuesses++;
                playerTurn = 0;
                pcTurn = 1;
                printf("\nPC found a pair!\n");

                if (playerCorrectGuesses + pcCorrectGuesses == 32) {
                    if (playerCorrectGuesses > pcCorrectGuesses) {
                        printf("Player Wins! Total guesses: %d\nTotal correct guesses: %d\n", playerGuesses, playerCorrectGuesses);
                    } else if (pcCorrectGuesses > playerCorrectGuesses) {
                        printf("PC Wins! Total PC guesses: %d\nTotal PC correct guesses: %d\n", pcGuesses, pcCorrectGuesses);
                    } else {
                        printf("GAME ENDS IN A DRAW...\n");
                    }
                    isGameFinished = 1;
                    pcTurn = 0;
                }
            } else {
                printf("\nPC made an incorrect guess.\n");
                pcMemoryValues[memoryIndex] = gameBoard[pcRow][pcColumn];
                pcMemoryRows[memoryIndex] = pcRow;
                pcMemoryCols[memoryIndex] = pcColumn;
                memoryIndex++;
                if (memoryIndex == 16) {
                    memoryIndex = 0;
                }
                pcMemoryValues[memoryIndex] = gameBoard[pcRow2][pcColumn2];
                pcMemoryRows[memoryIndex] = pcRow2;
                pcMemoryCols[memoryIndex] = pcColumn2;
                memoryIndex++;
                if (memoryIndex == 16) {
                    memoryIndex = 0;
                }
            }
        }
    }
}

void mediumMode() {
    system("color 3");

    int counter = 0;
    int gameBoard[6][6];
    int isGameFinished = 0;
    int pcMemoryValues[6];
    int pcMemoryRows[6];
    int pcMemoryCols[6];
    int i, j, k, m;
    int assignedNumber = 1;
    int pcGuesses = 0;
    int playerGuesses = 0;
    int receivedRow, receivedColumn;
    int playerTurn = 1;
    int pcTurn = 0;
    int receivedRow2, receivedColumn2;
    int playerCorrectGuesses = 0;
    int pcCorrectGuesses = 0;
    int pcRow, pcColumn, pcRow2, pcColumn2;
    int memoryIndex = 0;
    int isPairFound;

    srand(time(NULL));

    for (i = 0; i < 6; i++) {
        pcMemoryValues[i] = 0;
    }

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            gameBoard[i][j] = -1;
        }
    }

    while (assignedNumber < 19) {
        k = rand() % 6;
        m = rand() % 6;

        if (gameBoard[k][m] == -1) {
            gameBoard[k][m] = assignedNumber;
            counter++;
            if (counter % 2 == 0) {
                assignedNumber++;
            }
        }
    }

    printf("\n            GAME BOARD\n");
    printf("  ");
    for (j = 0; j < 6; j++) {
        printf("   %d. ", j + 1);
    }
    printf("\n");
    for (i = 0; i < 6; i++) {
        printf("%d.", i + 1);
        for (j = 0; j < 6; j++) {
            printf(" |%2d| ", gameBoard[i][j]);
        }
        printf("\n");
    }

    printf("\n\nGAME STARTING..\n");
    sleep(6);

    while (isGameFinished == 0) {

        while (playerTurn == 1) {
            sleep(2);
            system("CLS");
            printf("Current Game Board Status:\n");

            printf("  ");
            for (j = 0; j < 6; j++) {
                printf("  %d. ", j + 1);
            }
            printf("\n");
            for (i = 0; i < 6; i++) {
                printf("%d.", i + 1);
                for (j = 0; j < 6; j++) {
                    if (gameBoard[i][j] != -1)
                        printf(" |*| ");
                    else
                        printf(" |-| ");
                }
                printf("\n");
            }

            printf("Current Turn: Player\n");
            printf("Enter row and column to reveal (e.g., 1 2): ");
            scanf("%d %d", &receivedRow, &receivedColumn);

            for (i = 0; i < 6; i++) {
                for (j = 0; j < 6; j++) {
                    if (i == receivedRow - 1 && j == receivedColumn - 1) {
                        if (gameBoard[receivedRow - 1][receivedColumn - 1] != -1)
                            printf("|%3d|", gameBoard[receivedRow - 1][receivedColumn - 1]);
                        else
                            printf("| x |");
                    } else if (gameBoard[i][j] == -1) {
                        printf("| - |");
                    } else {
                        printf("| * |");
                    }
                }
                printf("\n");
            }

            printf("Current Turn: Player\n");
            printf("Enter row and column for the second card: ");
            scanf("%d %d", &receivedRow2, &receivedColumn2);

            playerGuesses++;

            for (i = 0; i < 6; i++) {
                for (j = 0; j < 6; j++) {
                    if ((i == receivedRow2 - 1) && (j == receivedColumn2 - 1)) {
                        if (gameBoard[receivedRow2 - 1][receivedColumn2 - 1] != -1)
                            printf("|%3d|", gameBoard[receivedRow2 - 1][receivedColumn2 - 1]);
                        else
                            printf("| x |");
                    } else if (gameBoard[i][j] == -1) {
                        printf("| - |");
                    } else {
                        printf("| * |");
                    }
                }
                printf("\n");
            }

            if (((gameBoard[receivedRow - 1][receivedColumn - 1] == gameBoard[receivedRow2 - 1][receivedColumn2 - 1]) && ((receivedRow - 1 != receivedRow2 - 1) || (receivedColumn - 1 != receivedColumn2 - 1))) && gameBoard[receivedRow - 1][receivedColumn - 1] != -1) {
                gameBoard[receivedRow - 1][receivedColumn - 1] = -1;
                gameBoard[receivedRow2 - 1][receivedColumn2 - 1] = -1;
                playerCorrectGuesses++;
                playerTurn = 1;
                pcTurn = 0;
                printf("\nCongratulations, you found a pair!\n");

                if (playerCorrectGuesses + pcCorrectGuesses == 18) {
                    if (playerCorrectGuesses > pcCorrectGuesses) {
                        printf("Player Wins! Total guesses: %d\nTotal correct guesses: %d\n", playerGuesses, playerCorrectGuesses);
                    } else if (pcCorrectGuesses > playerCorrectGuesses) {
                        printf("PC Wins! Total PC guesses: %d\nTotal PC correct guesses: %d\n", pcGuesses, pcCorrectGuesses);
                    } else {
                        printf("GAME ENDS IN A DRAW...\n");
                    }
                    isGameFinished = 1;
                    playerTurn = 0;
                }

            } else {
                printf("\nIncorrect match.\n");
                playerTurn = 0;
                pcTurn = 1;

                pcMemoryValues[memoryIndex] = gameBoard[receivedRow - 1][receivedColumn - 1];
                pcMemoryRows[memoryIndex] = receivedRow - 1;
                pcMemoryCols[memoryIndex] = receivedColumn - 1;
                memoryIndex++;
                if (memoryIndex == 6) {
                    memoryIndex = 0;
                }
                pcMemoryValues[memoryIndex] = gameBoard[receivedRow2 - 1][receivedColumn2 - 1];
                pcMemoryRows[memoryIndex] = receivedRow2 - 1;
                pcMemoryCols[memoryIndex] = receivedColumn2 - 1;
                memoryIndex++;
                if (memoryIndex == 6) {
                    memoryIndex = 0;
                }
            }
        }

        while (pcTurn == 1) {
            isPairFound = 0;
            sleep(2);
            system("CLS");
            printf("\nCurrent Turn: PC\n");

            for (i = 0; i < 6; i++) {
                for (j = i + 1; j < 6; j++) {
                    if (((pcMemoryValues[i] != 0 && pcMemoryValues[i] == pcMemoryValues[j]) && (pcMemoryRows[j] != pcMemoryRows[i] || pcMemoryCols[j] != pcMemoryCols[i]))) {
                        if (gameBoard[pcMemoryRows[i]][pcMemoryCols[i]] != -1 && gameBoard[pcMemoryRows[j]][pcMemoryCols[j]] != -1) {
                            pcRow = pcMemoryRows[i];
                            pcColumn = pcMemoryCols[i];
                            pcRow2 = pcMemoryRows[j];
                            pcColumn2 = pcMemoryCols[j];
                            pcMemoryValues[i] = 0;
                            pcMemoryRows[i] = 0;
                            pcMemoryCols[i] = 0;
                            pcMemoryValues[j] = 0;
                            pcMemoryRows[j] = 0;
                            pcMemoryCols[j] = 0;
                            isPairFound = 1;
                            break;
                        }
                    }
                }
                if (isPairFound) break;
            }

            if (isPairFound == 0) {
                do {
                    pcRow = rand() % 6;
                    pcColumn = rand() % 6;
                } while (gameBoard[pcRow][pcColumn] == -1);

                do {
                    pcRow2 = rand() % 6;
                    pcColumn2 = rand() % 6;
                } while (gameBoard[pcRow2][pcColumn2] == -1 || (pcRow == pcRow2 && pcColumn == pcColumn2));
            }

            pcGuesses++;
            pcTurn = 0;
            playerTurn = 1;

            printf("PC's first guess:\n");
            for (i = 0; i < 6; i++) {
                for (j = 0; j < 6; j++) {
                    if (i == pcRow && j == pcColumn) {
                        if (gameBoard[pcRow][pcColumn] != -1) {
                            printf("|%3d|", gameBoard[pcRow][pcColumn]);
                        } else {
                            printf("| x |");
                        }
                    } else if (gameBoard[i][j] == -1) {
                        printf("| - |");
                    } else {
                        printf("| * |");
                    }
                }
                printf("\n");
            }

            printf("PC's second guess:\n");
            for (i = 0; i < 6; i++) {
                for (j = 0; j < 6; j++) {
                    if (i == pcRow2 && j == pcColumn2) {
                        if (gameBoard[pcRow2][pcColumn2] != -1) {
                            printf("|%3d|", gameBoard[pcRow2][pcColumn2]);
                        } else {
                            printf("| x |");
                        }
                    } else if (gameBoard[i][j] == -1) {
                        printf("| - |");
                    } else {
                        printf("| * |");
                    }
                }
                printf("\n");
            }

            if (((gameBoard[pcRow][pcColumn] == gameBoard[pcRow2][pcColumn2]) && ((pcRow != pcRow2) || (pcColumn != pcColumn2))) && gameBoard[pcRow][pcColumn] != -1) {
                gameBoard[pcRow][pcColumn] = -1;
                gameBoard[pcRow2][pcColumn2] = -1;
                pcCorrectGuesses++;
                playerTurn = 0;
                pcTurn = 1;
                printf("\nPC found a pair!\n");

                if (playerCorrectGuesses + pcCorrectGuesses == 18) {
                    if (playerCorrectGuesses > pcCorrectGuesses) {
                        printf("Player Wins! Total guesses: %d\nTotal correct guesses: %d\n", playerGuesses, playerCorrectGuesses);
                    } else if (pcCorrectGuesses > playerCorrectGuesses) {
                        printf("PC Wins! Total PC guesses: %d\nTotal PC correct guesses: %d\n", pcGuesses, pcCorrectGuesses);
                    } else {
                        printf("GAME ENDS IN A DRAW...\n");
                    }
                    isGameFinished = 1;
                    pcTurn = 0;
                }
            } else {
                printf("\nPC made an incorrect guess.\n");
                pcMemoryValues[memoryIndex] = gameBoard[pcRow][pcColumn];
                pcMemoryRows[memoryIndex] = pcRow;
                pcMemoryCols[memoryIndex] = pcColumn;
                memoryIndex++;
                if (memoryIndex == 6) {
                    memoryIndex = 0;
                }
                pcMemoryValues[memoryIndex] = gameBoard[pcRow2][pcColumn2];
                pcMemoryRows[memoryIndex] = pcRow2;
                pcMemoryCols[memoryIndex] = pcColumn2;
                memoryIndex++;
                if (memoryIndex == 6) {
                    memoryIndex = 0;
                }
            }
        }
    }
}

void easyMode() {
    system("color 2");

    int counter = 0;
    int gameBoard[4][4];
    int isGameFinished = 0;
    int pcMemoryValues[2];
    int pcMemoryRows[2];
    int pcMemoryCols[2];
    int i, j, k, m;
    int assignedNumber = 1;
    int pcGuesses = 0;
    int playerGuesses = 0;
    int receivedRow, receivedColumn;
    int playerTurn = 1;
    int pcTurn = 0;
    int receivedRow2, receivedColumn2;
    int playerCorrectGuesses = 0;
    int pcCorrectGuesses = 0;
    int pcRow, pcColumn, pcRow2, pcColumn2;

    srand(time(NULL));

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            gameBoard[i][j] = -1;
        }
    }

    while (assignedNumber < 9) {
        k = rand() % 4;
        m = rand() % 4;

        if (gameBoard[k][m] == -1) {
            gameBoard[k][m] = assignedNumber;
            counter++;
            if (counter % 2 == 0) {
                assignedNumber++;
            }
        }
    }

    printf("\n      GAME BOARD\n");
    printf("  ");
    for (j = 0; j < 4; j++) {
        printf("  %d. ", j + 1);
    }
    printf("\n");
    for (i = 0; i < 4; i++) {
        printf("%d.", i + 1);
        for (j = 0; j < 4; j++) {
            printf(" |%d| ", gameBoard[i][j]);
        }
        printf("\n");
    }

    printf("\n\nGAME STARTING..\n");
    sleep(6);

    while (isGameFinished == 0) {

        while (playerTurn == 1) {
            sleep(2);
            system("CLS");
            printf("Current Game Board Status:\n");

            printf("  ");
            for (j = 0; j < 4; j++) {
                printf("  %d. ", j + 1);
            }
            printf("\n");
            for (i = 0; i < 4; i++) {
                printf("%d.", i + 1);
                for (j = 0; j < 4; j++) {
                    if (gameBoard[i][j] != -1)
                        printf(" |*| ");
                    else
                        printf(" |-| ");
                }
                printf("\n");
            }

            printf("Current Turn: Player\n");
            printf("Enter row and column to reveal (e.g., 1 2): ");
            scanf("%d %d", &receivedRow, &receivedColumn);

            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    if (i == receivedRow - 1 && j == receivedColumn - 1) {
                        if (gameBoard[receivedRow - 1][receivedColumn - 1] != -1)
                            printf("|%d|", gameBoard[receivedRow - 1][receivedColumn - 1]);
                        else
                            printf("|x|");
                    } else if (gameBoard[i][j] == -1) {
                        printf("|-|");
                    } else {
                        printf("|*|");
                    }
                }
                printf("\n");
            }

            printf("Current Turn: Player\n");
            printf("Enter row and column for the second card: ");
            scanf("%d %d", &receivedRow2, &receivedColumn2);

            playerGuesses++;

            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    if ((i == receivedRow2 - 1) && (j == receivedColumn2 - 1)) {
                        if (gameBoard[receivedRow2 - 1][receivedColumn2 - 1] != -1)
                            printf("|%d|", gameBoard[receivedRow2 - 1][receivedColumn2 - 1]);
                        else
                            printf("|x|");
                    } else if (gameBoard[i][j] == -1) {
                        printf("|-|");
                    } else {
                        printf("|*|");
                    }
                }
                printf("\n");
            }

            if (((gameBoard[receivedRow - 1][receivedColumn - 1] == gameBoard[receivedRow2 - 1][receivedColumn2 - 1]) && ((receivedRow - 1 != receivedRow2 - 1) || (receivedColumn - 1 != receivedColumn2 - 1))) && gameBoard[receivedRow - 1][receivedColumn - 1] != -1) {
                gameBoard[receivedRow - 1][receivedColumn - 1] = -1;
                gameBoard[receivedRow2 - 1][receivedColumn2 - 1] = -1;
                playerCorrectGuesses++;
                playerTurn = 1;
                pcTurn = 0;
                printf("\nCongratulations, you found a pair!\n");

                if (playerCorrectGuesses + pcCorrectGuesses == 8) {
                    if (playerCorrectGuesses > pcCorrectGuesses) {
                        printf("Player Wins! Total guesses: %d\nTotal correct guesses: %d\n", playerGuesses, playerCorrectGuesses);
                    } else if (pcCorrectGuesses > playerCorrectGuesses) {
                        printf("PC Wins! Total PC guesses: %d\nTotal PC correct guesses: %d\n", pcGuesses, pcCorrectGuesses);
                    } else {
                        printf("GAME ENDS IN A DRAW...\n");
                    }
                    isGameFinished = 1;
                    playerTurn = 0;
                }

            } else {
                printf("\nIncorrect match.\n");
                playerTurn = 0;
                pcTurn = 1;

                pcMemoryValues[0] = gameBoard[receivedRow - 1][receivedColumn - 1];
                pcMemoryRows[0] = receivedRow - 1;
                pcMemoryCols[0] = receivedColumn - 1;
                pcMemoryValues[1] = gameBoard[receivedRow2 - 1][receivedColumn2 - 1];
                pcMemoryRows[1] = receivedRow2 - 1;
                pcMemoryCols[1] = receivedColumn2 - 1;
            }
        }

        while (pcTurn == 1) {
            sleep(2);
            system("CLS");
            printf("\nCurrent Turn: PC\n");

            int pairFoundInMemory = 0;
            if (pcMemoryValues[0] != 0 && pcMemoryValues[1] != 0 && pcMemoryValues[0] == pcMemoryValues[1]) {
                if (gameBoard[pcMemoryRows[0]][pcMemoryCols[0]] != -1 && gameBoard[pcMemoryRows[1]][pcMemoryCols[1]] != -1) {
                    pcRow = pcMemoryRows[0];
                    pcColumn = pcMemoryCols[0];
                    pcRow2 = pcMemoryRows[1];
                    pcColumn2 = pcMemoryCols[1];
                    pcMemoryValues[0] = 0;
                    pcMemoryRows[0] = 0;
                    pcMemoryCols[0] = 0;
                    pcMemoryValues[1] = 0;
                    pcMemoryRows[1] = 0;
                    pcMemoryCols[1] = 0;
                    pairFoundInMemory = 1;
                }
            }

            if (pairFoundInMemory == 0) {
                do {
                    pcRow = rand() % 4;
                    pcColumn = rand() % 4;
                } while (gameBoard[pcRow][pcColumn] == -1);

                do {
                    pcRow2 = rand() % 4;
                    pcColumn2 = rand() % 4;
                } while (gameBoard[pcRow2][pcColumn2] == -1 || (pcRow == pcRow2 && pcColumn == pcColumn2));
            }

            pcGuesses++;
            pcTurn = 0;
            playerTurn = 1;

            printf("PC's first guess:\n");
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    if (i == pcRow && j == pcColumn) {
                        if (gameBoard[pcRow][pcColumn] != -1) {
                            printf("|%d|", gameBoard[pcRow][pcColumn]);
                        } else {
                            printf("|x|");
                        }
                    } else if (gameBoard[i][j] == -1) {
                        printf("|-|");
                    } else {
                        printf("|*|");
                    }
                }
                printf("\n");
            }

            printf("PC's second guess:\n");
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    if (i == pcRow2 && j == pcColumn2) {
                        if (gameBoard[pcRow2][pcColumn2] != -1) {
                            printf("|%d|", gameBoard[pcRow2][pcColumn2]);
                        } else {
                            printf("|x|");
                        }
                    } else if (gameBoard[i][j] == -1) {
                        printf("|-|");
                    } else {
                        printf("|*|");
                    }
                }
                printf("\n");
            }

            if (((gameBoard[pcRow][pcColumn] == gameBoard[pcRow2][pcColumn2]) && ((pcRow != pcRow2) || (pcColumn != pcColumn2))) && gameBoard[pcRow][pcColumn] != -1) {
                gameBoard[pcRow][pcColumn] = -1;
                gameBoard[pcRow2][pcColumn2] = -1;
                pcCorrectGuesses++;
                playerTurn = 0;
                pcTurn = 1;
                printf("\nPC found a pair!\n");

                if (playerCorrectGuesses + pcCorrectGuesses == 8) {
                    if (playerCorrectGuesses > pcCorrectGuesses) {
                        printf("Player Wins! Total guesses: %d\nTotal correct guesses: %d\n", playerGuesses, playerCorrectGuesses);
                    } else if (pcCorrectGuesses > playerCorrectGuesses) {
                        printf("PC Wins! Total PC guesses: %d\nTotal PC correct guesses: %d\n", pcGuesses, pcCorrectGuesses);
                    } else {
                        printf("GAME ENDs IN A DRAW...\n");
                    }
                    isGameFinished = 1;
                    pcTurn = 0;
                }
            } else {
                printf("\nPC made an incorrect guess.\n");
                pcMemoryValues[0] = gameBoard[pcRow][pcColumn];
                pcMemoryRows[0] = pcRow;
                pcMemoryCols[0] = pcColumn;
                pcMemoryValues[1] = gameBoard[pcRow2][pcColumn2];
                pcMemoryRows[1] = pcRow2;
                pcMemoryCols[1] = pcColumn2;
            }
        }
    }
}
