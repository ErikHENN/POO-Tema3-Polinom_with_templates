//
// Created by Erik on 5/16/2018.
//

#ifndef POLINOM_TEMA3_POLINOM_H
#define POLINOM_TEMA3_POLINOM_H


#include <iostream>
#include <fstream>
using namespace std;

template <class TipDate> class Polinom {
    int degree; 
    TipDate *coef; 
public:
    Polinom();
    Polinom(int n); 
    Polinom(int n, int v[]);// grad n cu toti coeficientii initializati cu vectorul x
    Polinom(Polinom &obj);// constructorul de copiere
    ~Polinom();
    int getDegree();
    long long getValueInPoint(int i); 
    int operator [](int i); // iau termen cu gradul i
    Polinom & operator = (const Polinom & p); 
    Polinom operator +(const Polinom &a); 
    Polinom operator *(const Polinom &a); 
    Polinom operator *(int x);
    Polinom operator /(const Polinom &b); //impart polinoamele

    template <class Tip2>
    friend istream &operator>>(istream &in, Polinom<Tip2> &p);
    template <class Tip2>
    friend ostream &operator<<(ostream &out, const Polinom<Tip2> &p);

    Polinom& add(int newDegree, int newCoef); // adaugare monom de grad i si coeficient dat
    Polinom& remove(int deletedDegree); // stergere monom de grad i
};


/**
 *
 * @tparam TipDate
 * Constructor fara parametrii
 * Initializez polinomul cu 0
 */
template <class TipDate>
Polinom<TipDate>::Polinom() {
    degree = 0;
    coef = new TipDate[1];
    coef[0] = 0;
}

/**
 *
 * @tparam TipDate
 * @param n - grad
 * Initializez polinom de grad @n cu toti coeficientii 0
 */
template <class TipDate>
Polinom<TipDate>::Polinom(int n) {
    degree = n;
    coef = new TipDate[n + 1];
    for (int i = 0; i <= n; i++)
        coef[i] = 0;
}

/**
 *
 * @tparam TipDate
 * @param n - grad
 * @param v  - vector de coeficienti
 * Initializez polinomul de grad N cu coeficienti din vectorul V
 */
template <class TipDate>
Polinom<TipDate>::Polinom(int n, int *v) {
    degree = n;
    coef = new TipDate[n + 1];
    for (int i = 0; i <= n; i++)
        coef[i] = v[i];
}

/**
 *
 * @tparam TipDate
 * @param obj - Polinom de copiat
 * Constructor de copiere
 */
template <class TipDate>
Polinom<TipDate>::Polinom(Polinom<TipDate> &obj) {
    degree = obj.degree;
    coef = new TipDate[degree + 1];
    for (int i = 0; i <= degree; i++)
        coef[i] = obj.coef[i];
}
/**
 *
 * @tparam TipDate
 * Destructor
 */
template <class TipDate>
Polinom<TipDate>::~Polinom() {
    delete[] coef;
}

/**
 *
 * @tparam TipDate
 * @return - gradul polinomului
 */
template <class TipDate>
int Polinom<TipDate>::getDegree() {
    return degree;
}

/**
 *
 * @tparam TipDate
 * @param x - punctul
 * @return - Valoarea polinomului in pct X
 */
template <class TipDate>
long long Polinom<TipDate>::getValueInPoint(int x) {
    int power = x;
    long long value = coef[0];
    for (int i = 1; i <= degree; i++) {
        value = value + coef[i] * power;
        power *= x;
    }
    return value;
}

/**
 *
 * @tparam TipDate
 * @param in
 * @param p
 * @return - Polinomul citit
 * Supraincarcarea operatorului de citire
 */
template <class TipDate>
istream &operator>>(istream &in, Polinom<TipDate> &p) {
    cout << "\nGradul polinomului: ";
    in >> p.degree;
    cout << "\nCoeficientii polinomului: ";
    p.coef = new TipDate[p.degree + 1];
    for (int i = 0; i <= p.degree; i++)
        in >> p.coef[i];
}
/**
 *
 * @tparam TipDate
 * @param out
 * @param p
 * @return - afisez gradul + coef
 * Supraincarc operator scriere
 */
template <class TipDate>
ostream &operator<<(ostream &out, const Polinom<TipDate> &p) {
    out << "Gradul polinomului este " << p.degree << " si are forma: ";
    for (int i = 0; i < p.degree; i++)
        out << p.coef[i] << "x^" << i << "+";
    out << p.coef[p.degree] << "x^" << p.degree << "\n";
}

/**
 *
 * @tparam TipDate
 * @param p
 * @return
 * Operator = : atribuire
 */
template <class TipDate>
Polinom<TipDate>& Polinom<TipDate>::operator=(const Polinom<TipDate> &p) {
    degree = p.degree;
    delete[] coef;
    coef = new TipDate[degree + 1];
    for (int i = 0; i <= degree; i++)
        coef[i] = p.coef[i];
    return *this;
}

/**
 *
 * @tparam TipDate
 * @param a
 * @return
 * Adunarea polinoamelor
 * Gradul polinomului nou va fi maximul dintre gradul celorlalte 2 polinoame intrate in ecuatie
 * Adunarea se va face grad cu grad (coeficientii cu acelasi grad)
 */
