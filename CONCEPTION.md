Toutes les classes héritant de la classe `Content` sont des choses affichables.
La classe `Support` sert à afficher les `Content`. Elle a deux sous-classes,
`TextSupport`, qui permet d'afficher en mode texte, et `QtSupport`,
qui permet l'affichage graphique. Chaque instance de `Content` possède une méthode
`draw`, et l'instance `Support` voulue doit être donnée en argument. Cela permet, si
on le souhaite, d'utiliser à la fois un affichage texte et un affichage graphique.

L'accélérateur contient une liste chaînée dont chaque node possède un pointeur vers
le node suivant et vers le node précédent, ainsi qu'un `shared_ptr` vers une particule.
L'accélérateur possède également une liste de `unique_ptr` vers des éléments, ainsi qu'une
liste de `unique_ptr` vers des faisceaux. Utiliser des listes de pointeurs permet de faire
du polymorphisme.
Lors de la création de l'accélérateur, celui-ci est encore vide. Il est nécessaire par la suite d'appeler les méthodes `addElement`, pour ajouter les éléments, et `addBeam`, pour les faisceaux.
Les faisceaux contiennent une liste de `shared_ptr` vers les particules
qu'ils ont créées.

Les particules n'appartiennent à personne. Elles existent indépendamment de l'accélérateur
et des faisceaux. Nous avons fait ce choix car les particules doivent être accessibles par
l'accélérateur et par les faisceaux, même si elles n'existent plus pour l'uns ou l'autre. 
Lors de la création d'un faisceau, l'accélérateur appelle la méthode `generateParticles` 
du faisceau, en se mettant en argument. Le faisceau appelle alors la méthode `addParticle` de l'accélérateur, à chaque création de particule.

En mode graphique, la classe `GlWidget` gère l'affichage de la fenêtre et le déroulement
du programme. Elle contient l'accélérateur en attribut. L'accélérateur peut être créé avant
puis mis en argument à la création de l'instance de `GlWidget` même s'il ne peut pas être copié, car l'instance est passée par std::move.
