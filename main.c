#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX 30

enum meuble { MEUBLE, N_MEUBLE}; // Differentes valeur possible de l'enumeration, il va donner en interne un valeur
enum fumeur { FUMEUR, N_FUMEUR};
enum clim { CLIM, N_CLIM};
enum piscine { PISCINE, N_PISCINE};
enum dispo { DISPO, N_DISPO};

#define MEUBLE 1
#define N_MEUBLE 2

#define FUMEUR 1
#define N_FUMEUR 2

#define CLIM 1
#define N_CLIM 2

#define PISCINE 1
#define N_PISCINE 2

#define DISPO 1
#define N_DISPO 2

typedef struct appartement{
    char nom[MAX];
    char ville[MAX];
    int surface;
    int prix;
    int meuble;
    int fumeur;
    int clim;
    int piscine;
    int dispo;
    char locataire[MAX];
}appartement;

typedef struct compte{
    char nom[MAX];
    char prenom[MAX];
    int tel;
    char mail[MAX];
    char mdp[MAX];
}compte;


void menu();                                        // Lancement du menu
void sous_menu_admin();                              // Lancement du menu pour admin
void sous_menu_client(compte pcompteactif);                             // Lancement du menu pour admin
void creer_compte(FILE * pfichier);                 // Creation compte
int connexion(FILE * pfichier, compte pcompte_actif);            //Fonction qui verifie si pcompte_actif est present dans une bdd
void afficher_clients(FILE * pfichier);             //Affichage de tous les clients
void recherche_clients(FILE * pfichier);         //Recherche d'un client en fonction du critere choisi
void ajouter_apparts(FILE * pfichier);          //Ajouter un appartement
void afficher_apparts(FILE * pfichier);          //Afficher tous les appartements
void recherche_apparts(FILE * pfichier);            //Recherche d'un appartement en fonction du critere choisi
void modif_apparts();            //Modification de l'etat d'un appartement
void supprimer_apparts();           //Suppression d'un appartement
void modif_comptes(compte pcomtpe_actif);           // Modification d'un compte
void reservation(compte pcompte_actif);         //Reservation d'un appartement




int main()
{
    printf("Bienvenue sur le site de location d'appartement : MAGASHELTER !!!\n\n\n                    ====\n                    !!!!\n                    !!!!\n     ============================\n    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n   ||     _____          _____    ||\n   ||     | | |          | | |    ||\n   ||     |-|-|          |-|-|    ||\n   ||     #####          #####    ||\n   ||                             ||\n   ||      _____  ____   _____    ||\n   ||      | | |  @@@@   | | |    ||\n   ||      |-|-|  @@@@   |-|-|    ||\n   ||      #####  @@*@   #####    ||\n   ||             @@@@            ||\n******************____*****************\n***************************************\n");

    menu();
    return 0;
}

void menu()
{
    compte compte_actif;        //Le compte qui sera connecte


    int input = 0;      //La variable qui sera modifie par l'utilisateur
    while ((input != 1) && (input !=2) && (input !=3))
    {
        connexion:
        printf("\nSouhaitez-vous:\n\n1. Vous connecter \n2. Creer un compte \n3. Quitter le programme\n\n");
        scanf("%d", &input);            //Soit il se créer un compte, soit il se connecte
        while(getchar() != '\n'){};

        switch(input)
        {
            case 1 :
            {
                printf("Veuillez rentrer votre adresse mail: ");
                gets(compte_actif.mail);        //L'utilisateur rentre son mail

                printf("Veuillez rentrer votre mot de passe: ");
                gets(compte_actif.mdp);         //L'utilisateur rentre son mot de passe
                FILE * fichier;
                fichier = fopen("comptes_admin.dat","rb");          //Ouverture de la bdd admin dans un premier temps
                if(fichier == NULL)
                {
                    printf("ERREUR");
                    exit(1);
                }

                int verification = connexion(fichier,compte_actif);

                fclose(fichier);

                if(verification==1)
                {
                    printf("vous etes connecte avec un compte administrateur !\n\n");
                    verification=2;
                    sous_menu_admin();
                    goto connexion;
                }
                else if(verification==0)
                {
                    FILE * fichier;
                    fichier = fopen("comptes_client.dat","rb");         //Si on ne trouve rien dans la bdd admin on cherche dans la bdd client
                    if(fichier == NULL)
                    {
                        printf("ERREUR");
                        exit(1);
                    }
                    int verification = connexion(fichier,compte_actif);
                    if(verification==1)
                    {
                        printf("vous etes connecte avec un compte client !\n\n");
                        sous_menu_client(compte_actif);
                        verification=2;
                        goto connexion;
                    }

                    else if(verification!=2)            //Si on ne trouve rien ni dans la bdd admin ni dans la bdd client
                    {
                        printf("\nVeuillez verifier vos identifiants ou vous creer un compte!\n\n");
                        goto connexion;
                    }
                }
            }
            break;

            case 2 :
            {
                FILE * fichier;
                fichier = fopen("comptes_client.dat","ab+");            //Creation d'un compte client
                if(fichier == NULL)
                {
                    printf("ERREUR");
                    exit(1);
                }

                creer_compte(fichier);
                printf("Felicitations, nous pouvons a present vous compter parmi nos heureux membres de MAGASHELTER !\n\nVous pouvez maintenant vous connecter!\n\n");
                fclose(fichier);

                goto connexion;
            }
            break;

            case 3 :
            {
                   exit(1);
            }
            break;

            default:
            {
                printf("HIN HIN vous ne m'aurez pas, veuillez selectionner 1 ou 2\n");          //Si l'utilisateur ne respecte pas les règles
            }
            break;
        }
    }
}

