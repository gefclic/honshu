CC = gcc -Wall -Wextra -g 

CC_SDL =  `pkg-config --cflags --libs  SDL_image SDL_ttf SDL_mixer` 
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = tests
DOCDIR = doc

all : $(BINDIR)/Honshu
test: $(TESTDIR)/test
doc : $(DOCDIR)/doxy


$(OBJDIR)/main.o : $(SRCDIR)/main.c 
	$(CC) -c $< -o $@

$(OBJDIR)/Tuiles.o : $(SRCDIR)/Tuiles.c $(SRCDIR)/Tuiles.h
	$(CC) -c $< -o $@

$(OBJDIR)/Grille.o : $(SRCDIR)/Grille.c $(SRCDIR)/Grille.h
	$(CC) -c $< -o $@

$(OBJDIR)/Jeu.o : $(SRCDIR)/Jeu.c $(SRCDIR)/Jeu.h
	$(CC) -c $< -o $@

$(OBJDIR)/Affichage.o : $(SRCDIR)/Affichage.c $(SRCDIR)/Affichage.h
	$(CC) -c $< -o $@

$(OBJDIR)/HonshuSDL.o : $(SRCDIR)/HonshuSDL.c $(SRCDIR)/HonshuSDL.h
	$(CC) -c $< -o $@  $(CC_SDL)

$(BINDIR)/Honshu : $(OBJDIR)/main.o $(OBJDIR)/Tuiles.o $(OBJDIR)/Grille.o $(OBJDIR)/Jeu.o $(OBJDIR)/Affichage.o $(OBJDIR)/HonshuSDL.o
	$(CC) $^ -o $@ $(CC_SDL)
	cp src/SDL/*.png bin/
	cp src/SDL/*.ttf bin/
	cp src/SDL/*.mp3 bin/

#TEST UNITAIRE
$(OBJDIR)/test.o: $(TESTDIR)/test.c
	$(CC) -c $< -o $@
$(TESTDIR)/test : $(OBJDIR)/test.o $(OBJDIR)/Tuiles.o $(OBJDIR)/Grille.o $(OBJDIR)/Jeu.o $(OBJDIR)/Affichage.o
	$(CC) -o $@ $^ -lcunit

#DOXYGEN
$(DOCDIR)/doxy : $(DOCDIR)/Doxyfile
	doxygen $<

clean :
	rm -rf $(OBJDIR)/*.o
	rm -rf $(BINDIR)/Honshu
	rm -rf $(TESTDIR)/test
	rm -rf doc/html
	rm -rf doc/latex