#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

int compare(const void *a, const void *b)
{
    struct PlayerShortcut *playerA = (struct PlayerShortcut *)a;
    struct PlayerShortcut *playerB = (struct PlayerShortcut *)b;
    return playerB->score - playerA->score;
}

void showLeaderboard()
{
    FILE *file = fopen("leaderboard.txt", "r+");
    struct PlayerShortcut players[1000];
    int count = 0;
    while (fscanf(file, "%s %d", &players[count].username, &players[count].score) == 2)
    {

        count++;
        if (count > 1000)
        {
            printf("Przekroczony limit graczy");
            break;
        }
    }
    qsort(players, count, sizeof(struct PlayerShortcut), compare);
    for (int i = 0; i < 10 && i<count; i++)
    {

        printf("%s %d\n", players[i].username, players[i].score);
    }
}
