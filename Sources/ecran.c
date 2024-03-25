#include "../Includes/common.h"
#include "../Includes/ecran.h"

// ***************************************//
// FONCTIONS DECLAREES DANS LE FICHIER .h //
// ***************************************//

// Initialise la console ncurses
void InitialiserEcran()
{
    // Initialiser l'écran en mode ncurses
    initscr();
}

// Terminer la console ncurses
void TerminerEcran()
{
    // Terminer l'écran en mode ncurses
    endwin();
}

// Efface l'ecran de la console ncurses
void EffacerEcran()
{
    // Effacer l'écran 
    clear();
}

// Va a la ligne dans la console ncurses
void RetourALaLigne()
{
    // Effectuer un retour à la ligne
    printw("\n");
    refresh(); // On rafraichit l'écran pour être sûr du changement
}

// Affiche dans la console ncurses un texte avec indentation
// a partir de la position courante
// sans retour a la ligne
// Paramètres:
// - la chaine de caracteres a afficher (pointeur)
void AfficherTexteIndenteSansRetour(char *texteAAfficher)
{
    // Afficher Texte avec indentation
    printw("\t%s", texteAAfficher);
    refresh(); // On rafraichit l'écran pour être sûr du changement
}

// Affiche une chaine de caracteres a la position courante dans la console ncurses
// sans retour a la ligne
// Paramètres:
// - la chaine de caracteres a afficher (pointeur)
void AfficherTexteSansRetour(char *texteAAfficher)
{
    // Afficher Texte sans retour à la ligne
    printw("%s", texteAAfficher);
    refresh(); // On rafraichit l'écran pour être sûr du changement
}

// Affiche un caractere a la position courante dans la console ncurses
// sans retour a la ligne
// Paramètres:
// - le caractere a afficher
// - le nombre de fois qu'il faut le repeter
void AfficherCharSansRetour(unsigned char caractereAAfficher, int repetition)
{
    // Afficher caractère x fois sans retour à la ligne
    for (int compteur = 0; compteur < repetition; compteur++)
    {
        printw("%c", caractereAAfficher);
    }
    refresh(); // On rafraichit l'écran pour être sûr du changement
}

// Affiche un nombre entier a la position courante dans la console ncurses
// sans retour a la ligne
// Paramètres:
// - le nombre a afficher
void AfficherNombreSansRetour(int nombreAAfficher)
{
    // Afficher nombre sans retour à la ligne
    printw("%d", nombreAAfficher);
    refresh(); // On rafraichit l'écran pour être sûr du changement
}

// Affiche un caractere special a la position courante dans la console ncurses
// sans retour a la ligne
// Cette fonction permet notamment de dessiner des bordures/contours
// Liste des codes: https://invisible-island.net/ncurses/man/curs_addch.3x.html
// Paramètres:
// - le caractere a traduire en code special
// - le nombre de fois qu'il faut le repeter
void AfficherCharSpecialSansRetour(unsigned char caractereAAfficher, int repetition)
{
    // Afficher caractère spécial x fois sans retour à la ligne
    for (int compteur = 0; compteur < repetition; compteur++)
    {
        addch(NCURSES_ACS(caractereAAfficher));
    }
    refresh(); // On rafraichit l'écran pour être sûr du changement
}

