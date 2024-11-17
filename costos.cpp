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

// Función para calcular la distancia mínima de edición
int calculateEditDistance(const string &S1, const string &S2, size_t &spaceUsed) {
    int m = S1.size(), n = S2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Calcular el espacio utilizado por dp
    spaceUsed = dp.size() * dp[0].size() * sizeof(int);

    // Inicializar las condiciones base para inserción y eliminación
    for (int i = 1; i <= m; ++i) dp[i][0] = dp[i - 1][0] + costDelete[S1[i - 1] - 'a'];
    for (int j = 1; j <= n; ++j) dp[0][j] = dp[0][j - 1] + costInsert[S2[j - 1] - 'a'];

    // Llenado de la tabla dp para calcular la distancia de edición
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int cost = (S1[i - 1] == S2[j - 1]) ? 0 : costReplace[S1[i - 1] - 'a'][S2[j - 1] - 'a'];
            dp[i][j] = min({dp[i - 1][j] + costDelete[S1[i - 1] - 'a'],  // Eliminación
                            dp[i][j - 1] + costInsert[S2[j - 1] - 'a'],  // Inserción
                            dp[i - 1][j - 1] + cost});                   // Sustitución

            // Verificar si es posible realizar una transposición
            if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1])
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + costTranspose[S1[i - 1] - 'a'][S1[i - 2] - 'a']);
        }
    }
    return dp[m][n];
}

// Función para medir el tiempo de ejecución
double measureExecutionTime(const string &S1, const string &S2, size_t &spaceUsed) {
    auto start = chrono::high_resolution_clock::now();
    calculateEditDistance(S1, S2, spaceUsed);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;
    return duration.count() * 1000;
}

// Función principal
int main() {
    loadCostTables();  // Cargar los costos desde los archivos

    string S1, S2;
    cout << "Ingrese la primera cadena (puede estar vacía): ";
    getline(cin, S1);
    cout << "Ingrese la segunda cadena (puede estar vacía): ";
    getline(cin, S2);

    size_t spaceUsed = 0;
    double timeElapsed = measureExecutionTime(S1, S2, spaceUsed);

    int distance = calculateEditDistance(S1, S2, spaceUsed);
    cout << "La distancia mínima de edición es: " << distance << endl;
    cout << "Tiempo de ejecución: " << timeElapsed << " ms" << endl;
    cout << "Espacio utilizado: " << spaceUsed << " bytes" << endl;

    return 0;
}
