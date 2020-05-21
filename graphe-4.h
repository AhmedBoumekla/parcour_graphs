/**
 * \file graphe-4.h
 * \brief Représentation des graphes par liste de successeurs
 * \version 1
 * \date lundi 30 septembre 2019, 10:04:11 (UTC+0200)
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse

 * Dans cette version :
 * - L'implémentation de la liste de successeurs est
 * réalisée par un tableau *dynamique*, de taille \f$n\f$,
 * où \f$n\f$ est l'ordre du graphe, chaque élément du tableau pointant vers la
 * liste des successeurs du sommet correspondant.
 * - Les graphes sont orientés ou non orientés.
*/

#ifndef GRAPHE_H
#define GRAPHE_H

/* ______________________________________ Structure de données */

/**
 * \brief Maillon de successeur dans un graphe arc/arête-valué
 *
 * Un maillon de successeur est représenté par :
 * un /a sommet (successeur du sommet considéré),
 * une /a valeur (valeur de l'arc ou arête allant du sommet considéré à ce
 * succeseur,
 * un pointeur /a suivant vers le maillon de successeur suivant (NULL s'il n'y
 * en a pas).
 */
typedef struct msuc {
	int sommet; /**< sommet successeur du sommet considéré */
	double valeur;/**< valeur de l'arc ou de l'arête menant du sommet considéré à
					ce successeur */
	struct msuc *suivant;/**< pointeur vers le prochain successeur (NULL s'il
						   n'y en a pas). */
} msuc;

/** \brief retourne le pointeur vers le maillon suivant
 * \param m adresse du maillon de successeur à lire
 * \return l'adresse du prochain maillon de successeur (NULL s'il n'y en a pas).
 */
msuc *msuc_suivant(msuc *m);

/** \brief retourne le sommet successeur du sommet considéré
 * \param m adresse du maillon de successeur à lire
 * \return le sommet successeur du sommet considéré.
 */
int msuc_sommet(msuc *m);
/** \brief retourne la valeur de l'arête ou de l'arc menant du sommet considéré
 * au sommet successeur.
 * \param m adresse du maillon de successeur à lire
 * \return la valeur de l'arête ou de l'arc menant du sommet considéré au sommet
 * successeur.
 */
double msuc_valeur(msuc *m);


/**
 * \brief Graphe orienté ou non orienté représenté par sa liste de successeurs.
 *
 * Un graphe est ici représenté par son nombre de sommets \a n
 * et un tableau de pointeurs vers des maillons de successeurs (tableau dynamique de n pointeurs) \a tab_sucs.
 *
 * L'ensemble des sommets du graphe est alors \f$\{0, 1, 2, \ldots, n-1\}\f$.
 *
 * Le champ \a m est le nombre d'arêtes et est mis à jour par les fonctions de
 * manipulation.
 *
 * Le champ \a est_or vaut 0 si le graphe n'est pas orienté, autre chose sinon.
 */
struct s_graphe {
	int n;/**< nombre de sommets du graphes (doit être >=0) */
	int m;/**< nombre d'arêtes du graphes */
	msuc **tab_sucs; /* tableau de pointeurs vers les listes de successeurs du graphe */
	int est_or;/** <0 si le graphe n'est pas orienté, autre chose sinon. */
};
typedef struct s_graphe graphe;

/* ______________________________________ Constructeur et destructeur */

/**
 * \brief Alloue de la mémoire pour un graphe et son tableau de listes de
 * successeurs à
 * \a n sommets, et l'initialise en un graphe sans arc ou arête.
 * \param g adresse d'une variable de type graphe *existante*
 * \param n ordre du graphe
 * \param est_or 0 si le graphe n'est pas orienté, autre chose sinon
 * \return l'adresse d'une nouvelle variable de type graphe
 * si l'allocation de mémoire a réussi, NULL sinon.
*/
graphe *graphe_creer(int n, int est_or);

/**
 * \brief Libère toute la mémoire associée au graphe g, créé par la fonction
 * graphe_creer (ne fait rien si le paramètre est NULL).
 */
void graphe_liberer(graphe *g);