void creer_compte(FILE * pfichier)
{
    compte texte, saisie;

    printf("Nom: ");
	gets(saisie.nom);

	printf("Prenom: ");
	gets(saisie.prenom);

	printf("Numero de telephone: ");
	scanf("%d", &saisie.tel);
	while(getchar() != '\n'){};

    mail:
	printf("Adresse mail: ");
	gets(saisie.mail);
	while(fread(&texte,sizeof(compte),1,pfichier) == 1)         // Si l'adresse mail existe deja l'utilisateur doit en prendre une autre
    {
        if((strcmp(texte.mail,saisie.mail)==0))
        {
            printf("\nVotre mail: %s existe deja dans notre base de donnee, veuillez ecrire une autre adresse mail\n\n", saisie.mail);
            goto mail;
        }
    }

	printf("Mot de passe: ");
	gets(saisie.mdp);

	fwrite(&saisie,sizeof(compte),1,pfichier);
}

int connexion(FILE * pfichier, compte pcompte_actif)
{
    compte texte;
    int cpt=0;          //Variable utilise pour savoir si le compte existe ou pas, s'il existe la variable prendra la valeur 1 sinon 0
    while(fread(&texte,sizeof(compte),1,pfichier) == 1)
    {
        if((strcmp(texte.mail,pcompte_actif.mail)==0) && (strcmp(texte.mdp,pcompte_actif.mdp)==0))          //Si un compte est trouve
        {
            printf("\nBienvenue %s %s ", texte.nom, texte.prenom);
            cpt=1;
        }
    }

    return cpt;         //La fonction connexion prend la valeur cpt
}

void sous_menu_admin()
{
    int input = 0;
    while ((input != 1) && (input !=2)&& (input !=3) && (input !=4) && (input !=5) && (input !=6) && (input !=7) && (input !=8) && (input !=9))
    {
        menuAdmin:
        printf("1. Afficher tous les clients \n2. Rechercher un client \n3. Ajouter un appartement \n4. Afficher tous les appartemments \n5. Rechercher un appartement \n6. Modifier un appartement \n7. Supprimer un appartement\n8. Creer un compte admin\n9. Deconnexion\n\n");
        scanf("%d", &input);
        while(getchar() != '\n'){};

        switch(input)
        {
            case 1 :
            {
                FILE * fichier;
                fichier = fopen("comptes_client.dat","rb");
                if(fichier == NULL)
                {
                    printf("ERREUR");
                    exit(1);
                }

                afficher_clients(fichier);

                fclose(fichier);
                goto menuAdmin;
            }
            break;

            case 2 :
            {
                FILE * fichier;
                fichier = fopen("comptes_client.dat","rb");
                if(fichier == NULL)
                {
                    printf("ERREUR");
                    exit(1);
                }

                recherche_clients(fichier);

                fclose(fichier);
                goto menuAdmin;
            }
            break;

            case 3 :
            {
                FILE * fichier;
                fichier = fopen("appartements.dat","ab+");
                if(fichier == NULL)
                {
                    printf("ERREUR");
                    exit(1);
                }

                ajouter_apparts(fichier);

                fclose(fichier);
                goto menuAdmin;
            }
            break;

            case 4 :
            {
                FILE * fichier;
                fichier = fopen("appartements.dat","rb");
                if(fichier == NULL)
                {
                    printf("ERREUR");
                    exit(1);
                }

                afficher_apparts(fichier);

                fclose(fichier);
                goto menuAdmin;
            }
            break;

            case 5 :
            {
                FILE * fichier;
                fichier = fopen("appartements.dat","rb");
                if(fichier == NULL)
                {
                    printf("ERREUR");
                    exit(1);
                }

                recherche_apparts(fichier);

                fclose(fichier);
                goto menuAdmin;
            }
            break;

            case 6 :
            {
                modif_apparts();
                goto menuAdmin;
            }
            break;

            case 7 :
            {
                supprimer_apparts();
                goto menuAdmin;
            }
            break;

            case 8 :
            {
                FILE * fichier;
                fichier = fopen("comptes_admin.dat","ab+");
                if(fichier == NULL)
                {
                    printf("ERREUR");
                    exit(1);
                }

                creer_compte(fichier);

                fclose(fichier);
                goto menuAdmin;
            }
            break;

            case 9 :

            break;

            default :
                printf("HIN HIN vous ne m'aurez pas, veuillez selectionner un numero dans le menu :P\n\n");
            break;
        }
    }
}

void sous_menu_client(compte pcompte_actif)
{
    int input = 0;
    while ((input != 1) && (input !=2) && (input !=3) && (input !=4))
    {
        menuClient:
        printf("1. Modifier mon compte \n2. Rechercher un appartement \n3. Reserver un appartement\n4. Deconnexion\n\n");
        scanf("%d", &input);
        while(getchar() != '\n'){};

        switch(input)
        {
            case 1 :
            {
                modif_comptes(pcompte_actif);
                goto menuClient;
            }
            break;

            case 2 :
            {
                FILE * fichier;
                fichier = fopen("appartements.dat","rb");
                if(fichier == NULL)
                {
                    printf("ERREUR");
                    exit(1);
                }

                recherche_apparts(fichier);
                fclose(fichier);
                goto menuClient;
            }
            break;

            case 3 :
            {
                reservation(pcompte_actif);
                goto menuClient;
            }
            break;

            case 4 :
            {

            }
            break;

            default:
            {
                printf("HIN HIN vous ne m'aurez pas, veuillez selectionner 1, 2, 3 ou 4\n");
            }
            break;
        }
    }
}

