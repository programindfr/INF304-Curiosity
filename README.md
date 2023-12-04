# INF304 Curiosity
> Mathias Rivet, Léo Grange

## TP 7 - Écriture des tests

## TP 8 - Programme-robots

## TP 9 - Observateur

On veut vérifier si les actions gauche et avancer sont précédées par l'action mesurer.

```
/--A,D,G------------------------------------A,D,G-\
|         |       /-----M-\                       |
|  +---------+    |  +----------+--A,G-->+---------------+
|->|EtatAutre|-M---->|EtatMesure|        |EtatApresMesure|
|  +---------+       +----------+<---M---+---------------+
|                         |
\---------------------D---/
```
