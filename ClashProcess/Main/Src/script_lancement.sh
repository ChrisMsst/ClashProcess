#!/bin/bash

for file in {1..10}
 do
  touch $file
  echo "Fichier $file créé"
 done

gcc Equipe.c -o E
gcc Fils.c -o F
gcc Pere.c -o P

./E