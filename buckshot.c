// study about rand function in full detail to be able to explain there
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h> 
#include <sys/types.h>

#define INPUT_MAX 300
pid_t musicPid = -1;


void startBackgroundMusic(const char *musicFile) {
    if (musicPid != -1) {
        return; // Avoid starting multiple music processes
    }

    pid_t pid = fork(); // Create a new process for music playback
    if (pid == 0) {
        // Child process: Redirect stdout and stderr to /dev/null
        freopen("/dev/null", "w", stdout); // Suppress standard output
        freopen("/dev/null", "w", stderr); // Suppress standard error

        // Detach from the terminal completely
        setsid();

        // Play music in non-interactive mode
        execlp("mpg123", "mpg123", "--quiet", "--loop", "-1", musicFile, NULL);
        perror("Failed to start music"); // This will only show if execlp fails
        exit(1);
    } else if (pid > 0) {
        // Parent process: Track the child process ID
        musicPid = pid;
    } else {
        perror("Failed to fork process");
    }
}

void stopBackgroundMusic() {
    if (musicPid != -1) {
        //printf("Stopping background music (PID: %d).\n", musicPid);
        kill(musicPid, SIGKILL); // Kill the music process
        musicPid = -1;
    } else {
        printf("No background music to stop.\n");
    }
}

typedef struct structure
{
    int money;
    int skip_turns;
    int extra_lives;
    int guaranteed_shots;
} Inventory;

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

void stats(int player_lives, int player_bullets, int z_lives, int z_bullets, Inventory *inventory)
{
    printf("\n====================\n");
    printf("       STATS\n");
    printf("====================\n");
    printf("Player's Lives  : %d\n", player_lives);
    printf("Player's Bullets: %d\n", player_bullets);
    printf("Player's Money  : $%d\n", inventory->money);
    printf("Skip Turns Left : %d\n", inventory->skip_turns);
    printf("Extra Lives Left: %d\n", inventory->extra_lives);
    printf("Guaranteed Shots Left: %d\n", inventory->guaranteed_shots);
    printf("\nMr. Z's Lives   : %d\n", z_lives);
    printf("Mr. Z's Bullets : %d\n", z_bullets);
    printf("\n====================\n");
    printf("\n\n\n\n\n");
}

// Function declarations
int numberGuessing(Inventory *inventory);
int wireDiffusion(Inventory *inventory);
int highLowGame(Inventory *inventory);

void minigame(Inventory *inventory)
{
    printf("\n\n\n=================================================");
    printf("\nWant to try your luck at the Saloon Games?\n");
    printf("Win big or lose a life - the choice is yours!\n");
    printf("\nAvailable Games:");
    printf("\n1. Number Guessing - Safe bet, small reward");
    printf("\n   Risk: Low  |  Reward: $10,000");
    printf("\n2. Wire Diffusion - Test your nerve!");
    printf("\n   Risk: High |  Reward: $50,000");
    printf("\n3. High-Low Cards - The gambler's favorite");
    printf("\n   Risk: Medium  |  Reward: $25,000");
    printf("\n=================================================");
    printf("\nFeeling lucky? (yes/no): ");

    while (1)
    {
        char input[INPUT_MAX];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline

        if (strcasecmp(input, "yes") == 0)
        {
            printf("\nWhich game catches your eye, partner?");
            printf("\nEnter your choice (1-3): ");

            char choice[INPUT_MAX];
            fgets(choice, sizeof(choice), stdin);

            sleep(1);

            switch (choice[0])
            {
            case '1':
                printf("\nA cautious gambler, eh? Let's try those numbers...\n");
                numberGuessing(inventory);
                break;
            case '2':
                printf("\nBrave soul! Don't let those nerves shake...\n");
                wireDiffusion(inventory);
                break;
            case '3':
                printf("\nAh, a classic card player! Let's see those instincts...\n");
                highLowGame(inventory);
                break;
            default:
                printf("\nSeems you're having trouble deciding. Come back when you're ready!\n");
            }
            printf("\n=================================================\n");
            break;
        }
        else if (strcasecmp(input, "no") == 0)
        {
            printf("\nNo shame in walking away. The games will be here when you're ready!\n");

            printf("=================================================\n");
            sleep(1);
            printf("\nContinuing in\n");
            for (int i = 3; i > 0; i--)
            {
                printf("%d...\n\n", i);
                sleep(1);
            }
            break;
        }
        else
        {
            printf("Come again? Just say 'yes' or 'no': ");
        }
    }
}