void afficher_clients(FILE * pfichier)
{
    compte texte;

	while(fread(&texte,sizeof(compte),1,pfichier) == 1)
    {
        printf("%s %s %d %s %s\n", texte.nom, texte.prenom, texte.tel, texte.mail, texte.mdp);
    }
    printf("\n\n");
}

void recherche_clients(FILE * pfichier)
{
    int choix = 0, cpt = 0;
    compte recherche;
    compte texte;

    while ((choix != 1) && (choix !=2) && (choix !=3) && (choix !=4) && (choix !=5))
    {
        rechercheClient:
        printf("\nSelon quel critere souhaitez-vous rechercher le client?\n\n1. Nom\n2. Prenom\n3. Numero de telephone\n4. Adresse mail\n5. Retour au menu\n\n");

        scanf("%d", &choix);
        while(getchar() != '\n'){};

        switch(choix)
        {
            case 1 :
            {
                printf("\nQuel est le nom que vous recherchez?\n\nNom: ");
                gets(recherche.nom);

                while(fread(&texte,sizeof(compte),1,pfichier) == 1)
                {
                    if(strcmp(texte.nom,recherche.nom)==0)
                    {
                        printf("%s  %s  %d  %s %s\n", texte.nom, texte.prenom, texte.tel, texte.mail, texte.mdp);
                        cpt++;
                    }
                }

                if(cpt==0)
                {
                    printf("\nDesole nous n'avons pas pu trouve ce nom !\n");
                    goto rechercheClient;
                }
            }
            break;

            case 2 :
            {
                printf("\nQuel est le prenom que vous recherchez?\n\nPrenom: ");
                gets(recherche.prenom);

                while(fread(&texte,sizeof(compte),1,pfichier) == 1)
                {
                    if(strcmp(texte.prenom,recherche.prenom)==0)
                    {
                        printf("%s  %s  %d  %s %s\n", texte.nom, texte.prenom, texte.tel, texte.mail, texte.mdp);
                        cpt++;
                    }

                    if(cpt==0)
                    {
                        printf("\nDesole nous n'avons pas pu trouve ce prenom !\n");
                        goto rechercheClient;
                    }
                }
            }
            break;

            case 3 :
            {
                printf("\nQuel est le numero de telephone que vous recherchez?\n\nNumero de telephone: ");
                scanf("%d", &recherche.tel);
                while(getchar() != '\n'){};

                while(fread(&texte,sizeof(compte),1,pfichier) == 1)
                {
                    if(recherche.tel==texte.tel)
                    {
                        printf("%s  %s  %d  %s %s\n\n", texte.nom, texte.prenom, texte.tel, texte.mail, texte.mdp);
                        cpt++;
                    }

                    if(cpt==0)
                    {
                        printf("\nDesole nous n'avons pas pu trouve ce numero de telephone !\n");
                        goto rechercheClient;
                    }
                }
            }
            break;

            case 4 :
            {
                printf("\nQuel est l'adresse mail que vous recherchez?\n\nAdresse mail: ");
                gets(recherche.mail);

                while(fread(&texte,sizeof(compte),1,pfichier) == 1)
                {
                    if(strcmp(texte.mail,recherche.mail)==0)
                    {
                        printf("%s  %s  %d  %s %s\n\n", texte.nom, texte.prenom, texte.tel, texte.mail, texte.mdp);
                        cpt++;
                    }
                    if(cpt==0)
                    {
                        printf("\nDesole nous n'avons pas pu trouve cet adresse mail !\n");
                        goto rechercheClient;
                    }
                }
            }
            break;

            case 5 :
            {

            }
            break;

            default :
                printf("HIN HIN vous ne m'aurez pas, veuillez selectionner 1 ou 2 ou 3 ou 4!!!\n");
            break;
        }
    }
}

void ajouter_apparts(FILE * pfichier)
{
    appartement texte, verif;
    int choix = 0;

    printf("Nom: ");
	gets(texte.nom);

	while(fread(&verif,sizeof(appartement),1,pfichier) == 1)
    {
        if(strcmp(texte.nom,verif.nom)==0)
        {
            printf("Cet appartement existe deja : %s %s %d %d %d %d %d %d %d\n", verif.nom, verif.ville, verif.surface, verif.prix, verif.meuble, verif.fumeur, verif.clim, verif.piscine, verif.dispo);
            choix=2;
            goto ajoutAppart;
        }
    }

    printf("Ville: ");
	gets(texte.ville);

    printf("Surface: ");
	scanf("%d", &texte.surface);
	while(getchar() != '\n'){};

	printf("Prix: ");
	scanf("%d", &texte.prix);
	while(getchar() != '\n'){};

	printf("Meuble?\n\n1. Oui\n2. Non\n\n");
	scanf("%d", &texte.meuble);
	while(getchar() != '\n'){};

	printf("Fumeur?\n\n1. Oui\n2. Non\n\n");
	scanf("%d", &texte.fumeur);
	while(getchar() != '\n'){};

	printf("Climatisation?\n\n1. Oui\n2. Non\n\n");
	scanf("%d", &texte.clim);
	while(getchar() != '\n'){};

	printf("Piscine?\n\n1. Oui\n2. Non\n\n");
	scanf("%d", &texte.piscine);
	while(getchar() != '\n'){};

	printf("Dispo?\n\n1. Oui\n2. Non\n\n");
	scanf("%d", &texte.dispo);
	while(getchar() != '\n'){};

	printf("Locataire: ");
	gets(texte.locataire);

    while ((choix != 1) && (choix !=2))
    {
        printf("Confirmez vous la creation de cet appartement?:");

        printf("|%s| |%s| |%dm2| |%deuros|", texte.nom, texte.ville, texte.surface, texte.prix);

        if(texte.meuble==1)
        {
            printf("|meuble|");
        }
        else if(texte.meuble==2)
        {
            printf("|non meuble|");
        }

        if(texte.fumeur==1)
        {
            printf("|fumeur|");
        }
        else if(texte.fumeur==2)
        {
            printf("|non fumeur|");
        }

        if(texte.clim==1)
        {
            printf("|climatise|");
        }
        else if(texte.clim==2)
        {
            printf("|non climatise|");
        }

        if(texte.piscine==1)
        {
            printf("|piscine dispo|");
        }
        else if(texte.piscine==2)
        {
            printf("|piscine non dispo|");
        }

        if(texte.dispo==1)
        {
            printf("|dispo|");
        }
        else if(texte.dispo==2)
        {
            printf("|non dispo|");
        }

        printf("|%s|\n", texte.locataire);
        scanf("%d", &choix);
        while(getchar() != '\n'){};
        if(choix==1)
        {
            fwrite(&texte,sizeof(appartement),1,pfichier);
            printf("Vous avez bien ajoute un appartement a la liste des biens propose par MAGASHELTER !");
        }

        else if(choix==2)
        {
            ajoutAppart:
            printf("L'appartement n'a pas ete ajouter!\n\n");
        }

        else
        {
            printf("Veuillez selectionner 1 ou 2 !\n\n");
        }
    }
}

