#include <iostream>
using namespace std;

int main()
{
    size_t N;
    int H, out=0;

    cin >> N;

    for (size_t i = 0; i < N; i++)
    {
        cin >> H;
        out += H*H*H;
    }
    
    cout << out;

    return 0;
}
