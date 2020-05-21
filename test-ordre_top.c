#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graphe-4.h"
#include "graphe_parcours.h"
#include "parcours.h"


int main()
{
	graphe *g;
	int n = 5, i;
	int *ordre_top;

	puts("Premier test :");
	g = graphe_creer(n, 1);
	graphe_ajouter_arc(g, 0, 2, 1.0);
	graphe_ajouter_arc(g, 0, 3, 1.0);
	graphe_ajouter_arc(g, 1, 2, 1.0);
	graphe_ajouter_arc(g, 1, 4, 1.0);
	graphe_ajouter_arc(g, 3, 4, 1.0);

	graphe_ordre_top(g, &ordre_top);
	if (ordre_top == NULL)
		puts("Il y a un circuit dans le graphe.");
	else {
		for (i = 0; i < n; ++i)
			printf("%d ", ordre_top[i]);
		puts("");
	}
	free(ordre_top);
	graphe_liberer(g);
	
	

	puts("Deuxième test :");
	g = graphe_creer(n, 1);
	graphe_ajouter_arc(g, 0, 2, 1.0);
	graphe_ajouter_arc(g, 0, 3, 1.0);
	graphe_ajouter_arc(g, 1, 2, 1.0);
	graphe_ajouter_arc(g, 1, 4, 1.0);
	graphe_ajouter_arc(g, 3, 4, 1.0);
	graphe_ajouter_arc(g, 4, 1, 1.0);

	graphe_ordre_top(g, &ordre_top);
	if (ordre_top == NULL)
		puts("Il y a un circuit dans le graphe.");
	else {
		for (i = 0; i < n; ++i)
			printf("%d ", ordre_top[i]);
		puts("");
	}
	free(ordre_top);
	graphe_liberer(g);
	return EXIT_SUCCESS;
}
