#include "../Includes/common.h"
#include "../Includes/mots.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"

// Cette fonction verifie qu'un mot comporte exactement 4 lettres minuscules sans accent
// Paramètres:
// - Le mot à vérifier
// Renvoie:
// - true si le mot est correct, false si le mot n'est pas correct
bool VerifierMot(char *motAVerifier){

    int length = strlen(motAVerifier);

    if(length != 4){
        return false; // Si la longueur n'est pas de 4
    }
    for(int compteur=0; compteur<length; compteur++){
        if(motAVerifier[compteur] < 'a' || motAVerifier[compteur] > 'z'){
            return false; // Si le caractère n'est pas une lettre minuscule
        }
    }
    return true; // Si le mot est correct
}

// Cette fonction initialise la structure avec le dictionnaire
// en l'allouant en memoire et en lisant le dictionnaire à partir d'un fichier
// En cas d'erreur:
// - elle garnit la structure Dico_Message avec l'explication de l'erreur puis renvoie NULL
// - c'est à l'appelant de décider d'afficher le message ou pas
// Paramètres:
// - le nom du fichier
// - l'adresse de la structure Dico_Message
// Renvoie:
// - Une structure Dictionnaire remplie
// - ou NULL s'il y a eu une erreur
struct Dictionnaire *LireDictionnaire(char *nomDeFichier, struct Dico_Message *messageDeRetour)
{
    FILE *dictionnaire = fopen(nomDeFichier, "r"); // On ouvre le fichier en lecture
    if(dictionnaire == NULL){ // Si le fichier n'a pas pu être ouvert
        strcpy(messageDeRetour->message, "Erreur lors de l'ouverture du fichier"); // On copie le message d'erreur
        messageDeRetour->codeErreur = errno; // On copie le code d'erreur
        return NULL; // On renvoie NULL
    } 
    // Si le fichier a bien été ouvert
    struct Dictionnaire *dico = malloc(sizeof(struct Dictionnaire)); // On alloue la mémoire pour le dictionnaire
    dico->nbMots = 0; // On initialise le nombre de mots à 0
    dico->mots = malloc(sizeof(char*)); // On alloue la mémoire pour le tableau de mots
    char buffer[LongueurDesMots+1]; // On crée un buffer pour stocker les mots
    while(fscanf(dictionnaire, "%s", buffer) != EOF){ // On lit les mots du fichier
        if(VerifierMot(buffer)){ // Si le mot est correct
            dico->mots[dico->nbMots] = malloc(sizeof(char) * LongueurDesMots+1); // On alloue la mémoire pour le mot
            strcpy(dico->mots[dico->nbMots], buffer); // On copie le mot dans le tableau
            dico->nbMots++; // On incrémente le nombre de mots
            dico->mots = realloc(dico->mots, sizeof(char*) * (dico->nbMots+1)); // On réalloue la mémoire pour le tableau
        } else{
            strcpy(messageDeRetour->message, "Erreur lors de la lecture du mot"); // On copie le message d'erreur
            messageDeRetour->codeErreur = 1; // On copie le code d'erreur
            fclose(dictionnaire); // On ferme le fichier
            return NULL; // On renvoie NULL
        }
    }
    fclose(dictionnaire); // On ferme le fichier
    return dico; // On renvoie le dictionnaire
}

// Cette fonction libère la mémoire du dictionnaire passé en Paramètre
// Elle libère d'abord la mémoire des pointeurs internes
// puis libère la mémoire globale du dictionnaire
// A appeler en fin de partie
void EffacerDictionnaire(struct Dictionnaire *dictionnaire)
{   
    for(int compteur=0; compteur<dictionnaire->nbMots; compteur++){
        free(dictionnaire->mots[compteur]); // On libère la mémoire de chaque mot
    }
    free(dictionnaire->mots); // On libère la mémoire du tableau de mots
    free(dictionnaire); // On libère la mémoire du dictionnaire
}

// Cette fonction compare deux mots pour une ligne de jeu
// en comptant les lettres bien placées et les lettres mal pacées
// Parammetres:
// - Solution (mot de reference)
// - Mot placé par le joueur
// - Adresse d'une structure a garnir avec le resultat
// Renvoie:
// - Si la comparaison n'est pas possible, elle renvoie false
// - Si la comparaison est possible, elle garnit la structure ResultatLigne et renvoie true
bool ComparerMots(char *solution, char *motPlace, struct ResultatLigne *resultat)
{
    if(VerifierMot(motPlace) == false){ // Si le mot placé n'est pas correct
        return false; // On renvoie false
    }
    resultat->bienPlaces = 0; // On initialise le nombre de lettres bien placées
    resultat->malPlaces = 0; // On initialise le nombre de lettres mal placées
    char *solutionTemp = malloc(sizeof(char) * strlen(solution)); // On alloue la mémoire pour une copie du mot de référence
    char *motPlaceTemp = malloc(sizeof(char) * strlen(motPlace)); // On alloue la mémoire pour une copie du mot placé
    strcpy(solutionTemp, solution); // On copie le mot de référence
    strcpy(motPlaceTemp, motPlace); // On copie le mot placé
    for(int compteur=0; compteur<strlen(solution); compteur++){
        if(solutionTemp[compteur] == motPlaceTemp[compteur]){ // Si la lettre est bien placée
            resultat->bienPlaces++; // On incrémente le nombre de lettres bien placées
            solutionTemp[compteur] = ' '; // On remplace la lettre par un espace
            motPlaceTemp[compteur] = ' '; // On remplace la lettre par un espace
        }
    }
    for(int compteur=0; compteur<strlen(solution); compteur++){
        for(int compteur2=0; compteur2<strlen(solution); compteur2++){
            if(solutionTemp[compteur] == motPlaceTemp[compteur2] && solutionTemp[compteur] != ' '){ // Si la lettre est mal placée
                resultat->malPlaces++; // On incrémente le nombre de lettres mal placées
                solutionTemp[compteur] = ' '; // On remplace la lettre par un espace
                motPlaceTemp[compteur2] = ' '; // On remplace la lettre par un espace
            }
        }
    }
    free(solutionTemp); // On libère la mémoire de la copie du mot de référence
    free(motPlaceTemp); // On libère la mémoire de la copie du mot placé
    return true; // On renvoie true
}