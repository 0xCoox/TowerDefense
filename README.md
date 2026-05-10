# TowerDefense

Projet réalisé par Elouan Simon et Ahmet Ates.

## Présentation

TowerDefense est un jeu de défense de tours développé en C++20 avec SDL2.

Le joueur doit placer des tours sur les cases constructibles afin d'empêcher les ennemis d'atteindre la base. Les ennemis arrivent par vagues, et le joueur gagne de l'argent en les éliminant. Cet argent permet ensuite de placer, améliorer ou vendre des tours.

## Dépendances nécessaires

Avant de compiler le projet, il faut installer les bibliothèques nécessaires.

Sous Linux / Ubuntu / WSL :

sudo apt update
sudo apt install build-essential make g++ libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev doxygen graphviz

Dépendances utilisées :

- g++ : compilateur C++.
- make : outil de compilation utilisé avec le Makefile.
- SDL2 : bibliothèque principale pour la fenêtre, les événements et le rendu.
- SDL2_image : chargement des images et textures.
- SDL2_ttf : affichage du texte.
- Doxygen : génération de la documentation.
- Graphviz : génération des diagrammes UML dans la documentation Doxygen.

## Compilation

Pour compiler le projet :

make

## Exécution

Pour lancer le jeu après compilation :

cd bin
./tower_defense

Il est aussi possible de compiler et lancer directement avec :

make run

## Documentation

Pour générer la documentation Doxygen avec les diagrammes UML :

make doc

La documentation est générée dans le dossier :

doc/

## Nettoyage

Pour supprimer les fichiers générés :

make clean

Cette commande supprime les fichiers de compilation, l'exécutable et la documentation générée.

## Commandes du jeu

### Sélection principale

La sélection principale se fait avec la souris.

Le curseur suit normalement la position de la souris sur la carte. Cela permet de sélectionner rapidement une case, de placer une tour ou de sélectionner une tour existante.

### Contrôle avec les flèches

Les flèches directionnelles peuvent aussi être utilisées pour déplacer le curseur sur la carte.

Elles sont surtout utiles dans deux cas :
- lorsque la souris est sur le HUD ou sur le menu ;
- lorsqu'une tour est sélectionnée et que la sélection est verrouillée sur cette tour.

Dans ces situations, le joueur peut continuer à contrôler précisément le curseur avec le clavier.

## Interactions

- Souris : déplacer la sélection sur la carte.
- Drag and drop : sélectionner une tour dans le menu et la déposer sur une case constructible.
- Flèches directionnelles : déplacer le curseur sur la carte.
- Entrée : lancer une vague.
- Bouton Vague : lancer une vague.
- Clic gauche sur une tour existante : sélectionner cette tour.
- Bouton Améliorer : améliorer la tour sélectionnée.
- Bouton Vendre : vendre la tour sélectionnée.
- Deuxième clic gauche sur la carte : désélectionner la tour et réactiver le déplacement de la sélection avec la souris.
- Échap ou croix de la fenêtre : quitter le jeu.
- Touches 1, 2, 3, 4 et 5 : changer le type de tour sélectionné pour le placement.
- Touche A : ajouter une tour sur la case sélectionnée, avec le dernier type de tour choisi ou le dernier type utilisé en drag and drop.

## Règles principales

Une seule vague peut être lancée à la fois.
Il faut attendre que la vague actuelle soit terminée avant d'en lancer une nouvelle.

Les tours peuvent être placées uniquement sur les cases constructibles prévues sur la carte.

Le joueur peut utiliser à la fois la souris et le clavier : la souris est le mode principal de sélection, tandis que les flèches servent de contrôle complémentaire lorsque la souris est utilisée sur le HUD ou lorsqu'une tour est verrouillée.


