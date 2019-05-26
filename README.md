# Particle Accelerator
Par Gabin Kolly et Diego Dorn, 2019.

Ceci est notre projet de Programmation II à l'epfl. Il permet de simuler un accélérateur de particules,
constitué de bipôles, quadrupôles, sextupôles et de segments droits.

# Compilation :
Pour compiler, il faut avoir C++17 et QT installés. Il faut ensuite exécuter les commandes qmake, puis make.

# Fonctionnement :
L'accélérateur est constitué d'éléments, comme les dipôles. Il contient des faisceaux (ou beams), qui
permettent d'injecter les particules dans l'accélérateur, et de suivre différents paramètres, comme l'émittance.
Chaque faisceau possède une particule de référence, qui indique les caractéristiques moyennes des particules.
Ensuite, on fait avancer le système par petit pas de temps. On peut choisir entre un affichage texte et
un affichage graphique.

# Utilisation :
Tout d'abord, il faut créer une instance d'accélérateur (class accelerator). On ajoute ensuite les éléments
les uns après les autres, et enfin on ajoute des faisceaux (beams). On peut ensuite faire évoluer le système
pas à pas. L'accélérateur doit être approximativement circulaire, centré à l'origine, et être contenu dans
le plan xy.

# Exemple :

 Le fichier testModele, dans le dossier text, est un exemple de simulation texte. L'accélérateur est
 constitué de quatre mailles FODO (avec sextupôles après les quadrupôles) reliées ensemble par des dipôles.

# Problèmes et défauts :
 Ce projet possède deux principaux problèmes. Le premier est que le générateur de hasard utilisé lors de la
 création des particules n'est pas réaliste, et ne permet pas simuler les distributions réelles des
 particules dans un accélérateur. Il n'a qu'un intérêt esthétique. Le second est une incohérence
 entre le repère radial utilisé pour le calcul des forces et de l'émittance, qui correspond à ce que
 l'on voit lors de l'affichage graphique, et la façon dont on détermine le passage d'un élément à un
 autre. Dans ce dernier cas, on suppose en effet que les éléments ont des bords qui pointent vers
 l'origine du repère cartésien. Cela cause des discontinuités lors de l'affichage de la vitesse
 radiale, en mode graphique.

# Améliorations possibles :
 Les améliorations possibles sont la mise en place d'une vraie simulation des distributions des particules,
 ainsi que l'ajout d'éléments appliquant des forces électriques, afin de réellement accélérer les particules.