Calculating Betweness Centrality of undirected graph using floyd warshall and bfs algorithm.

File Structure :

files/dn	-	dense graphs

files/sp	-	Sparse graphs

files/nc	-	not connected graphs, large component

graph_generate  -	Code to generate random graph using Erdos Renyl Model


How to run :

1) Fix n value at line 16 in client.c .

	Input files :
   -	Fix input filename as files/ at line 146 of method initfloyd() in impl.c .
   -	Fix input filename as files/ at line 197 of method initbfs() in impl.c .

	Output files :
   -	Add _floyd before .txt of filename at line 172 of method initfloyd() for output file in impl.c.
   -	Add _bfs before .txt of filename at line 246 of method initbfs() for output file in impl.c.


2) For Floyd, press 1.
	 method - void floyd(int n) in impl.c
3) For bfs, press 2.
   method - void bfs(int vert)

   Result will be generated in respective file paths, and time taken will be s

4) For not connected graph
	
	Step 1 : run first connect.c using to generate largest component
		 
	gcc connect.c -o connect
		 
	./connect.c
	
	Step 2	: run makefile for the largest component obtained through
	          
	connect.c
	
	Step 3	: Merge data of connect.c and makefile using
		  
	gcc mergedata.c -o merge
		  
	./merge

5) For Generating plots
	
	run graph_plot.py
	
	press 1 for sparse graph
	
	press 2 for dense graph
