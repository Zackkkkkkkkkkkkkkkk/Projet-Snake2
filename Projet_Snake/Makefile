# Makefile pour le jeu Snake

CC = gcc
CFLAGS = -Wall -Wextra -g
OBJDIR = obj
SRCDIR = src
HEADERDIR = header

# Liste des fichiers objets
OBJS = $(OBJDIR)/main.o $(OBJDIR)/carte.o $(OBJDIR)/serpent.o $(OBJDIR)/bonus.o $(OBJDIR)/jeu.o $(OBJDIR)/menu.o

# Nom de l'exécutable
TARGET = snake

# Règle par défaut
all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Règles pour créer les fichiers objets
$(OBJDIR)/main.o: $(SRCDIR)/main.c $(HEADERDIR)/types.h $(HEADERDIR)/carte.h $(HEADERDIR)/serpent.h $(HEADERDIR)/bonus.h $(HEADERDIR)/jeu.h $(HEADERDIR)/menu.h
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/carte.o: $(SRCDIR)/carte.c $(HEADERDIR)/carte.h $(HEADERDIR)/types.h $(HEADERDIR)/serpent.h
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/serpent.o: $(SRCDIR)/serpent.c $(HEADERDIR)/serpent.h $(HEADERDIR)/types.h
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/bonus.o: $(SRCDIR)/bonus.c $(HEADERDIR)/bonus.h $(HEADERDIR)/types.h $(HEADERDIR)/serpent.h
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/jeu.o: $(SRCDIR)/jeu.c $(HEADERDIR)/jeu.h $(HEADERDIR)/types.h $(HEADERDIR)/carte.h $(HEADERDIR)/serpent.h $(HEADERDIR)/bonus.h
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/menu.o: $(SRCDIR)/menu.c $(HEADERDIR)/menu.h $(HEADERDIR)/types.h $(HEADERDIR)/serpent.h
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)

# Nettoyage complet
mrproper: clean
	rm -rf $(OBJDIR)

# Reconstruction complète
rebuild: mrproper all

.PHONY: all clean mrproper rebuild
