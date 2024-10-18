# Projet Mastermind

## English

This project is an implementation of the **Mastermind** game in C, developed as part of the first year of the Bachelor's degree in IT Management at HELHa, Montignies-Sur-Sambre.

### Project Objectives

- Develop a functional project from a provided skeleton.
- Write and implement functional and unit tests.
- Use version control (GIT).
- Apply knowledge acquired during lessons.
- Present and defend the project in front of a jury.

### Key Features

- Start a game of Mastermind.
- Display the high scores.
- Enable/disable colors for improved visibility.
- Exit the application.

### How to Use

#### Launching the Application

Upon running the program, a menu will allow you to:

1. Start a game.
2. Display high scores.
3. Enable/disable colors.
4. Exit the application.

#### Playing a Game

- The game will ask you to enter a 4-letter word.
- Each correctly placed letter will be marked with a `+`, and incorrectly placed letters with a `-`.
- If the guessed word is incorrect, you have up to 10 attempts to find the solution.
- At the end of the game, you can save your score under a username.

### Scoring

The score is calculated using the formula: `11 - number of attempts`.

### Database Schema

The project uses a small database with two main tables:

- **Players**: stores the players' usernames.
- **Scores**: stores players' scores, with a foreign key to the `Players` table.

### Future Improvements

- Allow variable word lengths to increase difficulty.
- Improve the user interface by adding graphical elements.

### Tools Used

- [Valgrind](https://valgrind.org/) for memory leak detection.
- [Doxygen](https://www.doxygen.nl/) for automatic documentation generation from the code.

### Credits

Project developed by **Alexis Zarzycki** for the courses of Mr. Alary and Mr. Moins at HELHa, academic year 2023-2024.

---

## Français

Ce projet est une implémentation du jeu **Mastermind** en C, développé dans le cadre de la première année du Bachelier en Informatique de Gestion à la HELHa de Montignies-Sur-Sambre.

### Objectifs du projet

- Développer un projet fonctionnel à partir d'un squelette fourni.
- Rédiger et implémenter des tests fonctionnels et unitaires.
- Utiliser un gestionnaire de version (GIT).
- Appliquer les connaissances acquises durant les leçons.
- Présenter et défendre le projet devant un jury.

### Fonctionnalités principales

- Lancer une partie de Mastermind.
- Afficher les meilleurs scores.
- Activer/désactiver les couleurs pour améliorer la visibilité.
- Quitter l'application.

### Mode d'emploi

#### Lancement de l'application

À l'exécution du programme, un menu vous permet de :

1. Lancer une partie.
2. Afficher les meilleurs scores.
3. Activer/désactiver les couleurs.
4. Quitter l'application.

#### Jouer une partie

- Le jeu vous demande d'entrer un mot de 4 lettres.
- Chaque lettre bien placée est marquée par un `+`, et les lettres mal placées sont signalées par un `-`.
- Si le mot deviné est incorrect, vous avez jusqu'à 10 tentatives pour trouver la solution.
- À la fin d'une partie, vous pouvez enregistrer votre score sous un pseudo.

### Calcul du score

Le score est calculé selon la formule : `11 - nombre d'essais`.

### Schéma de la base de données

Le projet utilise une petite base de données avec deux tables principales :

- **Joueurs** : stocke les pseudos des joueurs.
- **Scores** : stocke les scores des joueurs avec une clé étrangère sur la table `Joueurs`.

### Améliorations futures

- Permettre la modification de la longueur du mot à deviner pour augmenter la difficulté.
- Amélioration de l'interface utilisateur en ajoutant des éléments graphiques.

### Outils utilisés

- [Valgrind](https://valgrind.org/) pour la détection des fuites de mémoire.
- [Doxygen](https://www.doxygen.nl/) pour la génération automatique de documentation à partir du code.

### Crédits

Projet développé par **Alexis Zarzycki** dans le cadre des cours de M. Alary et M. Moins à la HELHa, année académique 2023-2024.
