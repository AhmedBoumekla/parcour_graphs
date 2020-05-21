#include "file.h"
#include <stdlib.h>
#include <string.h> /* pour memcpy */

struct file {
	int *tab;
	int indice_fin;/**<indice de la tête de la structure */
	int indice_tete;/**<premier indice libre dans la structure */
};

file *file_creer(int n)
{
	file *f = malloc(sizeof(file));
	if (!f)
		return NULL;
	f->tab = malloc(n * sizeof(int));
	if (!(f->tab)) {
		free(f);
		return NULL;
	}
	f->indice_fin = 0;
	f->indice_tete = 0;
	return f;
}

file *file_creer_depuis_tabint(int * tab, int taille)
{
  file * f = file_creer(taille);
  if (f) {
    memcpy(f->tab, tab, taille * sizeof(int));
    f->indice_fin = taille ;
  }
  return f;
}

int file_taille(file * f)
{
  return f->indice_fin - f->indice_tete;
}

void file_detruire(file *f)
{
	if (f)
		free(f->tab);
	free(f);
}

int file_est_vide(file *f)
{
	return f->indice_fin == f->indice_tete;
}

void file_enfiler(file *f, int sommet)
{
	f->tab[(f->indice_fin)++] = sommet;
}

int file_defiler(file *f)
{
	return f->tab[f->indice_tete++];
}

int file_tete(file *p)
{
	return p->tab[p->indice_tete];
}

int * file_tabint(file *p, int * ptaille)
{
  int taille = p->indice_fin - p->indice_tete;
  if (ptaille) *ptaille = taille;
  if (taille==0)
    return NULL;
  int * tab = malloc(taille * sizeof(int));
  memcpy(tab, p->tab+p->indice_tete, taille*sizeof(int));
  return tab;
}