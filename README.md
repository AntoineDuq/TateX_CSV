# Tutorat de Programmation Avancée (IMA3 - 2016/2017)
---
</br>

#### **TateX** | Exploration de la collection du Tate Modern 



> Programme réalisé par Antoine GOSSE & Antoine DUQUENOY dans le cadre d'un projet de Programmation Avancée en IMA 3 à Polytech Lille.
>
> Les données utilisées dans ce programme sont sous licence *Creative Commons Public Domain [CC0](http://creativecommons.org/publicdomain/zero/1.0/)* et sont diffusées librement par le *Tate Modern* sur leur [git](https://github.com/tategallery/collection](https://github.com/tategallery/collection)).



## Procédure de lancement
---

</br>

Après avoir récupéré les fichiers du *repository*, placez vous dans le dossier, ouvrez un terminal et suivez la procédure suivante :

</br>

1. **Générer l'exécutable**

</br>

```
make
```

> La commande `make` se charge d'éxectuer le contenu du fichier *Makefile* et crée ainsi l'exécutable

</br></br>

2. **Lancer le programme**

Le lancement du programme peut se faire de deux manières différentes :

- Utilisation manuelle

```
./TateX data/tate_artwork.csv
```

Cette méthode permet de tester l'entierté des fonctions et de vérifier leurs résultats.

- Utilisation avec fichier de requêtes

```
./TateX data/tate_artwork.csv < requetes/5000_req.txt 
```

Cette seconde méthode permet l'exécution du programme avec des requêtes prédéfinies dans un fichier texte. Différents fichiers sont disponibles :

`0001_req.text` / `0005_req.txt` / `0050_req.txt` / `0500_req.txt` / `5000_req.txt` / `9999_req.txt`

Il est possible de tester le temps d'exécution du programme en tapant :

```
time ./TateX data/tate_artwork.csv < requetes/5000_req.txt > /dev/null
```
Et également de contrôler les fuites de mémoire :

```
valgrind ./TateX data/tate_artwork.csv < requetes/5000_req.txt > /dev/null
```
