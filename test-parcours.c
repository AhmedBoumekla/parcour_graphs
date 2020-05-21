#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graphe-4.h"
#include "parcours.h"
#include "conteneur_sommets.h"
#include "graphe_parcours.h"

int main()
{
	graphe *g, *arbo;
	int *suff;

	g = graphe_creer(10,1);
	graphe_ajouter_arc(g, 0, 8, 1.0);
	graphe_ajouter_arc(g, 0, 6, 1.0);
	graphe_ajouter_arc(g, 0, 5, 1.0);
	graphe_ajouter_arc(g, 0, 1, 1.0);
	graphe_ajouter_arc(g, 1, 8, 1.0);
	graphe_ajouter_arc(g, 1, 2, 1.0);
	graphe_ajouter_arc(g, 2, 9, 1.0);
	graphe_ajouter_arc(g, 2, 7, 1.0);
	graphe_ajouter_arc(g, 2, 6, 1.0);
	graphe_ajouter_arc(g, 2, 4, 1.0);
	graphe_ajouter_arc(g, 2, 2, 1.0);
	graphe_ajouter_arc(g, 2, 1, 1.0);
	graphe_ajouter_arc(g, 2, 0, 1.0);
	graphe_ajouter_arc(g, 3, 8, 1.0);
	graphe_ajouter_arc(g, 3, 3, 1.0);
	graphe_ajouter_arc(g, 4, 8, 1.0);
	graphe_ajouter_arc(g, 4, 5, 1.0);
	graphe_ajouter_arc(g, 4, 4, 1.0);
	graphe_ajouter_arc(g, 5, 9, 1.0);
	graphe_ajouter_arc(g, 5, 7, 1.0);
	graphe_ajouter_arc(g, 5, 6, 1.0);
	graphe_ajouter_arc(g, 5, 5, 1.0);
	graphe_ajouter_arc(g, 5, 2, 1.0);
	graphe_ajouter_arc(g, 5, 1, 1.0);
	graphe_ajouter_arc(g, 6, 6, 1.0);
	graphe_ajouter_arc(g, 6, 4, 1.0);
	graphe_ajouter_arc(g, 6, 0, 1.0);
	graphe_ajouter_arc(g, 7, 9, 1.0);
	graphe_ajouter_arc(g, 7, 6, 1.0);
	graphe_ajouter_arc(g, 7, 1, 1.0);
	graphe_ajouter_arc(g, 8, 8, 1.0);
	graphe_ajouter_arc(g, 8, 6, 1.0);
	graphe_ajouter_arc(g, 8, 5, 1.0);
	graphe_ajouter_arc(g, 8, 1, 1.0);
	graphe_ajouter_arc(g, 9, 6, 1.0);

	/* Parcours en profondeur d'abord */
	graphe_ecrire_dot(g, "graphe_depart.dot", 0);
	graphe_parcours_profondeur(g, &arbo, &suff, NULL);
	graphe_ecrire_dot(arbo, "parcours_prof.dot", 0);
	free(suff);
	graphe_liberer(arbo);

	/* Parcours en largeur d'abord */
	graphe_parcours_largeur(g, &arbo, &suff, NULL);
	graphe_ecrire_dot(arbo, "parcours_largeur.dot", 0);
	free(suff);
	graphe_liberer(arbo);

	/* Parcours utilisant la structure pile_ou_file */
	graphe_parcours_larg_ou_prof(g, &arbo, &suff, NULL);
	graphe_ecrire_dot(arbo, "parcours_larg_ou_prof.dot", 0);
	free(suff);
	graphe_liberer(arbo);
	graphe_liberer(g);

	return EXIT_SUCCESS;
}