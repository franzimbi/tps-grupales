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

def _ciclo(grafo, origen, orden, contador):
    orden.append(origen)
    print("guarde:" + origen + '\t' + "contador: " + str(contador) + "\t" + orden[0] + " == " + origen)
    contador-= 1
    if contador == 1 and orden[0] in grafo.adyacentes(origen):
        return True
    for v in grafo.adyacentes(origen):
        if len(grafo.adyacentes(v)) == 0:
            continue
        if v not in orden:
            if _ciclo(grafo, v, orden, contador):
                return True
    orden.remove(origen)
    contador =+ 1
    return False


def ciclo(grafo, origen, n):
    orden = []
    orden.append(origen)
    contador = n
    if _ciclo(grafo, origen, orden, contador):
        return orden
    return orden

def navegacion(grafo, origen):
    contador = 0
    orden = []
    while contador<20:
        orden.append(origen)
        origen = grafo.adyacentes(origen)[0]
        contador +=1
    return orden

def rango(grafo, pagina, n):
    

internet = grafo.Grafo(True)

internet.insertar_arista('a', 'b')
internet.insertar_arista('a', 'c')
internet.insertar_arista('c', 'd')
internet.insertar_arista('c', 'e')
internet.insertar_arista('b', 'f')
internet.insertar_arista('b', 'g')
internet.insertar_arista('d', 'i')
internet.insertar_arista('e', 'h')
internet.insertar_arista('f', 'h')
internet.insertar_arista('g', 'j')
internet.insertar_arista('i', 'k')
internet.insertar_arista('k', 'h')
internet.insertar_arista('j', 'k')
internet.insertar_arista('j', 'h')
internet.insertar_arista('h', 'a')


print(internet)

print(navegacion(internet, 'a'))