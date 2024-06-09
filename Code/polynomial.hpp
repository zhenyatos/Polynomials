#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Polynomial {
private:
    vector<int> coefficients;
    const int NEG_INF = INT_MIN; // Degree of the zero polynomial

public:
    // Creates the zero polynomial
    Polynomial() {};

    /* 
    Creates a polynomial out of a given dense list 
    of coefficients, e.g.
    {1, 0, 2, -1} -> 1 + 2x^2 - x^3

    Trims the redundant zeros at the end of the vector, 
    this property can be assumed to be hold for all the objects 
    of type Polynomial.
    */
    Polynomial(const vector<int>& coeff)
        : coefficients(coeff)
    {
        while (coefficients.back() == 0)
            coefficients.pop_back();
    }

    Polynomial add(const Polynomial& other) const {
        // TODO
    }

    Polynomial multiply(const Polynomial& other) const {
        // TODO
    }

    /* 
    Get a polynomial degree, that is the highest power of a variable 
    in a polynomial expression
    */
    int getDegree() {
        if (coefficients.size() == 0)
            return NEG_INF;
        return coefficients.size() - 1;
    }

    bool operator==(const Polynomial& poly) { 
        if (coefficients.size() != poly.coefficients.size())
            return false;
        int n = coefficients.size();
        for (int i = 0; i < n; i++) {
            if (coefficients[i] != poly.coefficients[i])
                return false;
        }
        return true;
    } 

    friend ostream& operator<<(ostream& os, const Polynomial& poly);
};

ostream& operator<<(ostream& os, const Polynomial& poly) {
    int n = poly.coefficients.size();
    if (n == 0) {
        cout << 0;
        return os;
    }

    n = n - 1;
    int k = n;
    string sign;
    
    for (auto it = poly.coefficients.rbegin(); it != poly.coefficients.rend(); ++it, k--) { 
        if (*it == 0)
            continue;
        else
            sign = *it > 0 ? " + " : " - ";
        if (k == n)
            sign = "";
        
        int c = abs(*it);
        if ((c != 1) || (k == 0))
            cout << sign << c;
        else 
            cout << sign;
            
        if (k == 1)
            cout << "x";
        else if (k != 0)
            cout << "x^" << k;  
    }
    return os;
}