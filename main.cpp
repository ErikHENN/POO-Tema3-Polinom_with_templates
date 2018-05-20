#include <iostream>
#include "Polinom.h"
#include <fstream>
using namespace std;

int main() {
    int coef1[10]={3, 2, 1};
    int coef2[10]={-1, 5, 2};
    int coef3[10]={-2, 3};
    Polinom<float> P(4, coef1), Q(2, coef2), X(2);
    cout<<"Polinomul X: ";
    cin >> X;
    cout << "Valoarea in pct 1 a polinomului X este " << X.getValueInPoint(1) << "\n";

    cout << "Gradul polinomului X este " << X.getDegree() << "\n";
    cout << "Coeficienti: " << X[0] << " " << X[1] << " " << X[2] << "\n";

    cout << "\nX: " << X << "\n Q: " << Q;
    P = Q + X;
    cout << "\nQ+X = " << P;
    cout << "\nQ * X: " << Q * X;
    cout << "\nQ: "<< Q;
    cout << "\nQ*3: " << Q*3;
    cout << Q;

    // adaug la Polinomul q un termen de grad 10 si coeficient 15
    P.add(7, 14);
    cout << P;
    // sterge din polinomul q termenul de grad 4
    Q.remove(4);
    cout << P;
    return 0;
}