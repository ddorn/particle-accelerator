# Réponses

### Question P1.1

> Comment représentez vous ces vecteurs ? Comment sont-ils organisés : quels attributs ? quelles méthodes ? quels droits d'accès ?

Nous représentons ces vecteurs avec trois coordonnées séparées, en utilisant un `typedef` pour pouvoir changer le type
si besoin plus facilement. Nous avons choisis d'avoir trois coordoonées séparées plutot qu'un `array` de 3 éléments
 pour avoir une meilleure lisibilité.
 Nous avons donc trois attributs privés `x_, y_, z_`, avec des methodes get publiques pour les lire
ainsi que d'autres methodes, publiques, pour faire toutes sortes d'opérations communes (additions, calculer la norme...).

### Question P4.1
> Avez-vous ajouté un constructeur de copie ? Pourquoi (justifiez votre choix) ?

Un constructeur de copie ne semble pas utile pour l'instant, puisqu'il ferait exactement la même chose que le constructeur de base,
car il n'y a pas de pointeurs.

### Question P4.2
> Si l'on souhaitait ajouter un constructeur par coordonnées sphériques (deux angles et une longueur),
>    - que cela impliquerait-il au niveau des attributs de la classe ?
>    - quelle serait la difficulté majeure (voire l'impossibilité) de sa réalisation en C++ ?

- On pourrait soit garder les attributs en cooordonnées cartésiennes, mais il faudrait
avoir des méthodes permettant de passer des coordonnées cartésiennes aux coordonnées sphériques, et vice-versa, soit
avoir deux attributs d'angles et un attribut de longueur.
- Parce que les formules de somme de vecteurs pour des coordonnées sphériques sont bien plus compliquées que pour les
vecteurs en coordonnées cartésiennes. Or, les forces sont additives, ce qui signifie que la simulation va nécessiter un
grand nombre de sommes de vecteurs, les coordonnées sphériques ralentiraient donc fortement les calculs.

### Question P4.3
> Quels opérateurs avez-vous introduits ?

Les opérateurs += et -=, *= et /= (multiplication et division par un scalaire), == et !=  (comparaison de
deux vecteurs avec un certain degré de précision, car les coordonnées sont des double), +
 et -, * et / (avec un scalaire), * (produit scalaire), ^ (produit vectoriel) et enfin ~ (vecteur unitaire).


### Question P5.1
> Comment avez-vous implémenté gamma : comme attribut ou comme méthode ? Même question pour l'énergie.
	Répondez et discutez les avantages/inconvénients de chaque possibilité dans votre fichier REPONSES. Argumentez ensuite votre choix.


### Question P7.2 
> Pourquoi fait-on cela ? Pourquoi qualifier ces deux méthodes de « deleted » ? 

L'`Accelerator` est un gros object, qui contient de nombreuses `Particle`s, 
faiscaux, `Element`s. Ainsi on ne veut pas qu'il puisse être copié, 
car cela ferait une copie de beaucoup d'objects si l'on faisait une copie 
profonde, et si l'on fait une copie de surface, toutes les particules et
éléments seront partagés entre les copies.


### Question P8.1
> En termes de POO, quelle est donc la nature de la méthode heurte_bord() ?

C'est une méthode virtual pure.


### Question P8.2
> Qu'est-ce que cela implique sur la classe générale Element ?

La classe générale Element est abstraite, on ne peut donc pas créer
d'instances de cette classe.