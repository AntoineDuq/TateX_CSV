#include "CSVlib.h"

/* Les fonctions sont documentées dans le fichier CSVlib.h */
/* Les commentaires présents ici détaillent des points techniques */

double poow(double x, int n)
{
	int i;
	double res = x;
	if(n == 0) return 1.0;
	for(i=1;i<n;i++)
	{
		res*=x;
	}
	return res;
}


int hash(char *word)
{
	int i = 0;
	int h = 0;
	int c = 11;
	while(word[i]!='\0')
	{
		h = h+(word[i]*poow(c,i));
		i++;
	}
	return h % TABLE_SIZE;
}


void init_ht(Hashtable ht)
{
	int i;
	for(i=0;i<TABLE_SIZE;i++)
	{
		ht[i].nb_artistes = 0;
		ht[i].artistes = NULL;
	}
}


void free_strut(Hashtable* ht)
{
	int i;
	for(i=0;i<TABLE_SIZE;i++)
	{
		if((*ht)[i].nb_artistes != 0)
		{
			supprimer_artistes(&((*ht)[i].artistes));
		}
	}
}


void supprimer_artistes(Liste_artistes* l_art)
{
	while (*l_art != NULL)
	{
		/* On supprime les oeuvres avant de supprimer la cellule de l'artiste */
		supprimer_oeuvres(&((**l_art).artiste.oeuvres));
		Ptcellule_artiste temp = (**l_art).suiv;
		free(*l_art);
		*l_art = temp;
	}
}


void supprimer_oeuvres(Liste_oeuvres* l_oeuvre)
{
	while (*l_oeuvre != NULL)
	{
		Ptcellule_oeuvre temp = (**l_oeuvre).suiv;

		/* On supprime d'abord les informations des oeuvres (mémoire allouée par strdup dans le programme principal) */
		free(((**l_oeuvre).oeuvre).id);
		free(((**l_oeuvre).oeuvre).accession_number);
		free(((**l_oeuvre).oeuvre).nom);
		free(((**l_oeuvre).oeuvre).artistRole);
		free(((**l_oeuvre).oeuvre).artistId);
		free(((**l_oeuvre).oeuvre).title);
		free(((**l_oeuvre).oeuvre).dateText);
		free(((**l_oeuvre).oeuvre).medium);
		free(((**l_oeuvre).oeuvre).creditLine);
		free(((**l_oeuvre).oeuvre).year);
		free(((**l_oeuvre).oeuvre).acquisitionYear);
		free(((**l_oeuvre).oeuvre).dimensions);
		free(((**l_oeuvre).oeuvre).width);
		free(((**l_oeuvre).oeuvre).height);
		free(((**l_oeuvre).oeuvre).depth);
		free(((**l_oeuvre).oeuvre).units);
		free(((**l_oeuvre).oeuvre).inscription);
		free(((**l_oeuvre).oeuvre).thumbnailCopyright);
		free(((**l_oeuvre).oeuvre).thumbnailUrl);
		free(((**l_oeuvre).oeuvre).url);

		/* On supprime ensuite la cellule, également allouée dynamiquement */
		free(*l_oeuvre);
		*l_oeuvre = temp;
	}

}


Ptcellule_oeuvre ajout_tete_oeuvre(Liste_oeuvres * liste, Oeuvre* o)
{
	Ptcellule_oeuvre temp = *liste;
	*liste = malloc(sizeof(Cellule_oeuvre));
	(*(*liste)).oeuvre = *o;
	(*(*liste)).suiv = temp;
	return *liste;
}


void ajout_tete_artiste(Liste_artistes* liste_art, Artiste* a)
{
	Ptcellule_artiste temp = *liste_art;
	*liste_art = malloc(sizeof(Cellule_artiste));
	(*(*liste_art)).artiste = *a;
	(*(*liste_art)).suiv = temp;
}


