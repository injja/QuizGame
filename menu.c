#include <stdio.h>

void showTitle()
{

    // ekran tytulowy
    sleep(3);

}

int showMenu()
{

    // przyciski (nowa gra, kontynuuj, ranking, wyjście), tytuł
    int choice;
    printf("wybor");
    scanf("%d", &choice);
    return choice;
}
