//
// Created by julian_camacho on 20/6/20.
//

#include "Bresenham.h"

/**
 * plotLineLow Función para retornar los pares ordenados del recorrido entre dos puntos
 * donde la pendiente de la recta entre ellos está entre 0 y 1
 * @param x0 Coordenada en el eje x del punto de partida
 * @param y0 Coordenada en el eje y del punto de partida
 * @param x1 Coordenada en el eje x del punto de llegada
 * @param y1 Coordenada en el eje y del punto de llegada
 * @return coordenas x y del recorrido según el algoritmo de Bresenham
 */
vector<int> Bresenham::plotLineLow(int x0, int y0, int x1, int y1){
    vector<int> result;
    int D, y;
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0){
        yi = -1;
        dy = -dy;
    }
    D = 2*dy - dx;
    y = y0;
    for (int x = x0; x < x1; x++){
        result.push_back(x);
        result.push_back(y);
        if (D > 0) {
            y = y + yi;
            D = D - 2 * dx;
        }
        D = D + 2*dy;
    }
    return result;
}

/**
 * plotLineHigh Función para retornar los pares ordenados del recorrido entre dos puntos
 * donde la pendiente de la recta entre ellos es mayor que 1
 * @param x0 Coordenada en el eje x del punto de partida
 * @param y0 Coordenada en el eje y del punto de partida
 * @param x1 Coordenada en el eje x del punto de llegada
 * @param y1 Coordenada en el eje y del punto de llegada
 * @return coordenas x y del recorrido según el algoritmo de Bresenham
 */
vector<int> Bresenham::plotLineHigh(int x0, int y0, int x1, int y1){
    vector<int> result;
    int D, x;
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0){
        xi = -1;
        dx = -dx;
    }
    D = 2*dx - dy;
    x = x0;
    for (int y = y0 ; y < y1; y++){
        result.push_back(x);
        result.push_back(y);
        if (D > 0){
            x = x + xi;
            D = D - 2*dy;
        }
        D = D + 2*dx;
    }
    return result;
}

/**
 * reverseList Función auxiliar que invierte una lista
 * @param vec Lista que se desea invertir
 * @return Lista invertida
 */
vector<int> Bresenham::reverseList(vector <int> const &vec) {
    vector<int> result;
    for (int j = vec.size()-1; j > 0; j--) {
        result.push_back(vec.at(j));
    }
    result.push_back(vec.at(0));
    return result;
}

/**
 * fixList Función para reordenar los datos en una lista, cambiando de posición cada los datos dos elementos
 * ej: 1, 2, 3, 4  -->  2, 1, 4, 3
 * @param vec Lista que se desea arreglar
 * @return Lista arreglada
 */
vector<int> Bresenham::fixList(vector <int> const &vec){
    vector<int> result;
    vector<int> fixedList = reverseList(vec);
    for(int i=0; i < vec.size(); i+=2){
        result.push_back(fixedList.at(i+1));
        result.push_back(fixedList.at(i));
    }
    return result;
}

/**
 * print Procedimiento auxiliar para visualizar la lista resultante
 * @param vec Lista a visualizar
 */
void Bresenham::print(vector <int> const &vec) {
    cout << "The path in the oder x,y is : ";
    for(int i=0; i < vec.size(); i++){
        cout << vec.at(i) << ' ';
    }
    cout << endl;
}

void Bresenham::printVector(vector<Position*>* toPrint){
    if (toPrint->empty()){
        cout << "[empty]" << endl;
    } else{
        cout << "[";
        for (auto & i : *toPrint){
            i->printPosition();
            cout << ", ";
        }
        cout << "]" << endl;
    }
}
/**
 * pasePath Función para convertir el camino por seguir a un vector de Posiciones
 * @param pPath
 * @return
 */

vector<Position*>* Bresenham::parsePath(vector<int> pPath){
    vector<Position*>* finalRoute = new vector<Position*>;
    for (int i = 0; i < pPath.size() ; i+=2) {
        Position* newPosition = new Position(pPath.at(i), pPath.at(i+1));
        finalRoute->push_back(newPosition);
    }
    return finalRoute;
}

/**
 * bresenham Función principal que calcula el algoritmo de Bresenham con las funciones auxiliares, según la pendiente
 * y evaluando los valores x,y de los puntos
 * @param x0 Coordenada en el eje x del punto de partida
 * @param y0 Coordenada en el eje y del punto de partida
 * @param x1 Coordenada en el eje x del punto de llegada
 * @param y1 Coordenada en el eje y del punto de llegada
 * @return coordenas x y del recorrido según el algoritmo de Bresenham
 */
vector<Position*>* Bresenham::bresenham(Pair src, Pair dest){
    vector<Position*>* finalRoute;
    vector<int> resultPath;
    int x0 = src.first; int y0 = src.second;
    int x1 = dest.first; int y1 = dest.second;
    if (abs(y1 - y0) < abs(x1 - x0)){
        if (x0 > x1){
            resultPath = fixList(plotLineLow(x1, y1, x0, y0));
        } else{
            resultPath = plotLineLow(x0, y0, x1, y1);
        }
    }
    else{
        if (y0 > y1){
            resultPath = fixList(plotLineHigh(x1, y1, x0, y0));
        }else{
            resultPath = plotLineHigh(x0, y0, x1, y1);
        }
    }
    finalRoute = parsePath(resultPath);
    cout << "Algoritmo de Bresenham calculado: ";
    printVector(finalRoute);
    return finalRoute;
}


