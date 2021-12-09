#!/usr/bin/python3

class Grafo:

    """ inicializa un grafo  en blanco"""
    def __init__(self):
        self._vertices = {}
        self._datos = {}
    
    """devulve una lista de todas las aristas del vertice"""
    def aristas(self, vertice):
        return self._vertices[vertice]

    """devuelve todos los vertices del grafo en un set"""
    def todos_los_vertices(self):
        return self._datos

    """devuelve una lista de las aristas del grafo"""
    def todas_las_aristas(self):
        aristas =[]
        for origen in self._vertices:
            for destino in self._vertices[origen]:
                aristas.append([origen,destino])
        return aristas

    """devuelve un set con la copia de todos los adyacentes del vertice"""
    def adyacentes_vertice(self, vertice):
        if vertice in self._vertices:
            return self._vertices[vertice].copy()
    
    """agrega el vertice al grafo"""
    def agregar_vertice(self, vertice, dato=None):
        if vertice not in self._vertices:
            self._vertices[vertice] = set()
            self._datos[vertice] = dato

    """saca el vertice del grafo y devuelve el dato que almacenaba"""
    def sacar_vertice(self, vertice):
        aux = self._datos[vertice]
        self._datos.pop(vertice)
        self._vertices.pop(vertice)
        return aux

    """agrega la arista al grafo"""
    def agregar_arista(self, origen, destino):
        if origen not in self._vertices:
            self.agregar_vertice(origen)
            self.agregar_vertice(destino)
        self._vertices[origen].add(destino)

    """saca la arista del grafo"""
    def sacar_arista(self, origen, destino):
        if origen in self._vertices:
            self._vertices[origen].discard(destino)
    
    def existe_arista(self, origen, destino):
        if origen in self._vertices:
            if destino in self._vertices[origen]:
                return True
        return False

    """devuelve el dato de la clave"""
    def dato(self, clave):
        return self._datos[clave]

    """devuelte true o false si el vertice existe"""
    def existe_vertice(self, clave):
        if clave in self._datos:
            return True
        else:
            return False

    def __str__(self):
        aux = ''
        for origen in self._vertices:
            aux += origen + '-->'
            if len(self._vertices[origen]) != 0:
                aux += str(self._vertices[origen].copy()) + '\n'
            else:
                aux += '\n'
        return aux


grafo = Grafo()

grafo.agregar_vertice('a')
grafo.agregar_vertice('b', 2)
grafo.agregar_vertice('c', 3)
grafo.agregar_vertice('d', 4)
grafo.agregar_vertice('e', 5)
grafo.agregar_vertice('e', 6)
grafo.agregar_arista('a', 'b')
grafo.agregar_arista('a', 'c')
grafo.agregar_arista('a', 'd')
grafo.agregar_arista('b', 'a')
grafo.agregar_arista('b', 'c')

print(grafo.adyacentes_vertice('a'))
print(grafo)