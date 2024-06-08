#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_WORDS 100
#define WORD_LENGTH 50

// Function prototypes
void displayWelcomeScreen();
void displayHomeScreen();
void displayHelp();
void configureWords();
void startGame();
void clearScreen();

// Global variable to store words
char words[MAX_WORDS][WORD_LENGTH];
int wordCount = 0;

int main() {
    displayWelcomeScreen();
    displayHomeScreen();
    return 0;
}

void displayWelcomeScreen() {
    clearScreen();
    printf("\n\n\n\n\n");
    printf("\t\t\t\tUDBL - DACTYLOGICIEL\n");
    sleep(5);  // Display for 5 seconds
    clearScreen();
}

void displayHomeScreen() {
    int choice;
    do {
        printf("\n=== Ecran d'Accueil ===\n");
        printf("1. Demarrer\n");
        printf("2. Configurer\n");
        printf("3. Aide\n");
        printf("4. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                startGame();
                break;
            case 2:
                configureWords();
                break;
            case 3:
                displayHelp();
                break;
            case 4:
                printf("Quitter l'application...\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choice != 4);
}

void displayHelp() {
    clearScreen();
    printf("\n=== Aide ===\n");
    printf("Description de l'application: UDBL - DACTYLOGICIEL\n");
    printf("Version: 1.0\n");
    printf("Concepteurs: Votre Nom\n");
    printf("Date de conception: 10/04/2024\n");
    printf("Autres informations...\n");
    printf("\nAppuyez sur une touche pour retourner au menu principal...\n");
    getchar();
    getchar();
}

void configureWords() {
    clearScreen();
    printf("\n=== Configurer ===\n");
    printf("Entrez le nombre de mots a ajouter: ");
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        if (wordCount < MAX_WORDS) {
            printf("Entrez le mot %d: ", wordCount + 1);
            scanf("%s", words[wordCount]);
            wordCount++;
        } else {
            printf("Base de donnees de mots pleine.\n");
            break;
        }
    }
    printf("Configuration terminee. Appuyez sur une touche pour retourner au menu principal...\n");
    getchar();
    getchar();
}

void startGame() {
    if (wordCount == 0) {
        printf("Veuillez d'abord configurer les mots.\n");
        return;
    }
    
    clearScreen();
    printf("\n=== Demarrer le Jeu ===\n");
    int numWords;
    printf("Entrez le nombre de mots a saisir dans la partie: ");
    scanf("%d", &numWords);

    if (numWords > wordCount) {
        printf("Nombre de mots disponibles insuffisant.\n");
        return;
    }

    char player1[50], player2[50];
    printf("Entrez le pseudo du joueur 1: ");
    scanf("%s", player1);
    printf("Entrez le pseudo du joueur 2: ");
    scanf("%s", player2);

    int player1Time = 0, player2Time = 0;
    char input[WORD_LENGTH];

    srand(time(NULL));

    // Player 1
    printf("\n%s, c'est a vous!\n", player1);
    for (int i = 0; i < numWords; i++) {
        int randomIndex = rand() % wordCount;
        printf("Mot %d: %s\n", i + 1, words[randomIndex]);
        
        clock_t startTime = clock();
        do {
            printf("Entrez le mot: ");
            scanf("%s", input);
        } while (strcmp(input, words[randomIndex]) != 0);
        clock_t endTime = clock();
        
        player1Time += (int)(endTime - startTime) / CLOCKS_PER_SEC;
    }

    // Player 2
    printf("\n%s, c'est a vous!\n", player2);
    for (int i = 0; i < numWords; i++) {
        int randomIndex = rand() % wordCount;
        printf("Mot %d: %s\n", i + 1, words[randomIndex]);
        
        clock_t startTime = clock();
        do {
            printf("Entrez le mot: ");
            scanf("%s", input);
        } while (strcmp(input, words[randomIndex]) != 0);
        clock_t endTime = clock();
        
        player2Time += (int)(endTime - startTime) / CLOCKS_PER_SEC;
    }

    // Display results
    printf("\nResultats:\n");
    printf("%s: %d secondes\n", player1, player1Time);
    printf("%s: %d secondes\n", player2, player2Time);
    if (player1Time < player2Time) {
        printf("Le joueur %s est plus rapide!\n", player1);
    } else if (player1Time > player2Time) {
        printf("Le joueur %s est plus rapide!\n", player2);
    } else {
        printf("Egalite parfaite!\n");
    }

    printf("Appuyez sur une touche pour retourner au menu principal...\n");
    getchar();
    getchar();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
