#include "pile_ou_file.h"
#include <stdlib.h>
#include <string.h> /* pour memcpy */


struct pile_ou_file {
  int *tab;
  int indice_tete;/**<indice de la tête de la structure */
  int indice_fin;/**<premier indice libre dans la structure */
  enum {PILE=0, FILE=1} file;      /**<0 si le prochain sommet à retirer sera le plus récemment ajouté,
				      1 si ce sera le plus récemment ajouté */
};

pile_ou_file *pile_ou_file_creer(int n)
{
	pile_ou_file *p = malloc(sizeof(pile_ou_file));
	if (!p)
		return NULL;
	p->tab = malloc(n * sizeof(int));
	if (!(p->tab)) {
		free(p);
		return NULL;
	}
	p->indice_tete = p->indice_fin = 0;
	p->file = rand() % 2 ;
	return p;
}

void pile_ou_file_detruire(pile_ou_file *p)
{
	if (p)
		free(p->tab);
	free(p);
}

int pile_ou_file_est_vide(pile_ou_file *p)
{
  return p->indice_tete == p->indice_fin;
}

void pile_ou_file_ajouter(pile_ou_file *p, int sommet)
{
	p->tab[(p->indice_fin)++] = sommet;
}

int pile_ou_file_retirer(pile_ou_file *p)
{
  int sommet ;
  if (p->file)
    sommet = p->tab[p->indice_tete ++];
  else
    sommet = p->tab[-- p->indice_fin];
  p->file = rand() % 2;
  return sommet;
}

int pile_ou_file_choisir(pile_ou_file *p)
{
  p->file = rand() % 2;
  if (p->file)
    return p->tab[p->indice_tete];
  else
    return p->tab[p->indice_fin - 1];
}

int * pile_ou_file_tabint(pile_ou_file *p, int * ptaille)
{
  int taille = p->indice_fin - p->indice_tete;
  if (ptaille) *ptaille = taille;
  if (taille==0) return NULL;
  int * tab = malloc(taille * sizeof(int));
  memcpy(tab, p->tab+p->indice_tete, taille * sizeof(int));
  return tab;
}
