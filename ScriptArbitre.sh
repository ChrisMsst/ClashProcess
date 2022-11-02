#!/bin/bash

nbrEquipe=$(zenity --entry --title="Préparation du jeu" --text="Combien d'équipes vont se confronter?!")

nbrFichier=$((6*$nbrEquipe))

for ((fichier=1; fichier<=nbrFichier; fichier++ ))
do  
	touch $fichier.dat
done

#for((equipe=0; equipe<nbrEquipe; equipe++))
#do
#	gcc Recherche.c -o Recherche
#	./Recherche
#done

echo "Nous venons donc de créer "$nbrFichier" fichiers et nous avons "$nbrEquipe" équipes!"