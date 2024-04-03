// Fonctions publiques
#include "./common.h"
#include "./mots.h"

#ifndef _DICO_PARTIE
#define _DICO_PARTIE
/**
 * @brief Permet de définir la structure Partie qui contient les informations d'une partie
 *          - La solution à trouver
 *          - Une liste des mots déjà essayés
 *          - Une liste des résultats des essais
 *          - Le nom du joueur
 *          - Le nombre d'essai en cours
 *          - Le résultat de la partie
 * 
 */
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

/**
 * @brief Fonction pour créer une partie
 * 
 * @param dictionnaire Le dictionnaire contenant tous les mots
 * @return struct Partie* Une structure Partie allouée en memoire, avec un mot choisi au hasard et toute l'information mise à zero pour commencer la partie
 */
struct Partie *CreerPartie(struct Dictionnaire *dictionnaire);

/**
 * @brief Fonction pour libérer la memoire liée a une partie
 * 
 * @param partieEnCours Pointeur vers la structure Partie a libérer de la memoire
 */
void EffacerPartie(struct Partie *partieEnCours);

/**
 * @brief Fonction pour jouer une partie
 * 
 * @param partieEnCours Pointeur vers la structure Partie préablement initialisée avec une nouvelle partie
 * @return true si fin de partie (gagnée ou perdue) 
 * @return false si abandon 
 */
bool JouerPartie(struct Partie *partieEnCours);

/**
 * @brief Fonction pour afficher une partie en cours. Pour chaque mot déjà essayé, on affiche
            - Le mot
            - Le resultat: un + par lettre bien placée et un - par lettre mal placée
 * 
 * @param partieEnCours Pointeur vers la structure Partie
 * @param modeDebug Booleen qui indique si on est en mode debug (qui affiche la solution)
 */
void AfficherPartie(struct Partie *partieEnCours, bool modeDebug);

/**
 * @brief Fonction pour afficher les meilleurs scores
 * 
 */
void AfficherMeilleursScores();

// Dépassement
/**
 * @brief Fonction pour afficher le menu principal
 * 
 */
void afficherMenu();