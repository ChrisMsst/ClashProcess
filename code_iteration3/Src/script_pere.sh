#!/bin/bash

rm PERE1.dat
rm PERE2.dat

nbrEquipe=$(zenity --entry --title="Préparation du jeu" --text="Combien d'équipes vont se confronter?!")

for ((fichier=1; fichier<=2; fichier++ ))
do  
	touch PERE$fichier.dat
done

gcc Lect_PID_pere.c -o L

for((equipe=0; equipe<nbrEquipe; equipe++))
do
	./L & 
done
