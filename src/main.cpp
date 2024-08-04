#include "GraphAlgorithms/Dijkstra/Dijkstra.hpp"
#include <Windows.h>


std::wstring getCurrentWorkingDirectory() {
    // Determina la dimensione del buffer necessaria
    DWORD bufferSize = GetCurrentDirectoryW(0, NULL);

    // Verifica che la funzione sia riuscita a determinare la dimensione
    if (bufferSize == 0) {
        return L"Error getting buffer size";
    }

    // Alloca il buffer per la directory corrente
    std::wstring buffer(bufferSize, L'\0');

    // Ottieni la directory corrente
    if (GetCurrentDirectoryW(bufferSize, &buffer[0])) {
        return buffer;
    }
    else {
        return L"Error getting current working directory";
    }
}


int main() {

    const size_t nodes_number = 45;
    const size_t neighbours_number = 10;

    std::wcout << L"Current Working Directory: " << getCurrentWorkingDirectory() << std::endl;

    Dijkstra dijkstra (nodes_number, neighbours_number);
    dijkstra.Play();
}

