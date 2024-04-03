#include "./tests.h"
#include "../Includes/mots.h"

/**
 * @brief Test de comparaison de mots identiques
 * 
 */
void TestComparerMots_Identiques()
{
    char mot1[] = "test"; // Mot à deviner
    char mot2[] = "test"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(4, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(0, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaison de mots trois lettres sont bien placées et une lettre absente
 * 
*/
void TestComparerMots_TroisLettresBienPlacees_UneLettreAbsente()
{
    char mot1[] = "test"; // Mot à deviner
    char mot2[] = "tost"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(3, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(0, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaison de mots deux lettres sont bien placées et deux lettres sont mal placées
 * 
**/
void TestComparerMots_DeuxLettresBienPlacees_DeuxLettresMalPlacees()
{
    char mot1[] = "lore"; // Mot à deviner
    char mot2[] = "lero"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(2, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(2, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaison de mots deux lettres sont bien placées et deux lettres sont absentes
 * 
 */
void TestComparerMots_DeuxLettresBienPlacees_DeuxLettresAbsentes()
{
    char mot1[] = "tard"; // Mot à deviner
    char mot2[] = "tant"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(2, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(0, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaison de mots une lettre est bien placée et trois lettres sont mal placées
 * 
 */
void TestComparerMots_UneLettreBienPlacee_TroisLettresMalPlacees()
{
    char mot1[] = "arme"; // Mot à deviner
    char mot2[] = "amer"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(1, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(3, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaison de mots une lettre est bien placée, deux lettres sont mal placées et une lettre est absente
 * 
 */
void TestComparerMots_UneLettreBienPlacee_DeuxLettresMalPlacees_UneLettreAbsente()
{
    char mot1[] = "arme"; // Mot à deviner
    char mot2[] = "amex"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(1, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(2, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaison de mots une lettre est bien placée et trois lettres sont absentes
 * 
 */
void TestComparerMots_UneLettreBienPlacee_TroisLettresAbsentes()
{
    char mot1[] = "arme"; // Mot à deviner
    char mot2[] = "azzz"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(1, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(0, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaison de mots aucune lettre n'est bien placée, mais les quatres lettres sont présentes
 * 
 */
void TestComparerMots_AucuneLettreBienPlacee()
{
    char mot1[] = "tard"; // Mot à deviner
    char mot2[] = "atdr"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(0, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(4, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaison de mots trois lettres sont mal placées et une lettre est absente
 * 
 */
void TestComparerMots_TroisLettresMalPlacees_UneLettreAbsente()
{
    char mot1[] = "lore"; // Mot à deviner
    char mot2[] = "olea"; // Mot proposé
    struct ResultatLigne resultat; //  Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(0, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(3, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaison de mots deux lettres sont mal placées et deux lettres sont absentes
 * 
 */
void TestComparerMots_DeuxLettresMalPlacees_DeuxLettresAbsentes()
{
    char mot1[] = "arme"; // Mot à deviner
    char mot2[] = "mzaz"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(0, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(2, resultat.malPlaces);  // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaison de mots une lettre est mal placée et trois lettres sont absentes
 * 
 */
void TestComparerMots_UneLettreMalPlacee_TroisLettresAbsentes()
{
    char mot1[] = "arme"; // Mot à deviner
    char mot2[] = "zazz"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(0, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(1, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaisons de mots aucune lettre n'est bien placée et une lettre est absente
 * 
 */
void TestComparerMots_AucuneLettreBienPlacee_UneLettreAbsente()
{
    char mot1[] = "arme"; // Mot à deviner
    char mot2[] = "zzzz"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(0, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(0, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaisons de mots deux lettres sont absentes et deux lettres sont bien placées
 * 
 */
void TestComparerMots_DeuxLettresAbsentes_DeuxLettresBienPlacees()
{
    char mot1[] = "arme"; // Mot à deviner
    char mot2[] = "xrmz"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(2, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(0, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaisons de mots une lettre est absente et trois lettres sont bien placées
 * 
 */
void TestComparerMots_UneLettreAbsente_TroisLettresBienPlacees()
{
    char mot1[] = "arme"; // Mot à deviner
    char mot2[] = "armz"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(3, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(0, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaisons de mots deux lettres sont absentes et deux lettres sont mal placées
 * 
 */
void TestComparerMots_DeuxLettresAbsentes_DeuxLettresMalPlacees()
{
    char mot1[] = "arme"; // Mot à deviner
    char mot2[] = "mxzr"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(0, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(2, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaisons de mots une lettre est absente, deux lettres sont mal placées et une lettre est bien placée
 * 
 */
void TestComparerMots_UneLettreAbsente_DeuxLettresMalPlacees_UneLettreBienPlacee()
{
    char mot1[] = "arme"; // Mot à deviner
    char mot2[] = "azrm"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(1, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(2, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Test de comparaisons de mots quatre lettres sont absentes
 * 
 */
void TestComparerMots_QuatreLettresAbsentes()
{
    char mot1[] = "arme"; // Mot à deviner
    char mot2[] = "zzzz"; // Mot proposé
    struct ResultatLigne resultat; // Résultat de la comparaison
    bool resultatAttendu = ComparerMots(mot1, mot2, &resultat); // Comparaison des mots
    TEST_ASSERT_TRUE(resultatAttendu); // Vérification de la comparaison
    TEST_ASSERT_EQUAL_INT(0, resultat.bienPlaces); // Vérification du nombre de lettres bien placées
    TEST_ASSERT_EQUAL_INT(0, resultat.malPlaces); // Vérification du nombre de lettres mal placées
}

/**
 * @brief Execute tous les tests de comparaison de mots
 * 
 */
void TestsComparaisonDeMots()
{
    RUN_TEST(TestComparerMots_Identiques);
    RUN_TEST(TestComparerMots_TroisLettresBienPlacees_UneLettreAbsente);
    RUN_TEST(TestComparerMots_DeuxLettresBienPlacees_DeuxLettresMalPlacees);
    RUN_TEST(TestComparerMots_DeuxLettresBienPlacees_DeuxLettresAbsentes);
    RUN_TEST(TestComparerMots_UneLettreBienPlacee_TroisLettresMalPlacees);
    RUN_TEST(TestComparerMots_UneLettreBienPlacee_DeuxLettresMalPlacees_UneLettreAbsente);
    RUN_TEST(TestComparerMots_UneLettreBienPlacee_TroisLettresAbsentes);
    RUN_TEST(TestComparerMots_AucuneLettreBienPlacee);
    RUN_TEST(TestComparerMots_TroisLettresMalPlacees_UneLettreAbsente);
    RUN_TEST(TestComparerMots_DeuxLettresMalPlacees_DeuxLettresAbsentes);
    RUN_TEST(TestComparerMots_UneLettreMalPlacee_TroisLettresAbsentes);
    RUN_TEST(TestComparerMots_AucuneLettreBienPlacee_UneLettreAbsente);
    RUN_TEST(TestComparerMots_DeuxLettresAbsentes_DeuxLettresBienPlacees);
    RUN_TEST(TestComparerMots_UneLettreAbsente_TroisLettresBienPlacees);
    RUN_TEST(TestComparerMots_DeuxLettresAbsentes_DeuxLettresMalPlacees);
    RUN_TEST(TestComparerMots_UneLettreAbsente_DeuxLettresMalPlacees_UneLettreBienPlacee);
    RUN_TEST(TestComparerMots_QuatreLettresAbsentes);
}