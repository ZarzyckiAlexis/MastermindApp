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
    dictionnaire = LireDictionnaire("./liste_francais_4.txt", dico_message);
    if(dictionnaire == NULL){
        AfficherErreurEtTerminer(dico_message->message, dico_message->codeErreur);
        return EXIT_FAILURE;
    }
    struct Partie *maPartie = CreerPartie(dictionnaire);

    // Initialisation de la structure Partie
    JouerPartie(maPartie);
    EffacerDictionnaire(dictionnaire);
    EffacerPartie(maPartie);
    getch();
    EffacerEcran();
    TerminerEcran();
    
    return EXIT_SUCCESS;
}