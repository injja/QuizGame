#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "gameLogic.h"
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <MMsystem.h>


struct quizQuestionAuthor drawAuthorQuestion(struct data *questions, int count, int level) {
    int randomQuestion = rand() % count;

    struct quizQuestionAuthor quizQuestionAuthor;
    sprintf(quizQuestionAuthor.question, "Jak nazywa się autor utworu %s?", questions[randomQuestion].title);
    strcpy(quizQuestionAuthor.answer, questions[randomQuestion].author);
    strcpy(quizQuestionAuthor.path, questions[randomQuestion].path);

    do {
        int random = rand() % count;
        strcpy(quizQuestionAuthor.answer2, questions[random].author);
    } while (strcmp(quizQuestionAuthor.answer2, quizQuestionAuthor.answer) == 0);

    do {
        int random = rand() % count;
        strcpy(quizQuestionAuthor.answer3, questions[random].author);
    } while (strcmp(quizQuestionAuthor.answer3, quizQuestionAuthor.answer) == 0 || strcmp(quizQuestionAuthor.answer3, quizQuestionAuthor.answer2) == 0);

    return quizQuestionAuthor;
}

struct quizQuestionYear drawYearQuestion(struct data *questions, int count, int level) {
    int randomQuestion = rand() % count;
    struct quizQuestionYear quizQuestionYear;
    sprintf(quizQuestionYear.question, "W jakim roku został wydany utwór %s?", questions[randomQuestion].title);
    quizQuestionYear.answer = questions[randomQuestion].year;
    strcpy(quizQuestionYear.path, questions[randomQuestion].path);
    quizQuestionYear.answer2 = quizQuestionYear.answer + rand() % 10 + 20 / (level+1);
    quizQuestionYear.answer3 = quizQuestionYear.answer - rand() % 10 + 20 / (level+1);
    if (quizQuestionYear.answer2 > 2024) {
        quizQuestionYear.answer2 = 2024;
    }

    return quizQuestionYear;
}

struct titleQuestion drawTitleQuestion(struct data *questions, int count) {
    int randomQuestion = rand() % count;
    struct titleQuestion titleQuestion;
    strcpy(titleQuestion.question, "Jaki jest tytuł tego utworu?");
    strcpy(titleQuestion.answer, questions[randomQuestion].title);
    strcpy(titleQuestion.path, questions[randomQuestion].path);

    return titleQuestion;
}

