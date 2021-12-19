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

def camino_mas_corto(grafo, origen, destino): # 1 ESTRELLA: ANDA
    (padres, orden) = bfs(grafo, origen)
    if destino in padres:
        recorrido = reconstruir_camino(padres, destino)
        return recorrido, len(recorrido) -1
    return None, None

def _ciclo(grafo, actual, orden, n):
    if len(orden) == n and actual in orden:
        return True
    if len(orden) == n or actual in orden:
        return False
    orden.append(actual)
    for v in grafo.adyacentes(actual):
            if _ciclo(grafo, v, orden, n):
                return True
    orden.remove(actual)
    return False

def ciclo(grafo, origen, n): # 3 ESTRELLAS: ANDA
    orden = []
    if _ciclo(grafo, origen, orden, n):
        return orden
    return None

def navegacion(grafo, origen): # 1 ESTRELLA: ANDA
    contador = 0
    orden = []
    while contador<=20:
        orden.append(origen)
        if(len(grafo.adyacentes(origen)) > 0):
            origen = grafo.adyacentes(origen)[0]
        else:
            break
        contador +=1
    return orden

def rango(grafo, pagina, n): # 1 ESTRELLA: ANDA
    (padres, orden) = bfs(grafo, pagina)
    paginas_rango = []
    for w in orden:
        if orden.get(w) == n:
            paginas_rango.append(w)
    return len(paginas_rango)

def diametro(grafo): # 1 ESTRELLA: ANDA
    max_min_dist = 0
    orden_max = []
    for v in grafo:
        (padres, orden) = bfs(grafo, v)
        for w in orden:
            if orden[w] > max_min_dist:
                max_min_dist = orden[w]
    return max_min_dist

orden_contador = 0
orden = {}

def min(a,b):
    if a < b:
        return a
    else:
        return b

def conectados_(grafo, v, visitados, apilados, orden, mb, pila):
    global orden_contador

    visitados.add(v)
    orden[v] = orden_contador
    mb[v] = orden[v]
    orden_contador +=1
    pila.appendleft(v)
    apilados.add(v)

    for w in grafo.adyacentes(v):
        #print(w)
        if w not in visitados:
            conectados_(grafo, w, visitados, apilados, orden, mb, pila)
        if w in apilados:
            if mb[v] > mb[w]:
                mb[v] = min(mb[v], mb[w])
    if orden[v] == mb[v] and len(pila) > 0:
        cfc = []
        while True:
            w = pila.popleft()
            apilados.remove(w)
            cfc.append(w)
            if w == v:
                break
        return cfc

def conectados(grafo, pagina): # 2 ESTRELLAS: no anda
    apilados = set()
    visitados = set()
    mb = {}
    pila = deque()
    return conectados_(grafo, pagina, visitados, apilados, orden, mb, pila)

