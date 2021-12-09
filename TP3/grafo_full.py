#!/usr/bin/python3

class Nodo:
    def __init__(self, clave, peso):
        self._clave = clave
        self._peso = peso

    def peso(self):
        return self._peso

    def clave(self):
        return self._clave

    def __str__(self):
        res ='clave: ' + str(self._clave)
        if(self._peso != None):
            res+= '->peso: ' + str(self._peso)
        return res

    
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
        if origen and destino in self._vertices:
            self._vertices[origen][destino] = peso
            if self._dirigido == False:
                self._vertices[destino][origen] = peso

    def adyacentes(self, vertice):
        if vertice in self._vertices:
            return set(self._vertices[vertice].keys())

    def sacar_vertice(self, vertice):
        for i in self._vertices:
            self._vertices[i].pop(vertice)
        self._vertices.pop(vertice)
        self._datos.pop(vertice)


    def sacar_vertice(self, origen, destino):
        self._vertices[origen].pop(destino)
        if self._dirigido == False:
            self._vertices[destino].pop(origen)

    def ver_dos_vertices_unidos(self, origen, destino):
        if destino in self._vertices[origen]:
            return True
        return False

    def existe_vertice(self, vertice):
        if vertice in self._vertices:
            return True
        return False

    def dato_vertice(self, vertice):
        if vertice in self._vertices:
            return self._datos[vertice]
        return None

    def todos_vertices(self):
        return [self._vertices.keys()]

    def __iter__(self):
        self._iter = iter(self._vertices)
        return self._iter

    def __next__(self):
        return next(self._iter)

    def __str__(self):
        res = ''
        for i in self._vertices:
            res+= str(i) + '-->'
            if(len(self._vertices[i]) != 0):
                res += str(self._vertices[i].copy()) + '\n'
            else:
                res += '\n'

        return res

no_dirigido = Grafo(False)

no_dirigido.insertar_vertice('a', 2)
no_dirigido.insertar_vertice('b', 3)
no_dirigido.insertar_vertice('c', 4)
no_dirigido.insertar_vertice('d', 5)
no_dirigido.insertar_vertice('e', 6)
no_dirigido.insertar_vertice('f', 7)

no_dirigido.insertar_arista('a', 'b', 2)
no_dirigido.insertar_arista('a', 'c', 4)
no_dirigido.insertar_arista('a', 'f', 6)
no_dirigido.insertar_arista('d', 'b', 4)
no_dirigido.insertar_arista('e', 'b', 6)
no_dirigido.insertar_arista('c', 'f', -12)



for i in no_dirigido:
    print(no_dirigido.sacar_vertice(i))

    