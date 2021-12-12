#!/usr/bin/python3
import random
from collections import deque


class Grafo:
    def __init__(self, dirigido=False):
        self._dirigido = dirigido
        self._vertices = {}
        self._datos = {}

    """inserta un vertice. si ese vertice existe, reemplaza el dato"""
    def insertar_vertice(self, vertice, dato=None):
        if vertice is not self._vertices:
            self._vertices[vertice] = {}
        self._datos[vertice] = dato

    """inserta una arista con peso. en caso de no ser pesado no insertar peso. en caso de no ser dirigido, origen y destino son indistintos"""
    def insertar_arista(self, origen, destino, peso=None):
        if origen in self._vertices and destino in self._vertices:
            self._vertices[origen][destino] = peso
            if self._dirigido == False:
                self._vertices[destino][origen] = peso
            return True
        return False

    """devuelve una lista con los vertices adyacentes"""
    def adyacentes(self, vertice):
        if vertice in self._vertices:
            return [self._vertices[vertice].keys()]
        return None

    """saca un vertice y devuelve su dato"""
    def sacar_vertice(self, vertice):
        for i in self._vertices:
            self._vertices[i].pop(vertice)
        self._vertices.pop(vertice)
        return self._datos.pop(vertice)

    """saca una arista"""
    def sacar_arista(self, origen, destino):
        self._vertices[origen].pop(destino)
        if self._dirigido == False:
            self._vertices[destino].pop(origen)

    """devuelve True si dos vertices estan unidos por una arista. False en caso contrario"""
    def ver_dos_vertices_unidos(self, origen, destino):
        if origen in self._vertices:
            return destino in self._vertices[origen]
        return False

    """devuelve True si un vertice existe. False en caso contrario"""
    def existe_vertice(self, vertice):
        return vertice in self._vertices
    
    """devuelve el dato del vertice"""
    def dato_vertice(self, vertice):
        if vertice in self._vertices:
            return self._datos[vertice]
        return None

    """devuelve una lista con todos los vertices"""
    def todos_vertices(self):
        return list(self._vertices.keys())

    """devuelve un vertice aleatorio"""
    def vertice_aleatorio(self):
        return random.choice(list(self._vertices.keys())) 

    def __iter__(self):
        return iter(self._vertices)

    def __str__(self):
        res = ''
        for i in self._vertices:
            res+= str(i) + '-->'
            if(len(self._vertices[i]) != 0):
                res += str(self._vertices[i].copy()) + '\n'
            else:
                res += '\n'
        return res

def bfs(grafo, origen):
    visitados = set()
    padres = {}
    orden = {}
    padres[origen] = None
    orden[origen] = 0
    visitados.add(origen)
    q = deque()
    q.append(origen) #encolar
    while len(q) != 0:
        v = q.popleft() #desencolar
        for w in grafo.adyacentes(v):
            if w not in visitados:
                padres[w] = v
                orden[w] = orden[v] + 1
                visitados.add(w)
                q.append(w)
    return padres, orden


grafo = Grafo()

grafo.insertar_vertice('a')
grafo.insertar_vertice('b')
grafo.insertar_vertice('c')
grafo.insertar_vertice('d')
grafo.insertar_vertice('e')
grafo.insertar_vertice('f')
grafo.insertar_vertice('g')
grafo.insertar_vertice('h')
grafo.insertar_vertice('i')

grafo.insertar_arista('a', 'b')
grafo.insertar_arista('a', 'c')
grafo.insertar_arista('c', 'd')
grafo.insertar_arista('e', 'd')
grafo.insertar_arista('g', 'h')
grafo.insertar_arista('i', 'b')
grafo.insertar_arista('c', 'e')

print(grafo)

print(bfs(grafo, 'a'))
