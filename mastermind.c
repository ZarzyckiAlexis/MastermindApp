#include "./Includes/common.h"
#include "./Includes/clavier.h"
#include "./Includes/score.h"
#include "./Includes/ecran.h"
#include "./Includes/mots.h"
#include "./Includes/partie.h"

int main()
{
    InitialiserEcran(); // Initialisation de l'écran
    start_color(); // Initialisation des couleurs
    // Définir les paires de couleurs
    init_pair(COULEURS_CONTOUR, COLOR_CYAN, COLOR_BLACK);
    init_pair(COULEURS_MOT, COLOR_WHITE, COLOR_BLACK);
    init_pair(COULEURS_BIENPLACE, COLOR_GREEN, COLOR_BLACK); // Couleur des lettres bien placées & de la question
    init_pair(COULEURS_MALPLACE, COLOR_RED, COLOR_BLACK); // Couleur des lettres mal placées & des erreurs
    afficherMenu(); // Affichage du menu
    EffacerEcran(); // Effacement de l'écran
    TerminerEcran(); // Terminaison de l'écran
    return EXIT_SUCCESS;
}