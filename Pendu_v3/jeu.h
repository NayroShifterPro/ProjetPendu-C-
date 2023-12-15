#define NB_ESSAIS 8

void Presentation(char joueur[255]);
void afficherMotEnCours(char *motEnCours);
void afficherPendu(int coupsRestants);
int jouer(char *motEnCours, char motMystere[], int *coupsRestants, char lettresSaisies[], int *indexLettresSaisies);