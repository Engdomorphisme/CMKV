# CMKV

## Utilisation

```shell
make
./a.out <input file> <output file>
```

## Test

### Utilisation

- ```./test_given.sh``` lance les test données
- ```./test.sh {n}``` lance les test de taille n, où n est la taille de la grille
- ```./test_all.sh``` lance tous les tests

### Préparation

Permet de préparer des tests automatiquement.
```shell
cd test
g++ create_test.cc
./prepare_test.sh <taille de la grille> <fichier>
```

## Groupe

- Enguerrand de Gentile Duquesne
- Youenn Loie
- Guillaume Larue
- Nicolas Trabet
