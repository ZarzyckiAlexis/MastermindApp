#include "./tests.h"
#include "../Includes/score.h"

// Fonction pour remettre la base de donnees a zero avant un test
// Ceci est appele dans presque tous les tests de DB mais pas ailleurs
// donc pas d'utilisation de SetUp()
void ViderDBDeTest()
{
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    viderBaseDeDonnees(true, dico_message); // Vider la base de donnees de test
    creerBaseDeDonnees(true, dico_message); // Creer la base de donnees de test
    free(dico_message); // Liberer la memoire
}

// Test de connexion a la base de donnees PRODUCTION
void test_connexionDBPROD_OK()
{
    ViderDBDeTest(); // Vider la base de donnees de test
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(false, dico_message); // Connexion a la base de donnees
    TEST_ASSERT_NOT_NULL(sqlConnection); // Verifier que la connexion a la base de donnees a reussi
    free(dico_message); // Liberer la memoire
    mysql_close(sqlConnection); // Fermer la connexion
}

// Test de connexion a la base de donnees TEST
void test_connexionDBTEST_OK()
{
    ViderDBDeTest(); // Vider la base de donnees de test
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(true, dico_message); // Connexion a la base de donnees
    TEST_ASSERT_NOT_NULL(sqlConnection); // Verifier que la connexion a la base de donnees a reussi
    free(dico_message); // Liberer la memoire
    mysql_close(sqlConnection); // Fermer la connexion
}

// Test OK de la fonction ExecuterInstructionSQL
void test_ExecuterInstructionSQL_OK()
{
    ViderDBDeTest(); // Vider la base de donnees de test
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
    ViderDBDeTest(); // Vider la base de donnees de test
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(true, dico_message); // Connexion a la base de donnees
    TEST_ASSERT_NOT_NULL(sqlConnection); // Verifier que la connexion a la base de donnees a reussi
    char *instructionSQL = "SELECT * FROM joueur"; // Instruction SQL éronnée
    bool resultat = ExecuterInstructionSQL(sqlConnection, instructionSQL, dico_message); // Execution de l'instruction SQL
    TEST_ASSERT_FALSE(resultat); // Verifier que l'instruction SQL a échoué
    TEST_ASSERT_EQUAL_INT(12, dico_message->codeErreur); // Verifier que le code d'erreur est valide
    free(dico_message); // Liberer la memoire
    mysql_close(sqlConnection); // Fermer la connexion
}

// Test OK de la fonction LireIDJoueur pas encore existant
void test_LireIDJoueur_OK_PasExistant()
{
    ViderDBDeTest(); // Vider la base de donnees de test
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(true, dico_message); // Connexion a la base de donnees
    TEST_ASSERT_NOT_NULL(sqlConnection); // Verifier que la connexion a la base de donnees a reussi
    char *nomJoueur = "Joueur1"; // Nom du joueur
    int idJoueur = LireIDJoueur(sqlConnection, nomJoueur, dico_message); // Lire l'ID du joueur
    TEST_ASSERT_TRUE(idJoueur > 0); // Verifier que l'ID du joueur est valide
    free(dico_message); // Liberer la memoire
    mysql_close(sqlConnection); // Fermer la connexion
}

