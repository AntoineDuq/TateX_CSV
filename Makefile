# Variables externes
EXEC = TateX
CC = gcc
DEBUG = no

# On change les flags selon le mode choisi
ifeq ($(DEBUG),yes)
	CFLAGS=-W -Wall -g
else
	CFLAGS=-W -Wall
endif

# all regroupe l'ensemble des dépendances à construire
all: $(EXEC) clean

# permet d'afficher si on est en mode debug ou non dans la console
ifeq ($(DEBUG),yes)
	@echo "Génération en mode debug"
else
	@echo "Génération en mode release"
endif

# 1ère cible
TateX : CSVlib.o TateX.o
	$(CC) -O3 $^ -o $@
# -O3 : optimise le temps d'exécution mais ralenti le temps de compilation 
# $@ : nom de la cible (TateX)
# $^ : liste des dépendances (CSVlib.o TateX.o)

# 2ème cible
CSVlib.o : CSVlib.c
	$(CC) -c $< $(CFLAGS)
# $< : nom de la première dépendance (CSVlib.c)

# 3ème cible 
TateX.o : TateX.c CSVlib.h
	$(CC) -c $< $(CFLAGS)
# $< : nom de la première dépendance (TateX.c)

# Supprime les fichiers non utilisés après la compilation
clean:
	rm -rf *.o