/**
 * \brief ALLOUE de la mémoire pour le tableau des listes de successeurs
 * \a n, et l'initialise le graphe en un graphe sans arc ou arête.
 * \param g adresse d'une variable de type graphe *existante*
 * \param n ordre du graphe
 * \param est_or 0 si le graphe n'est pas orienté, autre chose sinon
 * \return -1 si l'allocation mémoire a échoué, -2 si \a n est négatif, 0 sinon.
 *
 * Cette fonction est DEPRECIEE et n'est présente que par soucis de
 * compatibilité avec les versions précédentes.
 * Il vaut mieux utiliser graphe_creer.
*/
int graphe_stable(graphe* g, int n, int est_or);

/**
 * \brief Libère la zone mémoire occupée par un graphe.
 * \param g pointeur vers un graphe
 *
 * Si g->tab_sucs est le pointeur NULL, ne fait rien.
 *
 * Cette fonction est DEPRECIEE (car à utiliser en association avec
 * graphe_stable).
 * En cas d'initialisation avec graphe_creer, il faut utiliser graphe_liberer.
 */
void graphe_detruire(graphe *g);

/* ______________________________________ Ajout / Suppression d'arêtes */

/**
 * \brief Ajoute un arc entre deux sommets dans le graphe orienté
 * \param g adresse de la variable graphe à modifier
 * \param v une extrémité de l'arête (entre 0 et n - 1)
 * \param w une extrémité de l'arête (entre 0 et n - 1)
 * \param val valeur de l'arc ajouté
 * \return 0 en cas de succès, -1 si l'allocation du nouveau maillon a échoué.
 *
 * En dehors des fonctions internes à la bibliothèque, cette fonction ne devrait
 * pas être utilisée sur des graphes non orientés.
 */
int graphe_ajouter_arc(graphe *g, int v, int w, double val);

/**
 * \brief Ajoute une arête entre deux sommets dans le graphe non orienté
 * \param g adresse de la variable graphe à modifier
 * \param v une extrémité de l'arête (entre 0 et n - 1)
 * \param w une extrémité de l'arête (entre 0 et n - 1)
 * \param val valeur de l'arc ajouté
 * \return 0 en cas de succès, -1 si l'allocation du ou des nouveau(x)
 * maillon(s) a échoué.
 *
 * cette fonction ne devrait pas être utilisée sur des graphes orientés.
 */
int graphe_ajouter_arete(graphe* g, int v, int w, double val);

/**
 * \brief Supprime un arc entre deux sommets dans le graphe orienté
 * \param g adresse de la variable graphe à modifier
 * \param v extrémité initiale de l'arête (entre 0 et n - 1)
 * \param w extrémité terminale de l'arête (entre 0 et n - 1)
 * \param val valeur de l'arc à supprimer
 * \return -1 si l'arc ne peut être supprimée (n'existe pas), 0 sinon
 *
 * En dehors des fonctions internes à la bibliothèque, cette fonction ne devrait
 * pas être utilisée sur des graphes non orientés.
 */
int graphe_supprimer_arc(graphe *g, int v, int w, double val);

/**
 * \brief Supprime une arête entre deux sommets dans le graphe orienté
 * \param g adresse de la variable graphe à modifier
 * \param v une extrémité de l'arête (entre 0 et n - 1)
 * \param w une extrémité de l'arête (entre 0 et n - 1)
 * \param val valeur de l'arete à supprimer
 * \return -1 si l'arc ne peut être supprimée (n'existe pas), 0 sinon
 *
 * Cette fonction ne devrait pas être utilisée sur des graphes non orientés.
 */
int graphe_supprimer_arete(graphe* g, int v, int w, double val);

/* ______________________________________ Accesseurs en lecture */


/**
 * \brief Retourne 1 si le graphe est orienté, 0 sinon
 * \param g adresse de la variable graphe à lire
 * \return 1 si le graphe est orienté, 0 sinon
 */
int graphe_est_or(graphe *g);

/**
 * \brief Retourne l'ordre du graphe.
 * \param g adresse de la variable graphe à lire
 * \return le nombre de sommets du graphe
 */
int graphe_get_n(graphe* g);

/**
 * \brief Retourne le nombre d'arêtes du graphe.
 * \param g adresse de la variable graphe à lire
 * \return le nombre d'arêtes du graphe
 */
int graphe_get_m(graphe* g);

