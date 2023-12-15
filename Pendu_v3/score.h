#define MAX_JOUEURS 100

typedef struct {
    char nom[255];
    int score;
} Joueur;

void mettreAJourScores(Joueur scores[], char joueur[]);
void chargerScores(Joueur scores[]);
void sauvegarderScores(Joueur scores[]);
void afficherTopJoueurs(Joueur scores[]);
