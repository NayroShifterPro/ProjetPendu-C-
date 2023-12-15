#include "score.h"
#include <stdio.h>
#include <string.h>


// Fonction pour mettre à jour les scores
void mettreAJourScores(Joueur scores[], char joueur[]) {
    int joueurTrouve = -1;

    // Chercher le joueur dans le tableau
    for (int i = 0; i < MAX_JOUEURS; i++) {
        if (strcmp(scores[i].nom, joueur) == 0) {
            scores[i].score++;
            joueurTrouve = i;
            break;
        }
    }

    // Si le joueur n'est pas dans le tableau, l'ajouter à la fin
    if (joueurTrouve == -1) {
        strcpy(scores[MAX_JOUEURS - 1].nom, joueur);
        scores[MAX_JOUEURS - 1].score = 1;
        joueurTrouve = MAX_JOUEURS - 1;
    }

    // Tri du tableau des scores en fonction des scores décroissants
    for (int i = 0; i < MAX_JOUEURS - 1; i++) {
        for (int j = i + 1; j < MAX_JOUEURS; j++) {
            if (scores[j].score > scores[i].score) {
                // Échanger les éléments
                Joueur temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }
}
// Fonction pour charger les scores depuis le fichier
void chargerScores(Joueur scores[]) {
    FILE *scoresFile = fopen("scores.txt", "r");
    if (scoresFile != NULL) {
        for (int i = 0; i < MAX_JOUEURS; i++) {
            if (fscanf(scoresFile, "%s %d", scores[i].nom, &scores[i].score) != 2) {
                // Échec de la lecture des scores
                break;
            }
        }
        fclose(scoresFile);
    } else {
        printf("Erreur lors de l'ouverture du fichier scores.txt pour le chargement des scores.\n");
    }
}

// Fonction pour sauvegarder les scores dans un fichier
void sauvegarderScores(Joueur scores[]) {
    FILE *scoresFile = fopen("scores.txt", "w");
    if (scoresFile != NULL) {
        for (int i = 0; i < MAX_JOUEURS; i++) {
            fprintf(scoresFile, "%s %d\n", scores[i].nom, scores[i].score);
        }
        fclose(scoresFile);
    } else {
        printf("Erreur lors de l'ouverture du fichier scores.txt pour la sauvegarde des scores.\n");
    }
}

// Fonction pour afficher le top 10 des joueurs
void afficherTopJoueurs(Joueur scores[]) {
    printf("\n--- Top 10 des joueurs ---\n");
    for (int i = 0; i < 10 && i < MAX_JOUEURS; i++) {
        printf("%d. %s - Score: %d\n", i + 1, scores[i].nom, scores[i].score);
    }
    printf("--------------------------\n");
}