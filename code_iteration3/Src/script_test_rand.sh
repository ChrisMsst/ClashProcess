#!/bin/bash

nbrEquipe=$(zenity --entry --title="Préparation du jeu" --text="Combien d'équipes vont se confronter?!")

gcc Random.c -o R

for((equipe=0; equipe<nbrEquipe; equipe++))
do
	./R & 
	sleep 2
done
