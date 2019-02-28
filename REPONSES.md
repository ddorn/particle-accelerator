# Réponses

### Question P1.1 

>> Comment représentez vous ces vecteurs ? Comment sont-ils organisés : quels attributs ? quelles méthodes ? quels droits d'accès ?

Nous représentons ces vecteurs avec trois coordonnées séparées, en utilisant un `typedef` pour pouvoir changer le type 
si besoin plus facilement. Nous avons choisis d'avoir trois coordoonées séparées plutot qu'un `array` de 3 éléments
 pour avoir une meilleure lisibilité.
 Nous avons donc trois attributs privés `x_, y_, z_`, avec des methodes get publiques pour les lire
ainsi que d'autres methodes, publiques, pour faire toutes sortes d'opérations communes (additions, calculer la norme...).

