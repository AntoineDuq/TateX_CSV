#include "CSVlib.h"

int main(int argc, char *argv[])
{
	char line[MAXLINE]; /* Liste provisoire contenant une ligne complète d'un fichier */
	char s[2] = ","; /* Séparateur utilisé dans le parsage du CSV */
	char id[7]; /* Stocke l'id d'un artiste pour le menu */

	char* word; /* Pointe vers le contenu d'un champ d'une ligne */
	char* tab_art[MAXCOLUMN]; /* Liste provisoire contenant l'ensemble des adresses des contenus des champs */

	int i = 0; /* Utilisé pour remplir la liste tab_art */
	int a = 0; /* Utilisé pour négliger la première ligne */
	int choice;

	Oeuvre tempOeuvre; /* Oeuvre temporaire servant au remplissage de la structure */
	Hashtable ht; /* Déclaration d'une table de hachage comme définie dans CSVlib.h */
	FILE* fp; /* Déclaration d'un pointeur de fichier */
 
	if (argc >= 2)
	{
		fp = fopen(argv[argc-1], "r"); /* Lecture du fichier passer en paramètre lors de l'exécution du programme */
		if (fp == NULL)
		{
			printf("Impossible de charger le fichier !\n");
			return EXIT_FAILURE;
		}
	}
	
	else 
	{
		printf("Aucun fichier passé en paramètre !\n");
		return EXIT_FAILURE;
	}	

	init_ht(ht);
	
	
	while(fgets(line, MAXLINE, fp) != NULL) /* On lit l'entiereté du fichier */
	{
		if(a != 0) /* On ne prend pas la première ligne et on ajoute les oeuvres à la structure à partir de la 2ème ligne */
		{
			word = strtok_new(line, s); /* On récupère le contenu du premier champ de la ligne */
			while(word != NULL) /* On parcourt tous les champs de la ligne */
			{
				if((tab_art[i] = strdup(word)) == NULL) return EXIT_FAILURE; /* On attribue la place qu'il faut aux valeur des champs */
				word = strtok_new(NULL, s);
				i++;
			}
			tempOeuvre = remplir_oeuvre(tab_art); /* On remplie l'oeuvre temporaire */
			ajouter_oeuvre(ht,&tempOeuvre); 
			i = 0;
		}
		a = 1;
	}

	do /* On affiche le menu tant que le choix est différent de 7 (quitter) */
	{
		afficher_menu();
		scanf("%d",&choice);
		switch (choice) 
		{
			case 1 :
				afficher_oeuvres(ht);
				break;
			case 2 :
				scanf("%s",id);
				recherche_artiste(ht,id);
				break;
			case 3 :
				scanf("%s",id);
				liste_artiste(ht,id);
				break;
			case 4 :
				scanf("%s",id);
				nb_oeuvres_artiste(ht,id);
				break;
			case 5 :
				nb_oeuvres_all(ht);
				break;
			case 6 :
				afficher_old(ht);
				break;
			case 7 :
				break;
			default:
				printf("Action impossible !\n");
		}

	} while(choice != 7);

	printf("Au revoir !\n");
	fclose(fp);
	free_strut(&ht); /* On libère la mémoire allouée dynamiquement */

	return EXIT_SUCCESS;
}
