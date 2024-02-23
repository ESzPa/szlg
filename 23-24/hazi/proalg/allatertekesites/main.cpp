#include <iostream>
using namespace std;

int main()
{
    size_t N;
    int B, prev=0, out=0;

    cin >> N;

    for (size_t i = 0; i < N; i++)
    {
        cin >> B;
        if (B > prev){
            out++;
        }
        prev = B;
    }
    
    cout << out;

    return 0;
}
