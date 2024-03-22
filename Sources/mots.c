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
    // Conseil: commencer par décrire l'algorithme en détail, p.ex. en pseudo langage

    // FONCTIONS UTILISEES:
    // cf. cours LPP2 et LPP1 (chaînes de caractères)

    return false; // A adapter
}