#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

class Polynomial {
private:
    vector<double> coefficients;
    const int NEG_INF = INT_MIN; // Degree of the zero polynomial
    const double TOLERANCE = 1e-10;

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
    Polynomial(const vector<double>& coeff)
        : coefficients(coeff)
    {
        while (!coefficients.empty() && (abs(coefficients.back() - 0.0) < TOLERANCE))
            coefficients.pop_back();
    }

    Polynomial add(const Polynomial& other) const {
        int m = coefficients.size();
        int n = other.coefficients.size();
        
        int d = max(m, n);
        vector<double> coeff;
        if (d == m) {
            coeff = coefficients;
            for (int i = 0; i < n; i++)
                coeff[i] += other.coefficients[i];
        }
        else {
            coeff = other.coefficients;
            for (int i = 0; i < m; i++)
                coeff[i] += coefficients[i];
        }
        
        return Polynomial(coeff);
    }

    Polynomial multiply(const Polynomial& other) const {
        int m = coefficients.size();
        int n = other.coefficients.size();
        if (m == 0 || n == 0)
            return Polynomial();

        vector<double> coeff(m + n, 0.0);

        for (int i = 0; i < coefficients.size(); i++) {
            for (int j = 0; j < other.coefficients.size(); j++) {
                coeff[i + j] += coefficients[i] * other.coefficients[j];
            }
        }

        return Polynomial(coeff);
    }

    std::pair<Polynomial, Polynomial> divmod(const Polynomial& other) const {
        // TODO
        return std::make_pair(Polynomial(), Polynomial());
    }

    /* 
    Evaluates polynomial as a function using Horner's method
    */
    double operator()(double x) {
        int n = coefficients.size();
        if (n == 0)
            return 0.0;
        
        double val = coefficients[n-1];

        for (int i = 1; i < n; i++) {
            val *= x; 
            val += coefficients[n-i-1];
        }

        return val;
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
            if (abs(coefficients[i] - poly.coefficients[i]) >= TOLERANCE)
                return false;
        }
        return true;
    } 
    
    /*
    Compute the gcd of two polynomials with 1 as a leading coefficient.
    */
    friend Polynomial gcd(const Polynomial& f, const Polynomial& g);

    friend ostream& operator<<(ostream& os, const Polynomial& poly);
};

Polynomial gcd(const Polynomial& f, const Polynomial& g) {
    // TODO
    return Polynomial();
}

Polynomial interpolate(const std::vector<double> x, const std::vector<double> y) {
    // TODO
    return Polynomial();
}

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
        
        double c = abs(*it);
        if ((abs(c - 1.0) >= poly.TOLERANCE) || (k == 0))
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