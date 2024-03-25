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
        messageDeRetour->codeErreur = 12; // Code d'erreur
        strcpy(messageDeRetour->message, "Erreur lors de l'execution de l'instruction SQL"); // Message d'erreur
        return false; // On retourne false en cas d'erreur
    }

    // Stocker le résultat de la requête
    sqlResult = mysql_store_result(sqlConnection);
    if (sqlResult == NULL && mysql_affected_rows(sqlConnection) == 0) { // Si erreur
        messageDeRetour->codeErreur = 13; // Code d'erreur
        strcpy(messageDeRetour->message, "Erreur lors de l'execution de l'instruction SQL"); // Message d'erreur
        return false; // On retourne false en cas d'erreur
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
            messageDeRetour->codeErreur = 10; // Code d'erreur
            strcpy(messageDeRetour->message, "Erreur lors de la connexion a la base de donnees"); // Message d'erreur
            return NULL; // On retourne NULL en cas d'erreur
        }
    }
    else{ // Si c'est la base de donnees pour les tests

        // Connexion a la base de donnees pour les tests
        if (mysql_real_connect(sqlConnection, "localhost", "root", "", TEST_DB_NAME, 0, NULL, 0) == NULL)
        {
            messageDeRetour->codeErreur = 11; // Code d'erreur
            strcpy(messageDeRetour->message, "Erreur lors de la connexion a la base de donnees pour les tests"); // Message d'erreur
            return NULL; // On retourne NULL en cas d'erreur
        }

    }
    return sqlConnection; // On retourne la connexion a la base de donnees
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

    MYSQL *sqlConnection = ConnecterBaseDeDonnees(baseDeTest, messageDeRetour); // Connexion a la base de donnees
    if(sqlConnection == NULL){ // Si erreur
        return false;
    }

    // Lire l'ID du joueur
    int idJoueur = LireIDJoueur(sqlConnection, nomJoueur, messageDeRetour); // Lire l'ID du joueur
    if(idJoueur == -1){ // Si erreur
        return false; // On retourne false en cas d'erreur
    }
    
    if(nombreDEssais < 0){ // Si le nombre d'essais est inferieur a 1
        messageDeRetour->codeErreur = 15; // Code d'erreur
        strcpy(messageDeRetour->message, "Nombre d'essais invalide"); // Message d'erreur
        return false; // On retourne false en cas d'erreur
    }

    // Sauvegarde du score
    char query[256]; // Declaration de la requete SQL
    int score = 10 - nombreDEssais;
    sprintf(query, "INSERT INTO scores (score, id_joueur) VALUES (%d, %d)", score, idJoueur); // Creation de la requete SQL
    bool isOK = ExecuterInstructionSQL(sqlConnection, query, messageDeRetour); // Execution de l'instruction SQL
    if(!isOK){ // Si erreur
        return false; // On retourne false en cas d'erreur
    }

    // Fermeture de la connexion
    mysql_close(sqlConnection);
    return true;
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
    struct Points *points = malloc(sizeof(struct Points) * nombreDeScore); // Allocation de la memoire pour les scores
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(baseDeTest, messageDeRetour); // Connexion a la base de donnees
    if(sqlConnection == NULL){ // Si erreur
        return NULL; // On retourne NULL en cas d'erreur
    }

    // Lire les scores
    char query[256]; // Declaration de la requete SQL
    sprintf(query, "SELECT scores.score, scores.id_joueur, joueurs.pseudo FROM scores JOIN joueurs ON scores.id_joueur = joueurs.id_joueur ORDER BY scores.score DESC LIMIT %d;", nombreDeScore); // Creation de la requete SQL
    bool hasPassed = ExecuterInstructionSQL(sqlConnection, query, messageDeRetour); // Execution de l'instruction SQL
    if(!hasPassed){ // Si erreur
        return NULL; // On retourne NULL en cas d'erreur
    }
    // On garnit la structure des scores
    MYSQL_ROW sqlRow;
    int compteur = 0;
    for(int compteur=0; compteur<nombreDeScore; compteur++){ // On initialise les scores
        points[compteur].score = 0; // On initialise le score
        strcpy(points[compteur].nomJoueur, ""); // On initialise le nom du joueur
    }
    while((sqlRow = mysql_fetch_row(sqlResult)) != NULL){ // Tant qu'il y a des lignes
        points[compteur].score = atoi(sqlRow[0]); // On recupere le score
        strcpy(points[compteur].nomJoueur, sqlRow[2]); // On recupere le nom du joueur
        compteur++; // On incremente le compteur
    }
    // Fermeture de la connexion
    mysql_close(sqlConnection);
    return points;
}

bool viderBaseDeDonnees(bool baseDeTest, struct Dico_Message *messageDeRetour)
{
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(baseDeTest, messageDeRetour); // Connexion a la base de donnees
    if(sqlConnection == NULL){ // Si erreur
        printf("Erreur lors de la connexion a la base de donnees\n");
        return false;
    }

    // Vider la table scores
    char query[256]; // Declaration de la requete SQL
    sprintf(query, "DROP TABLE scores"); // Creation de la requete SQL
    ExecuterInstructionSQL(sqlConnection, query, messageDeRetour); // Execution de l'instruction SQL

    // Vider la table joueurs
    sprintf(query, "DROP TABLE joueurs"); // Creation de la requete SQL
    bool hasPassed = ExecuterInstructionSQL(sqlConnection, query, messageDeRetour); // Execution de l'instruction SQL
    if(hasPassed){ // Si erreur
        return false; // On retourne false en cas d'erreur
    }

    // Fermeture de la connexion
    mysql_close(sqlConnection);
    return true;
}

bool creerBaseDeDonnees(bool baseDeTest, struct Dico_Message *messageDeRetour)
{
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(baseDeTest, messageDeRetour); // Connexion a la base de donnees
    if(sqlConnection == NULL){ // Si erreur
        return false;
    }

    // Creation de la table joueurs
    char query[256]; // Declaration de la requete SQL
    sprintf(query, "CREATE TABLE joueurs (id_joueur INT AUTO_INCREMENT PRIMARY KEY, pseudo VARCHAR(50) NOT NULL);"); // Creation de la requete SQL
    ExecuterInstructionSQL(sqlConnection, query, messageDeRetour); // Execution de l'instruction SQL
    // Creation de la table scores
    sprintf(query, "CREATE TABLE scores (id_score INT AUTO_INCREMENT PRIMARY KEY, score INT NOT NULL, id_joueur INT NOT NULL, FOREIGN KEY (id_joueur) REFERENCES joueurs(id_joueur));"); // Creation de la requete SQL
    ExecuterInstructionSQL(sqlConnection, query, messageDeRetour); // Execution de l'instruction SQL

    // Fermeture de la connexion
    mysql_close(sqlConnection);
    return true;
}