void afficher_apparts(FILE * pfichier)
{
    appartement texte;

    fseek(pfichier, 0, SEEK_SET);     //Remettre le curseur au début
    printf("|Nom|   |Ville|   |Surface|   |Prix|   |Meuble|   |Fumeur|    |Climatise|   |Piscine|   |Dispo|   |Locataire|\n\n");
	while(fread(&texte,sizeof(appartement),1,pfichier) == 1)
    {
        printf("|%s| |%s| |%dm2| |%deuros|", texte.nom, texte.ville, texte.surface, texte.prix);

        if(texte.meuble==1)
        {
            printf("|meuble|");
        }
        else if(texte.meuble==2)
        {
            printf("|non meuble|");
        }

        if(texte.fumeur==1)
        {
            printf("|fumeur|");
        }
        else if(texte.fumeur==2)
        {
            printf("|non fumeur|");
        }

        if(texte.clim==1)
        {
            printf("|climatise|");
        }
        else if(texte.clim==2)
        {
            printf("|non climatise|");
        }

        if(texte.piscine==1)
        {
            printf("|piscine dispo|");
        }
        else if(texte.piscine==2)
        {
            printf("|piscine non dispo|");
        }

        if(texte.dispo==1)
        {
            printf("|dispo|");
        }
        else if(texte.dispo==2)
        {
            printf("|non dispo|");
        }

        printf("|%s|\n", texte.locataire);
    }
    printf("\nContemplez la multitude des biens detenus par MAGASHELTER !\n\n");
}

