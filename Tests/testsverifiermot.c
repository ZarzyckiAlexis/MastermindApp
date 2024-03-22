#include "./tests.h"
#include "../Includes/mots.h"

/** Test qui vérifie des mots de bonne longueur avec uniquement des minuscules
 * TestMot_OK
 * TestMot_KO_FULLMAJ   
 * TestMot_KO_premier_caractere_maj
 * TestMot_KO_deuxieme_caractere_maj
 * TestMot_KO_troisieme_caractere_maj
 * TestMot_KO_quatrieme_caractere_maj
 * TestMot_KO_pas_assez_de_lettre
 * TestMot_KO_trop_de_lettre
 * TestMot_KO_chaine_contient_carspe
 * TestMot_KO_chaine_vide
 * TestMot_KO_chaine_contient_nombre
 * TestMot_KO_chaine_uniquement_nombre
 * => Total: 12 tests
**/

// Test qui vérifie un mot correct
void TestMot_OK()
{
    TEST_ASSERT_EQUAL_INT(1, VerifierMot("abcd"));
}

// Test qui vérifie un mot avec uniquement des majuscules
void TestMot_KO_FULLMAJ()
{
    TEST_ASSERT_EQUAL_INT(0, VerifierMot("ABCD"));
}

// Test qui vérifie un mot avec un premier caractère en majuscule
void TestMot_KO_premier_caractere_maj()
{
    TEST_ASSERT_EQUAL_INT(0, VerifierMot("Abcd"));
}

// Test qui vérifie un mot avec un deuxième caractère en majuscule
void TestMot_KO_deuxieme_caractere_maj()
{
    TEST_ASSERT_EQUAL_INT(0, VerifierMot("aBcd"));
}

// Test qui vérifie un mot avec un troisième caractère en majuscule
void TestMot_KO_troisieme_caractere_maj()
{
    TEST_ASSERT_EQUAL_INT(0, VerifierMot("abCd"));
}

// Test qui vérifie un mot avec un quatrième caractère en majuscule
void TestMot_KO_quatrieme_caractere_maj()
{
    TEST_ASSERT_EQUAL_INT(0, VerifierMot("abcD"));
}

// Test qui vérifie un mot avec pas assez de lettres
void TestMot_KO_pas_assez_de_lettre()
{
    TEST_ASSERT_EQUAL_INT(0, VerifierMot("abc"));
}

// Test qui vérifie un mot avec trop de lettres
void TestMot_KO_trop_de_lettre()
{
    TEST_ASSERT_EQUAL_INT(0, VerifierMot("abcde"));
}

// Test qui vérifie un mot avec un caractère spécial
void TestMot_KO_chaine_contient_carspe()
{
    TEST_ASSERT_EQUAL_INT(0, VerifierMot("abc@"));
}

// Test qui vérifie une chaîne vide
void TestMot_KO_chaine_vide()
{
    TEST_ASSERT_EQUAL_INT(0, VerifierMot(""));
}

// Test qui vérifie une chaîne contenant un nombre
void TestMot_KO_chaine_contient_nombre()
{
    TEST_ASSERT_EQUAL_INT(0, VerifierMot("1bcd"));
}

// Test qui vérifie une chaîne contenant uniquement des nombres
void TestMot_KO_chaine_uniquement_nombre()
{
    TEST_ASSERT_EQUAL_INT(0, VerifierMot("1234"));
}


void TestsVerificationDUnMot()
{
    RUN_TEST(TestMot_OK);
    RUN_TEST(TestMot_KO_FULLMAJ);
    RUN_TEST(TestMot_KO_premier_caractere_maj);
    RUN_TEST(TestMot_KO_deuxieme_caractere_maj);
    RUN_TEST(TestMot_KO_troisieme_caractere_maj);
    RUN_TEST(TestMot_KO_quatrieme_caractere_maj);
    RUN_TEST(TestMot_KO_pas_assez_de_lettre);
    RUN_TEST(TestMot_KO_trop_de_lettre);
    RUN_TEST(TestMot_KO_chaine_contient_carspe);
    RUN_TEST(TestMot_KO_chaine_vide);
    RUN_TEST(TestMot_KO_chaine_contient_nombre);
    RUN_TEST(TestMot_KO_chaine_uniquement_nombre);
}