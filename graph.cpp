//
//  graph.cpp
//  Algorithms 3.2
//
//  Created by Marcos Vicente on 14.12.2017.
//  Copyright © 2017 Marcos Vicente. All rights reserved.
//

#include "graph.hpp"
#include <iostream>

void graph::createGraph()
{
    first = NULL;
}

bool graph::emptyGraph()
{
    if (first == NULL)
        return true;
    else
        return false;
}

int graph::sizeGraph()
{
    int cont = 0;
    vertex *aux;
    aux = first; //variável auxiliar funciona como um ponteiro para a lista de vértices (vai indicar cada vértice)
    
    while (aux != NULL){
        cont++;
        aux = aux->next; //o auxiliar percorre a lista de vértices até encontrar um cujo campo next seja NULL
    }
    return cont; //Mostra o tamanho do grafo
}

vertex *graph::getVertex(int label)
{
    vertex *aux;
    aux = first;
    
    while (aux != NULL)
    {
        if (aux->label == label)
            return aux;
        
        aux = aux->next;
    }
    return NULL;
}

void graph::insertVertex(int label)
{
    vertex *newVertex = new vertex;
    newVertex->label = label;
    newVertex->next = NULL;
    newVertex->adj = NULL;
    
    if (emptyGraph())
    {
        first = newVertex;
    }else{
        vertex *aux;
        aux = first;
        
        while (aux->next != NULL) //funciona como um iterador, vai percorrer os vértices até chegar ao último (se já existir pelo menos um)
        {
            aux = aux->next;
        }
        aux->next = newVertex;
    }
}

void graph::insertEdge(vertex *orig, vertex *dest, int digraph, int weight)
{
    edge *newEdge = new edge;
    newEdge->weight = weight;
    newEdge->next = NULL;
    newEdge->adj = NULL;
    
    edge *aux;
    
    aux = orig->adj; // recebe o vértice origem
    
    if (aux == NULL) // Se o vértice estiver vazio
    {
        orig->adj = newEdge; //liga a aresta ao vértice origem
        newEdge->adj = dest; //liga a aresta ao vértice destino
    }else{
        while (aux->next != NULL) // funciona como um iterador, vai percorrer as arestas até chegar a última (se já existir pelo menos uma)
        {
            aux = aux->next;
        }
        aux->next = newEdge; //aqui adiciona a nova aresta conectando-a ao vértice begin (dentro da lista das arestas)
        newEdge->adj = dest; // aqui conecta a mesma aresta ao vértice destino
    }
    
    if (digraph == 0) // verifica se é orientado, se não for, ele cria a aresta orientada ligando o fim ao princípio
        insertEdge(dest, orig, 1, weight); //создает ориентированный граф.
}

void graph::adjList()
{
    vertex *vertAux;
    edge *edgeAux;
    
    vertAux = first; // posicionado no primeiro vértice
    
    while (vertAux != NULL) //percorre todos os outros vértices
    {
        cout << vertAux->label << " -> "; //mostra o vértice que está a ser recorrido
        edgeAux = vertAux->adj; // posicionando o auxiliar das arestas no primeiro vértice
        while (edgeAux != NULL) // percorrendo as outras arestas desse vértice
        {
            cout << edgeAux->adj->label << " -> "; //mostra o nome do vértice origem que está a ser percorrido
            edgeAux = edgeAux->next;
        }
        vertAux = vertAux->next;
        cout << endl; //pulamos a linha
    }
}

void graph::free()
{
    vertex *aux;
    
    while (first != NULL)
    {
        aux = first; //posiciona o aux no vértice actual (first)
        first = first->next; // first vai para o seguinte vértice
        delete (aux); // remove o vértice anterior onde estava o aux
    } // e assim  se repetirá até o grafo ficar vazio
}

//função adicionada por mim para verificar se existe ou não uma aresta entre os vértices
void graph::checkVertex(int flag, vertex *orig, vertex *dest)
{
    edge *actual;
    flag = 0;
    
    actual = orig->adj;
    
    if (actual->adj == dest)
    {
        flag = 1;
    }
    
    if (flag == 0)
        cout << "Не существует ребро между вершинами!" << endl;
}

void graph::removeEdge(vertex *orig, vertex *dest)
{
    edge *actual, *prev = 0; //auxiliares
    int flag = 0;
    
    actual = orig->adj; //posiciona o actual no vértice origem
    
    if(actual == NULL)
    {
        cout << "No edges in the origin vertex!" << endl;
    }else if(actual->adj == dest)
    {
        orig->adj = actual->next; //liga o vértice origem a aresta que está a seguir
        delete(actual); //elimina a aresta
    }else{
        while (actual != NULL)
        {
            if (actual->adj == dest)
            {
                flag = 1;
                prev->next = actual->next;
                delete (actual);
                break;
            }
            prev = actual;
            actual = actual->next;
        }
        checkVertex(flag, orig, dest);
    }
}

void graph::removeVertex(vertex *insVertex)
{
    vertex *actual, *prev = 0;
    edge *aux;
    
    actual = first;
    
    while(actual != NULL)
    {
        aux = actual->adj;
        while (aux != NULL)
        {
            if (aux->adj == insVertex){
                removeEdge(actual, aux->adj);
                break;
            }
            aux = aux->next;
        }
        actual = actual->next;
    }
    
    actual = first;
    if (first == insVertex)
    {
        first = first->next;
        delete (actual);
    }else{
        while (actual != insVertex)
        {
            prev = actual;
            actual = actual->next;
        }
        prev->next = actual->next;
        delete (actual);
    }
}