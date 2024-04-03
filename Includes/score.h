#include <mysql.h>
#include "./common.h"

#ifndef _DICO_SCORE
#define _DICO_SCORE
/**
 * @brief Constante qui contient le nom de la base de données de production
 * 
 */
#define PROD_DB_NAME "la219263"

/**
 * @brief Constante qui contient le nom de la base de données de test
 * 
 */
#define TEST_DB_NAME "la219263_test"

/**
 * @brief Structure Points qui contient:
 *         - Le nom du joueur
 *         - Le score
 * 
 */
struct Points
{
    char nomJoueur[51]; // 50 caractères + 1 pour le \0
    int score;
};

/**
 * @brief Constante qui contient l'IP du serveur de base de données
 * 
 */
static const char *ServerDB = "127.0.0.1";

/**
 * @brief Constante qui contient le résultat de la requête SQL (global)
 * 
 */
static MYSQL_RES *sqlResult;
#endif

/**
 * @brief Fonction pour executer une instruction SQL. En cas d'erreur, affiche la cause a la console, mais continue toujours
 * 
 * @param sqlConnection Pointeur vers la structure de connexion MYSQL
 * @param instructionSQL Chaine de caracteres avec l'instruction a executer
 * @param messageDeRetour Structure pour ecrire un message et un code en cas d'erreur
 * @return true réussite
 * @return false échec
 */
bool ExecuterInstructionSQL(MYSQL *sqlConnection, char *instructionSQL, struct Dico_Message *messageDeRetour);

/**
 * @brief Fonction pour se connecter a la base de donnees en la creant si elle n'existe pas
 * 
 * @param DBDeTest Booleen qui indique si c'est la base de donnees pour les tests unitaires ou pas 
 * @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
 * @return MYSQL*  Pointeur vers la structure MYSQL de la connexion
 */
MYSQL *ConnecterBaseDeDonnees(bool DBDeTest, struct Dico_Message *messageDeRetour);

/**
 * @brief Fonction lire l'identifiant unique du joueur dans la base de donnees
 * 
 * @param sqlConnection Pointeur vers la structure de connexion MYSQL
 * @param nomJoueur Le nom du joueur
 * @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
 * @return int L'identifiant unique du joueur dans la base de donnees
 */
int LireIDJoueur(MYSQL *sqlConnection, char *nomJoueur, struct Dico_Message *messageDeRetour);

/**
 * @brief Fonction pour sauver un score dans la base de donnees
 * 
 * @param baseDeTest Booleen qui indique si c'est la base de donnees pour les tests unitaires ou pas 
 * @param nomJoueur Le nom du joueur
 * @param nombreDEssais Le nombre d'essai
 * @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
 * @return true réussite
 * @return false échec
 */
bool SauverScore(bool baseDeTest, char *nomJoueur, int nombreDEssais, struct Dico_Message *messageDeRetour);

/**
 * @brief Fonction pour lire les meilleurs scores dans la base de donnees
 * 
 * @param baseDeTest Booleen qui indique si c'est la base de donnees pour les tests unitaires ou pas 
 * @param nombreDeScore Le nombre de scores maximum à lire
 * @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
 * @return struct Points* Un pointeur vers le nombre demandé de Points ou bien NULL en cas d'erreur
 */
struct Points *LireMeilleursScores(bool baseDeTest, int nombreDeScore,  struct Dico_Message *messageDeRetour);

// Dépassement

/**
 * @brief Fonction qui supprimer les tables dans la base de données
 * 
 * @param baseDeTest Boolen qui indique si c'est la base de données de test ou de production
 * @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
 * @return true réussite
 * @return false échec
 */
bool viderBaseDeDonnees(bool baseDeTest, struct Dico_Message *messageDeRetour);

/**
 * @brief Fonction qui crée les tables dans la base de données
 * 
 * @param baseDeTest Boolen qui indique si c'est la base de données de test ou de production
 * @param messageDeRetour Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
 * @return true réussite
 * @return false échec
 */
bool creerBaseDeDonnees(bool baseDeTest, struct Dico_Message *messageDeRetour);