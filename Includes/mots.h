#ifndef _DICO_CONST
#define _DICO_CONST

/**
 * @brief Structure pour stocker le dictionnaire des mots
 *          - Elle contient un tableau dynamique de mots
 *          - Le compteur du nombre de mots
 * 
 */
struct Dictionnaire
{
    // Tableau dynamique de mots
    char **mots;
    // Compteur du nombre de mots
    int nbMots;
};

// Structure pour le résultat d'un ligne contenant le nombre de lettres bien
// placées et le nombre de lettre mal placées
/**
 * @brief Structure pour le résultat d'une ligne contenant 
 *          - le nombre de lettres bien placées 
 *          - le nombre de lettres mal placées
 * 
 */
struct ResultatLigne
{
    // Nombre de lettres bien placées
    int bienPlaces;
    // Nombre de lettres mal placées
    int malPlaces;
};
#endif

// Déclaration des fonctions du module
/**
 * @brief Fonction qui permet de vérifier qu'un mot comporte exactement 4 lettres minuscules sans accent
 * 
 * @param motAVerifier Le mot à vérifier (pointeur)
 * @return true si le mot est correct
 * @return false si le mot n'est pas correct
 */
bool VerifierMot(char *motAVerifier);

/**
 * @brief 
 * 
 * @param nomDeFichier le nom du fichier (pointeur)
 * @param messageDeRetour l'adresse de la structure Dico_Message
 * @return struct Dictionnaire* Une structure Dictionnaire remplie ou NULL s'il y a eu une erreur
 */
struct Dictionnaire *LireDictionnaire(char *nomDeFichier, struct Dico_Message *messageDeRetour);

/**
 * @brief Fonction qui permet de libèrer la mémoire du dictionnaire passé en Paramètre
 * 
 * @param dictionnaire le dictionnaire à libèrer (pointeur)
 */
void EffacerDictionnaire(struct Dictionnaire *dictionnaire);

/**
 * @brief Fonctionqui compare deux mots pour une ligne de jeu en comptant les lettres bien placées et les lettres mal pacées
 * 
 * @param solution Le mot de référence (pointeur)
 * @param motPlace Le mot placé par le joueur (pointeur)
 * @param resultat La structure qui contient le nombre de lettres bien placées et mal placées
 * @return true Si la comparaison est possible, elle garnit la structure ResultatLigne
 * @return false Si la comparaison n'est pas possible
 */
bool ComparerMots(char *solution, char *motPlace, struct ResultatLigne *resultat);