#include <iostream>
#include <cstdlib>

void input(int& n, int& k, int*& stations){
    std::cin >> n >> k;
    stations = (int*)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++){
        std::cin >> stations[i]; 
    }
}

int greedy(int* stations, int n, int k, int*& stops){
    int size = 1;
    int last = stations[0];

    stops = (int*)malloc(sizeof(int) * (n + 1));
    stops[0] = 1;

    for(int i = 1; i < n; i++){
        if(stations[i] - last >= k){
            last = stations[i];
            stops[size++] = i + 1;
        }
    }

    stops[size-1] = n;
    stops = (int*)realloc(stops, size * sizeof(int));
    return size;
}

int main(void){
    int n, k, m;
    int* stations = nullptr;
    int* stops = nullptr;

    input(n, k, stations);

    m = greedy(stations, n, k, stops);
    std::cout << m << '\n';
    for(int i = 0; i < m; i++){
        std::cout << stops[i] << ' ';
    }
    std::cout << '\n';

    free(stops);
    free(stations);
    return 0;
}
