#include <iostream>
using namespace std;

int main()
{
    size_t N;
    int K=0, S;

    cin >> N;

    for (size_t i = 0; i < N; i++){
        cin >> S;
        if (S > 100){
            K++;
        }
    }

    cout << K;

    return 0;
}