// Affiche dans la console ncurses un texte dans un cadre indente d'une tabulation
// Paramètres:
// - la chaine de caracteres a afficher dans le cadre (pointeur)
void AfficherTexteDansCadre(char *texteAAfficher)
{
    RetourALaLigne();
    int longeurTexte = strlen(texteAAfficher)+2; // On prends la longeur du texte + 2 pour les coins

    // Affichage de la ligne suppérieur du cadre
    AfficherCharSpecialSansRetour('l', 1); // On affiche le coin supérieur gauche
    AfficherCharSpecialSansRetour('q', longeurTexte); // On affihce la ligne du haut
    AfficherCharSpecialSansRetour('k', 1); // On affiche le coin supérieur droit
    
    // Affichage de la ligne centrale du cadre avec le texte
    RetourALaLigne();
    AfficherCharSpecialSansRetour('x', 1); // On affiche la barre gauche
    AfficherCharSansRetour(' ', 1); // On affiche 3 espace pour la séparation
    AfficherTexteSansRetour(texteAAfficher); // On affiche le texte
    AfficherCharSansRetour(' ', 1); // On affiche 1 espace pour la séparation
    AfficherCharSpecialSansRetour('x', 1);  // On affiche la barre droite

    // Affichage de la ligne inférieur du cadre
    RetourALaLigne(); // On fais un retour à la ligne
    AfficherCharSpecialSansRetour('m', 1);  // On affiche le coin inférieur gauche
    AfficherCharSpecialSansRetour('q', longeurTexte); // On affiche la ligne du bas
    AfficherCharSpecialSansRetour('j', 1); // On affiche le coin inférieur droit
    RetourALaLigne(); // On fais un retour à la ligne
    RetourALaLigne(); // On fais un retour à la ligne
    refresh(); // On rafraichît l'écran pour être sûr du changement
}

// Cette fonction efface l'ecran, affiche "Erreur" dans un cadre
// affiche un message et un code d'erreur sous le cadre,
// attend 5 secondes puis termine l'application
// Paramètres:
// - Le texte d'erreur
// - Le code d'erreur eventuel
void AfficherErreurEtTerminer(char *texteDErreur, int codeDErreur)
{
    EffacerEcran(); // On efface l'écran
    AfficherTexteDansCadre("Erreur"); // On affiche le texte "Erreur" dans un cadre
    AfficherTexteSansRetour(texteDErreur); // On affiche le texte d'erreur
    RetourALaLigne(); // On fais un retour à la ligne
    AfficherTexteSansRetour("Code d'erreur: "); // On affiche le texte "Code d'erreur: "
    AfficherNombreSansRetour(codeDErreur); // On affiche le code d'erreur
    RetourALaLigne() ; // On fais un retour à la ligne
    sleep(5); // On attends 5 secondes
    TerminerEcran(); // On termine l'écran
    exit(EXIT_FAILURE); // On exit en failure
}

// Affiche le haut du cadre de jeu (bordure supérieure)
// Paramètres:
// - Le mot à afficher, ou NULL si rien ne doit etre affiché
void AfficherHautDeJeu(char *motAAfficher)
{
    if (motAAfficher == NULL) { // Si le mot à afficher est NULL
        for(int compteur=0; compteur<NombreDeTabulationAGauche; compteur++){
            AfficherTexteIndenteSansRetour(" "); // On affiche les tabulations
        }
        AfficherCharSpecialSansRetour('l', 1); // On affiche le coin supérieur gauche
        AfficherCharSpecialSansRetour('q', LENGTH); // On affiche la ligne du haut
        AfficherCharSpecialSansRetour('w', 1); // On affiche la ligne du haut
        AfficherCharSpecialSansRetour('q', LENGTH-8); // On affiche la ligne du haut
        AfficherCharSpecialSansRetour('k', 1); // On affiche le coin supérieur droit
        RetourALaLigne(); // On fait un retour à la ligne
    } else { // Sinon
        for(int compteur=0; compteur<NombreDeTabulationAGauche; compteur++){
            AfficherTexteIndenteSansRetour(" "); // On affiche les tabulations
        }
        AfficherCharSpecialSansRetour('l', 1); // On affiche le coin supérieur gauche
        AfficherCharSpecialSansRetour('q', LENGTH-strlen(motAAfficher)); // On affiche la ligne du haut
        AfficherTexteSansRetour(motAAfficher); // On affiche le mot
        AfficherCharSpecialSansRetour('w', 1); // On affiche la ligne du haut
        AfficherCharSpecialSansRetour('q', LENGTH-8); // On affiche la ligne du haut
        AfficherCharSpecialSansRetour('k', 1); // On affiche le coin supérieur droit
        RetourALaLigne(); // On fait un retour à la ligne
    }
}

