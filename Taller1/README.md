###HPC
#Taller 1
####Suma Vetores

En este taller se ejecutó la suma de dos vectores, primero se ejecutó de manera secuencial y despues se ejecuto de manera paralela
usando cudaMalloc y cudaMemcpy. 
Se realizó una toma de datos con diferentes tamaños para el vector, por cada tamaño se ejecuto 5 o 7 veces y se tomó el tiempo
que se demoraba cada ejecución (Ts y Tp), luego se sacó Ts/Tp, por ultimo se sacó el promedio de Ts/Tp y se realizo la gráfica
para ver el comportamiento de la ejecución.

Tamaño = 10 |   Ts       | Tp          | x= Ts / Tp                     
------------|------------|-------------|-----------------
            |0,000001    |0,09834      |0,00001016880212
            |0,000001    |0,093103     |0,00001074079246
            |0,000001    |0,09259|0,00001080030241
            |0,000001|0,096368|0,00001037688859
            |0,000001|0,094532|0,00001057842847
            |         |         |0,00001053304281

tamaño = 10.000.000|    Ts    |     Tp    |x= Ts / Tp
-------------------|----------|-----------|-----------
                   |0,025527|0,013222|1,930645893
                   |0,025579|0,013442|1,902916233
                   |0,025571|0,013166|1,942199605
                   |0,02555	|0,013189|1,937220411
                   |0,025578	|0,012978|1,970873786
                   |0,025565|	0,013326|1,918430137
                   |0,025549|	0,012863|1,986239602
                   | | |1,941217952

[Enlace para ver toma de datos y gráficas](https://docs.google.com/spreadsheets/d/1n-hjtcWSAYgRCqzw0lMCroT37GhxgKNCfioGPcaBwhQ/edit?usp=sharing)
