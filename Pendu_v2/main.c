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
// Fonction de présentation du joueur et des règles du jeu
void Presentation(char joueur[255]) {
    printf("Bonjour, veuillez saisir votre nom : \n");
    scanf("%s", joueur);
    printf("Bonjour '%s', pret pour jouer au jeu du pendu ?\n", joueur);
    printf("Les regles sont simples, trouver le mot mystere, vous avez le droit a 8 erreurs. \n");
    printf("Veuillez saisir une lettre de l'alphabet francais a la fois, pas de ponctuation et ne pas saisir de caractere accentue ni de chiffre ! \n");
}

// Fonction pour charger les mots depuis le fichier
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
char *choisirMot(char mots[][30], int nbMots) {
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

        return -1;
    }

    return -1;
}

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
    for (int i = 0; i < MAX_JOUEURS; i++) {
        printf("%d. %s - Score: %d\n", i + 1, scores[i].nom, scores[i].score);
    }
    printf("--------------------------\n");
}

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
            mettreAJourScores(scores, joueur);
            sauvegarderScores(scores);
        }

        afficherTopJoueurs(scores);  // Afficher le top 10 après la partie

        free(motEnCours);

        // Demander au joueur s'il souhaite rejouer
        printf("Voulez-vous rejouer ? (O/N) : ");
        scanf(" %c", &Rejouer);

    } while (Rejouer == 'O' || Rejouer == 'o');

    return 0;
}