# CMKV

## Utilisation
```make
./a.out <input file> <output file>
```

## Test
### Utilisation
- ```./test_given``` lance les test données
- ```./test {n}``` lance les test de  taille n, où n est la taille de la grille
- ```./test_all``` lance tous les tests

### Préparation
```cd test
g++ test.cc
./prepare_test.sh <taille de la grille> <fichier>
```