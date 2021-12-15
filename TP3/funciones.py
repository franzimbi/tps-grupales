import grafo
from collections import deque

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

def _dfs(grafo, v, visitados, padres, orden):
    for w in grafo.adyacentes(v):
        if w not in visitados:
            visitados.add(w)
            padres[w] = v
            orden[w] = orden[v] + 1
            _dfs(grafo, w, visitados, padres, orden)

def dfs(grafo, origen):
    padres = {}
    orden = {}
    visitados = set()
    padres[origen] = None
    orden[origen] = 0
    visitados.add(origen)
    _dfs(grafo, origen, visitados, padres, orden)
    return padres, orden

def recorrido_dfs_completo(grafo):
    visitados = set()
    padres = {}
    orden = {}
    for v in grafo:
        if v not in visitados:
            visitados.add(v)
            padres[v] = None
            orden[v] = 0
            _dfs(grafo, v, visitados, padres, orden)
    return padres, orden

def reconstruir_camino(padres, destino):
    recorrido = []
    while destino is not None:
        recorrido.append(destino)
        destino = padres[destino]
    return recorrido[::-1]

def camino_mas_corto(grafo, origen, destino):
    (padres, orden) = bfs(grafo, origen)
    return reconstruir_camino(padres, destino)

def diametro(grafo):
    


internet = grafo.Grafo()

internet.insertar_arista('a', 'b')
internet.insertar_arista('a', 'c')
internet.insertar_arista('c', 'd')
internet.insertar_arista('e', 'g')
internet.insertar_arista('g', 'h')
internet.insertar_arista('i', 'b')
internet.insertar_arista('f', 'g')
internet.insertar_arista('b', 'f')
internet.insertar_arista('d', 'e')

print(internet)

print(camino_mas_corto(internet, 'a', 'i'))
