#include <stdio.h>
#include <stdlib.h>
#include "gameLogic.c"
#include "structs.h"

void loadSavedGame()
{
    struct Player player;
    FILE *file = fopen("saved_game.txt", "r+");
    fgets(player.username, sizeof(player.username), file);
    while (fscanf(file, "%d %d %d", &player.level, &player.score, &player.hearts) == 3)
    {
    }
    startGame(&player);
}

void newGame()
{
    struct Player player;
    FILE *file = fopen("saved_game.txt", "w+");
    player.hearts = 3;
    player.level = 1;
    player.score = 0;
    // ekran podania nazwy uzytkownika
    printf("Podaj nazwe");
    scanf("%s", player.username);
    startGame(&player);
}
