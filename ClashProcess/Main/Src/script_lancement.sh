#!/bin/bash

nbrEquipe=$(zenity --entry --title="Préparation du jeu" --text="Combien d'équipes vont se confronter?!")

nbrFichier=$((6*$nbrEquipe))

for ((fichier=1; fichier<=nbrFichier; fichier++ ))
do  
	touch $fichier.dat
done

echo "Nous venons donc de créer "$nbrFichier" fichiers et nous avons "$nbrEquipe" équipes!"

gcc Fils.c -o F
gcc Pere.c -o P

for((equipe=0; equipe<nbrEquipe; equipe++))
do
	gcc Equipe.c -o E
	./E
done