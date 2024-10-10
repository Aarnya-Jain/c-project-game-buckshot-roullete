#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_MAX 100

typedef struct
{
    char name[INPUT_MAX];
    int lives;
    int money;
} Character;

void printmp(const char *filename)
{
    FILE *filepointer;
    filepointer = fopen(filename, "r");
    char ch;
    while ((ch = fgetc(filepointer)) != EOF)
    {
        printf("%c", ch);
    }
    fclose(filepointer);
}

void stats()
{
    printf("BULLETS LEFT : \n");
    printf("LIVES LEFT : \n\n");
}

void shoot()
{
    srand(time(0));

    // Generate a random number (0 or 1)
    int shell = rand() % 2;

    if (shell == 0)
    {
        printf("EMPTY SHELL \n\n");
    }

    else if (shell == 1)
    {
        printf("SHOT FIRED !\n\n");
    }
}

void gameloop()
{
    while (60)
    {

        printf("PRESS ENTER TO SHOOT OR SPACE-->ENTER TO CHECK CURRENT STATS\n");
        char ch = getchar();

        if (ch == '\n')
        {
            shoot();
        }
        else if (ch == ' ')
        {
            getchar();
            stats();
        }
    }
}

int main()
{

    printf("START THE GAME : yes / no  \n");
    char input1[INPUT_MAX];
    fgets(input1, sizeof(input1), stdin);
    input1[strcspn(input1, "\n")] = 0;
    printf("\n");
    if (strcasecmp(input1, "yes") == 0)
    {
        printmp("boss.txt");
        printf("\n");
        printf("HELLO THERE!  LOOKS LIKE YOU ARE LOST.....\n\nWANNA PLAY A QUICK GAME WITH ME ?\n");

        while (69)
        {
            printf("ENTER YES OR NO TO PROCEED : ");
            char input[INPUT_MAX];
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            // for removing new line character

            printf("\n");

            if (strcasecmp(input, "yes") == 0)
            {
                printf("WELL! WELL! IT'S SIMPLE.....\n\n\nTHERE ARE TWO GUNS HERE, WITH SOME BULLETS IN THEM...\n\nWE'LL FIRE AT EACH OTHER,IF YOU LIVE YOU GET SOME MONEY BUT IF THE SHELL ISN'T EMPTY THEN............\n\n\nEASY RIGHT , YOU CAN ALSO CHOOSE SOME ACCESSORIES\nLET'S PROCEED\n");
                printmp("boss2.txt");
                printf("\n");
                gameloop();
                break;
            }
            else if (strcasecmp(input, "no") == 0)
            {
                printf("THERE IS NO ESCAPE MY FRIEND..........LET'S LEARN SOME RULES SHALL WE\n\n");
                printf("THERE ARE TWO GUNS HERE, WITH SOME BULLETS IN THEM...\n\nWE'LL SHOOT EACH OTHER,IF YOU LIVE YOU GET SOME MONEY BUT IF THE SHELL ISN'T EMPTY THEN............\n\n\nEASY RIGHT , YOU CAN ALSO CHOOSE SOME ACCESSORIES\nLET'S PROCEED\n");
                printmp("boss2.txt");
                printf("\n");
                gameloop();
                break;
            }
            else
            {
                printf("ENTER A VALID INPUT!! DON'T MESS WITH ME\n\n");
            }
        }
    }
    else if (strcasecmp(input1, "no") == 0)
    {
        printf("exiting the game for now will do something later");
    }

    return 0;
}
