//Nevan Samadhana
//SID:1539153
//pa5
//Graph.c
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

//Structs------------------
typedef struct GraphObj{
  int order; //number of vertices
  int size; //number of edges
  int label;
  List *neighbour;
  int *color;
  int *parent;
  int *distance;
  int *discover;
  int *finish;
} GraphObj;

//Constructor for a graph
Graph newGraph(int n){
  int i;
  Graph nGraph = malloc(sizeof(GraphObj));
  nGraph->order = n; //Set number of vertices to n
  nGraph->size = 0; //Set number of edges to 0
  nGraph->label = 0;
  nGraph->neighbour = calloc(n+1,sizeof(List)); //Calloc memory for each array
  nGraph->color = calloc(n+1, sizeof(int));
  nGraph->parent = calloc(n+1, sizeof(int));
  nGraph->distance = calloc(n+1, sizeof(int));
  nGraph->discover = calloc(n+1, sizeof(int));
  nGraph->finish = calloc(n+1, sizeof(int));
  for(i=1;i<n+1;i++){
    nGraph->neighbour[i] = newList(); //Populate each indice of the array with an empty List
    nGraph->color[i] = 0;
    nGraph->parent[i] = NIL;
    nGraph->distance[i] = INF;
    nGraph->discover[i] = UNDEF;
    nGraph->finish[i] = UNDEF;
  }
  return nGraph;
}

void freeGraph(Graph* pG){//Frees memory associated with a graph
  int i;
  for(i=1; i<(*pG)->order+1;i++){
    freeList(&(*pG)->neighbour[i]);
  }
  free((*pG)->color); //Free up memory of the arrays
  free((*pG)->parent);
  free((*pG)->discover);
  free((*pG)->finish);
  free((*pG)->neighbour);
  free(*pG);
  *pG = NULL;
}

//Returns the number of vertices
int getOrder(Graph G){
    return(G->order);
}

//Returns the number of edges
int getSize(Graph G){
    return(G->size);
}

//Returns the source
int getSource(Graph G){
  if(G->label==0){
    return NIL;
  }else{
    return(G->label);
  }
}

//Returns the discover time of a vertex
int getDiscover(Graph G, int u){
  if(1<=u && u<=getOrder(G)){
    return(G->discover[u]);
  }else{
    printf("getDiscover() called with invalid argument");
    exit(1);
  }
}

//Returns the finish time of a vertex
int getFinish(Graph G, int u){
  if(1<=u && u<=getOrder(G)){
    return(G->finish[u]);
  }else{
    printf("getFinish() called with invalid argument");
    exit(1);
  }
}


//Returns parent of a vertex
int getParent(Graph G, int u){
  if(1<=u && u<=getOrder(G))
  {
    return(G->parent[u]);
  }else{
    printf("Calling getParent() with invalid arguments");
    exit(1);
  }
}

//Returns distance from the source to vertex
int getDist(Graph G, int u){
  if(1>u || u>getOrder(G)){//Checks preconditions
    printf("getDist() called with invalid argument");
    exit(1);
  }else{
    if(getSource(G)==0){
      return INF;
    }else{
      return(G->distance[u]);
    }
  }
}

//Returns the shortest path from the source to vertex u
void getPath(List L, Graph G, int u){ //Employs same recursive logic as printPath()
  if(getSource(G)!=NIL && 1<=u && u<=getOrder(G)){
    if(G->label==u){ //If at the source, append the source and finish/BASE CASE
      append(L,u);
    }else if(G->parent[u]==NIL){ //If no parent exists
      append(L,NIL);
    }else{
      getPath(L,G,getParent(G,u)); //If a parent exists, and parent is not the source, recursive call to getPath
      append(L,u);
    }
  }else{
    printf("getPath() called with either invalid graph or vertex");
    exit(1);
  }
}


//Manipulation processes--------------
void addEdge(Graph G, int u, int v){
  if(u<1 || u>getOrder(G) || v<1|| v>getOrder(G)){//Check preconditions
    printf("Calling addEdge() with invalid vertices.");
    return;
  }
  List A = G->neighbour[u]; //
  List B = G->neighbour[v];
  moveFront(A); //Place the cursor at the front
  for(int i=0;i<=length(A);i++){ //Iterate through each adjacent neighbour contained in the list
    if(index(A)==-1){ //If at the end of the list or list is empty, append
      append(A,v);
      break;
    }else if(get(A)>v){ //If the neighbour is larger, insert before
      insertBefore(A,v);
      break;
    }
    moveNext(A); //Move to the next neighbour
  }

  moveFront(B); //Perform the exact same algorithm for B
  for(int i=0;i<=length(B);i++){
    if(index(B)==-1){
      append(B,u);
      break;
    }else if(get(B)>u){
      insertBefore(B,u);
      break;
    }
    moveNext(B);
  }
  G->size++;
}

