
###HPC
#Taller 2
####Multiplicación de Matrices

En este taller se escribió un codigo para la multiplicación de matrices de manera secuencial y otro de manera paralela. Se realizó una toma de datos con diferentes tamaños para las matrices, por cada tamaño se ejecuto 5 veces y se tomó el tiempo que se demoraba cada ejecución (Ts y Tp), luego se sacó el valor de Ts/Tp, por ultimo se sacó el promedio de Ts/Tp y se realizo la gráfica para ver el comportamiento de la ejecución.

**Algoritmo secuencial Vs Algoritmo paralelo (ingenuo)**

![alt tag]()


Tamaño = 100 | Ts | Tp | X = Ts/Tp
----------|----|----|------------
          |0.003747|0.310913 |
          |0.003335|0.279837 |
          |0.003344|0.308428 |
          |0.008010| 0.319888|
          |0.003336|0.279707 |

**Algoritmo secuencial Vs Algoritmo paralelo (Tiling)**
