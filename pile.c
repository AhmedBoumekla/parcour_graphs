#include "pile.h"
#include <stdlib.h>
#include <string.h> /* pour memcpy */

struct pile {
	int *tab;
	int taille;
};

pile *pile_creer(int n)
{
	pile *p = malloc(sizeof(pile));
	if (!p)
		return NULL;
	p->tab = malloc(n * sizeof(int));
	if (!(p->tab)) {
		free(p);
		return NULL;
	}
	p->taille = 0;
	return p;
}

pile *pile_creer_depuis_tabint(int * tab, int taille)
{
  pile * p = pile_creer(taille);
  if (p) {
    memcpy(p->tab, tab, taille * sizeof(int));
    p->taille = taille ;
  }
  return p;
}

int pile_taille(pile *p)
{
  return p->taille ;
}

void pile_detruire(pile *p)
{
	if (p)
		free(p->tab);
	free(p);
}

int pile_est_vide(pile *p)
{
	return p->taille == 0;
}

void pile_empiler(pile *p, int sommet)
{
	p->tab[(p->taille)++] = sommet;
}

int pile_depiler(pile *p)
{
	return p->tab[--p->taille];
}

int pile_sommet(pile *p)
{
	return p->tab[p->taille - 1];
}

int * pile_tabint(pile *p, int * ptaille)
{
  int taille = p->taille;
  if (ptaille) *ptaille=taille;
  if (taille==0)
    return NULL;
  int * tab = malloc(taille * sizeof(int));
  memcpy(tab, p->tab, taille * sizeof(int));
  return tab;
}