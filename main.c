#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.c"
#include "initialization.c"
#include "leaderboard.c"
#include "structs.h"
#include "gameLogic.h"
int main()
{
    srand(time(NULL));
    int choice;
    int game = 1;
    showTitle();
    while (game == 1)
    {
        choice = showMenu();
        if (choice == 0)
        {
            loadSavedGame();
        }
        else if (choice == 1)
        {
            newGame();
        }
        else if (choice == 2)
        {
            showLeaderboard();
        }
        else if (choice == 3)
        {
            game = 0;
        }
    }
}