// Game 1: Number Guessing
int numberGuessing(Inventory *inventory)
{
    sleep(1);
    printf("\n=== NUMBER GUESSING GAME ===\n");
    printf("I'm thinking of a number between 1 and 20.\n");
    printf("You have 3 tries. Guess correctly to win $10,000!\n");
    sleep(1);

    int number = rand() % 20 + 1;
    int tries = 3;

    while (tries > 0)
    {
        printf("\nTries left: %d\n", tries);
        printf("Enter your guess: ");

        int guess;
        scanf("%d", &guess);
        getchar(); // Clear buffer
        sleep(1);

        if (guess == number)
        {
            printf("\nCORRECT! You won $10,000!\n");
            inventory->money += 10000;
            return 1;
        }
        else if (guess < number)
        {
            printf("Too low!\n");
        }
        else
        {
            printf("Too high!\n");
        }
        tries--;
    }

    printf("\nGame Over! The number was %d\n", number);
    sleep(1);
    printf("\nContinuing in\n");
    for (int i = 3; i > 0; i--)
    {
        printf("%d...\n\n", i);
        sleep(1);
    }
    return 0;
}

int wireDiffusion(Inventory *inventory)
{
    sleep(1);
    printf("\n=== WIRE DIFFUSION CHALLENGE ===\n");
    printf("You seem like a daring one to me\n");
    sleep(1);
    printf("There are 4 colored wires: Red, Blue, Green, Yellow\n");
    printf("Cut the right sequence of 3 wires to diffuse the bomb!\n");
    sleep(1);
    printf("WARNING: Wrong sequence = INSTANT DEATH!\n");
    printf("Successful diffusion rewards $50,000!\n\n");

    const char *colors[] = {"Red", "Blue", "Green", "Yellow"};
    char input[INPUT_MAX];
    int sequence[3];
    int failed = 0;

    // Generate random correct sequence
    for (int i = 0; i < 3; i++)
    {
        sequence[i] = rand() % 4;
    }

    // Give player a cryptic hint about the sequence
    printf("ANALYSIS REPORT:\n");
    if (sequence[0] == sequence[1] || sequence[0] == sequence[2])
    {
        printf("- Same color appears multiple times\n");
    }
    if (sequence[0] == 0 || sequence[1] == 0 || sequence[2] == 0)
    {
        printf("- Red wire is critical\n");
    }
    if (sequence[0] > sequence[1])
    {
        printf("- First wire has higher risk than second\n");
    }
    if ((sequence[0] + sequence[1] + sequence[2]) % 2 == 0)
    {
        printf("- Sum of wire positions is even\n");
    }
    printf("\nWire Colors: R)ed, B)lue, G)reen, Y)ellow\n");

    // Get player's three choices
    for (int i = 0; i < 3; i++)
    {
        printf("Cut wire #%d (R/B/G/Y): ", i + 1);
        fgets(input, sizeof(input), stdin);

        int player_choice = -1;
        char choice = input[0];

        // Simple if-else logic instead of switch and toupper
        if (choice == 'R' || choice == 'r')
            player_choice = 0;
        else if (choice == 'B' || choice == 'b')
            player_choice = 1;
        else if (choice == 'G' || choice == 'g')
            player_choice = 2;
        else if (choice == 'Y' || choice == 'y')
            player_choice = 3;

        if (player_choice == -1)
        {
            printf("\nINVALID WIRE - BOMB DETONATED!\n");
            printf("\nThe correct sequence was: %s-%s-%s\n", colors[sequence[0]], colors[sequence[1]], colors[sequence[2]]);
            printf("\n====================\n");
            printf("     GAME OVER\n");
            printf("====================\n");
            printf("     You died\n");
            exit(0);
        }

        // Immediate feedback for each wire
        printf("*SNIP* ");
        sleep(1);
        if (player_choice == sequence[i])
        {
            printf("Wire cut successfully...\n");
        }
        else
        {
            printf("\n*BOOM* - Wrong wire!\n");
            printf("\nThe correct sequence was: %s-%s-%s\n", colors[sequence[0]], colors[sequence[1]], colors[sequence[2]]);
            printf("\n====================\n");
            printf("     GAME OVER\n");
            printf("====================\n");
            printf("     You died\n");
            exit(0);
        }
    }

    // Only reaches here if successful
    printf("\nBomb successfully diffused! You won $50,000!\n");
    printf("Correct sequence was: %s-%s-%s\n", colors[sequence[0]], colors[sequence[1]], colors[sequence[2]]);
    inventory->money += 50000;
    sleep(1);
    printf("\nContinuing in\n");
    for (int i = 3; i > 0; i--)
    {
        printf("%d...\n\n", i);
        sleep(1);
    }
    return 1;
}
// Game 3: High-Low Card Game
int highLowGame(Inventory *inventory)
{
    sleep(1);
    printf("\n=== HIGH-LOW CARD GAME ===\n");
    printf("Guess if the next card will be higher or lower!\n");
    printf("Get 3 right in a row to win $25,000!\n");
    sleep(1);

    int current_card, next_card;
    int correct_guesses = 0;

    while (correct_guesses < 3)
    {
        current_card = rand() % 13 + 1;
        next_card = rand() % 13 + 1;

        printf("\nCurrent card: %d\n", current_card);
        printf("Will the next card be (h)igher or (l)ower?: ");

        char guess[INPUT_MAX];
        fgets(guess, sizeof(guess), stdin);
        guess[strcspn(guess, "\n")] = 0;

        sleep(1);

        if ((guess[0] == 'h' && next_card > current_card) ||
            (guess[0] == 'l' && next_card < current_card))
        {
            printf("Correct! Next card was: %d\n", next_card);
            correct_guesses++;
            printf("Correct guesses: %d/3\n", correct_guesses);
        }
        else
        {
            printf("\n========================\n");
            printf("Wrong! Next card was: %d\n", next_card);
            printf("Game Over!\n");
            printf("You lost $25000\n");
            printf("========================\n");
            sleep(1);
            printf("\nContinuing in\n");
            for (int i = 3; i > 0; i--)
            {
                printf("%d...\n\n", i);
                sleep(1);
            }
            inventory->money -= 25000;
            return 0;
        }
    }

    printf("\n=====================");
    printf("\nYou won $25,000!\n");
    printf("=====================\n");
    inventory->money += 25000;
    sleep(1);
    printf("\nContinuing in\n");
    for (int i = 3; i > 0; i--)
    {
        printf("%d...\n\n", i);
        sleep(1);
    }
    return 1;
}

