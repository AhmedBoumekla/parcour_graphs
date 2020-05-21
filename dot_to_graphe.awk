#! /usr/bin/awk -f

BEGIN {
	max_v = 0;
	oriente = 0;
}
NR == 1 {
	if ($1 == "digraph") {
		oriente = 1;
	} else {
		oriente = 0;
	}
}
NF == 1 {
	max_v = max_v < $1 ? $1 : max_v;
}
NF == 0 {
	++max_v;
	print "g = graphe_creer(" max_v "," oriente ")" ";";
}
NF > 2 {
	if (oriente) {
		printf("graphe_ajouter_arc(g, %d, %d, 1.0);\n", $1, $3);
	} else {
		printf("graphe_ajouter_arete(g, %d, %d, 1.0);\n", $1, $3);
	}
}
