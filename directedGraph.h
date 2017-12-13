#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
template <class THING>
class directedGraph{
private:
    class vertex{
    public:
      THING data;
      int id;
      vector<vertex*> neighbors;
      vertex * predecessor;
      bool marked;

      vertex(THING x)
      {
        marked = false;
        predecessor = NULL;
        data = x;
      }

      void mark(){
        marked = true;
      }

      void setPredecessor(vertex * x){
        predecessor = x;
      }

      void clearData(){
        predecessor = NULL;
        marked = false;
      }
    };


    //maintain a data structure holding all vertices
    vector<vertex*> vertexList;

    //private helper methods

    //return vertex with x as data field
    vertex * findVertex(int x){
     // cout << "Finding vertex" << endl;
      for(int i=0; i<vertexList.size(); i++)
      {
        if( vertexList[i]->data == x )
        return vertexList[i];
      }
        return NULL;
    }

    void breadthFirstSearch(vertex * s){

      clearData(); //sets pred of all vertexes to NULL and unmarks

      vertex * x;
      vertex * y;
      s->mark(); //calls helper method to mark vertex
      queue<vertex*> vertexQueue;

      vertexQueue.push(s);
      while(!vertexQueue.empty()){
        x = vertexQueue.front();
        vertexQueue.pop();

        for(int i = 0; i < x->neighbors.size(); i++){
          y = x->neighbors[i];
          if(!y->marked){
            y->mark();
            y->setPredecessor(x);
            vertexQueue.push(y);
          }//end of if(marked)
        }//end of for
      }//end of while(q.empty)
    }//end of method

    void displayBreadthFirstSearch(){
      for(int i = 0; i < vertexList.size(); i++){
        if(vertexList[i]->predecessor != NULL)
        cout << "Vertex " << vertexList[i]->data << "'s '"
        << "predecessor is: " << vertexList[i]->predecessor->data << endl;
      }

    }




public:

    void addVertex(THING x) {
      vertex * babyVertex = new vertex(x);
      vertexList.push_back(babyVertex);
    }

    void addDirectedEdge(int x, int y){
      vertex * ptrX = findVertex(x);
      vertex * ptrY = findVertex(y);

      ptrX->neighbors.push_back(ptrY);
    }

    void addEdge(THING x, THING y){
      vertex * ptrX = findVertex(x);
      vertex * ptrY = findVertex(y);

      ptrX->neighbors.push_back(ptrY);
      ptrY->neighbors.push_back(ptrX);
    }

    void display(){
      for(int i=0; i<vertexList.size(); i++){
        cout << vertexList[i]->data << " :: ";
        for(int j=0; j<vertexList[i]->neighbors.size(); j++){
        cout << vertexList[i]->neighbors[j]->data << ", ";
        }
          cout << endl;
      }
    }

    void clear(){
      vertexList.clear();
    }

    void testBreadthFirstSearch(int x){
      vertex * s = findVertex(x);
      if(s != NULL){
        breadthFirstSearch(findVertex(x));
        //displayBreadthFirstSearch();
      }

    }

    void clearData(){
      for(int i = 0; i < vertexList.size(); i++){
        vertexList[i]->clearData();
      }
    }

    string shortestPath(int x, int y){
      breadthFirstSearch(findVertex(x));
      vertex * ptrX = findVertex(x);
      vertex * ptrY = findVertex(y);
      vertex * walker = ptrY;
      string returnValue = ptrY->data + ", ";
      if(walker->predecessor != NULL) walker = walker->predecessor;
      while(walker != NULL && walker != ptrX){
        returnValue += walker->data;
        returnValue +=  ", ";
        walker = walker->predecessor;
      }
      returnValue += ptrX->data;
     // if(walker == NULL) returnValue = "No path";
      return returnValue;
    }

    bool findPath(int x, int y){
      breadthFirstSearch(findVertex(x));
      vertex * ptrX = findVertex(x);
      vertex * ptrY = findVertex(y);
      vertex * walker = ptrY;
      if(walker->predecessor != NULL) walker = walker->predecessor;
      while(walker != NULL && walker != ptrX){
        walker = walker->predecessor;
      }
      if(walker == ptrX) return true;
      return false;
    }





};

#endif