// Affiche un separateur entre deux mots du jeu
void AfficherSeparateurDeJeu()
{
    AfficherCharSpecialSansRetour('x', 1); // On affiche la barre gauche
}

// Affiche un mot du jeu et son resultat
// - Un '+' par lettre bien placée
// - Un '-' par lettre mal placée
// - Des espaces pour compléter
void AfficherMotDeJeu(char *motAAfficher, int nbreLettresBienplacées, int nbreLettresMalplacées)
{
    for(int compteur=0; compteur<NombreDeTabulationAGauche; compteur++){
            AfficherTexteIndenteSansRetour(" "); // On affiche les tabulations
    }
    AfficherSeparateurDeJeu(); // On affiche le séparateur de jeu
    AfficherCharSansRetour(' ', 2); // On affiche 2 espaces
    for(int compteur=0; compteur<strlen(motAAfficher); compteur++){ // Pour chaque lettre du mot à afficher
        AfficherCharSansRetour(motAAfficher[compteur], 1); // On affiche la lettre
        AfficherCharSansRetour(' ', 2); // On affiche 2 espaces
    }
    AfficherCharSansRetour(' ', 1); // On affiche 1 espace
    AfficherSeparateurDeJeu(); // On affiche le séparateur de jeu
    AfficherCharSansRetour(' ', 1); // On affiche 1 espace
    int space = LENGTH-9; // On initialise la variable space à 10
    for(int compteur=0; compteur<nbreLettresBienplacées; compteur++){ // Pour chaque lettre bien placée
        space--; // On décrémente la variable space
        AfficherCharSansRetour('+', 1); // On affiche un +
    }
    for(int compteur=0; compteur<nbreLettresMalplacées; compteur++){ // Pour chaque lettre mal placée
        space--; // On décrémente la variable space
        AfficherCharSansRetour('-', 1); // On affiche un -
    }    
    AfficherCharSansRetour(' ', space); // On affiche 1 espace
    AfficherSeparateurDeJeu(); // On affiche le séparateur de jeu
    RetourALaLigne(); // On fait un retour à la ligne
    for(int compteur=0; compteur<NombreDeTabulationAGauche; compteur++){
        AfficherTexteIndenteSansRetour(" "); // On affiche les tabulations
    }
    AfficherCharSpecialSansRetour('t', 1); // On affiche le coin inférieur gauche
    AfficherCharSpecialSansRetour('q', LENGTH); // On affiche la ligne du bas
    AfficherCharSpecialSansRetour('n', 1); // On affiche la ligne du bas
    AfficherCharSpecialSansRetour('q', LENGTH-8); // On affiche la ligne du bas
    AfficherCharSpecialSansRetour('u', 1); // On affiche le coin inférieur droit
    RetourALaLigne(); // On fait un retour à la ligne
    refresh();
}

// Affiche la bordure inférieure du jeu
void AfficherBasDeJeu()
{
    int x,y;
    getyx(stdscr, y, x); // On récupère la position courante
    move(y-1, 0); // On se déplace à la position courante
    for(int compteur=0; compteur<NombreDeTabulationAGauche; compteur++){
        AfficherTexteIndenteSansRetour(" "); // On affiche les tabulations
    }
    AfficherCharSpecialSansRetour('m', 1); // On affiche le coin inférieur gauche
    AfficherCharSpecialSansRetour('q', LENGTH); // On affiche la ligne du bas
    AfficherCharSpecialSansRetour('v', 1); // On affiche la ligne du bas
    AfficherCharSpecialSansRetour('q', LENGTH-8); // On affiche la ligne du bas
    AfficherCharSpecialSansRetour('j', 1); // On affiche le coin inférieur droit
    RetourALaLigne(); // On fait un retour à la ligne
}
