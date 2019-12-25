#!/usr/bin/python

import networkx as nx
import numpy as np
from networkx.generators.random_graphs import erdos_renyi_graph
import matplotlib.pyplot as plt


n=20000

p=0.001290309

g=erdos_renyi_graph(n,p)

##nx.draw(g, with_labels=True)
##plt.show()

file1 = open(str(n)+"_sp"+"_nodes.txt","w+")
for (i,j) in g.edges:
    file1.write(str(j)+" "+str(i)+"\n")
file1.close()


