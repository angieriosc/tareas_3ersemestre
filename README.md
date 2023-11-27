# tareas_3ersemestre
# BST
Las unicas correciones que implemente fue en el archivo de bst.h en la funcion de ancestorsAux linea 383 y levelbylevel linea 190 donde agregue una condición para el espacio 
        if (aux.tellp() != 1){
            aux << " ";
        }

si es diferente al primero imprimir espacio antes de imprimir el siguiente valor, esto arreglo el problema del espacio extra que tuve en la primer entrega
