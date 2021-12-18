import grafo
import funciones
import csv
import sys

def leer_parser(archivo):
    file = open(archivo)
    tsv_file = csv.reader(file, delimiter = "\t")
    return tsv_file

def crear_red(tsv):
    red = grafo.Grafo(True)
    contador = 0
    origen = None
    for p in tsv:
        for r in p:
            if contador == 0:
                origen = r
            else:
                red.insertar_arista(origen, r)
            contador += 1
        contador = 0
    return red

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(1)

    tsv = leer_parser(sys.argv[1])
    red = crear_red(tsv)

    sys.setrecursionlimit(75000)
    #print(sys.getrecursionlimit())

    print(funciones.conectados(red, "Boca Juniors"))
    print(funciones.conectados(red, "Boca Juniors"))



