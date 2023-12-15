#include "jeu.h"
#include "mot.h"
#include "score.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char joueur[255];
    char Rejouer;

    do {
        Presentation(joueur);

        char mots[999][30];
        int nbMots;
        ChargerMots(mots, &nbMots);

        char *motMystere = choisirMot(mots, nbMots);
        char *motEnCours = initialiserMotEnCours(motMystere);

        int coupsRestants = NB_ESSAIS;
        char lettresSaisies[26];
        int indexLettresSaisies = 0;

        Joueur scores[MAX_JOUEURS];
        chargerScores(scores);

        int resultat;
        do {
            afficherMotEnCours(motEnCours);
            printf("Il vous reste %u essai(s).\n", coupsRestants);

            resultat = jouer(motEnCours, motMystere, &coupsRestants, lettresSaisies, &indexLettresSaisies);
        } while (resultat == -1);

        if (resultat == 1) {
            mettreAJourScores(scores, joueur); // Utilisez la variable 'joueur' ici
            sauvegarderScores(scores);
            chargerScores(scores);
        }

        afficherTopJoueurs(scores);  // Afficher le top 10 après la partie

        free(motEnCours);

        // Demander au joueur s'il souhaite rejouer
        printf("Voulez-vous rejouer ? (O/N) : ");
        scanf(" %c", &Rejouer);

    } while (Rejouer == 'O' || Rejouer == 'o');

    return 0;
}