void shoot1(int arr[], int *current_chamber, int *target_lives, char *target_name, int guaranteed_shot)
{
    if (guaranteed_shot || arr[*current_chamber] == 1)
    {
        sleep(1);
        printf("SHOT FIRED!\n\n");
        if (!guaranteed_shot)
        {
            arr[*current_chamber] = 0; // Bullet fired
        }
        (*target_lives)--; // Decrease target's lives when shot hits
        printf("%s were shot! Now has %d lives left.\n", target_name, *target_lives);
    }
    else
    {
        sleep(1);
        printf("EMPTY SHELL! No shot fired.\n");
    }
    *current_chamber = (*current_chamber + 1) % 6; // Rotate chamber
}

void givePowerUps(Inventory *inventory)
{
    // Give all 3 power-ups at the start of the round
    inventory->skip_turns += 1;       // 1 "skip turn" power-up
    inventory->extra_lives += 1;      // 1 "extra life" power-up
    inventory->guaranteed_shots += 1; // 1 "guaranteed shot" power-up

    printf("\nYou received the following power-ups this round:\n");
    printf("- Skip Mr. Z's Turn\n");
    printf("- Extra Life\n");
    printf("- Guaranteed Shot");
}

void gameloop()
{
    int round;
    int i;
    int bullet;

    // Arrays for player's gun in each round
    int player_array1[] = {1, 1, 1, 1, 1, 0};
    int player_array2[] = {1, 1, 1, 1, 0, 0};
    int player_array3[] = {1, 1, 1, 0, 0, 0};

    // Arrays for Mr. Z's gun (same as player's gun arrays now)
    int z_array1[] = {1, 1, 1, 1, 1, 0};
    int z_array2[] = {1, 1, 1, 1, 0, 0};
    int z_array3[] = {1, 1, 1, 0, 0, 0};

    int freq[2] = {0};

    srand(time(0));

    // Initial player and Mr. Z's lives and money
    int player_lives = 5;
    int z_lives = 5;
    Inventory inventory = {0, 0, 0, 0}; // Player starts with no money or power-ups

    for (round = 1; round <= 3; round++)
    {
        i = 0;
        int player_chamber = rand() % 6;
        int z_chamber = rand() % 6;

        int *player_current_array;
        int *z_current_array;

        // Clear the screen using ANSI escape code
        printf("\033[2J\033[H");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // Pushes text down
        system("cls");

        printmp("logo1.txt");
        printf("\n====================\n");
        printf("  ROUND %d STARTING!\n", round);
        printf("====================\n");

        // Set the gun arrays for the current round
        switch (round)
        {
        case 1:
            player_current_array = player_array1;
            z_current_array = z_array1;
            break;

        case 2:
            player_current_array = player_array2;
            z_current_array = z_array2;
            break;

        case 3:
            player_current_array = player_array3;
            z_current_array = z_array3;
            break;
        }

        // Give all 3 power-ups at the start of each round
        givePowerUps(&inventory);

        while (1)
        {

            // Check player's gun
            freq[0] = freq[1] = 0;
            for (int j = 0; j < 6; j++)
            {
                freq[player_current_array[j]]++;
            }
            int player_bullets = freq[1];

            // Check Mr. Z's gun
            freq[0] = freq[1] = 0;
            for (int j = 0; j < 6; j++)
            {
                freq[z_current_array[j]]++;
            }
            int z_bullets = freq[1];

            // If both guns are empty, end the round
            if (player_bullets == 0 && z_bullets == 0)
            {
                printf("\nBoth guns are empty. Ending round.\n");
                break;
            }

            // Player's turn
            if (i % 2 == 0)
            {
                if (player_bullets > 0)
                {
                    printf("\n\n\n\n\n");
                    printf("\n==== YOUR TURN ====\n\n");
                    printf("Press ENTER to shoot, SPACE to check stats, or S to use a power-up: \n");
                    char ch = getchar();

                    if (ch == '\n')
                    {
                        shoot1(player_current_array, &player_chamber, &z_lives, "Mr. Z", 0); // Shoot at Mr. Z

                        if (z_lives == 0)
                        {
                            printf("\nYou ended all lives of Mr. Z\n");
                            break;
                        }
                        else if (player_lives == 0)
                        {
                            printf("\n====================\n");
                            printf("     GAME OVER\n");
                            printf("====================\n");
                            printf("     You died\n");
                            exit(0);
                        }
                    }
                    else if (ch == ' ')
                    {
                        getchar();
                        stats(player_lives, player_bullets, z_lives, z_bullets, &inventory);
                        continue; //(continue to skip z's turn for this time)
                    }
                    else if (ch == 's' || ch == 'S')
                    {
                        getchar();
                        printf("\nWhich power-up would you like to use?\n");
                        printf("1. Skip Mr. Z's turn\n");
                        printf("2. Gain an extra life\n");
                        printf("3. Take a guaranteed shot\n\n");
                        printf("Enter your choice (1-3): ");
                        int powerup_choice;
                        scanf("%d", &powerup_choice);
                        getchar();


                        if (powerup_choice == 1 && inventory.skip_turns > 0)
                        {
                            inventory.skip_turns--;
                            printf("\n");
                            shoot1(player_current_array, &player_chamber, &z_lives, "Mr. Z", 0);
                            printf("\nYou used a power-up to skip Mr. Z's turn!\n");
                            // Check if the round ends
                            if (z_lives == 0)
                            {
                                printf("\nYou ended all lives of Mr. Z\n");
                                break;
                            }
                            else if (player_lives == 0)
                            {
                                printf("\n====================\n");
                                printf("     GAME OVER\n");
                                printf("====================\n");
                                printf("     You died\n");
                                exit(0);
                            }


                            // Skip Mr. Z turn
                        }
                        else if (powerup_choice == 2 && inventory.extra_lives > 0)
                        {
                            inventory.extra_lives--;
                            player_lives++;
                            printf("\n\nYou used a power-up to gain an extra life! Your lives: %d\n", player_lives);

                        }
                        else if (powerup_choice == 3 && inventory.guaranteed_shots > 0)
                        {
                            inventory.guaranteed_shots--;
                            printf("\n");
                            shoot1(player_current_array, &player_chamber, &z_lives, "Mr. Z", 1); // Guaranteed shot
                            // Check if the round ends
                            if (z_lives == 0)
                            {
                                sleep(1);
                                printf("\nYou ended all lives of Mr. Z\n");
                                break;
                            }
                            else if (player_lives == 0)
                            {
                                printf("\n====================\n");
                                printf("     GAME OVER\n");
                                printf("====================\n");
                                printf("     You died\n");
                                exit(0);
                            }
                        }
                        else
                        {
                            printf("\n\nThis power-up is no longer available.\n");
                            printf("\n\n\n\n\n");
                        }
                        continue; // Skip Mr. Z turn after using power-up
                    }
                }
                else
                {
                    printf("\nYour gun is empty!\n");
                }
            }
            // Mr. Z turn
            else
            {
                if (z_bullets > 0)
                {
                    printf("\n==== MR. Z'S TURN ====\n\n");
                    shoot1(z_current_array, &z_chamber, &player_lives, "You", 0);
                    // Check if the round ends
                    if (z_lives == 0)
                    {
                        sleep(1);
                        printf("\nYou ended all lives of Mr. Z\n");
                        break;
                    }
                    else if (player_lives == 0)
                    {
                        printf("\n====================\n");
                        printf("     GAME OVER\n");
                        printf("====================\n");
                        printf("     You died\n");
                        exit(0);
                    }

                }
            }

            i++;
        }

        if (player_lives > 0)
        {
            int money_won = 0;
            switch (round)
            {
            case 1:
                money_won = 50000;
                break;
            case 2:
                money_won = 100000;
                break;
            case 3:
                money_won = 500000;
                break;
            }
            inventory.money += money_won;
            sleep(1);
            printf("\n=========================");
            printf("\n You won $%d this round!\n", money_won);
            printf("=========================\n");
            printf("\n\n\n");
            sleep(1);
        }

        // to reset lives of both player and mr z
        if (player_lives > 0)
        {
            player_lives = 3;
            z_lives = 3;
        }

        // so that the minigames only appear after round 1 and 2
        if (round == 1 || round == 2)
        {
            minigame(&inventory);
        }
    }
    printf("\n==================\n");
    printf("   GAME COMPLETED");
    printf("\n==================\n");
    printf("You defeated the BOSS\n");
    printf("You won %d from this game.\n", inventory.money);
}

