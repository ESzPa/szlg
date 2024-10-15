#include <iostream>
#include <vector>

int Sum(std::vector<int> lista, int innen=0)
{
    // kilépési feltétel  = a legeslegyszerűbb eset, amit már nincs hova visszavezetni!
    if (innen == lista.size())
        return 0;
    // ide csak akkor jut a program, ha innen < lista.Count! Azaz a lista[innen] lekérdezhető
    return lista[innen] + Sum(lista, innen + 1); // jobbrekurzió
}

int EvenCount(std::vector<int> lista, int innen=0){
    return lista.size() <= innen ? 0 : (lista[innen] % 2 ? 0 : 1 + EvenCount(lista, innen+1));
}

bool HasOdd(std::vector<int> lista, int innen=0){
    return lista.size() <= innen ? 0 : (lista[innen] % 2 ? 1 : HasOdd(lista, innen+1));
}



int main(void){



    return 0;
}