void recherche_apparts(FILE * pfichier)
{
    int cpt = 0;
    int min, max, input2;
    appartement recherche, texte;

    rechercheAppart:
    printf("\nSelon quel critere souhaitez vous triez ? \n\n1. Nom \n2. Ville \n3. Surface \n4. Prix \n5. Meuble ou non? \n6. Fumeur ou non? \n7. Climatise ou non? \n8. Piscine ou non? \n9. Dispo ou non?\n10. Retour au menu\n\n");
    int choix = 0;
    while ((choix != 1) && (choix !=2) && (choix !=3) && (choix !=4) && (choix !=5) && (choix !=6) && (choix !=7) && (choix !=8) && (choix !=9) && (choix !=10))
    {
        scanf("%d", &choix);
        while(getchar() != '\n'){};

        switch(choix)
        {
            case 1 :
            {
                printf("Quel est le nom de l'appartement ?\n\nNom: ");
                gets(recherche.nom);

                while(fread(&texte,sizeof(appartement),1,pfichier) == 1)
                {
                    if(strcmp(texte.nom,recherche.nom)==0)
                    {
                        printf("%s %s %d %d %d %d %d %d %d\n", texte.nom, texte.ville, texte.surface, texte.prix, texte.meuble, texte.fumeur, texte.clim, texte.piscine, texte.dispo);
                        cpt++;
                    }
                }

                if(cpt==0)
                {
                    printf("\nDesole nous n'avons pas trouve ce nom !\n");
                    goto rechercheAppart;
                }
            }
            break;

            case 2 :
            {
                printf("Quelle ville recherchez-vous ?\n\nVille: ");
                gets(recherche.ville);

                while(fread(&texte,sizeof(appartement),1,pfichier) == 1)
                {
                    if(strcmp(texte.ville,recherche.ville)==0)
                    {
                        printf("%s %s %d %d %d %d %d %d %d\n", texte.nom, texte.ville, texte.surface, texte.prix, texte.meuble, texte.fumeur, texte.clim, texte.piscine, texte.dispo);
                        cpt++;
                    }
                }

                if(cpt==0)
                {
                    printf("\nDesole nous n'avons pas trouve cette ville !\n");
                    goto rechercheAppart;
                }
            }
            break;

            case 3 :
            {
                printf("Quelle surface minimale voulez vous?\nMinimum : ");
                scanf("%d", &min);
                while(getchar() != '\n'){};
                printf("Quelle surface maximale voulez vous?\nMaximum : ");
                scanf("%d", &max);
                while(getchar() != '\n'){};

                while(fread(&texte,sizeof(appartement),1,pfichier) == 1)
                {
                    if(min<= texte.surface && texte.surface <=max)
                    {
                        printf("\n%s %s %d %d %d %d %d %d %d\n", texte.nom, texte.ville, texte.surface, texte.prix, texte.meuble, texte.fumeur, texte.clim, texte.piscine, texte.dispo);
                        cpt++;
                    }
                }
                if(cpt==0)
                {
                    printf("\nDesole nous n'avons pas trouve cet surface !\n");
                    goto rechercheAppart;
                }
            }
            break;

            case 4 :
            {
                printf("Quelle prix minimum voulez vous?\nMinimum : ");
                scanf("%d", &min);
                while(getchar() != '\n'){};
                printf("Quelle prix maximum voulez vous?\nMaximum : ");
                scanf("%d", &max);
                while(getchar() != '\n'){};

                while(fread(&texte,sizeof(appartement),1,pfichier) == 1)
                {
                    if(min<=texte.prix && texte.prix<=max)
                    {
                        printf("%s %s %d %d %d %d %d %d %d\n", texte.nom, texte.ville, texte.surface, texte.prix, texte.meuble, texte.fumeur, texte.clim, texte.piscine, texte.dispo);
                        cpt++;
                    }
                }

                if(cpt==0)
                {
                    printf("\nDesole nous n'avons pas trouve ce prix !\n");
                    goto rechercheAppart;
                }
            }
            break;


            case 5 :
            {
                printf("Le souhaitez-vous meuble ? \n\n1. Oui \n2. Non\n\n");
                scanf("%d", &input2);
                while(getchar() != '\n'){};

                while(fread(&texte,sizeof(appartement),1,pfichier) == 1)
                {
                    if(input2 == texte.meuble)
                    {
                        printf("%s %s %d %d %d %d %d %d %d\n", texte.nom, texte.ville, texte.surface, texte.prix, texte.meuble, texte.fumeur, texte.clim, texte.piscine, texte.dispo);
                        cpt++;
                    }
                }
                if(cpt==0)
                {
                    printf("\nDesole nous n'avons pas trouve ce critere !\n");
                    goto rechercheAppart;
                }
            }
            break;

            case 6 :
            {
                printf("Etes-vous fumeur ?\n\n1. Oui\n2. Non\n\n");
                scanf("%d", &input2);
                while(getchar() != '\n'){};

                while(fread(&texte,sizeof(appartement),1,pfichier) == 1)
                {
                    if(input2 == texte.fumeur)
                    {
                        printf("%s %s %d %d %d %d %d %d %d\n", texte.nom, texte.ville, texte.surface, texte.prix, texte.meuble, texte.fumeur, texte.clim, texte.piscine, texte.dispo);
                        cpt++;
                    }
                }

                if(cpt==0)
                {
                    printf("\nDesole nous n'avons pas trouve ce critere !\n");
                    goto rechercheAppart;
                }
            }
            break;

            case 7 :
            {
                printf("Souhaitez-vous que votre appartement dispose d'une clim ?\n\n1. Oui\n2. Non\n\n");
                scanf("%d", &input2);
                while(getchar() != '\n'){};

                while(fread(&texte,sizeof(appartement),1,pfichier) == 1)
                {
                    if(input2==texte.clim)
                    {
                        printf("%s %s %d %d %d %d %d %d %d\n", texte.nom, texte.ville, texte.surface, texte.prix, texte.meuble, texte.fumeur, texte.clim, texte.piscine, texte.dispo);
                        cpt++;
                    }
                }

                if(cpt==0)
                {
                    printf("\nDesole nous n'avons pas trouve ce critere !\n");
                    goto rechercheAppart;
                }
            }
            break;

            case 8 :
            {
                printf("Souhaitez-vous que votre appartement dispose d'une piscine?\n\n1. Oui\n2. Non\n\n");
                scanf("%d", &input2);
                while(getchar() != '\n'){};

                while(fread(&texte,sizeof(appartement),1,pfichier) == 1)
                {
                    if(input2==texte.piscine)
                    {
                        printf("%s %s %d %d %d %d %d %d %d\n", texte.nom, texte.ville, texte.surface, texte.prix, texte.meuble, texte.fumeur, texte.clim, texte.piscine, texte.dispo);
                        cpt++;
                    }
                }

                if(cpt==0)
                {
                    printf("\nDesole nous n'avons pas trouve ce critere !\n");
                    goto rechercheAppart;
                }
            }
            break;

            case 9 :
            {
                printf("Souhaitez-vous voir uniquement les appartements disponible ?\n\n1. Oui\n2. Non\n\n");
                scanf("%d", &input2);
                while(getchar() != '\n'){};

                while(fread(&texte,sizeof(appartement),1,pfichier) == 1)
                {
                    if(input2==texte.dispo)
                    {
                        printf("%s %s %d %d %d %d %d %d %d\n", texte.nom, texte.ville, texte.surface, texte.prix, texte.meuble, texte.fumeur, texte.clim, texte.piscine, texte.dispo);
                        cpt++;
                    }
                }

                if(cpt==0)
                {
                    printf("\nDesole nous n'avons pas trouve d'appartement disponible !\n");
                    goto rechercheAppart;
                }
            }
            break;

            case 10 :

            break;

            default :
                printf("HIN HIN vous ne m'aurez pas ! ");
            break;
        }
    }
}