void shuffle(char *array[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void shuffleInt(int array[], int n) {

    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}



void question(struct Player *player, int easyCount, int mediumCount, int hardCount, struct data *easyquestions, struct data *mediumquestions, struct data *hardquestions) {
    int questionType = rand() % 3;
    int count;
    int points;
    struct data *selectedQuestions;

    if (player->level < 6) {
        selectedQuestions = easyquestions;
        count = easyCount;
        points = 10;
    } else if (player->level < 12) {
        selectedQuestions = mediumquestions;
        count = mediumCount;
        points = 20;
    } else {
        selectedQuestions = hardquestions;
        count = hardCount;
        points = 30;
    }

    switch (questionType) {
        case 0: {
            struct quizQuestionAuthor quizQuestion = drawAuthorQuestion(selectedQuestions, count, player->level);
            quizQuestion.points = points;
            char *options[] = { quizQuestion.answer, quizQuestion.answer2, quizQuestion.answer3 };

            shuffle(options, 3);

            printf("%s\n", quizQuestion.question);
            printf("a) %s\n", options[0]);
            printf("b) %s\n", options[1]);
            printf("c) %s\n", options[2]);

            char answer;
            printf("Twoja odpowiedź (a, b lub c): ");
            scanf(" %c", &answer);

            if ((answer == 'a' && strcmp(options[0], quizQuestion.answer) == 0) ||
                (answer == 'b' && strcmp(options[1], quizQuestion.answer) == 0) ||
                (answer == 'c' && strcmp(options[2], quizQuestion.answer) == 0)) {
                player->score += quizQuestion.points;
                player->level += 1;
                printf("Poprawna odpowiedź\n");
            } else {
                printf("Błędna odpowiedź. Poprawna odpowiedź to: %s\n", quizQuestion.answer);
                player->hearts -= 1;
            }
            break;
        }
        case 1: {
            struct quizQuestionYear quizQuestion = drawYearQuestion(selectedQuestions, count, player->level);
            quizQuestion.points = points;
            int answers[] = { quizQuestion.answer, quizQuestion.answer2, quizQuestion.answer3 };
            char *options[] = { "a", "b", "c" };
            int shuffledAnswers[3];
            memcpy(shuffledAnswers, answers, sizeof(answers));

            shuffleInt(shuffledAnswers, 3);

            printf("%s\n", quizQuestion.question);
            printf("a) %d\n", shuffledAnswers[0]);
            printf("b) %d\n", shuffledAnswers[1]);
            printf("c) %d\n", shuffledAnswers[2]);

            char answer;
            printf("Twoja odpowiedź (a, b lub c): ");
            scanf(" %c", &answer);

            int selectedAnswer;
            switch (answer) {
                case 'a': selectedAnswer = shuffledAnswers[0]; break;
                case 'b': selectedAnswer = shuffledAnswers[1]; break;
                case 'c': selectedAnswer = shuffledAnswers[2]; break;
                default: selectedAnswer = -1; break;
            }

            if (selectedAnswer == quizQuestion.answer) {
                player->score += quizQuestion.points;
                player->level += 1;
                printf("Poprawna odpowiedź\n");
            } else {
                printf("Błędna odpowiedź. Poprawna odpowiedź to: %d\n", quizQuestion.answer);
                player->hearts -= 1;
            }
            break;
        }
        case 2: {
            struct titleQuestion quizQuestion = drawTitleQuestion(selectedQuestions, count);
            quizQuestion.points = points;
            printf("%s\n", quizQuestion.question);
            PlaySound(TEXT(quizQuestion.path),NULL, SND_ASYNC);
            char answer[256];
            printf("Twoja odpowiedź: ");
            scanf(" %[^\n]s", answer);

            if (strcmp(answer, quizQuestion.answer) == 0) {
                player->score += quizQuestion.points;
                player->level += 1;
                printf("Poprawna odpowiedź\n");
            } else {
                printf("Błędna odpowiedź. Poprawna odpowiedź to: %s\n", quizQuestion.answer);
                player->hearts -= 1;
            }
            break;
        }
    }
}

void savePlayerResults(struct Player *player) {
    FILE *file = fopen("leaderboard.txt", "a");
        fprintf(file, "%s %d\n", player->username, player->score);
        fclose(file);

}

void startGame(struct Player *player) {
    int points;

    FILE *easyfile = fopen("easy.txt", "r+");
    FILE *mediumfile = fopen("medium.txt", "r+");
    FILE *hardfile = fopen("hard.txt", "r+");

    struct data easyquestions[100];
    int easyCount = 0;

    while (fgets(easyquestions[easyCount].title, sizeof(easyquestions[easyCount].title), easyfile) &&
           fgets(easyquestions[easyCount].author, sizeof(easyquestions[easyCount].author), easyfile) &&
           fgets(easyquestions[easyCount].path, sizeof(easyquestions[easyCount].path), easyfile) &&
           fscanf(easyfile, "%d\n", &easyquestions[easyCount].year) == 1) {
        easyquestions[easyCount].title[strcspn(easyquestions[easyCount].title, "\n")] = '\0';
        easyquestions[easyCount].author[strcspn(easyquestions[easyCount].author, "\n")] = '\0';
        easyquestions[easyCount].path[strcspn(easyquestions[easyCount].path, "\n")] = '\0';
        easyCount += 1;
    }

    struct data mediumquestions[100];
    int mediumCount = 0;

    while (fgets(mediumquestions[mediumCount].title, sizeof(mediumquestions[mediumCount].title), mediumfile) &&
           fgets(mediumquestions[mediumCount].author, sizeof(mediumquestions[mediumCount].author), mediumfile) &&
           fgets(mediumquestions[mediumCount].path, sizeof(mediumquestions[mediumCount].path), mediumfile) &&
           fscanf(mediumfile, "%d\n", &mediumquestions[mediumCount].year) == 1) {
        mediumquestions[mediumCount].title[strcspn(mediumquestions[mediumCount].title, "\n")] = '\0';
        mediumquestions[mediumCount].author[strcspn(mediumquestions[mediumCount].author, "\n")] = '\0';
        mediumquestions[mediumCount].path[strcspn(mediumquestions[mediumCount].path, "\n")] = '\0';
        mediumCount += 1;
    }

    struct data hardquestions[100];
    int hardCount = 0;

    while (fgets(hardquestions[hardCount].title, sizeof(hardquestions[hardCount].title), hardfile) &&
           fgets(hardquestions[hardCount].author, sizeof(hardquestions[hardCount].author), hardfile) &&
           fgets(hardquestions[hardCount].path, sizeof(hardquestions[hardCount].path), hardfile) &&
           fscanf(hardfile, "%d\n", &hardquestions[hardCount].year) == 1) {
        hardquestions[hardCount].title[strcspn(hardquestions[hardCount].title, "\n")] = '\0';
        hardquestions[hardCount].author[strcspn(hardquestions[hardCount].author, "\n")] = '\0';
        hardquestions[hardCount].path[strcspn(hardquestions[hardCount].path, "\n")] = '\0';
        hardCount += 1;
    }

    fclose(easyfile);
    fclose(mediumfile);
    fclose(hardfile);

    srand(time(NULL));

    while (1) {
        printf("Pytanie nr %d, aktualne punkty: %d życia %d\n", player->level, player->score, player->hearts);

        question(player, easyCount, mediumCount, hardCount, easyquestions, mediumquestions, hardquestions);
        if (player->hearts == 0) {
            printf("Koniec gry, twój wynik to %d\n", player->score);
            savePlayerResults(player);
            break;
        }
    }
}
