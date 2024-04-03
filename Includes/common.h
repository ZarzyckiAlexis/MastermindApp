#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>

#ifndef _DICO_COMMON
#define _DICO_COMMON

/**
 * @brief Structure pour stocker un message d'erreur et son code à renvoyer
 * 
 */
struct Dico_Message
{
    char message[201];
    int codeErreur;
};

/**
 * @brief Nombre maximum d'essais pour deviner un mot
 * 
 */
#define NbreMaxDEssais 10

/**
 * @brief Longeur max du nom d'un joueur
 * 
 */
#define LongueurMaxNomJoueur 10

/**
 * @brief Longeur max d'un mot
 * 
 */
#define LongueurDesMots 4

/**
 * @brief Nombre de scores à afficher
 * 
 */
#define NbreDeScoresAAfficher 10

/**
 * @brief Utilisé la DB de test ?
 * 
 */
#define Is_DB_TEST false
#endif