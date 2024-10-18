# Projet Mastermind

Ce projet est une implémentation du jeu **Mastermind** en C, développé dans le cadre de la première année du Bachelier en Informatique de Gestion à la HELHa de Montignies-Sur-Sambre.

## Objectifs du projet

- Développer un projet fonctionnel à partir d'un squelette fourni.
- Rédiger et implémenter des tests fonctionnels et unitaires.
- Utiliser un gestionnaire de version (GIT).
- Appliquer les connaissances acquises durant les leçons.
- Présenter et défendre le projet devant un jury.

## Fonctionnalités principales

- Lancer une partie de Mastermind.
- Afficher les meilleurs scores.
- Activer/désactiver les couleurs pour améliorer la visibilité.
- Quitter l'application.

## Mode d'emploi

### Lancement de l'application

À l'exécution du programme, un menu vous permet de :

1. Lancer une partie.
2. Afficher les meilleurs scores.
3. Activer/désactiver les couleurs.
4. Quitter l'application.

### Jouer une partie

- Le jeu vous demande d'entrer un mot de 4 lettres.
- Chaque lettre bien placée est marquée par un `+`, et les lettres mal placées sont signalées par un `-`.
- Si le mot deviné est incorrect, vous avez jusqu'à 10 tentatives pour trouver la solution.
- À la fin d'une partie, vous pouvez enregistrer votre score sous un pseudo.

### Calcul du score

Le score est calculé selon la formule : `11 - nombre d'essais`.

## Schéma de la base de données

Le projet utilise une petite base de données avec deux tables principales :

- **Joueurs** : stocke les pseudos des joueurs.
- **Scores** : stocke les scores des joueurs avec une clé étrangère sur la table `Joueurs`.

## Améliorations futures

- Permettre la modification de la longueur du mot à deviner pour augmenter la difficulté.
- Amélioration de l'interface utilisateur en ajoutant des éléments graphiques.

## Outils utilisés

- [Valgrind](https://valgrind.org/) pour la détection des fuites de mémoire.
- [Doxygen](https://www.doxygen.nl/) pour la génération automatique de documentation à partir du code.

## Crédits

Projet développé par **Alexis Zarzycki** dans le cadre des cours de M. Alary et M. Moins à la HELHa, année académique 2023-2024.
