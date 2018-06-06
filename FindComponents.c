//Nevan Samadhana
//SID:1539153
//pa5
//FindComponents.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"
#define MAX_LEN 100

int main(int argc, char* argv[]){
  int n=0, counter=0;
  int var1, var2;
  FILE *in, *out;
  //check command line for correct number of arguments
  if( argc != 3 ){
     printf("Usage: %s <input file> <output file>\n", argv[0]);
     exit(1);
  }

  in = fopen(argv[1],"r");
  out = fopen(argv[2], "w");

  if( in==NULL || out == NULL ){
     printf("Error: one or both files are invalid\n");
     exit(1);
  }

  fscanf(in, "%d", &n); //Read amount of vertices
  Graph graph = newGraph(n); //Make a graph with n vertices

  while(fscanf(in, "%d %d", &var1, &var2)!=EOF){ //While not at the end of the file
    if(var1==0 && var2==0){ //If the values are 0 and 0, break because you have hit the marker
      break;
    }
    addArc(graph, var1, var2); //Add the edges of each vertice
  }

  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, graph); //Print the adjacency list of G
  fprintf(out, "\n"); //Print a new line


  List test = newList(); //New list that represents components
  for(int i=1;i<=getOrder(graph);i++){
    append(test, i);
  }

  DFS(graph,test); //Run DFS on the original graph
  Graph flip = transpose(graph); //Transpose the graph
  DFS(flip,test); //Run DFS on the transpose

  int amount = 0;
  for(int i=1; i<=length(test);i++){ //Loop to find amount of strongly connected components
    if(getParent(flip, i)==NIL){ //If the parent is NIL, increment amount
      amount++;
    }
  }

  List returned = SCC(flip,test ); //List that is now the strongly connected components
  //printList(stdout, returned);
  fprintf(out, "\n");
  fprintf(out, "G contains %d strongly connected components: \n", amount);
  clear(test);

  moveBack(returned); //Place the cursor at the end of the list of scc's
  while(index(returned)!=-1){ //Go throughout the list
    int val = get(returned);
    prepend(test, val);
    if(getParent(flip,val)==NIL){ //If the parent is NIL,
      counter++;
      fprintf(out, "Component %d: ", counter);
      printList(out, test); //Print out the list
      fprintf(out, "\n");
      clear(test); //Clear the list in preparation for the next SCC
    }
    movePrev(returned);
  }



  fclose(in); //Close the files
  fclose(out);
  freeGraph(&graph);
  freeGraph(&flip);
  freeList(&returned);
  freeList(&test);
  graph=NULL;
  return(0);
}
