#include "mot.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

// Fonction pour charger les mots depuis le fichier words.txt
void ChargerMots(char mots[999][30], int *nbMots) {
    FILE *fichier = fopen("words.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    *nbMots = 0;
    while (fgets(mots[*nbMots], sizeof(mots[*nbMots]), fichier) != NULL && *nbMots < 999) {
        mots[*nbMots][strlen(mots[*nbMots]) - 1] = '\0';
        (*nbMots)++;
    }

    fclose(fichier);
}

// Fonction pour choisir un mot aléatoire parmi la liste
char *choisirMot(char mots[999][30], int nbMots) {
    srand(time(NULL));
    return mots[rand() % nbMots];
}

// Fonction pour initialiser le mot en cours avec des underscores
char *initialiserMotEnCours(char *motMystere) {
    unsigned int length = strlen(motMystere);
    char *motEnCours = (char *)malloc(length + 1);

    for (int i = 0; i < length; i++) {
        motEnCours[i] = '_';
    }
    motEnCours[length] = '\0';

    return motEnCours;
}