//Adds a directed edge from u to v
void addArc(Graph G, int u, int v){
  if(1<=u && u <= getOrder(G) && 1<=v && v<= getOrder(G)){
    List A = G->neighbour[u]; //Exact same code as addEdge(), but only on one side
    moveFront(A);
    for(int i=0;i<=length(A);i++){
      if(index(A)==-1){
        append(A,v);
        break;
      }else if(get(A)>v){
        insertBefore(A,v);
        break;
      }
      moveNext(A);
    }
    G->size++;
  }else{
    printf("Calling addArc() with invalid arguments");
    exit(1);
  }
}

//Returns the transpose of a graph
Graph transpose(Graph G){
  Graph transpose = newGraph(getOrder(G));
  for(int i=1;i<getOrder(G)+1;i++){
    List adjacent = G->neighbour[i];
    moveFront(adjacent);
    while(index(adjacent)!=-1){
      int val = get(adjacent);
      addArc(transpose,val,i);
      moveNext(adjacent);
    }
  }
  return transpose;
}

Graph copyGraph(Graph G){
  Graph copy = newGraph(getOrder(G));
  for(int i=1;i<getOrder(G)+1;i++){
    copy->neighbour[i] = G->neighbour[i];
    copy->color[i] = G->color[i];
    copy->discover[i] = G->discover[i];
    copy->finish[i] = G->finish[i];
    copy->parent[i] = G->parent[i];
  }
  copy->order = G->order;
  copy->size = G->size;
  return copy;
}

//Resets a graph to its original empty state
void makeNull(Graph G){
  for(int i=1;i<G->order+1;i++){
    clear(G->neighbour[i]);
    G->color[i] = 0;
    G->parent[i] = NIL;
    G->distance[i] = INF;
  }
  G->size = 0;
  G->label = 0;
}

//visits a vertex
void Visit(Graph G, int x, int *time, List S){
  G->color[x] = 1; //Set the color to grey
  G->discover[x] = ++ (*time);
  List adjacent = G->neighbour[x];
  moveFront(adjacent); //Place the cursor at the front
  while(index(adjacent)!=-1){ //Iterate through the list of neighborus
    int value = get(adjacent);
    if(G->color[value]==0){ //If neighbour is undiscovered, make x the parent
      G->parent[value] = x;
      Visit(G, value, time, S);
    }
    moveNext(adjacent); //Move to the next value in the list of neighbours
  }
    G->color[x] = 2; //Finish x/color it black
    G->finish[x] = ++ (*time);
    prepend(S, x);
}

List SCC(Graph G, List S){
  List scc = newList(); //Empty list that will be returned
  moveBack(S);
  while(index(S)!=-1){
    int val = get(S);
    prepend(scc,val);
    // printf("parent: %d\n", getParent(G,val));
    // if(getParent(G, val)==NIL){ //If the parent is Nil, add a 0 as a marker
    //   prepend(scc, 0);
    // }
    movePrev(S);
  }
  return scc;
}

//Depth first search
void DFS(Graph G, List S){
  int time = 0; //Set time to 0
  moveFront(S);
  while(index(S)!=-1){ //Initialize
    int value = get(S);
    G->color[value]=0;
    G->parent[value]=NIL;
    moveNext(S);
  }

  moveFront(S); //PLace the cursor back at the front
  while(index(S)!=-1){
    int value = get(S);
    if(G->color[value]==0){
      Visit(G, value, &time, S);
    }
    moveNext(S);
  }
  for(int i =0; i<getOrder(G);i++){
    deleteBack(S);
  }
}

//Prints out the graph
void printGraph(FILE* out, Graph G){
  if(G==NULL){
    printf("Calling printGraph upon a null graph reference");
    return;
  }else{
    for(int i=1; i<G->order+1; i++){
      fprintf(out, "%d: ",i);
      printList(out, G->neighbour[i]);
      fprintf(out, "\n");
    }
  }
}
