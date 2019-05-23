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
 Diego et Gabin commençaient leur grand voyage à travers le
 deuxième semestre, voyage qui se terminerait dans la folie
 et la souffrance.



### Semaine 4
Cette semaine on a fait la classe `Particle`, en ayant un peu de mal à comprendre ce que l'on devait faire,
 notement
 - pour la vitesse (on ne comprennait pas pourquoi il ne fallait pas la stocker)
 - pour l'ajout de force magnetique... Si l'energie ne change pas, pourquoi fait-on un *accélerateur* de particules ?
On a ensuite commencé la hierarchie des `Elements` et  petit à petit leur implementation, mais il n'est pas facile de voir comment tout va s'agencer.
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
On implémente différentes classes d'éléments, ainsi que le polymorphisme.
Les méthodes collideBorder et isOut fonctionnent bien.

##### Humeur
 « En fait c'est facile la programmation ! » se disaient-ils, ne sachant
 pas les nuits sans lune qui les attendaient.


### Semaine 6
Le projet prend de plus en plus forme, ce qui est motivant.
On implémente la classe accelerator, on peut donc tester
notre premier vrai circuit. On peut le tester graphiquement, c'est
émouvant.
##### Humeur
 Unités, oh ! unités, où êtes-vous passées ?


### Semaine 7
Début des faisceaux, ce qui demande de nouvelles méthodes complexes
pour calculer des positions radiales à partir des positions absolues
des particules.
##### Humeur
 De jour comme de nuit, nous ruminions dans notre tête cet unique
 mot : émittance, émittance, émittance. Ce frottement continu
 arrachait peu à peu notre chair jusqu'à mettre à sang notre esprit.


### Semaine 8
Finalement, les méthodes de conversion du repère cartésien au repère radial
n'étaient pas si compliquées. Les faisceaux circulaires fonctionnent
parfaitement grâce à ça.

##### Humeur
 « Mes faisceaux circulaires ont fonctionné du premier coup. » Gabin, 2019.


### Semaine 9
 On travaille sur la simulation P10. Nos particules, pour on ne sait quelle raison,
 se décalent progressivement des données de l'exemple. Les forces sont pourtant tout à
 fait correctes au départ, on ne comprend donc pas la raison de ce décalage progressif.
 De plus, nos particules sont instables et heurtent rapidement les bords. On a changé
 le système d'unités pour être plus proche de celui de référence, mais cela n'aide pas.
##### Humeur
 Nous sommes désabusés.


### Semaine 10
 Après beaucoup d'heures de recherches, notre accélérateur fonctionne enfin !
 Nous utilisions une méthode différente pour décider quand une particule
 passait d'un élément à un autre. Les deux méthodes sont très similaires,
 et pourtant ces petites différences rendent l'accélérateur instable.
##### Humeur
 Qui aurait cru que quelques boules de couleur avaient le pouvoir de redonner
 le goût de la vie ?


### Semaine 11
  Nous avons ajouté les sextupôles, les mailles FODO, et les particules peuvent
  maintenant aller dans les deux sens.
  Par contre, nous n'avons aucune idée de comment utiliser les sextupôles.
  Diego a bien travaillé la version graphique, qui a maintenant une valeur estimée
  à beaucoup trop de nuits blanches.

##### Humeur
 Les sextupôles, comme les femmes, restent bien mystérieux.


### Semaine 12
 Pour la gestion des interactions interparticules, nous avons décidé
 de mettre en place une liste doublement chaînée circulaire. Cela
 nous permettra d'avoir une complexité en O(n) et d'économiser de
 la mémoire.
 C'est fait. Ça a été plus facile que ce à quoi on s'attendait.
 Cepedant, les forces interparticules sont si faibles que la
 différence est indétectable.

##### Humeur
 En vrai on a juste fait ça parce que c'est trop classe de dire :
 « Ouais moi j'ai mis en place une LDCC, c'était clairement un must.
 Quoi, tu sais pas ce que c'est une LDCC ? Trop la loose quoi. »
 


### Semaine 13
 On finalise le projet, en corrigeant quelques maladresses de code,
 Diego rajoute quelques détails graphiques, on complète les fichiers
 JOURNAL, CONCEPTION, README et on rend le projet.
 
##### Humeur
 Dans un mauvais film, quelqu'un dirait que ce n'est pas une fin mais
 un commencement. Il aurait tort. Ce projet est terminé, et plus
 jamais je ne ferai d'accélérateur de particules. La seule chose
 qui a de la valeur dans ce monde veule et laid, ce sont les
 mathématiques pures, forêt vierge imaginaire et infinie. Si vous
 me cherchez, je suis probablement quelque part là-dedans, en train
 de siroter un théorème fondamental des polynômes symétriques, ou
 de faire des brasses dans le lac du théorème de compacité. ~ Gabin
 
 C'était quand même cool. ~ Diego


### Semaine 14
 Fin