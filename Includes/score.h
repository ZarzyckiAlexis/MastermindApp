#include <mysql.h>
#include "./common.h"

#ifndef _DICO_SCORE
#define _DICO_SCORE
struct Points
{
    char nomJoueur[51]; // 50 caractères + 1 pour le \0
    int score;
};
static const char *ServerDB = "127.0.0.1";
#endif

MYSQL *ConnecterBaseDeDonnees(bool DBDeTest, struct Dico_Message *messageDeRetour);
int LireIDJoueur(MYSQL *sqlConnection, char *nomJoueur, struct Dico_Message *messageDeRetour);
bool SauverScore(bool baseDeTest, char *nomJoueur, int nombreDEssais, struct Dico_Message *messageDeRetour);
struct Points *LireMeilleursScores(bool baseDeTest, int nombreDeScore,  struct Dico_Message *messageDeRetour);
