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
    partieEnCours->solution[LongueurDesMots+1] = '\0';
    partieEnCours->nomJoueur[LongueurMaxNomJoueur] = '\0';
    for (int compteur = 0; compteur < NbreMaxDEssais; compteur++){
        for(int compteur_essai = 0; compteur_essai < 4; compteur_essai++){
            partieEnCours->liste_essais[compteur][compteur_essai] = ' ';
        }
        partieEnCours->liste_essais[compteur][4] = '\0'; // Mettre le caractère de fin de chaîne après avoir rempli les espaces
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
    if(modeDebug == true){ // Si on est en mode debug
        AfficherHautDeJeu(partieEnCours->solution); // On affiche le haut du jeu avec le mot
    }
    else{ // Si on est pas en mode debug
        AfficherHautDeJeu(NULL); // On affiche le haut du jeu sans le mot
    }
    for(int compteur = 0; compteur < NbreMaxDEssais; compteur++){
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
    bool modeDebug = false; // On initialise le mode debug
    do{
        AfficherPartie(partieEnCours, modeDebug);
        AfficherTexteSansRetour("Entrez un mot de 4 lettres ou ENTER pour abandonner: ");
        char *answer = LireTexte();

        if(strcmp(answer, "*") == 0) {
            modeDebug = !modeDebug; // Toggle debug mode
            free(answer); // On libère la mémoire allouée pour la réponse
            continue; // Skip the rest of the loop and start from the beginning
        }
        else{
            strcpy(partieEnCours->liste_essais[partieEnCours->essaiEnCours], answer);
            if((VerifierMot(partieEnCours->liste_essais[partieEnCours->essaiEnCours]) == false)){ // On vérifie que le mot est correct
                RetourALaLigne();
                AfficherTexteSansRetour("Vous avez abandonner ou votre mot n'était pas correcte. La solution était: "); // On affiche un message
                AfficherTexteSansRetour(partieEnCours->solution); // On affiche la solution
                free(answer); // On libère la mémoire allouée pour la réponse
                return false; // On sort de la boucle
            }
            ComparerMots(partieEnCours->solution, partieEnCours->liste_essais[partieEnCours->essaiEnCours], &partieEnCours->resultats[partieEnCours->essaiEnCours]); // On compare les mots
            if (strcmp(partieEnCours->liste_essais[partieEnCours->essaiEnCours], partieEnCours->solution) == 0){ // Si le mot est correct
                AfficherPartie(partieEnCours, modeDebug); // On affiche la partie
                partieEnCours->resultat = true; // On met le résultat à true
                free(answer); // On libère la mémoire allouée pour la réponse
                break; // On sort de la boucle
            }
            partieEnCours->essaiEnCours++; // On incrémente le nombre d'essais
            AfficherPartie(partieEnCours, modeDebug); // On affiche la partie   
        }
        free(answer); // On libère la mémoire allouée pour la réponse
    } while (partieEnCours->resultat == false && partieEnCours->essaiEnCours < NbreMaxDEssais); // Tant que le jeu n'est pas fini
    if(partieEnCours->resultat == true){ // Si le résultat est vrai => Le joueur à gagner
        RetourALaLigne();
        AfficherTexteSansRetour("Quel est votre pseudo ? "); // On demande le pseudo du joueur
        char *pseudo = LireTexte(); // On lit le pseudo du joueur
        strcpy(partieEnCours->nomJoueur, pseudo); // On copie le pseudo dans la structure
        free(pseudo); // On libère la mémoire allouée pour le pseudo
    }
    return partieEnCours->resultat; // On retourne le résultat
}

// Fonction pour afficher les meilleurs scores
// Le nombre de scores est une constante du code, on peut la modifier et recompiler
// La fonction LireMeilleursScores() est appellée pour obtenir les meilleurs scores
// Son résultat est un tableau alloué en mémoire, qu'il faut libérer a la fin
void AfficherMeilleursScores()
{
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // On alloue la mémoire pour la structure Dico_Message
    struct Points *points = LireMeilleursScores(Is_DB_TEST, NbreDeScoresAAfficher, dico_message); // On lit les meilleurs scores
    EffacerEcran(); // On efface l'écran
    AfficherTexteDansCadre("Meilleurs scores"); // On affiche le texte dans un cadre
    if(points == NULL){ // Si on n'a pas pu lire les meilleurs scores
        AfficherTexteSansRetour("Il n'y a pas de score."); // On affiche un message d'erreur
        RetourALaLigne(); // On retourne à la ligne
        AfficherTexteSansRetour("Appuyez sur une touche pour continuer"); // On affiche un message
        getch(); // On attend que l'utilisateur appuie sur une touche
        EffacerEcran(); // On efface l'écran
        TerminerEcran(); // On termine l'écran
        exit(0); // On quitte le programme
    }
    for(int compteur = 0; compteur < NbreDeScoresAAfficher; compteur++){
        // Si le nom du joueur est vide
        if(strcmp(points[compteur].nomJoueur, "") == 0){
            break; // On sort de la boucle
        }
        AfficherTexteSansRetour(points[compteur].nomJoueur); // On affiche le nom du joueur
        AfficherTexteSansRetour(" : "); // On affiche un deux points
        AfficherNombreSansRetour(points[compteur].score); // On affiche le score
        RetourALaLigne(); // On retourne à la ligne
    }
    RetourALaLigne(); // On retourne à la ligne
    AfficherTexteSansRetour("Enfoncez ENTER pour continuer..."); // On affiche un message
    getch(); // On attend que l'utilisateur appuie sur une touche
    free(dico_message); // On libère la mémoire allouée pour la structure Dico_Message
    free(points); // On libère la mémoire allouée pour les points
}

// Dépassement
/*
    Fonction pour afficher le menu
*/
void afficherMenu(){
    char *choix;
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message));
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(Is_DB_TEST, dico_message); // Se connecter à la DB
    mysql_close(sqlConnection); // Fermer la connexion à la DB
    do{
        EffacerEcran(); // On efface l'écran
        // On affiche le menu
        AfficherTexteSansRetour("1. Jouer\n");
        AfficherTexteSansRetour("2. Meilleurs scores\n");
        AfficherTexteSansRetour("3. Quitter\n");
        AfficherTexteSansRetour("Votre choix: ");
        choix = LireTexte(); // On lit le choix de l'utilisateur
        if(strcmp(choix, "1") == 0){
             // Création des instances de la structure Partie et Dictionnaire
            struct Dictionnaire *dictionnaire;
            MYSQL *sqlConnection = ConnecterBaseDeDonnees(Is_DB_TEST, dico_message); // Se connecter à la DB
            mysql_close(sqlConnection); // Fermer la connexion à la DB
            
            dictionnaire = LireDictionnaire("./liste_francais_4.txt", dico_message);
            if(dictionnaire == NULL){
                AfficherErreurEtTerminer(dico_message->message, dico_message->codeErreur);
            }
            
            struct Partie *maPartie = CreerPartie(dictionnaire);
            // Initialisation de la structure Partie
            JouerPartie(maPartie);
            if(maPartie == NULL){
                AfficherErreurEtTerminer("Erreur lors de la création de la partie", 1);
            }
            if(maPartie->resultat == true){
                bool resultat = SauverScore(Is_DB_TEST, maPartie->nomJoueur, maPartie->essaiEnCours, dico_message);
                if(resultat == false){
                    AfficherErreurEtTerminer(dico_message->message, dico_message->codeErreur);
                }
            }
            RetourALaLigne();
            AfficherTexteSansRetour("Appuyez sur une touche pour continuer");
            getch();
            AfficherMeilleursScores();
            EffacerDictionnaire(dictionnaire);
            EffacerPartie(maPartie);
            free(choix);
        }
        else if(strcmp(choix, "2") == 0){
            // On affiche les meilleurs scores
            free(choix);
            AfficherMeilleursScores();
        }
        else if(strcmp(choix, "3") == 0){
            // On quitte le jeu
            free(choix);
            TerminerEcran();
            exit(EXIT_SUCCESS);
        }
    } while (strcmp(choix, "1") != 0 && strcmp(choix, "2") != 0 && strcmp(choix, "3") != 0);
}