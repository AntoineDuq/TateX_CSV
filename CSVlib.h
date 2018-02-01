#ifndef H_CSVLIB
#define H_CSVLIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1284
/* Nombre de cellules de la table de hachage */
#define MAXLINE 2048
/* Nombre maximal de caractères dans une ligne du CSV */
#define MAXCOLUMN 20
/* Nombre de champs dans le CSV */


/* ------------------- PARTIE STRUCTURE ------------------- */


typedef struct{
	char* id;
	char* accession_number;
	char* nom;
	char* artistRole;
	char* artistId;
	char* title;
	char* dateText;
	char* medium;
	char* creditLine;
	char* year;
	char* acquisitionYear;
	char* dimensions;
	char* width;
	char* height;
	char* depth;
	char* units;
	char* inscription;
	char* thumbnailCopyright;
	char* thumbnailUrl;
	char* url;
} Oeuvre;

/*
Structure Oeuvre contenant toutes les informations d'une oeuvre
*/

typedef struct cell {
	Oeuvre oeuvre;
	struct cell * suiv;
} Cellule_oeuvre, *Ptcellule_oeuvre, *Liste_oeuvres;

/*
Liste chainée d'oeuvres
*/

typedef struct{
	int nb_oeuvres;
	char* idArt;
	char* nomArt;
	Ptcellule_oeuvre old;
	Liste_oeuvres oeuvres;
} Artiste;

/*
Structure Artiste contenant : son nombre d'oeuvres, son id, son nom, son oeuvre la plus vieille et sa liste d'oeuvres
*/

typedef struct cell_artiste {
	Artiste artiste;
	struct cell_artiste* suiv;
} Cellule_artiste, *Ptcellule_artiste, *Liste_artistes;

/*
Liste chainée d'artistes
*/

typedef struct{
	int nb_artistes;
	Liste_artistes artistes;
} Hash_cell;

/*
Cellule de la table de hachage
*/

typedef Hash_cell Hashtable[TABLE_SIZE];

/*
Table de hachage
*/


/* ------------------- PROTOTYPES ------------------- */


/* ------ Découpage du CSV ------ */


char * strtok_new (char*, char*);

/*
Fonction de séparation d'une chaine à l'aide d'un séparateur
Prend 2 paramètres : str (pointeur de caractère) et delim (pointeur de caractère)
Retourne un pointeur de caractère sur le dernier mot séparé par le délimiteur (delim)
*/

double poow(double, int);

/*
Fonction puissance
Prend 2 paramètres : x (double), n(entier)
Retourne x puissance n
*/ 

int hash(char*);

/*
Fonction de hachage
Prend 1 paramètre : word (pointeur de caractère)
Retourne l'indice de hachage d'un mot dans une table de taille TABLE_SIZE
*/


/* ------ Ajout dans la structure ------ */

Oeuvre remplir_oeuvre(char**);

/*
Fonction de remplissage d'une oeuvre
Prend 1 paramètre : tab (tableau de pointeurs de caractères)
Retourne une oeuvre de type Oeuvre
*/

void init_ht(Hashtable);

/*
Action d'initialisation de la table de hachage
Prend 1 paramètre : ht (table de hachage)
Initialise la table de hachage
*/ 

Ptcellule_oeuvre ajout_tete_oeuvre(Liste_oeuvres*, Oeuvre*);

/*
Fonction d'ajout en tête d'une Oeuvre dans une liste chainée d'Oeuvres
Prend 2 paramètres : liste (liste chainée d'oeuvres), o (Pointeur d'Oeuvre) 
Ajoute le contenu de o en tête de liste et retourne l'adresse de la cellule oeuvre
*/

void ajout_tete_artiste(Liste_artistes*, Artiste*);

/*
Action d'ajout en tête d'un Artiste dans une liste chainée d'Artistes
Prend 2 paramètres : liste (liste chainée d'artistes), a (Pointeur d'Artiste) 
Ajoute le contenu de a en tête de liste_art 
*/

void ajouter_oeuvre(Hashtable, Oeuvre*);

/*
Procedure d'ajout d'une Oeuvre dans la structure de données
Prend 2 paramètres : ht (table de hachage), o (Pointeur d'Oeuvre) 
Ajoute le contenu de o dans la structure de données (en créant un nouvel artiste ou en rajoutant une oeuvre à un artiste existant)
*/


/* ------ Fonctions d'affichage ------ */


void afficher_lc_oeuvres(Liste_oeuvres);

/*
Action d'affichage d'une liste chainée d'Oeuvres
Prend 1 paramètre : liste (liste chainée d'Oeuvres) 
Affiche une liste chainée d'Oeuvres (ID artiste et nom / Titre de l'oeuvre et année)
*/

void afficher_oeuvres(Hashtable);

/*
Action d'affichage des oeuvres de la structure de données
Prend 1 paramètre : ht (table de hachage)
Affiche une liste de tous les artistes et leurs oeuvres
*/

void afficher_old(Hashtable);

/*
Action d'affichage des 2 plus vieilles oeuvres
Prend 1 paramètre : ht (table de hachage) 
Affiche les 2 plus vieilles oeuvres contenues dans la structure de données
*/

int recherche_artiste(Hashtable, char*);

/*
Fonction de recherche d'un artiste identifié par son id
Prend 2 paramètres: ht (table de hachage), id (pointeur de caractère) 
Retourne 1 si l'id correspond à un id d'artiste contenu dans ht, retourne 0 sinon 
*/

void liste_artiste(Hashtable, char*);

/*
Action de listing de toutes les oeuvres d'un artiste donné par son id
Prend 2 paramètres: ht (table de hachage), ida (pointeur de caractère) 
Liste toutes les oeuvres de l'Artiste ida contenu dans ht si l'artiste existe
*/

int nb_oeuvres_artiste(Hashtable, char*);

/*
Fonction de comptage du nombre d'oeuvres d'un artiste donné par son id
Prend 2 paramètres: ht (table de hachage), id (pointeur de caractère) 
Compte le nombre d'oeuvres pour un artiste donné par son id dans une table de hachage ht si l'artiste existe
Retourne le nombre d'oeuvres ou -1 si l'artiste n'existe pas
*/

void nb_oeuvres_all(Hashtable);

/*
Action d'affichage du nombre d'oeuvres par Artiste
Prend 1 paramètre: ht (table de hachage) 
Affiche le nombre d'oeuvre pour chaque Artiste contenu dans ht
*/

void afficher_menu();

/*
Action d'affichage du menu principal
*/


/* ------ Fonctions de libération de la mémoire ------ */


void free_strut(Hashtable*);

/*
Action de libération de la mémoire de la structure de données
Prend 1 paramètre : ht (table de hachage)
Utilise les fonctions supprimer_artistes et supprimer_oeuvres pour libérer la mémoire allouée dynamiquement
*/

void supprimer_artistes(Liste_artistes*);

/*
Action de libération de la mémoire d'une liste chainée d'artistes
Prend 1 paramètre : l_art (liste chainée d'artistes)
Libère la mémoire occupée par chaque artiste
*/

void supprimer_oeuvres(Liste_oeuvres*);

/*
Action de libération de la mémoire d'une liste chainée d'oeuvres
Prend 1 paramètre : l_oeuvre (liste chainée d'oeuvres)
Libère la mémoire occupée par les oeuvres d'un artiste
*/

#endif
