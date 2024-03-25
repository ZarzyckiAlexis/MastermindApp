#include "./Includes/common.h"
#include "./Includes/clavier.h"
#include "./Includes/score.h"
#include "./Includes/ecran.h"
#include "./Includes/mots.h"
#include "./Includes/partie.h"

int main()
{
    InitialiserEcran(); // Initialisation de l'écran

    // Création des instances de la structure Partie et Dictionnaire
    struct Dictionnaire *dictionnaire;
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message));

    creerBaseDeDonnees(Is_DB_TEST, dico_message); // Crée la DB si elle n'existe pas

    dictionnaire = LireDictionnaire("./liste_francais_4.txt", dico_message);
    if(dictionnaire == NULL){
        AfficherErreurEtTerminer(dico_message->message, dico_message->codeErreur);
        return EXIT_FAILURE;
    }
    
    struct Partie *maPartie = CreerPartie(dictionnaire);
    // Initialisation de la structure Partie
    JouerPartie(maPartie);
    if(maPartie == NULL){
        AfficherErreurEtTerminer("Erreur lors de la création de la partie", 1);
        return EXIT_FAILURE;
    }
    if(maPartie->resultat == true){
        bool resultat = SauverScore(Is_DB_TEST, maPartie->nomJoueur, maPartie->essaiEnCours, dico_message);
        if(resultat == false){
            AfficherErreurEtTerminer(dico_message->message, dico_message->codeErreur);
            return EXIT_FAILURE;
        }
    }

    RetourALaLigne();
    AfficherTexteSansRetour("Appuyez sur une touche pour continuer");
    LireTexte();
    AfficherMeilleursScores();
    free(dico_message);
    EffacerDictionnaire(dictionnaire);
    EffacerPartie(maPartie);
    EffacerEcran();
    TerminerEcran();

    return EXIT_SUCCESS;
}