#include "./tests.h"
#include "../Includes/score.h"

// Fonction pour remettre la base de donnees a zero avant un test
// Ceci est appele dans presque tous les tests de DB mais pas ailleurs
// donc pas d'utilisation de SetUp()
void ViderDBDeTest()
{
    // Créer ici le code qui vide la DB de test 
    // pour que tous les tests de DB démarrent avec une DB propre.
}

// Test de connexion a la base de donnees PRODUCTION
void test_connexionDBPROD_OK()
{
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message));
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(false, dico_message);
    TEST_ASSERT_NOT_NULL(sqlConnection);
    free(dico_message);
    mysql_close(sqlConnection);
}

// Test de connexion a la base de donnees TEST
void test_connexionDBTEST_OK()
{
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message));
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(true, dico_message);
    TEST_ASSERT_NOT_NULL(sqlConnection);
    free(dico_message);
    mysql_close(sqlConnection);
}

// Execute tous les tests de scores dans la base de donnees
void TestsScores()
{
    RUN_TEST(test_connexionDBPROD_OK);
    RUN_TEST(test_connexionDBTEST_OK);
}