void ajouter_oeuvre(Hashtable ht, Oeuvre* o)
{
	int indice = hash(o->artistId); /* On hash l'indice de l'oeuvre à ajouter */
	int i;
	int p = ht[indice].nb_artistes;
	Ptcellule_oeuvre temp;
	Ptcellule_artiste temp_art = ht[indice].artistes;
	for(i = 0; i < p; i++) /* Si p vaut 0, on ne rentre pas de cette boucle sinon on parcourt la liste d'artistes pour vérifier si l'artiste est présent ou non */
	{	
		if(strcmp(o->artistId,temp_art->artiste.idArt) == 0) /* Si l'artiste est présent, on lui ajoute une nouvelle oeuvre */
		{
			temp_art->artiste.nb_oeuvres+=1;
			temp = ajout_tete_oeuvre(&(temp_art->artiste.oeuvres),o);
			if(*(o->year) == 0) return;
			else if(  (strcmp(o->year,(temp_art->artiste.old)->oeuvre.year) < 0) || ( *((temp_art->artiste.old)->oeuvre.year) == 0 )  ) /* On profite d'enregistrer l'oeuvre la plus vieille de l'artiste */
			{
				temp_art->artiste.old = temp;
			}
			return;
		}
		temp_art = temp_art->suiv;
		
	}
	/* Ici, l'artiste n'est pas encore répertorié */
	ht[indice].nb_artistes+=1;
	Artiste new_art = {1, o->artistId,o->nom, NULL, NULL};
	ajout_tete_artiste(&(ht[indice].artistes), &new_art); /* On ajoute d'abord l'artiste */
	ht[indice].artistes->artiste.old = ajout_tete_oeuvre(&(ht[indice].artistes->artiste.oeuvres),o); /* Puis son oeuvre */
}


void afficher_lc_oeuvres(Liste_oeuvres liste)
{
	Ptcellule_oeuvre temp = liste;
	while(temp != NULL)
	{
		printf("* (%s) %s : %s | %s\n",(*temp).oeuvre.artistId,(*temp).oeuvre.nom, (*temp).oeuvre.title, (*temp).oeuvre.year);
		temp = (*temp).suiv;
	}
	printf("\n");
}


void afficher_oeuvres(Hashtable ht)
{
	int i,j;
	for(i=0;i<TABLE_SIZE;i++)
	{
		int n = ht[i].nb_artistes;
		Ptcellule_artiste temp_art = ht[i].artistes;
		for(j=0;j<n;j++)
		{
			printf("Artiste : %s\n",temp_art->artiste.nomArt);
			afficher_lc_oeuvres(temp_art->artiste.oeuvres);
			temp_art = temp_art->suiv;
		}
	}
}


void afficher_old(Hashtable ht)
{
	int i,j,n,a = 0;
	Ptcellule_oeuvre older,older2; /* Assure l'affichage des deux oeuvres les plus vieilles */
	for(i=0;i<TABLE_SIZE;i++)
	{
		n = ht[i].nb_artistes;
		Ptcellule_artiste temp_art = ht[i].artistes;
		for(j=0;j<n;j++)
		{
			if((a == 0) && (*((temp_art->artiste.old)->oeuvre.year) != 0) ) /* On ne mémorise pas l'oeuvre si son année n'est pas renseignée */
			{
				older = temp_art->artiste.old;
				a++;
			}
			else if( ( *((temp_art->artiste.old)->oeuvre.year) != 0 ) && ( strcmp((temp_art->artiste.old)->oeuvre.year,older->oeuvre.year) < 0 ) && (a!=0))
			{
				older = temp_art->artiste.old;
			}
			else if( ( *((temp_art->artiste.old)->oeuvre.year) != 0 ) && ( strcmp((temp_art->artiste.old)->oeuvre.year,older->oeuvre.year) == 0 ) && (a!=0))
			{
				older2 = temp_art->artiste.old;
			}
			temp_art = temp_art->suiv;
		}
	}
	printf("\"%s\" de %s est la plus vieille oeuvre (%s)\n",older->oeuvre.title,older->oeuvre.nom,older->oeuvre.year);
	if(older2 != NULL) printf("Mais \"%s\" de %s est aussi vieille (%s)\n",older2->oeuvre.title,older->oeuvre.nom,older->oeuvre.year);
}


int recherche_artiste(Hashtable ht, char* id)
{
	int indice = hash(id);
	int i;
	int p = ht[indice].nb_artistes;
	Ptcellule_artiste temp_art = ht[indice].artistes;
	for(i=0;i<p;i++)
	{
		if(strcmp(id,temp_art->artiste.idArt) == 0)
		{
			printf("L'artiste \"%s\" (%s) est dans la liste\n",temp_art->artiste.nomArt,id);
			return 1;
		}
		temp_art = temp_art->suiv;
	}
	printf("L'artiste %s n'est pas dans la liste\n",id);
	return 0;
}


