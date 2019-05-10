# Journal du projet

### Repartition des taches
Tout au long du projet nous nous sommes répartis les taches sur la base de la motivation,
si l'un de nous deux veut faire quelque chose, il le dit à l'autre et le fait. Comme on
communique beaucoup et qu'on est tous les deux motivé cela a bien marché, avec l'effet positif
que l'on travaille uniquement sur des choses qui nous font envie (et donc mieux).

### Semaine 2

 - Creation de la structure et des principaux fichiers du projet
 - Creation de la classe Vector3D et du fichier test_vector3D, on
	a déjà fait les opérateurs (note de relecture: mal)
##### Humeur
*Diego*: En fait c'est sympa le `c++`, j'apprécie la structure et le fait que tu saches
mieux (qu'en python) ce que ton code fait, au niveau des types par exemple et la
grande verbosité du code.


### Semaine 3
 - Amelioration de la classe Vector3D, avec une meilleure implementation des operateurs
 - Ajout de la methode de rotation d'un vecteur
 - Debut de familiarisation avec l'environnement graphique

##### Humeur

### Semaine 4
Cette semaine on a fait la classe `Particle`, en ayant un peu de mal à comprendre ce que l'on devait faire,
 notement
 - pour la vitesse (on ne comprennait pas pourquoi il ne fallait pas la stocker)
 - pour l'ajout de force magnetique... Si l'energie ne change pas, pourquoi fait-on un *accélerateur* de particules ?
On a ensuite commencé la hierarchie des `Elements` et  petit à petit leur implementation, mais il n'est pas facile
de voir comment tout va s'agencer.
Mais tous ces problèmes ont été résolus et on à commencé à faire
l'interface texte et graphique pour avoir un rendu joli et motivant.

##### Humeur

*Diego*: J'ai commencé à faire des tests avec qt et opengl, faire des jolies
couleurs, implementer de la lumiere (diffuse + refraction) c'etait sympa et
j'ai appris pas mal de choses, mais j'ai toujours absolument aucune idee des
raison pour lesquelles le code qui dessine une sphere marche... Comme dirait
je-sais-plus-qui,
> Toute technologie suffisament avancée ne peut être distingue de la magie
Et clairement, ici, c'est de la magie.


### Semaine 5
 - Semaine de vide
 -
##### Humeur



### Semaine 6
On implémente différentes classes d'éléments, ainsi que le polymorphisme.
Le projet prend de plus en plus forme, ce qui est motivant.
On implémente la classe accelerator, on peut donc tester
notre premier vrai circuit. On peut le tester graphiquement, c'est
émouvant.
##### Humeur
C'est un peu pénible que les exemples donnés de test n'aient pas
des unités bien indiquées


### Semaine 7
Début des faisceaux, ce qui demande de nouvelles méthodes complexes
pour calculer des positions radiales à partir des positions absolues
des particules.
##### Humeur
La partie sur le calcul de l'émittance est difficile à comprendre,
c'est assez pénible


### Semaine 8
Semaine de vide

##### Humeur



### Semaine 9
 Les méthodes permettant de passer d'un repère cartésien à un repère radial marchent bien
 Les faisceaux circulaires fonctionnent parfaitement grâce à ça
##### Humeur


### Semaine 10
 On travaille sur la simulation P10. Nos particules, pour on ne sait quelle raison,
 se décalent progressivement des données de l'exemple. Les forces sont pourtant tout à
 fait correctes au départ, on ne comprend donc pas la raison de ce décalage progressif.
 De plus, nos particules sont instables et heurtent rapidement les bords. On a changé
 le système d'unités pour être plus proche de celui de référence, mais cela n'aide pas.

##### Humeur



### Semaine 11
  Le problème a été résolu, l'accélérateur fonctionne maintenant parfaitement.
  Nous avons ajouté les sextupôles, les mailles FODO, et les particules peuvent
  maintenant aller dans les deux sens. Nous avons décidé de mettre en place une
  gestion des interactions interparticules à l'aide d'une liste doublement chaînée
  circulaire, afin d'économiser l'utilisation de mémoire inutile.

##### Humeur



### Semaine 12
 -
 -
##### Humeur



### Semaine 13
 -
 -
##### Humeur



### Semaine 14
 -
 -
##### Humeur


