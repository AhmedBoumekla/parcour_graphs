/**
 * \file graphe-4.c
 * \brief Représentation des graphes par liste de successeurs
 * \version 1
 * \date lundi 30 septembre 2019, 10:04:11 (UTC+0200)
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
*/
#include "graphe-4.h"
#include "parcours.h"
#include "conteneur_sommets.h"

#include <stdio.h>
#include <stdlib.h>

/* __________________________________ Accesseurs sur les maillons */
msuc *msuc_suivant(msuc *m)
{
	return !m ? NULL : m->suivant;
}

int msuc_sommet(msuc *m)
{
	return m->sommet;
}

double msuc_valeur(msuc *m)
{
	return m->valeur;
}


/* __________________________________ Initialisation / Destruction */

graphe *graphe_creer(int n, int est_or)
{
	graphe *g = malloc(sizeof(graphe));
	if (!g)
		return NULL;
	if (graphe_stable(g, n, est_or) < 0) {
		free(g);
		return NULL;
	}
	return g;
}

void graphe_liberer(graphe *g)
{
	if (g) {
		graphe_detruire(g);
		free(g);
	}
}

int graphe_stable(graphe *g, int n, int est_or)
{
	if (n < 0)
		return -2;
	g->tab_sucs = calloc(n, sizeof(msuc *));
	if (!(g->tab_sucs)) {
		perror("calloc");
		return -1;
	}
	g->n = n;
	g->m = 0;
	g->est_or = est_or;
	return 0;
}

void graphe_detruire(graphe *g)
{
	int i;
	msuc *m, *suiv;
	if (!(g->tab_sucs))
		return;
	for (i = 0; i < g->n; ++i) {
		m = g->tab_sucs[i];
		while (m) {
			suiv = msuc_suivant(m);
			free(m);
			m = suiv;
		}
	}
	free(g->tab_sucs);
}
/* __________________________________ Ajout / Suppression d'arêtes */

/* Attention :
 * Si le graphe est orienté, utiliser les fonctions _arc
 * Si le graphe est non orienté, utiliser les fonction _arete
 */

int graphe_ajouter_arc(graphe *g, int v, int w, double val)
{
	msuc *m = malloc(sizeof(*m));
	if (!m) {
		perror("malloc");
		return -1;
	}

	m->sommet = w;
	m->valeur = val;
	m->suivant = g->tab_sucs[v];
	g->tab_sucs[v] = m;
	++(g->m);
	return 0;
}

int graphe_supprimer_arc(graphe *g, int v, int w, double val)
{
	msuc *m = graphe_get_prem_msuc(g, v);
	msuc *prec = NULL;
	while (m) {
		if (msuc_sommet(m) == w && msuc_valeur(m) == val) {
			if (!prec)
				g->tab_sucs[v] = msuc_suivant(m);
			else
				prec->suivant = msuc_suivant(m);
			free(m);
			--(g->m);
			return 0;
		}
		prec = m;
		m = msuc_suivant(m);
	}
	return -1;
}

int graphe_ajouter_arete(graphe* g, int v, int w, double val)
{
	int stat;
	stat = graphe_ajouter_arc(g, v, w, val);
	if (stat < 0)
		return -1;
	if (v != w) {
		stat = graphe_ajouter_arc(g, w, v, val);
		if (stat < 0) {
			graphe_supprimer_arc(g, v, w, val);
			return -1;
		}
		--(g->m); /* ajouter_arc incrémente le nombre d'aretes */
	}
	return 0;
}

int graphe_supprimer_arete(graphe* g, int v, int w, double val)
{
	int stat;
	stat = graphe_supprimer_arc(g, v, w, val);
	if (stat < 0)
		return -1;
	if (v != w) {
		graphe_supprimer_arc(g, w, v, val);
		++(g->m); /* supprimer_arc décrémente le nombre d'aretes */
	}
	return 0;
}

/* ______________________________________ Accesseurs en lecture */
int graphe_est_or(graphe *g)
{
	return g->est_or;
}

int graphe_get_n(graphe* g)
{
	return g->n;
}

int graphe_get_m(graphe* g)
{
	return g->m;
}

int graphe_get_multiplicite_arc(graphe* g, int v, int w)
{
	int res = 0;
	msuc *m;
	for (m = graphe_get_prem_msuc(g, v); m; m = msuc_suivant(m))
		res += (msuc_sommet(m) == w);
	return res;
}

int graphe_get_multiplicite_arete(graphe* g, int v, int w)
{
	return graphe_get_multiplicite_arc(g, v, w);
}

