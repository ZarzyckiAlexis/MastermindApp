#include "../Includes/common.h"
#include "../Includes/clavier.h"

// Lit au clavier et renvoit une chaîne de caractères en l'affichant
// Renvoie:
// - Le pointeur vers de la mémoire allouée avec la chaîne de caractères
// Note: cette chaîne devra être libérée par l'appelant plus tard
char *LireTexte(){
   char buffer[11] = "\0"; // Pour stocker temporairement la chaîne de caractère
   scanw("%10s", buffer); // On précise 10  pour éviter le overflow
   char *texte = (char *) malloc(strlen(buffer) + 1); // On prends la taille réel du buffer pour le malloc + 1 pour le null byte
   strcpy(texte, buffer); // On copie le contenu du buffer dans notre texte
   return texte; // On renvoie le pointeur
}