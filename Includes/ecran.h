#include <time.h>
#include <unistd.h>
#include <ncurses.h>

// Definition des caractères de bordures pour les cadres autour des mots
#ifndef _ECRAN_CONST
/**
 * @brief Nombre de tabulations à gauche pour l'indentation
 * 
 */
static const int NombreDeTabulationAGauche = 3;

// Definition d'aliases pour les codes de couleurs (dépassement)
/**
 * @brief Définition d'aliases pour les codes couleurs de contour
 * 
 */
#define COULEURS_CONTOUR 1

/**
 * @brief Définition d'aliases pour les codes couleurs de mot
 * 
 */
#define COULEURS_MOT 2

/**
 * @brief Définition d'aliases pour les codes couleurs de mot bien placé
 * 
 */
#define COULEURS_BIENPLACE 3

/**
 * @brief Définition d'aliases pour les codes couleurs des questions
 * 
 */
#define COULEURS_QUESTION 3

/**
 * @brief Définition d'aliases pour les codes couleurs de mot mal placé
 * 
 */
#define COULEURS_MALPLACE 4

/**
 * @brief Définition d'aliases pour les codes couleurs d'erreur
 * 
 */
#define COULEURS_ERREUR 4
#endif

/**
 * @brief Longeur dynamique du tableau de mots
 * 
 */
#define LENGTH 15 // Longeur dynamique

// Déclaration des fonctions du module
/**
 * @brief Permet de choisir si l'ont veut utiliser les couleurs ou non
 * 
 * @param couleur booléen : true pour activer ; false pour désactiver
 */
void ChoisirModeEcran(bool couleur);

/**
 * @brief Fonction qui permet d'intialiser l'écran
 * 
 */
void InitialiserEcran();

/**
 * @brief Fonction qui permet de terminer l'écran
 * 
 */
void TerminerEcran();

/**
 * @brief Fonction qui permet d'effacer l'écran
 * 
 */
void EffacerEcran();

/**
 * @brief Fonction qui permet d'effectuer un retour à la ligne
 * 
 */
void RetourALaLigne();

/**
 * @brief Fonction qui permet d'afficher un texte indenté sans retour à la ligne
 * 
 * @param texteAAfficher la chaine de caracteres a afficher (pointeur)
 */
void AfficherTexteIndenteSansRetour(char *texteAAfficher);

/**
 * @brief Fonction qui permet d'afficher un texte sans retour à la ligne
 * 
 * @param texteAAfficher la chaine de caracteres a afficher (pointeur)
 */
void AfficherTexteSansRetour(char *texteAAfficher);

/**
 * @brief Fonction qui permet d'afficher un caractère sans retour à la ligne
 * 
 * @param caractereAAfficher le caractère a afficher
 * @param repetition le nombre de fois que le caractère doit être affiché
 */
void AfficherCharSansRetour(unsigned char caractereAAfficher, int repetition);

/**
 * @brief Fonction qui permet d'afficher un nombre sans retour à la ligne
 * 
 * @param nombreAAfficher le nombre a afficher
 */
void AfficherNombreSansRetour(int nombreAAfficher);

/**
 * @brief Fonction qui permet d'afficher un caractère spécial sans retour à la ligne
 * 
 * @param caractereAAfficher le caractere a traduire en code special
 * @param repetition le nombre de fois que le caractère doit être affiché
 */
void AfficherCharSpecialSansRetour(unsigned char caractereAAfficher, int repetition);

/**
 * @brief Fonction qui permet d'afficher un texte dans un cadre
 * 
 * @param texteAAfficher la chaine de caracteres a afficher dans le cadre (pointeur)
 */
void AfficherTexteDansCadre(char *texteAAfficher);

/**
 * @brief Fonction qui permet d'afficher une erreur et de terminer le programme
 * 
 * @param texteDErreur l'erreur à afficher (pointeur)
 * @param codeDErreur le code d'erreur à afficher
 */
void AfficherErreurEtTerminer(char *texteDErreur, int codeDErreur);

/**
 * @brief Affiche le haut du cadre de jeu (bordure supérieure)
 * 
 */
void AfficherHautDeJeu();

/**
 * @brief // Affiche un separateur entre deux mots du jeu
 * 
 */
void AfficherSeparateurDeJeu();

/**
 * @brief Affiche un mot du jeu et son resultat
            - Un '+' par lettre bien placée
            - Un '-' par lettre mal placée
            - Des espaces pour compléter
 * @param motAAfficher le mot à afficher (pointeur)
 * @param nbreLettresBienplacées le nombre de lettres bien placées
 * @param nbreLettresMalplacées le nombre de lettres mal placées
 */
void AfficherMotDeJeu(char *motAAfficher, int nbreLettresBienplacées, int nbreLettresMalplacées);

/**
 * @brief Fonction qui permet d'afficher la bordure du jeu
 * 
 */
void AfficherBasDeJeu();