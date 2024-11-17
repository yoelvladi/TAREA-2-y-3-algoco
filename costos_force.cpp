#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>  // Para medir el tiempo de ejecución
#include <limits>

using namespace std;

// Variables globales para costos
vector<int> costInsert(26);
vector<int> costDelete(26);
vector<vector<int>> costReplace(26, vector<int>(26));
vector<vector<int>> costTranspose(26, vector<int>(26));

// Función para cargar las tablas de costo desde archivos de texto
void loadCostTables() {
    ifstream file;

    // Cargar costos de inserción
    file.open("cost_insert.txt");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo cost_insert.txt\n";
        return;
    }
    for (int i = 0; i < 26; ++i) file >> costInsert[i];
    file.close();

    // Cargar costos de eliminación
    file.open("cost_delete.txt");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo cost_delete.txt\n";
        return;
    }
    for (int i = 0; i < 26; ++i) file >> costDelete[i];
    file.close();

    // Cargar costos de sustitución
    file.open("cost_replace.txt");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo cost_replace.txt\n";
        return;
    }
    for (int i = 0; i < 26; ++i)
        for (int j = 0; j < 26; ++j) file >> costReplace[i][j];
    file.close();

    // Cargar costos de transposición
    file.open("cost_transpose.txt");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo cost_transpose.txt\n";
        return;
    }
    for (int i = 0; i < 26; ++i)
        for (int j = 0; j < 26; ++j) file >> costTranspose[i][j];
    file.close();
}

// Función de fuerza bruta para calcular la distancia de edición
int bruteForceEditDistance(const string &S1, const string &S2, int i, int j, int &maxDepth, int currentDepth) {
    maxDepth = max(maxDepth, currentDepth);  // Actualizar la profundidad máxima

    // Casos base
    if (i == 0) return j == 0 ? 0 : costInsert[S2[j - 1] - 'a'] + bruteForceEditDistance(S1, S2, i, j - 1, maxDepth, currentDepth + 1);
    if (j == 0) return costDelete[S1[i - 1] - 'a'] + bruteForceEditDistance(S1, S2, i - 1, j, maxDepth, currentDepth + 1);

    // Caso de coincidencia directa
    if (S1[i - 1] == S2[j - 1])
        return bruteForceEditDistance(S1, S2, i - 1, j - 1, maxDepth, currentDepth + 1);

    // Calcular los costos de las operaciones posibles
    int insertCost = costInsert[S2[j - 1] - 'a'] + bruteForceEditDistance(S1, S2, i, j - 1, maxDepth, currentDepth + 1);
    int deleteCost = costDelete[S1[i - 1] - 'a'] + bruteForceEditDistance(S1, S2, i - 1, j, maxDepth, currentDepth + 1);
    int replaceCost = costReplace[S1[i - 1] - 'a'][S2[j - 1] - 'a'] + bruteForceEditDistance(S1, S2, i - 1, j - 1, maxDepth, currentDepth + 1);

    // Evaluar si es posible una transposición
    int transposeCost = numeric_limits<int>::max();
    if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1])
        transposeCost = costTranspose[S1[i - 1] - 'a'][S1[i - 2] - 'a'] + bruteForceEditDistance(S1, S2, i - 2, j - 2, maxDepth, currentDepth + 1);

    // Retornar el mínimo costo de las operaciones posibles
    return min({insertCost, deleteCost, replaceCost, transposeCost});
}

// Función para medir el tiempo de ejecución
double measureExecutionTime(const string &S1, const string &S2, int &maxDepth) {
    auto start = chrono::high_resolution_clock::now();
    bruteForceEditDistance(S1, S2, S1.size(), S2.size(), maxDepth, 1);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;
    return duration.count()*1000;
}

// Función principal
int main() {
    loadCostTables();  // Cargar los costos desde los archivos

    string S1, S2;
    cout << "Ingrese la primera cadena (puede estar vacía): ";
    getline(cin, S1);
    cout << "Ingrese la segunda cadena (puede estar vacía): ";
    getline(cin, S2);

    int maxDepth = 0;
    double timeElapsed = measureExecutionTime(S1, S2, maxDepth);

    int distance = bruteForceEditDistance(S1, S2, S1.size(), S2.size(), maxDepth, 1);
    cout << "La distancia mínima de edición es: " << distance << endl;
    cout << "Tiempo de ejecución: " << timeElapsed << " milisegundos" << endl;
    cout << "Espacio utilizado (profundidad máxima de la pila): " << maxDepth * sizeof(int) << " bytes" << endl;

    return 0;
}
