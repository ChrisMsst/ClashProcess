#!/bin/bash

rm *.dat
rm E P F

nbrEquipe=$(zenity --scale --text="Combien d'équipes voulez-vous?" --value=2 --min-value=2 --max-value=10)

nbrFichier=$((6*$nbrEquipe))

for ((fichier=1; fichier<=nbrFichier; fichier++ ))
do  
	touch $fichier.dat
done

# for ((fichier=1; fichier<=2; fichier++ ))
# do  
# 	touch PERE$fichier.dat
# done

echo "Nous venons donc de créer "$nbrFichier" fichiers et nous avons "$nbrEquipe" équipes!"

gcc Fils.c -o F
gcc Pere.c -o P
gcc Equipe.c -o E


for((equipe=0; equipe<nbrEquipe; equipe++))
do
	./E $nbrEquipe &
	echo "Equipe n°$equipe" 
	sleep 0.5
done