template <class TipDate>
Polinom<TipDate> Polinom<TipDate>::operator+(const  Polinom<TipDate> &a) {
    Polinom<TipDate> c(max(a.degree, degree));
    for (int i = 0; i <= c.degree; i++)
        if (i <= a.degree && i <= degree) {
            c.coef[i] = a.coef[i] + coef[i];
        } else if (i <= a.degree) {
            c.coef[i] = a.coef[i];
        } else {
            c.coef[i] = coef[i];
        }
    return c;
}

/**
 *
 * @tparam TipDate
 * @param i - grad
 * @return - Coeficientul cu gradul @i
 */
template <class TipDate> int Polinom<TipDate>::operator[](int i) {
    if (i <= degree && i >= 0) {
        return coef[i];
    }
}

/**
 *
 * @tparam TipDate
 * @param x  - Scalar
 * @return - Polinomul nou
 * Inmultirea unui polinom cu scalar
 * Inultesc fiecare coeficient cu @x
 */
template <class TipDate>
Polinom<TipDate> Polinom<TipDate>::operator*(int x) {
    Polinom<TipDate> c(degree);
    for (int i = 0; i <= degree; i++)
        c.coef[i] = coef[i] * x;
    return c;
}

/**
 *
 * @tparam TipDate
 * @param a
 * @return - Polinoamele inmultite
 * Inultirea polinoamelor
 * Gradul nou va fi suma gradelor polinoamelor intrate in ecuatie.
 */
template <class TipDate>
Polinom<TipDate> Polinom<TipDate>::operator*(const  Polinom<TipDate> &a) {
    Polinom<TipDate> c(a.degree + degree);
    for (int i = 0; i <= degree; i++)
        for (int j = 0; j <= a.degree; j++)
            c.coef[i + j] += coef[i] * a.coef[j];
    return c;
}

/**
 *
 * @tparam TipDate
 * @param newDegree - gradul noului termen adaugat
 * @param newCoef - coeficientul noului termen adaugat
 * @return
 * Adaug termenul cu grad @newDegree si coef. @newCoef doar daca pozitia este libera.
 * Daca gradul nou este mai mare decat gradul maxim curent al polinomului aloc memorie suplimentara
 *
 */
template <class TipDate>
Polinom<TipDate> & Polinom<TipDate>::add(int newDegree, int newCoef) {
// adauga un termen de grad newDegree cu coeficientul newCoef
// adaug termenul numai daca pozitia este libera
// in cazul in care newDegree e mai mare decat gradul curent al polinomului, aloc din nou memorie pentru polinom
    int i;
    if (newDegree >= 0) {
        if (newDegree <= degree) {
            if (!coef[newDegree]) {
                coef[newDegree] = newCoef;
            }
        } else {
            Polinom<TipDate> aux(*this);
            degree = newDegree;
            delete[] coef;
            coef = new TipDate[degree + 1];
            for (i = 0; i <= degree; i++)
                coef[i] = 0;
            for (i = 0; i <= aux.degree; i++)
                coef[i] = aux.coef[i];
            coef[newDegree] = newCoef;
        }
    }
    return *this;
}
/**
 *
 * @tparam TipDate
 * @param deletedDegree - coeficientul cu grad @deletedDegreee ce trebuie sters
 * @return Polinom fara gradul @deletedDegree
 * Daca @deletedDegree exista sterg termenul facandu-i coeficientul 0.
 * Daca @deletedDegree este gradul maxim al polinomului dezaloc memorie  dupa ce actualizez gradul maxim.
 * Stergere termen de grad deletedDegree
 */
template <class TipDate>
Polinom<TipDate> &Polinom<TipDate>::remove(int deletedDegree) {
    if (deletedDegree >= 0 && deletedDegree < degree) {
        coef[deletedDegree] = 0;
    } else if (deletedDegree == degree) {
        Polinom<TipDate> aux(*this);
        coef[deletedDegree] = 0;
        while (!coef[degree])
            degree--;
        coef = new TipDate[degree + 1];
        for (int i = 0; i <= degree; i++)
            coef[i] = aux.coef[i];
    }
    return *this;
}

/**
 *
 * @tparam TipDate
 * @param b
 * @return - Rezultatul impartirii
 * Impartirea a 2 polinoame
 * Gradul nou va fi diferenta gradelor celor 2 polinoame care intra in ecuatie
 * Impart coeficient cu coeficient si dupa actualizez polinomul deimpartit cat timp gradul deimpartitului este mai mare.
 */
template <class TipDate>
Polinom<TipDate>  Polinom<TipDate>::operator/(const  Polinom<TipDate>&b) {
    Polinom<TipDate> a(*this);
    Polinom<TipDate> c(a.degree - b.degree);
    int k = c.degree;

    while (a.degree >= b.degree) {
        if (a.degree == b.degree) {
            c.coef[k] = a.coef[a.degree] / b.coef[b.degree];
        } else {
            c.coef[k] = a.coef[a.degree];
        }

        for (int i = a.degree, j = b.degree; j >= 0; i--, j--) {
            a.coef[i] = a.coef[i] - c.coef[k] * b.coef[j];
        }
        a.degree--;
        k--;
    }
    return c;
}


#endif //POLINOM_TEMA3_POLINOM_H
