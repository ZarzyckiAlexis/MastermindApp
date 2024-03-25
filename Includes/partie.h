// Fonctions publiques
#include "./common.h"
#include "./mots.h"

#ifndef _DICO_PARTIE
#define _DICO_PARTIE
struct Partie
{
    char solution[5]; // 4 lettres + \0
    char liste_essais[10][5]; // 10 mots de 4 lettres + \0
    struct ResultatLigne resultats[10]; // 10 résultats
    char nomJoueur[21]; // 20 lettres + \0
    int essaiEnCours; // 0 à 9
    bool resultat; // true = victoire, false = abandon
};
#endif

struct Partie *CreerPartie(struct Dictionnaire *dictionnaire);
void EffacerPartie(struct Partie *partieEnCours);
bool JouerPartie(struct Partie *partieEnCours);
void AfficherPartie(struct Partie *partieEnCours, bool modeDebug);
void AfficherMeilleursScores();
// Dépassement
void afficherMenu();