void modif_apparts()
{
    appartement texte, recherche, modif, stock;
    int choix, choix2;

    FILE * tampon;
    tampon = fopen("tampon.dat","wb+");
    if(tampon == NULL)
    {
        printf("ERREUR");
        exit(1);
    }

    FILE * fichier;
    fichier = fopen("appartements.dat","rb");
    if(fichier == NULL)
    {
        printf("ERREUR");
        exit(1);
    }

    fseek(fichier, 0, SEEK_SET);     //Remettre le curseur au début
	while(fread(&texte,sizeof(appartement),1,fichier) == 1)
    {
        printf("%s %s %d %d %d %d %d %d %d\n", texte.nom, texte.ville, texte.surface, texte.prix, texte.meuble, texte.fumeur, texte.clim, texte.piscine, texte.dispo);
    }

    printf("\nQuel est le nom de l'appartement que vous souhaitez modifier ?\n\nNom: ");
    gets(recherche.nom);

    fseek(fichier, 0, SEEK_SET);     //Remettre le curseur au début
    while(fread(&texte,sizeof(appartement),1,fichier) == 1)
    {
        if(strcmp(texte.nom,recherche.nom)==0)          //On enregistre les infos de l'appartement a modifier
        {
            strcpy(modif.nom,texte.nom);
            strcpy(modif.ville,texte.ville);
            modif.surface=texte.surface;
            modif.prix=texte.prix;
            modif.meuble=texte.meuble;
            modif.fumeur=texte.fumeur;
            modif.clim=texte.clim;
            modif.piscine=texte.piscine;
            modif.dispo=texte.dispo;
            strcpy(modif.locataire,recherche.locataire);
        }
    }

    fseek(fichier, 0, SEEK_SET);     //Remettre le curseur au début
    while(fread(&stock,sizeof(appartement),1,fichier) == 1)
    {
        if(strcmp(stock.nom,recherche.nom)!=0)         //Tout ce qui est différent sera recopie dans le fichier tampon
        {
            fwrite(&stock,sizeof(appartement),1,tampon);
            printf("%s", stock.nom);
        }
    }
    fclose(fichier);
    fclose(tampon);

    FILE * fichierFinal;
    fichierFinal = fopen("appartements.dat","wb+");         //Ouverture avec effacement au debut
    if(fichier == NULL)
    {
        printf("ERREUR");
        exit(1);
    }

    FILE * tamponLecture;
    tamponLecture = fopen("tampon.dat","rb");           //Ouverture en lecture
    if(tampon == NULL)
    {
        printf("ERREUR");
        exit(1);
    }

    fseek(tamponLecture, 0, SEEK_SET);     //Remettre le curseur au début
    while(fread(&texte,sizeof(appartement),1,tamponLecture) == 1)
    {
        fwrite(&texte,sizeof(appartement),1,fichierFinal);
    }

    fclose(tamponLecture);

    choixModif:
    choix=0;
    printf("\nQue voulez vous modifier? \n\n1. Nom \n2. Ville \n3. Surface \n4. Prix \n5. Meuble ou non? \n6. Fumeur ou non? \n7. Climatise ou non? \n8. Piscine ou non? \n9. Dispo ou non?\n\n");

    while ((choix != 1) && (choix !=2) && (choix !=3) && (choix !=4) && (choix !=5) && (choix !=6) && (choix !=7) && (choix !=8) && (choix !=9))
    {
        scanf("%d", &choix);
        while(getchar() != '\n'){};

        switch(choix)
        {
            case 1 :
            {
                printf("\nQuel est le nom de l'appartement?\n\nNom: ");
                gets(modif.nom);
            }
            break;

            case 2 :
            {
                printf("\nDans quelle ville se trouve l'appartement?\n\nVille: ");
                gets(modif.ville);
            }
            break;

            case 3 :
            {
                printf("\nQuelle est la surface de l'appartement? \n\n:Surface: ");
                scanf("%d", &modif.surface);
                while(getchar() != '\n'){};
            }
            break;

            case 4 :
            {
                printf("\nQuel est le prix de l'appartement?\n\nPrix: ");
                scanf("%d", &modif.prix);
                while(getchar() != '\n'){};
            }
            break;


            case 5 :
            {
                printf("\nL'appartement est-il meuble?\n1. Oui \n2. Non\n\n");
                scanf("%d", &modif.meuble);
                while(getchar() != '\n'){};
            }
            break;

            case 6 :
            {
                printf("\nL'appartement est-il fumeur?\n1. Oui \n2. Non\n\n");
                scanf("%d", &modif.fumeur);
                while(getchar() != '\n'){};
            }
            break;

            case 7 :
            {
                printf("\nL'appartement possède t-il une cilmatisation?\n1. Oui \n2. Non\n\n");
                scanf("%d", &modif.clim);
                while(getchar() != '\n'){};
            }
            break;

            case 8 :
            {
                printf("\nL'appartement possède t-il une piscine?\n1. Oui \n2. Non\n\n");
                scanf("%d", &modif.piscine);
                while(getchar() != '\n'){};
            }
            break;

            case 9 :
            {
                printf("\nL'appartement est t-il disponible?\n1. Oui \n2. Non\n\n");
                scanf("%d", &modif.dispo);
                while(getchar() != '\n'){};
            }
            break;

            default :
                printf("HIN HIN vous ne m'aurez pas, veuillez selectionner:\n\n1. Nom \n2. Ville \n3. Surface \n4. Prix \n5. Meuble ou non? \n6. Fumeur ou non? \n7. Climatise ou non? \n8. Piscine ou non? \n9. Dispo ou non?\n\n");
            break;
        }
    }


    printf("\nSouhaitez-vous modifier une autre information?\n1. Oui \n2. Non\n\n");
    scanf("%d", &choix2);
    while(getchar() != '\n'){};

    if(choix2==1)
    {
        choix=0;
        goto choixModif;
    }
    else if(choix2==2)
    {
        fclose(fichierFinal);
    }

    FILE * fichierFinal2;
    fichierFinal2 = fopen("appartements.dat","ab+");         //Ouverture avec effacement au debut
    if(fichier == NULL)
    {
        printf("ERREUR");
        exit(1);
    }
    fwrite(&modif,sizeof(appartement),1,fichierFinal2);

    fclose(fichierFinal2);
}

