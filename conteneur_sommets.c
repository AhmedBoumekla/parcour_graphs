#include "conteneur_sommets.h"
#include "pile.h"
#include "file.h"
#include "pile_ou_file.h"
#include <stdlib.h>

struct conteneur_sommets {
  void *donnees;
  int (*est_vide)(void *);
  void (*ajouter)(void *, int);
  void (*supprimer)(void *);
  int (*choisir)(void *);
  void (*detruire)(void *);
} ;

/* Partie générique */

int cs_est_vide(conteneur_sommets *cs)
{
  return cs->est_vide(cs->donnees);
}
void cs_ajouter(conteneur_sommets *cs, int sommet)
{
  cs->ajouter(cs->donnees, sommet);
}
void cs_supprimer(conteneur_sommets *cs)
{
  cs->supprimer(cs->donnees);
}
int cs_choisir(conteneur_sommets *cs)
{
  return cs->choisir(cs->donnees);
}

void cs_detruire(conteneur_sommets *cs)
{
  cs->detruire(cs->donnees);
  free(cs);
}


conteneur_sommets *cs_creer(conteneur_sommets * modele)
{
  if (! modele->donnees) return NULL;
  conteneur_sommets * pcs = malloc(sizeof(conteneur_sommets));
  if (!pcs) {
    modele->detruire(modele->donnees);
    return NULL;
  }
  *pcs = *modele;
  return pcs;
}

/* Partie PILE */

conteneur_sommets *cs_creer_pile(int n) /*On veut creer le conteneur de pile*/
{
  conteneur_sommets cs = {.donnees   = pile_creer(n), /*on declare le conteneur qui est egale a la donner qui est une pile puis rempli tout ses champs avec les fonctions correspondant au pile*/
			  .est_vide  = (int (*)(void *))        pile_est_vide,
			  .ajouter   = (void (*)(void *, int))  pile_empiler,
			  .supprimer = (void (*)(void *))       pile_depiler,
			  .choisir   = (int (*)(void *))        pile_sommet,
			  .detruire  = (void (*)(void *))       pile_detruire};
  return cs_creer(&cs);
}

/* Partie FILE */

/*Question 1)
  On veut creer les cs file et pile_ou_file
  En gardant la synthaxe de pile , on remarque qu'on a juste besoin de modifier
  les fonctions correspondante a chaque structure */
conteneur_sommets *cs_creer_file(int n) 
{

   conteneur_sommets cs = {.donnees   = file_creer(n),
        .est_vide  = (int (*)(void *))        file_est_vide, 
			  .ajouter   = (void (*)(void *, int))  file_enfiler,
			  .supprimer = (void (*)(void *))       file_defiler,
			  .choisir   = (int (*)(void *))        file_tete,
			  .detruire  = (void (*)(void *))       file_detruire};
  return cs_creer(&cs);
}


/* Partie PILE_OU_FILE */

conteneur_sommets *cs_creer_pile_ou_file(int n)
{
  /* TODO : à implémenter */
  conteneur_sommets cs = {.donnees   = pile_ou_file_creer(n),
			  .est_vide  = (int (*)(void *))        pile_ou_file_est_vide,
			  .ajouter   = (void (*)(void *, int))  pile_ou_file_ajouter,
			  .supprimer = (void (*)(void *))       pile_ou_file_retirer,
			  .choisir   = (int (*)(void *))        pile_ou_file_choisir,
			  .detruire  = (void (*)(void *))       pile_ou_file_detruire};
  return cs_creer(&cs);
}