// Test OK de la fonction LireIDJoueur déjà existant
void test_LireIDJoueur_OK_Existant()
{
    ViderDBDeTest(); // Vider la base de donnees de test
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
    ViderDBDeTest(); // Vider la base de donnees de test
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
    ViderDBDeTest(); // Vider la base de donnees de test
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

// Test OK de la fonction SauverScore
void test_SauverScore_OK()
{
    ViderDBDeTest(); // Vider la base de donnees de test
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(true, dico_message); // Connexion a la base de donnees
    TEST_ASSERT_NOT_NULL(sqlConnection); // Verifier que la connexion a la base de donnees a reussi
    char *nomJoueur = "Joueur1"; // Nom du joueur
    int nombreDEssais = 10; // Nombre d'essais
    bool resultat = SauverScore(true, nomJoueur, nombreDEssais, dico_message); // Sauver le score
    TEST_ASSERT_TRUE(resultat); // Verifier que le score a ete sauve
    free(dico_message); // Liberer la memoire
    mysql_close(sqlConnection); // Fermer la connexion
}

// Test KO pour la fonction SauverScore
void test_SauverScore_KO()
{
    ViderDBDeTest(); // Vider la base de donnees de test
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(true, dico_message); // Connexion a la base de donnees
    TEST_ASSERT_NOT_NULL(sqlConnection); // Verifier que la connexion a la base de donnees a reussi
    char *nomJoueur = "Joueur1"; // Nom du joueur
    int nombreDEssais = -2; // Nombre d'essais négatif pour créer l'erreur
    bool resultat = SauverScore(true, nomJoueur, nombreDEssais, dico_message); // Sauver le score
    TEST_ASSERT_EQUAL_INT(0, resultat); // Verifier que le score n'a pas ete sauve
    TEST_ASSERT_EQUAL_INT(15, dico_message->codeErreur); // Verifier que le code d'erreur est valide
    free(dico_message); // Liberer la memoire
    mysql_close(sqlConnection); // Fermer la connexion
}

// Test OK de la fonction viderBaseDeDonnees
void test_supprimerDB_OK(){
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    bool resultat = viderBaseDeDonnees(true, dico_message); // Vider la base de donnees de test
    TEST_ASSERT_TRUE(resultat); // Verifier que la base de donnees a ete vide
    free(dico_message); // Liberer la memoire
}

// Test OK de la fonction creerBaseDeDonnees
void test_creerDB_OK(){
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    bool resultat = creerBaseDeDonnees(true, dico_message); // Creer la base de donnees de test
    TEST_ASSERT_TRUE(resultat); // Verifier que la base de donnees a ete cree
    free(dico_message); // Liberer la memoire
}

// Test OK de la fonction LireMeilleursScores
void test_LireMeilleursScores_OK(){
    ViderDBDeTest(); // Vider la base de donnees de test
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    char *nomJoueur = "Joueur1"; // Nom du joueur
    int nombreDEssais = 2; // Nombre d'essais
    bool resultat = SauverScore(true, nomJoueur, nombreDEssais, dico_message); // Sauver le score pour l'obtenir ensuite
    struct Points *points = LireMeilleursScores(true, 1, dico_message); // Lire les meilleurs scores
    TEST_ASSERT_NOT_NULL(points); // Verifier que les scores ont ete lus
    TEST_ASSERT_EQUAL_INT(8, points->score); // Verifier que l'ID du joueur est valide
    TEST_ASSERT_EQUAL_STRING(nomJoueur, points->nomJoueur); // Verifier que le nom du joueur est valide
    free(dico_message); // Liberer la memoire
}

// Test KO de la fonction LireMeilleursScores
void test_LireMeilleursScores_KO(){
    ViderDBDeTest(); // Vider la base de donnees de test
    struct Dico_Message *dico_message = malloc(sizeof(struct Dico_Message)); // Allocation de la memoire pour les messages
    // Ici on ne crée pas le score
    struct Points *points = LireMeilleursScores(true, 1, dico_message); // Lire les meilleurs scores
    TEST_ASSERT_NOT_NULL(points); // Verifier que les scores ont ete lus
    free(dico_message); // Liberer la memoire
}

// Execute tous les tests de scores dans la base de donnees
void TestsScores()
{
    RUN_TEST(test_connexionDBPROD_OK);
    RUN_TEST(test_connexionDBTEST_OK);
    RUN_TEST(test_ExecuterInstructionSQL_OK);
    RUN_TEST(test_ExecuterInstructionSQL_KO);
    RUN_TEST(test_LireIDJoueur_OK_PasExistant);
    RUN_TEST(test_LireIDJoueur_OK_Existant);
    RUN_TEST(test_LireIDJoueur_KO_NULL);
    RUN_TEST(test_LireIDJoueur_KO_50C);
    RUN_TEST(test_SauverScore_OK);
    RUN_TEST(test_SauverScore_KO);
    RUN_TEST(test_supprimerDB_OK);
    RUN_TEST(test_creerDB_OK);
    RUN_TEST(test_LireMeilleursScores_OK);
    RUN_TEST(test_LireMeilleursScores_KO);
}