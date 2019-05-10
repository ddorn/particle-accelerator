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

C'est une méthode virtual pure publique.


### Question P8.2
> Qu'est-ce que cela implique sur la classe générale Element ?

La classe générale Element est abstraite, on ne peut donc pas créer
d'instances de cette classe.


### Question P9.1
> En termes de POO, quelle est donc la nature de la méthode dessine() ?

C'est un cas de double dispatch.



### Question P9.2
> Quelle est la bonne façon de le faire dans un cadre de programmation orientée-objet ?

(en ce qui concerne les collections de particules et d'éléments de l'accélérateur)
Pour garder les spécificités, il faut créer une collection hétérogène. On va mettre en place
un vector de unique_ptr, afin de garder le polymorphisme.



### Question P9.3
> A quoi faut-il faire attention pour les classes contenant des pointeurs ? Quelles solutions peut-on envisager ?

Il faut faire attention à ce que les zones mémoire allouées soient
bien libérées après utilisation. Comme nous utilisons des unique_ptr,
cela se fait automatiquement. Il faut également faire attention lors de la
création des instances à ne pas créer des instances locales, puis à les ajouter
à une classe abstraite, car les zones mémoire seraient alors désallouées, mais
les pointeurs ne seraient pas supprimés. La solution est alors d'allouer dynamiquement
les zones mémoires, en faisant new Class(...).

### Question P11.1
> Comment avez-vous implémenté ces différentes caractéristiques : comme attribut ou comme méthode ? (concernant les
    ellipses de phase et l'émittance)

Ces valeurs changent avec le temps, il n'y a donc pas de raison de les mettre comme attributs.
A VOIR : Il pourrait cependant être intéressant de garder les valeurs de départ, notamment pour les faisceaux avec
une distribution aléatoire.

### Question 13.1
> Quelle est la complexité de ces deux algorithmes ? (algorithmes d'application des forces interparticules où les
    particules dans un faisceau interagissent toutes entre elles.)

Avec n particules dans un faisceau, cela demande une complexité en O(n²) pour chaque faisceau. En effet, on applique
toutes les forces, on a donc ((n - 1)² + n - 1) / 2 interactions. Le fait de parcourir la liste des
particules d'un faisceau est en O(n), cela ne change par conséquent pas la complexité.

### Question 14.1
> quelle est la complexité temporelle pire cas de cette solution en fonction du nombre de particules ? Quelles
    inconvénients présentent cette solution ? (En ce qui concerne la gestion proposée des meilleurs voisins)

Soit n le nombre de particules. Comme l'on suppose que le nombre de particules par case
est en O(1), les forces à appliquer sur chaque particules sont également en O(1). De plus, le nombre de
cases ne dépend pas du nombre de particules, il est en O(1). Parcourir la liste des cases est
par conséquent en O(1). On a finalement une complexité en O(n * O(1) + O(1)) = O(n).

Le principal inconvénient de cette méthode est qu'il utilise énormément de mémoire : il y a de de 10⁵ à 10⁶ cases
dans le modèle proposé, alors qu'on ne simule que quelques dizaines, voire quelques centaines de particules. La
grande majorité des cases sont donc vides.

### Question 14.2
> Comment et où avez-vous implémenté cette nouvelle façon de calculer les interactions entre particules ?

Pour éviter d'utiliser beaucoup de mémoire inutilement, mais en gardant une complexité en O(n), nous avons
décidé de faire une liste doublement chaînée circulaire de particules, dans l'ordre de leurs positions
longitudinales. Nous faisons intéragir chaque particule avec les suivantes dans la liste, jusqu'à ce que la suivante
soit plus loin qu'une certaine distance maximale, et à ce moment-là nous passons à la suivante.
À chaque pas, nous contrôlons que l'ordre est correct. Un pointeur vers la tête de la liste chaînée est contenu
dans l'accélérateur et celui-ci gère la liste. Nous expliquons plus longuement son fonctionnement
dans le fichier CONCEPTION.