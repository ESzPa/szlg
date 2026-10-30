#include <iostream>
#include <vector>

using namespace std;

void swap(vector<int> &list, int i){
    int temp = list[i];
    list[i] = list[i+1];
    list[i+1] = temp;
}

void dumb_bubblesort(vector<int> &list){
    int n = list.size();
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(list[j] > list[j+1]){
                swap(list, j);
            }
        }
    }
}

void bubblesort(vector<int> &list){
    int length = list.size();
    
}

int main(void){
    vector<int> list;
    for(int i = 0; i < 15; i++){
        list.push_back(rand() % 100);
    }

    
    bubblesort(list);
    for (int i : list){
        std::cout << i << ", ";
    }
    std::cout << "\n";
    
    return 0;
}
