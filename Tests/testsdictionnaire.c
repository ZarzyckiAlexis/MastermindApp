#include "./tests.h"
#include "../Includes/mots.h"

/** Test qui vérifie le garnissage des données dans le dictionnaire
 * TestDictionnaire_OK
 * TestDictionnaire_KO_mauvais_fichier
 * TestDictionnaire_KO_erreur_mot
 * => Total: 3 tests
**/

// Test qui lit un dictionnaire correct
void TestDictionnaire_OK()
{
    struct Dico_Message message; // On crée la structure qui contient le message d'erreur
    struct Dictionnaire *dico = LireDictionnaire("../liste_francais_4.txt", &message); // On lit le dictionnaire
    TEST_ASSERT_NOT_NULL(dico); // On vérifie que le dictionnaire n'est pas nul
    TEST_ASSERT_EQUAL_INT(416, dico->nbMots); // On vérifie que le nombre de mots est correct
    TEST_ASSERT_EQUAL_STRING("abri", dico->mots[0]); // On vérifie que le premier mot est correct
    TEST_ASSERT_EQUAL_STRING("abus", dico->mots[1]); // On vérifie que le deuxième mot est correct
    TEST_ASSERT_EQUAL_STRING("acre", dico->mots[2]); // On vérifie que le troisième mot est correct
    EffacerDictionnaire(dico); // On libère la mémoire du dictionnaire
}

// Test qui lit un dictionnaire avec une erreur d'ouverture de fichier
void TestDictionnaire_KO_mauvais_fichier()
{
    struct Dico_Message message; // On crée la structure qui contient le message d'erreur
    struct Dictionnaire *dico = LireDictionnaire("fichier_inexistant.txt", &message); // On lit le dictionnaire
    TEST_ASSERT_NULL(dico); // On vérifie que le dictionnaire est nul
    TEST_ASSERT_EQUAL_STRING("Erreur lors de l'ouverture du fichier", message.message); // On vérifie que le message d'erreur est correct
    TEST_ASSERT_EQUAL_INT(2, message.codeErreur); // On vérifie que le code d'erreur est correct
}

// Test qui lit un dictionnaire avec une erreur de mot
void TestDictionnaire_KO_erreur_mot()
{
    struct Dico_Message message; // On crée la structure qui contient le message d'erreur
    struct Dictionnaire *dico = LireDictionnaire("../liste_francais_4_erreur.txt", &message); // On lit le dictionnaire
    TEST_ASSERT_NULL(dico); // On vérifie que le dictionnaire est nul
    TEST_ASSERT_EQUAL_STRING("Erreur lors de la lecture du mot", message.message); // On vérifie que le message d'erreur est correct
    TEST_ASSERT_EQUAL_INT(1, message.codeErreur); // On vérifie que le code d'erreur est correct
}


// Execute tous les tests de lecture du dictionnaire
void TestsDictionnaire()
{
    RUN_TEST(TestDictionnaire_OK);
    RUN_TEST(TestDictionnaire_KO_mauvais_fichier);
    RUN_TEST(TestDictionnaire_KO_erreur_mot);
}