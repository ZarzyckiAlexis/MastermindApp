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
    init_pair(1, COULEURS_CONTOUR, COLOR_BLACK); // Couleur du texte
    afficherMenu(); // Affichage du menu
    EffacerEcran(); // Effacement de l'écran
    TerminerEcran(); // Terminaison de l'écran
    return EXIT_SUCCESS;
}