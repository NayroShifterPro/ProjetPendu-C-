#include "jeu.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NB_ESSAIS 8

// Fonction de présentation du joueur et des règles du jeu
void Presentation(char joueur[255]) {
    printf("Bonjour, veuillez saisir votre nom : \n");
    scanf("%s", joueur);
    printf("Bonjour '%s', pret pour jouer au jeu du pendu ?\n", joueur);
    printf("Les regles sont simples, trouver le mot mystere, vous avez le droit a 8 erreurs. \n");
    printf("Veuillez saisir une lettre de l'alphabet francais a la fois, pas de ponctuation et ne pas saisir de caractere accentue ni de chiffre ! \n");
}

// Fonction pour afficher le mot en cours
void afficherMotEnCours(char *motEnCours) {
    printf("%s\n", motEnCours);
}

// Fonction pour afficher le pendu en fonction des essais restants
void afficherPendu(int coupsRestants) {
    // Utilisation de constantes pour rendre le code plus lisible

    switch (coupsRestants) {
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
}

int jouer(char *motEnCours, char motMystere[], int *coupsRestants, char lettresSaisies[], int *indexLettresSaisies) {
    char c;
    printf("Choisissez une lettre : ");
    scanf(" %c", &c);
    c = tolower(c);

    int lettreDejaSaisie = 0;
    for (int i = 0; i < *indexLettresSaisies; i++) {
        if (lettresSaisies[i] == c) {
            lettreDejaSaisie = 1;
            printf("Vous avez deja saisi la lettre %c. Choisissez une autre lettre.\n", c);
            break;
        }
    }

    if (!lettreDejaSaisie) {
        lettresSaisies[(*indexLettresSaisies)++] = c;

        int nbTrouvee = 0;
        for (int i = 0; i < strlen(motMystere); i++) {
            if (motMystere[i] == c) {
                nbTrouvee++;
                motEnCours[i] = c;
            }
        }

        if (nbTrouvee == 0) {
            (*coupsRestants)--;
            afficherPendu(*coupsRestants);

            if (*coupsRestants == 0) {
                printf("Vous avez perdu\nLe mot mystere etait \"%s\"\n", motMystere);
                return 0;
            }
        } else {
            printf("La lettre %c est presente %d fois\n", c, nbTrouvee);
        }

        if (strcmp(motEnCours, motMystere) == 0) {
            printf("Vous avez gagne\nLe mot mystere etait \"%s\"\n", motMystere);
            return 1;
        }

        return -1; // Retourne -1 pour indiquer que le jeu continue
    }

    return -1; // Retourne -1 si la lettre a déjà été saisie
}