msuc *graphe_get_prem_msuc(graphe *g, int v)
{
	return g->tab_sucs[v];
}
/* NE PAS ACCÉDER DIRECTEMENT AUX CHAMPS EN-DESSOUS DE CETTE LIGNE */

int graphe_get_degre_sortant(graphe* g, int v)
{
	int deg = 0;
	msuc *m;
	for (m = graphe_get_prem_msuc(g, v); m; m = msuc_suivant(m))
		++deg;
	return deg;
}

int graphe_get_degre_entrant(graphe* g, int w)
{
	int deg =0;
	int v;
	/* c'est terrible, mais on n'y peut rien, sauf à maintenir aussi une
	 * liste de prédécesseurs */
	for (v = 0; v < graphe_get_n(g); ++v)
		deg += graphe_get_multiplicite_arc(g, v, w);
	return deg;
}

int graphe_get_degre(graphe *g, int v)
{
	if (graphe_est_or(g))
		return graphe_get_degre_entrant(g, v) +
			graphe_get_degre_sortant(g, v);
	return graphe_get_degre_entrant(g, v) +
		graphe_get_multiplicite_arete(g, v, v);
}

/* ______________________________________ Entrées / Sorties */

void graphe_afficher(graphe* g)
{
	int v, w;
	msuc *m;
	int n = graphe_get_n(g);
	printf("graphe %s d'ordre %d à %d aretes :\n",
		graphe_est_or(g) ? "orienté" : "non orienté",
		graphe_get_n(g), graphe_get_m(g));
	for (v = 0; v < n; ++v) {
		printf("successeurs de %d : ",v);
		for (m = graphe_get_prem_msuc(g, v); m; m = msuc_suivant(m)) {
			w = msuc_sommet(m);
			printf("%2d, ", w);
		}
		puts("");
	}
}

int graphe_ecrire_dot(graphe *g, char *nom_fichier, int ecrire_valeurs)
{
	int u;
	int n = graphe_get_n(g);
	FILE *f = fopen(nom_fichier, "w");
	int est_or = graphe_est_or(g);
	msuc *m;
	if (!f) { perror("fopen"); return -1; }

	if (est_or)
		fputs("digraph {\n", f);
	else
		fputs("graph {\n", f);

	for (u = 0; u < n; ++u)
		fprintf(f, "\t%d;\n", u);
	fputs("\n", f);

	for (u = 0; u < n; ++u)
		for (m = graphe_get_prem_msuc(g, u); m; m = msuc_suivant(m)) {
			int v = msuc_sommet(m);
			double val = msuc_valeur(m);
			if (!est_or && v < u) /* arête déjà rencontrée */
				continue;
			fprintf(f, "\t%d -%c %d ",
					u, est_or ? '>' : '-', v);
			if (ecrire_valeurs)
				fprintf(f, " [label = %.2f]", val);
			fprintf(f, ";\n");
		}
	fputs("}\n", f);

	fclose(f);
	return 0;
}

/* ______________________________________ Autres fonctions d'initialisation */

graphe *graphe_complet(int n, int est_or)
{
	int v, w;
	graphe *g = graphe_creer(n, est_or);
	if (!g)
		return NULL;
	for (v = 0; v < graphe_get_n(g); ++v)
		if (est_or) {
			for (w = v + 1; w < graphe_get_n(g); ++w)
				if (graphe_ajouter_arete(g, v, w, 0.) < 0) {
					graphe_liberer(g);
					return NULL;
				}
		} else {
			for (w = 0; w < graphe_get_n(g); ++w)
				if (graphe_ajouter_arc(g, v, w, 0.) < 0) {
					graphe_liberer(g);
					return NULL;
				}
		}
	return g;
}

graphe *graphe_aleatoire(int n, double p, int est_or)
{
	int v, w;
	graphe *g = graphe_creer(n, est_or);
	if (!g)
		return NULL;
	if (p < 0 || p > 1) {
		graphe_liberer(g);
		return NULL;
	}
	if (!est_or) {
		for (v = 0; v < graphe_get_n(g); ++v)
			for (w = v + 1; w < graphe_get_n(g); ++w)
				if ((double) rand()/RAND_MAX < p)
					if (graphe_ajouter_arete(g, v, w, 0.) < 0) {
						graphe_liberer(g);
						return NULL;
					}
	} else {
		for (v = 0; v < graphe_get_n(g); ++v)
			for (w = 0; w < graphe_get_n(g); ++w)
				if ((double) rand()/RAND_MAX < p)
					if ( graphe_ajouter_arc(g, v, w, 0.) < 0) {
						graphe_liberer(g);
						return NULL;
					}
	}
	return g;
}

