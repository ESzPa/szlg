#include <iostream>
using namespace std;

int main()
{
    size_t N;
    int K, S, M;
    cin >> N >> M >> K;
    K = 0;
    for (size_t i = 0; i < N; i++){
        cin >> S;
        if (S < M && S != 0){
            K++;
        }
    }
    cout << K;

    return 0;
}

