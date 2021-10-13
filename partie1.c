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
    printf("%lf\n", xRecursive(100));
    return 0;
}