#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdio.h>

#define NB_ESSAIS 8
#define MAX_JOUEURS 10

typedef struct {
    char nom[255];
    int score;
} Joueur;

int main() {
    //Présentation du joueur
    char joueur[255];  // Renommé de Joueur à joueur
    printf("Bonjour, veuillez saisir votre nom : \n");
    scanf("%s", joueur);
    printf("Bonjour '%s', pret pour jouer au jeu du pendu ?\n", joueur);
    //charger les mots depuis le fichier
    FILE *fichier = fopen("words.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    char mots[999][30];
    int nbMots = 0;
    while (fgets(mots[nbMots], sizeof(mots[nbMots]), fichier) != NULL) {
        mots[nbMots][strlen(mots[nbMots]) - 1] = '\0';
        nbMots++;
    }

    fclose(fichier);
    //choisir un mot aléatoire
    srand(time(NULL));
    char *motMystere = mots[rand() % nbMots];
    //initialiser le mot en cours avec des "_"
    unsigned int length = strlen(motMystere);
    char *motEnCours = (char *)malloc(length + 1);
    for (int i = 0; i < length; i++) {
        motEnCours[i] = '_';
    }
    motEnCours[length] = '\0';
    Joueur scores[MAX_JOUEURS];

    FILE *scoresFile = fopen("scores.txt", "r");
    if (scoresFile != NULL) {
        int i = 0;
        while (fscanf(scoresFile, "%s %d", scores[i].nom, &scores[i].score) == 2 && i < MAX_JOUEURS) {
            i++;
        }
        fclose(scoresFile);
    }

    unsigned int coupsRestants = NB_ESSAIS;
    int nbtrouvee;
    char lettresSaisies[26];
    int indexLettresSaisies = 0;

    do {
        printf("%s\n", motEnCours);
        printf("Il vous reste %u essai(s).\n Choisissez une lettre : ", coupsRestants);
        char c;
        scanf(" %c", &c);
        c = tolower(c);

        int lettreDejaSaisie = 0;
        for (int i = 0; i < indexLettresSaisies; i++) {
            if (lettresSaisies[i] == c) {
                lettreDejaSaisie = 1;
                printf("Vous avez deja saisi la lettre %c. Choisissez une autre lettre.\n", c);
                break;
            }
        }

        if (!lettreDejaSaisie) {
            lettresSaisies[indexLettresSaisies++] = c;

            nbtrouvee = 0;
            for (int i = 0; i < length; i++) {
                if (motMystere[i] == c) {
                    nbtrouvee++;
                    motEnCours[i] = c;
                }
            }

            if (nbtrouvee == 0) {
                coupsRestants--;
                switch (coupsRestants)
                {
                    case 0:
                        printf("\n   |--------|     \n");
                        printf("   o        |     \n");
                        printf("  /|\\       |     \n");
                        printf("   -        |     \n");
                        printf("  / \\       |     \n");
                        printf("            |     \n");
                        printf(" ---------------  \n");
                        printf("\n");
                        break;

                    case 1:
                        printf("\n   |--------|     \n");
                        printf("   o        |     \n");
                        printf("  /|\\        |     \n");
                        printf("   -        |     \n");
                        printf("    \\        |     \n");
                        printf("            |     \n");
                        printf(" ---------------  \n");
                        printf("\n");
                        break;

                    case 2:
                        printf("\n   |--------|     \n");
                        printf("   o        |     \n");
                        printf("  /|\\       |     \n");
                        printf("   -        |     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf(" ---------------  \n");
                        printf("\n");
                        break;

                    case 3:
                        printf("\n   |--------|     \n");
                        printf("   o        |     \n");
                        printf("  /|\\       |     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf(" ---------------  \n");
                        printf("\n");
                        break;

                    case 4:
                        printf("\n   |--------|     \n");
                        printf("   o        |     \n");
                        printf("  /|        |     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf(" ---------------  \n");
                        printf("\n");
                        break;

                    case 5:
                        printf("\n   |--------|     \n");
                        printf("   o        |     \n");
                        printf("   |        |     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf(" ---------------  \n");
                        printf("\n");
                        break;

                    case 6:
                        printf("\n   |--------|     \n");
                        printf("   o        |     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf(" ---------------  \n");
                        printf("\n");
                        break;

                    case 7:
                        printf("\n   |--------|     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf("            |     \n");
                        printf(" ---------------  \n");
                        printf("\n");
                        break;

                    default:
                        printf("\n");
                }

                if (coupsRestants == 0) {
                    printf("Vous avez perdu\nLe mot mystere etait \"%s\"\n", motMystere);
                    break;
                }
            } else {
                printf("La lettre %c est presente %u fois\n", c, nbtrouvee);
            }
        }
    } while (strcmp(motEnCours, motMystere) != 0);

    if (coupsRestants > 0) {
        printf("Vous avez gagne\nLe mot mystere etait \"%s\"\n", motMystere);

        int joueurTrouve = 0;
        for (int i = 0; i < MAX_JOUEURS; i++) {
            if (strcmp(scores[i].nom, joueur) == 0) {  // Changé de Joueur à joueur
                scores[i].score++;
                joueurTrouve = 1;
                break;
            }
        }

        if (!joueurTrouve) {
            strcpy(scores[MAX_JOUEURS - 1].nom, joueur);
            scores[MAX_JOUEURS - 1].score = 1;
        }

        scoresFile = fopen("scores.txt", "w");
        if (scoresFile != NULL) {
            for (int i = 0; i < MAX_JOUEURS; i++) {
                fprintf(scoresFile, "%s %d\n", scores[i].nom, scores[i].score);
            }
            fclose(scoresFile);
        }
    }

    free(motEnCours);
    return 0;
}