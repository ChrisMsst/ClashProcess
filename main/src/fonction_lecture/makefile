test: creation_fichier_fils.o fonction_read.o creation_fichier_fils2.o fonction_read2.o
	gcc creation_fichier_fils.o fonction_read.o -o test
	gcc creation_fichier_fils2.o fonction_read2.o -o test2


creation_fichier_fils.o: creation_fichier_fils.c
	gcc -c creation_fichier_fils.c -Wall

fonction_read.o: fonction_read.c
	gcc -c fonction_read.c -Wall


creation_fichier_fils2.o: creation_fichier_fils2.c
	gcc -c creation_fichier_fils2.c -Wall

fonction_read2.o: fonction_read2.c
	gcc -c fonction_read2.c -Wall



clean: ###pour le lancer il faut faire make clear###
	rm test
	rm *.o
	rm *.dat

