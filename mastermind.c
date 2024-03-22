#include "./Includes/common.h"
#include "./Includes/clavier.h"
#include "./Includes/score.h"
#include "./Includes/ecran.h"
#include "./Includes/mots.h"
#include "./Includes/partie.h"

int main()
{
    // A CODER - fonctions principale. 
    // Penser à MM2, LPP2, FBD2

    // Création d'une instance de Partie
    struct Dictionnaire *dictionnaire;
    dictionnaire = LireDictionnaire("./liste_francais_4.txt", NULL);
    struct Partie *maPartie = CreerPartie(dictionnaire);

    // Initialisation de la structure Partie
    InitialiserEcran();
    AfficherPartie(maPartie, false);
    getch();
    EffacerEcran();
    TerminerEcran();
    EffacerDictionnaire(dictionnaire);
    EffacerPartie(maPartie);
    // FONCTIONS UTILISEES:
    // InitialiserEcran()
    // LireDictionnaire()
    // AfficherErreurEtTerminer()
    // CreerPartie()
    // JouerPartie()
    // AfficherMeilleursScores()
    // EffacerPartie()
    // EffacerDictionnaire()
    // TerminerEcran()
    
    return EXIT_SUCCESS; // A adapter
}