#include "../Includes/common.h"
#include "../Includes/score.h"
#define PROD_DB_NAME "la219263"
#define TEST_DB_NAME "la219263_test"

// Fonction pour executer une instruction SQL
// En cas d'erreur, affiche la cause a la console, mais continue toujours
//
// Paramètres:
// - Pointeur vers la structure de connexion MYSQL
// - Chaine de caracteres avec l'instruction a executer
// - Structure pour ecrire un message et un code en cas d'erreur
// Renvoie:
// - booleen qui indique le resultat
bool ExecuterInstructionSQL(MYSQL *sqlConnection, char *instructionSQL, struct Dico_Message *messageDeRetour)
{
    // A coder - cf cours FBD2
    return false; // A adapter
}


// Fonction pour se connecter a la base de donnees en la creant si elle n'existe pas
// Paramètres:
// - Booleen qui indique si c'est la base de donnees pour les tests unitaires ou pas (et donc: de production)
// - Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
// Renvoie:
// - Pointeur vers la structure MYSQL de la connexion
MYSQL *ConnecterBaseDeDonnees(bool baseDeTest, struct Dico_Message *messageDeRetour)
{
    MYSQL *sqlConnection;
    sqlConnection = mysql_init(NULL); // Initialisation de la structure de connexion MYSQL
    if(baseDeTest == false){ // Si c'est la base de donnees de production
        // Connexion a la base de donnees
        if (mysql_real_connect(sqlConnection, "localhost", "root", "", PROD_DB_NAME, 0, NULL, 0) == NULL)
        {
            messageDeRetour->codeErreur = 10;
            strcpy(messageDeRetour->message, "Erreur lors de la connexion a la base de donnees");
            return NULL;
        }
    }
    else{ // Si c'est la base de donnees pour les tests

        // Connexion a la base de donnees pour les tests
        if (mysql_real_connect(sqlConnection, "localhost", "root", "", TEST_DB_NAME, 0, NULL, 0) == NULL)
        {
            messageDeRetour->codeErreur = 11;
            strcpy(messageDeRetour->message, "Erreur lors de la connexion a la base de donnees pour les tests");
            return NULL;
        }

    }

    return sqlConnection;
}

// Fonction lire l'identifiant unique du joueur dans la base de donnees
// Si le joueur n'est pas déjà present, il est ajoute puis la fonction
// se rapelle en recursif pour obtenir l'identifiant autoincremente dans la base de donnees
// Paramètres:
// - Pointeur vers la structure de connexion MYSQL
// - Le nom du joueur
// - Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
// Renvoie
// - L'identifiant unique du joueur dans la base de donnees
int LireIDJoueur(MYSQL *sqlConnection, char *nomJoueur, struct Dico_Message *messageDeRetour)
{
    MYSQL_RES *sqlResult;
    MYSQL_ROW sqlRow;

    // FONCTIONS APPELLEES:
    // ExecuterInstructionSQL();
    // Autres fonctions: voir le cours FBD2

    // Verification du nom du joueur: pas NULL et max 50 caracteres

    return 0; // A Adapter
}

// Fonction pour sauver un score dans la base de donnees
// Le score se calcule comme etant (nombre maximum d'essais + 1 - nombre d'essais)
// Paramètres:
// - Booleen qui indique si c'est la base de donnees pour les tests unitaires ou pas (et donc: de production)
// - Le nom du joueur
// - Le nombre d'essai.
// - Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
// Renvoie
// - Un booleen qui indique si le sauvetage s'est fait ou pas
bool SauverScore(bool baseDeTest, char *nomJoueur, int nombreDEssais, struct Dico_Message *messageDeRetour)
{
    // FONCTIONS APPELLEES:
    // ConnecterBaseDeDonnees();
    // LireIDJoueur();
    // ExecuterInstructionSQL();
    // Autres fonctions: voir le cours FBD2

    return false; // A adapter
}

// Fonction pour les meilleurs scores dans la base de donnees
// Paramètres:
// - Booleen qui indique si c'est la base de donnees pour les tests unitaires ou pas (et donc: de production)
// - Le nombre de scores maximum à lire
// - Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
// Renvoie
// - Un pointeur vers le nombre demandé de Points (pointeur vers un tableau)
//   ou bien NULL en cas d'erreur
struct Points *LireMeilleursScores(bool baseDeTest, int nombreDeScore, struct Dico_Message *messageDeRetour)
{
    // FONCTIONS APPELLEES:
    // ConnecterBaseDeDonnees();
    // ExecuterInstructionSQL();
    // malloc
    // Autres fonctions: voir le cours FBD2

    return NULL; // A adapter
}