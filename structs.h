#ifndef LIST_H_
#define LIST_H_


struct Player
{
    char username[50];
    int hearts;
    int score;
    int level;
    //+ ew tablica z zaliczonymi pytaniami
};

struct  PlayerShortcut
{
    char username[50];
    int score;
};

struct quizQuestionAuthor
{
    int points;
    char question[200];
    char answer[200];
    char path[200];
    char answer2[200];
    char answer3[200];
};

struct quizQuestionYear
{
    int points;
    char question[200];
    int answer;
    char path[200];
    int answer2;
    int answer3;


};

struct lyricsQuestion
{
    char title[200];
    char author[200];
    int points;
    char question[200];
    char answer[200];
};

struct titleQuestion
{
    char question[200];
    char title[200];
    int points;
    char answer[200];
    char path[200];
};

struct data
{
    char author[200];
    char title[200];
   // char lyrics[1000];
    char path[200];
    int year;
};

#endif
