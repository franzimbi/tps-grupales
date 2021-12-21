#!/usr/bin/python3
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

def camino(grafo, parametros): #funciona 
    (recorrido, costo) = funciones.camino_mas_corto(grafo, parametros[0], parametros[1])
    if recorrido == None:
        print("No se encontro recorrido")
        return
    print(" -> ".join(recorrido))
    print("Costo: "+ str(costo))

def conectados(grafo, parametros): #funciona
    sys.setrecursionlimit(75000)
    conectividad = funciones.conectados(grafo, parametros[0])
    print(", ".join(conectividad))
    sys.setrecursionlimit(5000)

def ciclo(grafo, parametros): #funciona
    orden = funciones.ciclo(grafo, parametros[0], int(parametros[1]))
    if orden == None:
        print("No se encontro recorrido.")
        return
    res = ""
    for i in range(0,len(orden)-1):
        res += orden[i] + " -> "
    res += parametros[0]
    print(res)

def rango(grafo, parametros): #funciona
    print(funciones.rango(grafo, parametros[0], int(parametros[1])))

def navegacion(grafo, parametros):  #funciona
    orden = funciones.navegacion(grafo, parametros[0])
    print(" -> ".join(orden))

def listar(grafo, parametros):
    print("camino\nconectados\nciclo\nrango\nnavegacion")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(1)

    tsv = leer_parser(sys.argv[1])
    red = crear_red(tsv)

#                       1                   2                       3               1               1           
    dicc_comandos = {"camino": camino, "conectados": conectados,"ciclo": ciclo, "rango": rango, "navegacion": navegacion, "listar_operaciones": listar}


    for line in sys.stdin: #lee linea
        line = line.replace('\n', '') #elimina los \n
        palabras = line.split(',') #separa las palabras
        aux = palabras[0].split(' ')
        palabras.pop(0)
        funcion = aux.pop(0)
        palabras.insert(0, " ".join(aux))
        comando = dicc_comandos[funcion]
        comando(red, palabras)
