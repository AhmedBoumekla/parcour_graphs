#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graphe-4.h"
#include "graphe_parcours.h"

int main()
{
	graphe *g;
	int n = 12, i;
	int *reprs_cfc;

	g = graphe_creer(n, 1);
	graphe_ajouter_arc(g, 0, 1, 1.0);
	graphe_ajouter_arc(g, 1, 0, 1.0);
	graphe_ajouter_arc(g, 2, 4, 1.0);
	graphe_ajouter_arc(g, 2, 6, 1.0);
	graphe_ajouter_arc(g, 3, 5, 1.0);
	graphe_ajouter_arc(g, 4, 3, 1.0);
	graphe_ajouter_arc(g, 4, 6, 1.0);
	graphe_ajouter_arc(g, 5, 4, 1.0);
	graphe_ajouter_arc(g, 5, 7, 1.0);
	graphe_ajouter_arc(g, 5, 9, 1.0);
	graphe_ajouter_arc(g, 6, 8, 1.0);
	graphe_ajouter_arc(g, 7, 9, 1.0);
	graphe_ajouter_arc(g, 7, 6, 1.0);
	graphe_ajouter_arc(g, 8, 7, 1.0);
	graphe_ajouter_arc(g, 10, 11, 1.0);
	graphe_ajouter_arc(g, 11, 10, 1.0);

	graphe_comp_fort_conn(g, &reprs_cfc);
	for (i = 0; i < n; ++i)
		printf("%d ", reprs_cfc[i]);
	puts("");
	free(reprs_cfc);
	graphe_liberer(g);

	return EXIT_SUCCESS;
}