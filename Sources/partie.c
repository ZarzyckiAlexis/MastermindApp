#include "../Includes/common.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"
#include "../Includes/mots.h"
#include "../Includes/partie.h"
#include "../Includes/score.h"

// Fonction pour créer une partie
// Paramètre:
// - Le dictionnaire contenant tous les mots
// Renvoie
// - Une structure Partie allouée en memoire, avec un mot choisi au hasard
//   et toute l'information mise à zero pour commencer la partie
struct Partie *CreerPartie(struct Dictionnaire *dictionnaire)
{
    struct Partie *partieEnCours;

    // On alloue la mémoire pour la structure Partie
    partieEnCours = malloc(sizeof(struct Partie));

    // On initialise les champs de la structure
    partieEnCours->essaiEnCours = 0;
    partieEnCours->resultat = false;
    partieEnCours->solution[5] = '\0';
    partieEnCours->nomJoueur[20] = '\0';
    for (int compteur = 0; compteur < 10; compteur++){
        for(int compteur_essai = 0; compteur_essai < 4; compteur_essai++){
            partieEnCours->liste_essais[compteur][compteur_essai] = ' ';
        }
        partieEnCours->liste_essais[compteur][4] = '\0'; // Mettez le caractère de fin de chaîne après avoir rempli les espaces
        partieEnCours->resultats[compteur].bienPlaces = 0;
        partieEnCours->resultats[compteur].malPlaces = 0;
    }
    // On choisit un mot au hasard dans le dictionnaire
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires
    int index = rand() % dictionnaire->nbMots; // Un nombre entre 0 et nbMots-1
    strcpy(partieEnCours->solution, dictionnaire->mots[index]); // On copie le mot dans la structure

    // On renvoie la structure initialisée
    return partieEnCours;
}

// Fonction pour libérer la memoire liee a une partie
// Paramètre:
// - Pointeur vers la strcuture Partie a libérer de la memoire
void EffacerPartie(struct Partie *partieEnCours)
{
    // On libère la mémoire allouée pour la structure
    free(partieEnCours);
}

// Fonction pour afficher une partie en cours
// Pour chaque mot déjà essayé, on affiche
// - Le mot
// - Le resultat: un + par lettre bien placée et un - par lettre mal placée
// Paramètre:
// - Pointeur vers la structure Partie
// - Booleen qui indique si on est en mode debug (qui affiche la solution)
void AfficherPartie(struct Partie *partieEnCours, bool modeDebug)
{
    // On efface tout et on affiche le jeu dans son état actuel
    EffacerEcran();
    AfficherHautDeJeu();
    for(int compteur = 0; compteur < 10; compteur++){
        AfficherMotDeJeu(partieEnCours->liste_essais[compteur], partieEnCours->resultats[compteur].bienPlaces, partieEnCours->resultats[compteur].malPlaces);
    }
    AfficherBasDeJeu();
}

// Fonction pour jouer une partie
// Paramètre:
// - Pointeur vers la structure Partie préablement initialisée avec une nouvelle partie
// Renvoie:
// - false si abandon, true si fin de partie (gagnée ou perdue)
// Fonctionnement:
// - Affiche la partie (mots déjà joués)
// - Demande un nouveau mot de 4 lettres ou ENTER pour abandonner le jeu
// - Verifier le mot et s'il est correct, calculer le resultat
//   (10 si trouve en 1 coup, 9 en 2 coups... 1 en 10 cours)
// - Si le mot n'est pas correct, le resultat est 0.
// A la fin de la partie:
// - Si gagne ou perdu: on demande le nom du jour et on sauve le résultat
// - Si abandon: fin de partie, on affiche la solution
bool JouerPartie(struct Partie *partieEnCours)
{
    strcpy(partieEnCours->solution, partieEnCours->solution); // Fix un bug de solution?
    do{
        AfficherPartie(partieEnCours, false); // On affiche la partie
        AfficherTexteIndenteSansRetour("Entrez un mot de 4 lettres ou ENTER pour abandonner: "); // On demande un mot
        char *answer = LireTexte(); // On demande un mot
        strcpy(partieEnCours->liste_essais[partieEnCours->essaiEnCours], answer); // On copie le mot dans la structure
        if(VerifierMot(partieEnCours->liste_essais[partieEnCours->essaiEnCours]) == false){ // On vérifie que le mot est correct
            AfficherErreurEtTerminer("Le mot doit contenir exactement 4 lettres.", 0); // On affiche un message d'erreur
            return false; // On retourne false pour abandonner
        }
        ComparerMots(partieEnCours->solution, partieEnCours->liste_essais[partieEnCours->essaiEnCours], &partieEnCours->resultats[partieEnCours->essaiEnCours]); // On compare les mots
        if (strcmp(partieEnCours->liste_essais[partieEnCours->essaiEnCours], partieEnCours->solution) == 0){ // Si le mot est correct
            AfficherPartie(partieEnCours, false); // On affiche la partie
            partieEnCours->resultat = true; // On met le résultat à true
            break; // On sort de la boucle
        }
        partieEnCours->essaiEnCours++; // On incrémente le nombre d'essais
        AfficherPartie(partieEnCours, false); // On affiche la partie
    } while (partieEnCours->resultat == false && partieEnCours->essaiEnCours < 10); // Tant que le jeu n'est pas fini

    return partieEnCours->resultat; // On retourne le résultat
}

// Fonction pour afficher les meilleurs scores
// Le nombre de scores est une constante du code, on peut la modifier et recompiler
// La fonction LireMeilleursScores() est appellée pour obtenir les meilleurs scores
// Son résultat est un tableau alloué en mémoire, qu'il faut libérer a la fin
void AfficherMeilleursScores()
{
    // FONCTIONS UTILISEES:
    // LireMeilleursScores()
    // AfficherErreurEtTerminer()
    // EffacerEcran()
    // AfficherTexteDansCadre()
    // AfficherTexteIndenteSansRetour()
    // AfficherTexteSansRetour()
    // AfficherNombreSansRetour()
    // RetourALaLigne()
    // LireTexte();
    // free()
}