int main()
{
    startBackgroundMusic("menu.mp3");
    printf("\n\n");
    printmp("logo4.txt");
    printf("\n\n\n\n\n");

    printf("Start the game (yes/no): ");
    char input1[INPUT_MAX];
    while (8)
    {
        fgets(input1, sizeof(input1), stdin);
        input1[strcspn(input1, "\n")] = 0;

        if (strcasecmp(input1, "yes") == 0)
        {
            break;
        }
        else if (strcasecmp(input1, "no") == 0)
        {
            printf("\n\nMaybe next time. Bye!\n\n");
            exit(0);
        }
        else
        {
            printf("Enter a valid input : ");
        }
    }

restart:
    printf("\n");
    printmp("boss.txt");
    printf("\n\n\n");

    printf("Hello there!");
    printf("\nMy name is Z");
    printf("\n\nLooks like you are lost.....");
    printf("\n\nWanna play a quick game with me? (yes/no): ");

    while (1)
    {
        char input[INPUT_MAX];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcasecmp(input, "yes") == 0)
        {
            printf("\n\n==================================================================");
            printf("\n\nThe rules are simple...");
            printf("\n\n1.There are two guns........");
            printf("\n\n2.We fire at each other.......");
            printf("\n\n==================================================================\n\n");
            sleep(2);
            printf("\n\nLet's start!\n\n");
            for (int i = 5; i > 0; i--)
            {
                sleep(1);
                printf("%d...\n\n", i);
            }
            sleep(1);

            stopBackgroundMusic("menu.mp3");
            startBackgroundMusic("game.mp3");

            gameloop();
            printf("\n\nRestart the game ? (yes/no) : ");
            char input2[INPUT_MAX];
            fgets(input2, sizeof(input2), stdin);
            input2[strcspn(input2, "\n")] = 0;
            if (strcasecmp(input2, "yes") == 0)
            {
                goto restart;
            }

            else if (strcasecmp(input2, "no") == 0)
            {
                break;
            }
            else
            {
                printf("Enter a valid input\n");
            }
        }
        else if (strcasecmp(input, "no") == 0)
        {
            printf("\n\n==================================================================");
            printf("\n\nYou can't escape now....\n");
            sleep(1);
            printf("\n\nThe rules are simple...");
            printf("\n\n1.There are two guns........");
            printf("\n\n2.We fire at each other.......");


            printf("\n\n==================================================================\n\n");
            sleep(2);
            printf("\n\nLet's start!\n\n");
            for (int i = 5; i > 0; i--)
            {
                sleep(1);
                printf("%d...\n\n", i);
            }
            sleep(1);

            stopBackgroundMusic("menu.mp3");
            startBackgroundMusic("game.mp3");

            gameloop();
            printf("\n\nRestart the game ? (yes/no) : ");
            char input3[INPUT_MAX];
            fgets(input3, sizeof(input3), stdin);
            input3[strcspn(input3, "\n")] = 0;
            if (strcasecmp(input3, "yes") == 0)
            {
                goto restart;
            }

            else if (strcasecmp(input3, "no") == 0)
            {
                break;
            }
            else
            {
                printf("Enter a valid input\n");
            }
        }
        else
        {
            printf("\nDON'T ");
            printf("MESS ");
            printf("WITH ");
            printf("ME! ");
            printf("ENTER A VALID INPUT : ");
        }
    }

    return 0;
}