void supprimer_apparts()
{
    appartement texte, recherche, modif, stock;
    int choix, cpt=0;

    FILE * tampon;
    tampon = fopen("tampon.dat","wb+");
    if(tampon == NULL)
    {
        printf("ERREUR");
        exit(1);
    }

    FILE * fichier;
    fichier = fopen("appartements.dat","rb");
    if(fichier == NULL)
    {
        printf("ERREUR");
        exit(1);
    }

    fseek(fichier, 0, SEEK_SET);     //Remettre le curseur au début
	while(fread(&texte,sizeof(appartement),1,fichier) == 1)
    {
        printf("%s %s %d %d %d %d %d %d %d\n", texte.nom, texte.ville, texte.surface, texte.prix, texte.meuble, texte.fumeur, texte.clim, texte.piscine, texte.dispo);
    }

    printf("\nQuel est le nom de l'appartement que vous souhaitez supprimer ?\n\nNom: ");
    gets(recherche.nom);

    fseek(fichier, 0, SEEK_SET);     //Remettre le curseur au début
    while(fread(&texte,sizeof(appartement),1,fichier) == 1)
    {
        if(strcmp(texte.nom,recherche.nom)==0)          //On enregistre les infos de l'appartement a supprimer
        {
            strcpy(modif.nom,texte.nom);
            strcpy(modif.ville,texte.ville);
            modif.surface=texte.surface;
            modif.prix=texte.prix;
            modif.meuble=texte.meuble;
            modif.fumeur=texte.fumeur;
            modif.clim=texte.clim;
            modif.piscine=texte.piscine;
            modif.dispo=texte.dispo;
            strcpy(modif.locataire,recherche.locataire);
            cpt++;
        }
    }

    if(cpt==1)
    {
        fseek(fichier, 0, SEEK_SET);     //Remettre le curseur au début
        while(fread(&stock,sizeof(appartement),1,fichier) == 1)
        {
            if(strcmp(stock.nom,recherche.nom)!=0)         //Tout ce qui est différent sera recopie dans le fichier tampon
            {
                fwrite(&stock,sizeof(appartement),1,tampon);
            }
        }
        fclose(fichier);
        fclose(tampon);
        printf("Souhaitez vous supprimer cet appartement : %s %s %d %d %d %d %d %d %d\n\n1. Oui\n2. Non\n\n", modif.nom, modif.ville, modif.surface, modif.prix, modif.meuble, modif.fumeur, modif.clim, modif.piscine, modif.dispo);
        scanf("%d", &choix);
        while(getchar() != '\n'){};

        if(choix==1)
        {
            FILE * fichierFinal;
            fichierFinal = fopen("appartements.dat","wb+");         //Ouverture avec effacement au debut
            if(fichier == NULL)
            {
                printf("ERREUR");
                exit(1);
            }

            FILE * tamponLecture;
            tamponLecture = fopen("tampon.dat","rb");           //Ouverture en lecture
            if(tampon == NULL)
            {
                printf("ERREUR");
                exit(1);
            }

            fseek(tamponLecture, 0, SEEK_SET);     //Remettre le curseur au début
            while(fread(&texte,sizeof(appartement),1,tamponLecture) == 1)
            {
                fwrite(&texte,sizeof(appartement),1,fichierFinal);
            }

            fclose(tamponLecture);
            fclose(fichierFinal);
        }

        else if(choix==2)
        {
            printf("L'appartement n'a pas ete supprime !\n");
        }

        else
        {
            printf("Veuillez selectionner 1 ou 2 !\n\n");
        }
    }

    else if(cpt==0)
    {
        printf("\nDesole nous n'avons pas trouve ce nom !\n\n");
    }

}

