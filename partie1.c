#include <stdio.h>

/**
 * Approxime exp(1) sans recalculer 1/(n!) à chaque itération
 * @param unsigned int nombre d'itérations
 * @return double exp(1) approximé
 **/
double exponentielle(unsigned int limit)
{
    double output = 1;
    double u = 1;
    for (int n = 1; n < limit; n++)
    {
        u /= n;
        output += u;
    }
    return output;
}

/**
 * Calcule x^n avec n ∈ ℤ
 * @param double x
 * @param int n
 * @return double x^n
 **/
double puissance(double x, int n)
{
    double output = 1;
    // ici j'utilise un do while pour éviter de regarder
    // deux fois si n est positif ou négatif : on gagne un
    // check au coût d'un peu de lisibilité.
    if (n > 0)
        do
        {
            output *= x;
            n--;
        } while (n > 0);
    else
        for (; n < 0; n++)
            output /= x;
    return output;
}

/**
 * Similaire à puissance mais avec des floats
 * @param float x
 * @param int n
 * @return double x^n
 **/
float puissanceFloat(float x, int n)
{
    float output = 1;
    if (n > 0)
        do
        {
            output *= x;
            n--;
        } while (n > 0);
    else
        for (; n < 0; n++)
            output /= x;
    return output;
}

/**
 * Fonction power iteratif : x^n = x*x^(n-1)
 * @param float x
 * @param unsigned int n
 * @return double x^n
 **/
double powerIt(float x, unsigned int n)
{
    double output = 1;
    while (n > 0)
    {
        output *= x;
        n--;
    }
    return output;
}

/**
 * Fonction power recursif : x^n = x*x^(n-1)
 * @param float x
 * @param unsigned int n
 * @return double x^n
 **/
double powerRec(float x, unsigned int n)
{
    if (n == 0) return 1;
    return x*powerRec(x, n-1);
}

/**
 * Fonction power : x^p = x^(p/2) * x^(p/2)
 * @param float x
 * @param unsigned float p
 * @return double x^p
 **/
double powerP(float x, unsigned int p)
{
    if (p == 0) return 1;
    double output = powerP(x, p/2);
    if (p%2 == 0) { // si pair
        return output * output;
    } else { // si impair
        return output * output * x;        
    }
}

/**
 * Fonction intermediaire pour power recursif terminal
 * @param float x
 * @param unsigned int n
 * @param double acc
 * @return double x^n
 **/
double powerRecTermBis(float x, unsigned int n, double acc)
{
    if (n == 0) return acc;
    return powerRecTermBis(x, n-1, x*acc);
}

/**
 * Fonction power recursif terminal
 * @param float x
 * @param unsigned int n
 * @return double x^n
 **/
double powerRecTerm(float x, unsigned int n)
{
    return powerRecTermBis(x, n, 1);
}

/**
 * Fonction d'Ackermann
 * @param unsigned int m
 * @param unsigned int n
 * @return A(m, n)
 **/
unsigned int ackermann(unsigned int m, unsigned int n)
{
    if (m == 0)
        return n + 1;

    if (n == 0)
        return ackermann(m - 1, 1);

    return ackermann(m - 1, ackermann(m, n - 1));
}

/**
 * Suite X(n), version itérative
 * @param unsigned int n
 * @return X(n)
 **/
double xIterative(unsigned int n)
{
    double x = 1.0;
    for (; n > 0; n--)
        x = x + 1 / x;
    return x;
}

/**
 * Suite X(n), version récursive (nulle)
 * @param unsigned int n
 * @return X(n)
 **/
double xRecursive(int n)
{
    if (n == 0)
        return 1;
    double prev = xRecursive(n - 1);
    return prev + 1 / prev;
}

int main()
{
    //printf("%lf", puissance(1.001, 1000));
    //printf("%ld", ackermann(5, 0));
    //printf("%lf\n", xRecursive(100));
    printf("%lf\n", powerIt(10.5, 3));
    printf("%lf\n", powerRec(10.5, 3));
    printf("%lf\n", powerRecTerm(10.5, 3));
    printf("%lf\n", powerP(10.5, 3));
    return 0;
}