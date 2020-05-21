/**
 * \file parcours.h
 * \brief parcours générique d'un graphe représenté par des listes de
 * successeurs
 * \version 1
 * \date mer. 20 nov. 2019 11:35:37 CET
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 */

#ifndef PARCOURS_H
#define PARCOURS_H

#include "graphe-4.h"
#include "conteneur_sommets.h"
#include "file.h"
#include "pile.h"

/**
 * \brief Structure parcours contenant des données utiles pendant et à la fin
 * d'un parcours générique
 */
struct parcours 
{ 
  graphe *g; /*graphe en lecture*/
  conteneur_sommets *conteneur;/*conteneur pour faire le parcours*/  
  graphe *arbo;/* Graphe du resultat du parcours*/
  int *prio;/*liste des priorité lors du parcours*/
  int *prefixe;/*tableau des prefixe contenant les sommets ajoute au fur et a mesure*/
  int *suffixe;/*tableau des suffixe contenant les sommets ajoute au fur et a mesure*/
  int *est_visite;/*tableau des sommets visite*/
  int *est_explore;/*tableau des sommets explorés*/
  int *cfc;/*tableau fortement connexe*/
  int *distance;
  int arc_arriere;/*variable 0 ou 1 si le graphe possede un arc arriere*/
  int i;/* Variable permettant de stocker l'index du prefixe*/
  int j;/* Variable permettant de stocker l'index du suffixe*/
  int est_fini;
};
typedef struct parcours parcours;
/**
 * \brief Alloue de la mémoire pour une structure de parcours générique et
 * l'initialise de façon à pouvoir commencer un parcours sur un graphe, à l'aide
 * d'un conteneur de sommets donné et avec des priorités données pour les
 * racines.
 * \param g adresse du graphe (en lecture) dont on compte (par la suite)
 * faire le parcours
 * \param cs adresse du conteneur de sommets utilisé pour le parcours
 * \param prio tableau de priorités pour le choix des racines pendant le
 * parcours. Si ce paramètre est NULL, la priorité est par défaut 0, 1, 2, ...
 */
struct parcours *pc_init(graphe *g, conteneur_sommets *cs, int *prio);

/**
 * \brief Libère la mémoire associée à un parcours (ne fait rien si le paramètre
 * est NULL).
 */
void pc_detruire(struct parcours *p);

/**
 * \brief Choisit la prochaine racine du parcours en tenant compte des priorités
 * pour les choix des racines dans le parcours.
 */
int pc_choisir_racine(struct parcours *p);

/**
 * \brief Retourne 1 si le parcours est terminé (tous les sommets sont explorés)
 * et 0 sinon.
 */
int pc_est_fini(struct parcours *p);

/**
 * \brief Marque le sommet \a sommet comme étant visité.
 */
void pc_marquer_comme_visite(struct parcours *p, int sommet);

/**
 * \brief Marque le sommet \a sommet comme étant visité lors d'un parcours depuis
 * la racine \a depuis.
 */
void pc_marquer_comme_visite_depuis(struct parcours *p, int sommet, int depuis);

/**
 * \brief Marque le sommet \a sommet comme étant exploré.
 */
void pc_marquer_comme_explore(struct parcours *p, int sommet);
/**
 * \brief Etat du conteneur
 * \return 1 si le conteneur est vide, 0 sinon.
 */
int pc_conteneur_est_vide(struct parcours *p);
/**
 * \brief Ajoute le sommet \a sommet au conteneur de sommets
 */
void pc_ajouter_dans_conteneur(struct parcours *p, int sommet);
/**
 * \brief Choisit un sommet dans le conteneur de sommets,
 * selon les règles de ce conteneur.
 * \return le sommet choisi.
 */
int pc_choisir_dans_conteneur(struct parcours *p);
/**
 * \brief Supprime du conteneur le dernier sommet choisi.
 */
void pc_supprimer_du_conteneur(struct parcours *p);

/**
 * \brief choisit dans la liste de ses successeurs le prochain maillon de
 * successeur du sommet \a sommet.
 *
 * Cette fonction sert à s'assurer qu'on ne parcourt
 * la liste des successeur d'un sommet
 * qu'une et une seule fois.
 */
msuc *pc_prochain_msuc(struct parcours *p, int sommet);
/**
 * \brief Indique si le sommet \a sommet a déjà été visité
 * \return 1 si oui, 0 sinon.
 */
int pc_est_visite(struct parcours *p, int sommet);

/** \brief Parcourt le graphe en prenant le sommet \a r comme racine du
 * parcours et en s'arrêtant lorsque tous les sommets accessibles depuis \a r
 * sont parcourus.
 *
 * Pré-condition : le conteneur de sommets associé au parcours doit être vide à
 * l'appel de cette fonction.
 * Pré-condition : le conteneur de sommets associé au parcours est vide après
 * l'appel de cette fonction.
 */
void pc_parcourir_depuis_sommet(struct parcours *p, int r);

/** \brief Parcourt entièrement le graphe associé à \a p.
 *
 * Les priorités pour le choix des racines sont données par le tableau \a prio
 * renseigné à l'appel de \a pc_init.
 */
void pc_parcourir(struct parcours *p);
#endif
