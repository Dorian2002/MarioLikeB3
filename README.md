# Projet de programmation B3

Dorian Fonseca / Kevin Granger / Louis Merlaud

## Presentation du projet

Ce projet avait pour but de réaliser un jeu de platforme type "Super Mario Bros" en utilisant l'outil de rendu graphique sfml en c++ tout en construisant une architecture ordonnée.

### Contraintes : 
- utilisations de design patterns (dans notre cas : ecs, state machine, signal slot)
- faire un effet de parallax
- faire un cmake pour faciliter l'initialisation du projet


### Initialisation : 
L'initialisation du projet se fait via cmake, tout d'abord assurez vous que dans le fichier `.env` la variable `PATH_VCPKG` contient le path vers votre fichier `vcpkg.cmake` (situé dans le dossier de vcpkg, ex :`PATH_VCPKG=C:\Users\louis\vcpkg\scripts\buildsystems\vcpkg.cmake`) pour générer les fichiers de builds exécutez la commande `cmake -G "Visual Studio 17 2022" -A x64` à la racine du projet où se situe le fichier `CMakeLists.txt` (assurez-vous d'avoir cmake d'installer sur votre machine: https://cmake.org/download/)

Après un build cmake, le projet peut être lancé de deux manières : 

soit via visual studio en accédant au projet via le .sln généré via cmake

soit via l'exécutable situé dans le répertoire `Debug` généré via cmake la racine du projet, (dans ce cas-ci, veuillez copier le dossier `ressources` à l'intérieur du répertoire `Debug`)

### Jouabilité

Une fois le projet lancé cliquez sur play pour jouer.

#### Commandes : 

| bouton               | Action      |
| -------------------- | ----------- |
| Q / flèche de gauche | gauche      |
| S / flèche de droite | droite      |
| SPACE                | saut        |

Pour gagner il faut toucher le drapeau à la fin du niveau,
toucher les ennemis sur les côtés ou tomber dans le vide met fin à la partie, les ennemis peuvent être éliminés en leur sautant dessus.