void modif_comptes(compte pcompte_actif)
{
    compte texte, recherche, modif, stock;
    int choix, cpt=0;

    FILE * tampon;
    tampon = fopen("tampon.dat","wb+");
    if(tampon == NULL)
    {
        printf("ERREUR");
        exit(1);
    }

    FILE * fichier;
    fichier = fopen("comptes_client.dat","rb");
    if(fichier == NULL)
    {
        printf("ERREUR");
        exit(1);
    }

    fseek(fichier, 0, SEEK_SET);     //Remettre le curseur au début
	while(fread(&texte,sizeof(compte),1,fichier) == 1)
    {
        printf("%s %s %d %s %s\n", texte.nom, texte.prenom, texte.tel, texte.mail, texte.mdp);
    }

    strcpy(recherche.mail,pcompte_actif.mail);

    fseek(fichier, 0, SEEK_SET);     //Remettre le curseur au début
    while(fread(&texte,sizeof(compte),1,fichier) == 1)
    {
        if(strcmp(texte.mail,recherche.mail)==0)          //On enregistre les infos du compte a modifier
        {
            strcpy(modif.nom,texte.nom);
            strcpy(modif.prenom,texte.prenom);
            modif.tel=texte.tel;
            strcpy(modif.mail,texte.mail);
            strcpy(modif.mdp,texte.mdp);
            cpt++;
        }
    }

    if(cpt==1)
    {
        fseek(fichier, 0, SEEK_SET);     //Remettre le curseur au début
        while(fread(&stock,sizeof(compte),1,fichier) == 1)
        {
            if(strcmp(stock.mail,recherche.mail)!=0)         //Tout ce qui est différent sera recopie dans le fichier tampon
            {
                fwrite(&stock,sizeof(compte),1,tampon);
            }
        }
        fclose(fichier);
        fclose(tampon);
        printf("Souhaitez vous modifier ce compte : %s %s %d %s %s\n\n1. Oui\n2. Non\n\n", modif.nom, modif.prenom, modif.tel, modif.mail, modif.mdp);
        scanf("%d", &choix);
        while(getchar() != '\n'){};

        if(choix==1)
        {
            FILE * fichierFinal;
            fichierFinal = fopen("comptes_client.dat","wb+");         //Ouverture avec effacement au debut
            if(fichier == NULL)
            {
                printf("ERREUR");
                exit(1);
            }

            FILE * tamponLecture;
            tamponLecture = fopen("tampon.dat","rb");           //Ouverture en lecture
            if(tampon == NULL)
            {
                printf("ERREUR");
                exit(1);
            }

            fseek(tamponLecture, 0, SEEK_SET);     //Remettre le curseur au début
            while(fread(&texte,sizeof(compte),1,tamponLecture) == 1)
            {
                fwrite(&texte,sizeof(compte),1,fichierFinal);
            }

            fclose(tamponLecture);
            fclose(fichierFinal);


            FILE * fichier2;
            fichier2 = fopen("comptes_client.dat","ab+");            //Creation d'un compte client
            if(fichier2 == NULL)
            {
                printf("ERREUR");
                exit(1);
            }

            creer_compte(fichier2);
            printf("\nVotre compte a bien ete modifie\n\n");
            fclose(fichier2);


        }

        else if(choix==2)
        {
            printf("Le compte n'a pas ete modifie !\n");
        }

        else
        {
            printf("Veuillez selectionner 1 ou 2 !\n\n");
        }
    }

    else if(cpt==0)
    {
        printf("\nDesole nous n'avons pas trouve ce mail !\n\n");
    }
}

void reservation(compte pcompte_actif)
{
    appartement texte, recherche, modif, stock;

    FILE * tampon;
    tampon = fopen("tampon.dat","wb+");
    if(tampon == NULL)
    {
        printf("ERREUR");
        exit(1);
    }

    FILE * fichier;
    fichier = fopen("appartements.dat","rb");
    if(fichier == NULL)
    {
        printf("ERREUR");
        exit(1);
    }

    fseek(fichier, 0, SEEK_SET);     //Remettre le curseur au début
	while(fread(&texte,sizeof(appartement),1,fichier) == 1)
    {
        printf("%s %s %d %d %d %d %d %d %d\n", texte.nom, texte.ville, texte.surface, texte.prix, texte.meuble, texte.fumeur, texte.clim, texte.piscine, texte.dispo);
    }

    printf("\nQuel est le nom de l'appartement que vous souhaitez reserver ?\n\nNom: ");
    gets(recherche.nom);

    fseek(fichier, 0, SEEK_SET);     //Remettre le curseur au début
    while(fread(&texte,sizeof(appartement),1,fichier) == 1)
    {
        if(strcmp(texte.nom,recherche.nom)==0)          //On enregistre les infos de l'appartement a modifier
        {
            strcpy(modif.nom,texte.nom);
            strcpy(modif.ville,texte.ville);
            modif.surface=texte.surface;
            modif.prix=texte.prix;
            modif.meuble=texte.meuble;
            modif.fumeur=texte.fumeur;
            modif.clim=texte.clim;
            modif.piscine=texte.piscine;
            modif.dispo=texte.dispo;
        }
    }

    fseek(fichier, 0, SEEK_SET);     //Remettre le curseur au début
    while(fread(&stock,sizeof(appartement),1,fichier) == 1)
    {
        if(strcmp(stock.nom,recherche.nom)!=0)         //Tout ce qui est différent sera recopie dans le fichier tampon
        {
            fwrite(&stock,sizeof(appartement),1,tampon);
        }
    }
    fclose(fichier);
    fclose(tampon);

    FILE * fichierFinal;
    fichierFinal = fopen("appartements.dat","wb+");         //Ouverture avec effacement au debut
    if(fichier == NULL)
    {
        printf("ERREUR");
        exit(1);
    }

    FILE * tamponLecture;
    tamponLecture = fopen("tampon.dat","rb");           //Ouverture en lecture
    if(tampon == NULL)
    {
        printf("ERREUR");
        exit(1);
    }

    fseek(tamponLecture, 0, SEEK_SET);     //Remettre le curseur au début
    while(fread(&texte,sizeof(appartement),1,tamponLecture) == 1)
    {
        fwrite(&texte,sizeof(appartement),1,fichierFinal);
    }

    fclose(tamponLecture);
    fclose(fichierFinal);

    strcpy(modif.locataire,pcompte_actif.mail);
    modif.dispo=2;
    printf("%s", modif.locataire);

    FILE * fichierFinal2;
    fichierFinal2 = fopen("appartements.dat","ab+");         //Ouverture avec effacement au debut
    if(fichier == NULL)
    {
        printf("ERREUR");
        exit(1);
    }
    fwrite(&modif,sizeof(appartement),1,fichierFinal2);

    fclose(fichierFinal2);
}