void liste_artiste(Hashtable ht, char* ida)
{
	int indice = hash(ida);
	int i;
	int p = ht[indice].nb_artistes;
	Ptcellule_artiste temp_art = ht[indice].artistes;
	for(i=0;i<p;i++)
	{
		if(strcmp(ida,temp_art->artiste.idArt) == 0)
		{
			afficher_lc_oeuvres(temp_art->artiste.oeuvres);
			return;
		}
		temp_art = temp_art->suiv;
	}
	printf("L'artiste %s n'est pas dans la liste\n",ida);
}


int nb_oeuvres_artiste(Hashtable ht, char* id)
{
	int indice = hash(id);
	int i;
	int p = ht[indice].nb_artistes;
	Ptcellule_artiste temp_art = ht[indice].artistes;
	for(i=0;i<p;i++)
	{
		if(strcmp(id,temp_art->artiste.idArt) == 0)
		{
			printf("%s | %s | %d\n",temp_art->artiste.idArt,temp_art->artiste.nomArt,temp_art->artiste.nb_oeuvres);
			return temp_art->artiste.nb_oeuvres;
		}
	temp_art = temp_art->suiv;
	}
	printf("L'artiste %s n'est pas dans la liste\n",id);
	return -1; 
}


void nb_oeuvres_all(Hashtable ht)
{
	int i,j,p;
	for(i=0;i<TABLE_SIZE;i++)
	{
		Ptcellule_artiste temp_art = ht[i].artistes;
		p = ht[i].nb_artistes;
		for(j=0;j<p;j++)
		{
			printf("%s | %s | %d\n",temp_art->artiste.idArt,temp_art->artiste.nomArt,temp_art->artiste.nb_oeuvres);
			temp_art = temp_art->suiv;
		}
	}
}


char * strtok_new (char* str, char* delim)
{
	static char* old_pt = NULL; /*  old_pt est défini une seule fois au premier appel  */
	char* p;
	char* ret = 0;
	int r = 1;
	if(str != NULL)
	{
		old_pt = str;
	}
	if(old_pt == NULL)
	{
		return NULL;
	}
	if(*old_pt == '"') /*  On change le délimiteur si le premier caractère est un guillemet  */
	{
		delim = "\",";
		old_pt++; /* On ne garde pas le guillemet */
		r = 2;
	}
	if((p = strstr(old_pt, delim)) != NULL) /* Si on trouve le délimiteur, strstr renvoie un pointeur vers le premier caractère du délimiteur trouvé*/
	{
		*p  = 0; /* On remplace la virgule ou le guillemet selon le cas par un caractère de fin de chaine */
		ret = old_pt; /* Pointeur retourné */
		p = p+r; /* si r vaut 2 (cas du guillemet), on passe au dessus de la virgule */
		old_pt = p; /* old_pt pointe vers le premier caractère de la suite de la ligne  */
	}
	else if(*old_pt) /* Si on ne trouve aucun délimiteur, on ajoute \0 en fin de chaine à la place du \n */
	{
		p = strpbrk(old_pt, "\n");
		*p = 0;
		ret = old_pt;
		old_pt = NULL; /* Au prochain appel, strtok_new() renverra NULL car old_pt et str vaudront NULL */
	}
	return ret;
}


Oeuvre remplir_oeuvre(char* tab[MAXCOLUMN])
{
	Oeuvre o;
	o.id = tab[0];
	o.accession_number = tab[1];
	o.nom = tab[2];
	o.artistRole = tab[3];
	o.artistId = tab[4];
	o.title = tab[5];
	o.dateText = tab[6];
	o.medium = tab[7];
	o.creditLine = tab[8];
	o.year = tab[9];
	o.acquisitionYear = tab[10];
	o.dimensions = tab[11];
	o.width = tab[12];
	o.height = tab[13];
	o.depth = tab[14];
	o.units = tab[15];
	o.inscription = tab[16];
	o.thumbnailCopyright = tab[17];
	o.thumbnailUrl = tab[18];
	o.url = tab[19];
	return o;
}


void afficher_menu()
{
	printf
	(
	"-------------------------\n"
	"- 1 : liste de toutes les oeuvres\n"
	"- 2 id: recherche d'un artiste identifie par id\n"
	"- 3 id: liste de toutes les oeuvres d'un artiste donne par son id\n"
	"- 4 id: compte le nombre d'oeuvres pour un artiste donne par son id\n"
	"- 5: afficher le nombre d'oeuvres par artiste\n"
	"- 6: affiche l'oeuvre la plus vieille\n"
	"- 7: quitter\n"
	"-------------------------\n"
	);
}
