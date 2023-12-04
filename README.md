# INF304 Curiosity

> Mathias Rivet, Léo Grange

## TP 7 - Écriture des tests

Il y a 4 tests, qui révèlent des erreurs d'implémentation dans les interprètes 4 et 5.

Les tests utilisent des terrains correctes de tailles différentes ainsi que des programmes plus ou moins complexes. Le but étant de deseler des bugs dans l'interprétation de programmes complexes.

## TP 8 - Programme-robots

## TP 9 - Observateur

On veut vérifier si les actions gauche et avancer sont précédées par l'action mesurer.

```
/---A,D,G------------------------------------A,D,G-\
|         |       /-----M-\                        |
|  +---------+    |  +----------+---A,G-->+---------------+
|->|EtatAutre|-M---->|EtatMesure|         |EtatApresMesure|
|  +---------+       +----------+<----M---+---------------+
|                         |
\---------------------D---/
```

$Observateur = (Q, q_{init}, \Sigma, \delta, F)$

$(EtatAutre, EtatMesure, EtatApresMesure) \in Q³$

$q_{init} = EtatAutre$

$(A, G, D, M) \in \Sigma⁴$

$EtatApresMesure \in F$
