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
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(false, dico_message); // Connexion a la base de donnees
    TEST_ASSERT_NOT_NULL(sqlConnection); // Verifier que la connexion a la base de donnees a reussi
    free(dico_message); // Liberer la memoire
    mysql_close(sqlConnection); // Fermer la connexion
}

// Test de connexion a la base de donnees TEST
void test_connexionDBTEST_OK()
{
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(true, dico_message); // Connexion a la base de donnees
    TEST_ASSERT_NOT_NULL(sqlConnection); // Verifier que la connexion a la base de donnees a reussi
    free(dico_message); // Liberer la memoire
    mysql_close(sqlConnection); // Fermer la connexion
}

// Test OK de la fonction ExecuterInstructionSQL
void test_ExecuterInstructionSQL_OK()
{
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(true, dico_message); // Connexion a la base de donnees
    TEST_ASSERT_NOT_NULL(sqlConnection); // Verifier que la connexion a la base de donnees a reussi
    char *instructionSQL = "SELECT * FROM joueurs"; // Instruction SQL
    bool resultat = ExecuterInstructionSQL(sqlConnection, instructionSQL, dico_message); // Execution de l'instruction SQL
    TEST_ASSERT_TRUE(resultat); // Verifier que l'instruction SQL a reussi
    free(dico_message); // Liberer la memoire
    mysql_close(sqlConnection); // Fermer la connexion
}

// Test KO de la fonction ExecuterInstructionSQL
void test_ExecuterInstructionSQL_KO()
{
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(true, dico_message); // Connexion a la base de donnees
    TEST_ASSERT_NOT_NULL(sqlConnection); // Verifier que la connexion a la base de donnees a reussi
    char *instructionSQL = "SELECT * FROM joueur"; // Instruction SQL éronnée
    bool resultat = ExecuterInstructionSQL(sqlConnection, instructionSQL, dico_message); // Execution de l'instruction SQL
    TEST_ASSERT_FALSE(resultat); // Verifier que l'instruction SQL a échoué
    free(dico_message); // Liberer la memoire
    mysql_close(sqlConnection); // Fermer la connexion
}

// Test OK de la fonction LireIDJoueur
void test_LireIDJoueur_OK()
{
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(true, dico_message); // Connexion a la base de donnees
    TEST_ASSERT_NOT_NULL(sqlConnection); // Verifier que la connexion a la base de donnees a reussi
    char *nomJoueur = "Joueur1"; // Nom du joueur
    int idJoueur = LireIDJoueur(sqlConnection, nomJoueur, dico_message); // Lire l'ID du joueur
    TEST_ASSERT_TRUE(idJoueur > 0); // Verifier que l'ID du joueur est valide
    free(dico_message); // Liberer la memoire
    mysql_close(sqlConnection); // Fermer la connexion
}

// Test KO Pseudo NULL de la fonction LireIDJoueur
void test_LireIDJoueur_KO_NULL()
{
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(true, dico_message); // Connexion a la base de donnees
    TEST_ASSERT_NOT_NULL(sqlConnection); // Verifier que la connexion a la base de donnees a reussi
    char *nomJoueur = NULL; // Nom du joueur à NULL
    int idJoueur = LireIDJoueur(sqlConnection, nomJoueur, dico_message); // Lire l'ID du joueur
    TEST_ASSERT_EQUAL_INT(-1, idJoueur); // Verifier que l'ID du joueur est valide
    TEST_ASSERT_EQUAL_INT(14, dico_message->codeErreur); // Verifier que le code d'erreur est valide
    free(dico_message); // Liberer la memoire
    mysql_close(sqlConnection); // Fermer la connexion
}

// Test KO Pseudo + de 50 caractères de la fonction LireIDJoueur
void test_LireIDJoueur_KO_50C()
{
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(true, dico_message); // Connexion a la base de donnees
    TEST_ASSERT_NOT_NULL(sqlConnection); // Verifier que la connexion a la base de donnees a reussi
    char *nomJoueur = "Ceciestunpseudovraimentbeaucouptroplongnestcepasnonmdrlol"; // Nom du joueur à + de 50 caractères
    int idJoueur = LireIDJoueur(sqlConnection, nomJoueur, dico_message); // Lire l'ID du joueur
    TEST_ASSERT_EQUAL_INT(-1, idJoueur); // Verifier que l'ID du joueur est valide
    TEST_ASSERT_EQUAL_INT(14, dico_message->codeErreur); // Verifier que le code d'erreur est valide
    free(dico_message); // Liberer la memoire
    mysql_close(sqlConnection); // Fermer la connexion
}



// Execute tous les tests de scores dans la base de donnees
void TestsScores()
{
    RUN_TEST(test_connexionDBPROD_OK);
    RUN_TEST(test_connexionDBTEST_OK);
    RUN_TEST(test_ExecuterInstructionSQL_OK);
    RUN_TEST(test_ExecuterInstructionSQL_KO);
    RUN_TEST(test_LireIDJoueur_OK);
    RUN_TEST(test_LireIDJoueur_KO_NULL);
    RUN_TEST(test_LireIDJoueur_KO_50C);
}