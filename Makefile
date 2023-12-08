aventuraBipartida: aventura-bipartida/exercicio.c lib/utils.c lib/graph.c lib/graph_adjacency_list.c 
	gcc aventura-bipartida/exercicio.c lib/utils.c lib/graph.c lib/graph_adjacency_list.c -o aventuraBipartida -lm

desbravandoCiclos: desbravando-ciclos/exercicio.c lib/utils.c lib/graph.c lib/graph_adjacency_list.c 
	gcc desbravando-ciclos/exercicio.c lib/utils.c lib/graph.c lib/graph_adjacency_list.c -o desbravandoCiclos -lm

conectandoPovoadosDistantes: conectando-povoados-distantes/exercicio.c lib/utils.c lib/graph.c lib/graph_adjacency_list.c
	gcc conectando-povoados-distantes/exercicio.c lib/utils.c lib/graph.c lib/graph_adjacency_list.c -o conectandoPovoadosDistantes -lm

desvendandoMagiaDasConexoes: desvendando-a-magia-das-conexoes/exercicio.c lib/utils.c lib/graph.c lib/graph_adjacency_list.c
	gcc desvendando-a-magia-das-conexoes/exercicio.c lib/utils.c lib/graph.c lib/graph_adjacency_list.c -o desvendandoMagiaDasConexoes -lm

umaJornadaFinal: uma-jornada-final-na-grafolandia/exercicio.c lib/utils.c lib/graph.c lib/graph_adjacency_list.c
	gcc uma-jornada-final-na-grafolandia/exercicio.c lib/utils.c lib/graph.c lib/graph_adjacency_list.c -o umaJornadaFinalNaGrafolandia -lm
