#include "../Includes/common.h"
#include "../Includes/score.h"


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
    if(mysql_query(sqlConnection, instructionSQL)){ // Si erreur
        messageDeRetour->codeErreur = 12;
        strcpy(messageDeRetour->message, "Erreur lors de l'execution de l'instruction SQL");
        return false;
    }

    // Stocker le résultat de la requête
    sqlResult = mysql_store_result(sqlConnection);
    if (sqlResult == NULL && mysql_affected_rows(sqlConnection) == 0) { // Si erreur
        messageDeRetour->codeErreur = 13;
        strcpy(messageDeRetour->message, "Erreur lors de l'execution de l'instruction SQL");
        return false;
    }
    return true;
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
    MYSQL_ROW sqlRow;

    if(nomJoueur == NULL || strlen(nomJoueur) > 50){ // Si le nom du joueur est NULL ou depasse 50 caracteres
        messageDeRetour->codeErreur = 14; // Code d'erreur
        strcpy(messageDeRetour->message, "Nom du joueur invalide"); // Message d'erreur
        return -1; // On retourne -1 en cas d'erreur
    }
    char query[256]; // Declaration de la requete SQL
    sprintf(query, "SELECT id_joueur FROM joueurs WHERE pseudo='%s'", nomJoueur); // Creation de la requete SQL
    bool hasPassed = ExecuterInstructionSQL(sqlConnection, query, messageDeRetour); // Execution de l'instruction SQL
    if(!hasPassed){ // Si erreur
        return -1;
    }
    sqlRow = mysql_fetch_row(sqlResult); // Recuperation de la ligne
    if(sqlRow == NULL){ // Si le joueur n'existe pas
        sprintf(query, "INSERT INTO joueurs (pseudo) VALUES ('%s')", nomJoueur); // Creation de la requete SQL
        hasPassed = ExecuterInstructionSQL(sqlConnection, query, messageDeRetour); // Execution de l'instruction SQL
        if(!hasPassed){ // Si erreur
            return -1; // On retourne -1 en cas d'erreur
        }
        return LireIDJoueur(sqlConnection, nomJoueur, messageDeRetour); // On rappelle la fonction pour obtenir l'ID du joueur
    }

    return atoi(sqlRow[0]); // On retourne l'ID du joueur
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