/** \brief retourne l'adresse du premier maillon de successeur de la liste de
 * successeurs du sommet \a v dans le graphe d'adresse \a g
 * \param g adresse de la variable graphe à modifier
 * \param v sommet (entre 0 et n - 1) dont on veut parcourir la liste des
 * successeurs
 * \return l'adresse du premier maillon de successeur de la liste de
 * successeurs du sommet \a v dans le graphe d'adresse \a g
 */
msuc *graphe_get_prem_msuc(graphe *g, int v);

/**
 * \brief Retourne le nombre de fois qu'une arete est présente entre deux
 * sommets donnés.
 * \param g adresse de la variable graphe à lire
 * \param v une extrémité de l'arête (entre 0 et n - 1)
 * \param w une extrémité de l'arête (entre 0 et n - 1)
 * \return le nombre d'arêtes entre les sommets \a v et \a w
 *
 * Ne devrait pas être utilisée sur un graphe orienté.
 */
int graphe_get_multiplicite_arete(graphe* g, int v, int w);

/**
 * \brief Retourne le nombre de fois qu'un arc est présente entre deux
 * sommets donnés.
 * \param g adresse de la variable graphe à lire
 * \param v extrémité initiale de l'arête (entre 0 et n - 1)
 * \param w extrémité terminale de l'arête (entre 0 et n - 1)
 * \return le nombre d'arêtes entre les sommets \a v et \a w
 *
 * Ne devrait pas être utilisée sur un graphe non orienté.
 */
int graphe_get_multiplicite_arc(graphe* g, int v, int w);

/* NE PAS ACCÉDER DIRECTEMENT AUX CHAMPS EN-DESSOUS DE CETTE LIGNE */


/**
 * \brief Retourne le degré sortant d'un sommet
 * \param g adresse de la variable graphe à lire
 * \param v sommet du graphe
 * \return le nombre d'arcs ou arêtes d'extrémité initiale \a v.
 */
int graphe_get_degre_sortant(graphe* g, int v);

/**
 * \brief Retourne le degré entrant d'un sommet
 * \param g adresse de la variable graphe à lire
 * \param v sommet du graphe
 * \return le nombre d'arcs ou arêtes d'extrémité terminale \a v.
 */
int graphe_get_degre_entrant(graphe* g, int v);

/**
 * \brief Retourne le degré d'un sommet.
 * \param g adresse de la variable graphe à lire
 * \param v sommet du graphe (entre 0 et n - 1)
 * \return le degré du sommet v dans le graphe
 */
int graphe_get_degre(graphe* g, int v);

/* ______________________________________ Entrées / Sorties */

/**
 * \brief Affiche sur la sortie standard les données d'un graphe
 * \param g adresse de la variable graphe à lire
 *
 * Affiche le nombre de sommets, d'arêtes, le caractère orienté ou non et les
 * listes de successeurs dans le graphe d'adresse \a g
 */
void graphe_afficher(graphe* g);

/**
 * \brief Écrit le graphe au format dot dans un fichier.
 * \param g adresse de la variable graphe à lire
 * \param nom_fichier nom du fichier à écrire
 * \param ecrire_valeurs 0 si l'on ne veut pas de l'affichage des valeurs des
 * arcs ou arêtes, autre chose sinon
 * \return 0 si l'écriture du fichier a réussi, -1 sinon
 */
int graphe_ecrire_dot(graphe *g, char *nom_fichier, int ecrire_valeurs);

/* ______________________________________ Autres fonctions d'initialisation */
/**
 * \brief Crée un graphe d'ordre
 * \a n, et l'initialise en un graphe simple complet
 * \param n ordre du graphe
 * \param est_or caractère orienté du graphe
 * \return NULL si l'allocation de mémoire pour le graphe a échoué,
 * un pointeur vers le nouveau graphe complet sinon
*/
graphe *graphe_complet(int n, int est_or);

/**
 * \brief Crée un graphe d'ordre
 * \a n, et l'initialise en un graphe simple aléatoire d'ordre \a n, où chaque arête
 * est, de façon indépendante, présente avec probabilité \a p.
 * \param g adresse d'une variable de type graphe *existante*
 * \param n ordre du graphe
 * \param p probabilité de présence de chaque arête
 * \param est_or caractère orienté ou non du graphe
 * \return NULL en cas de problème, un pointeur vers ce nouveau graphe aléatoire
 * sinon
 */
graphe *graphe_aleatoire(int n, double p, int est_or);

#endif
