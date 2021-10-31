#include <stdio.h>
#include <time.h>

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
 * Calcule x^n avec n ∈ ℤ de maniere iterative : x^n = x*x^(n-1)
 * @param float x
 * @param int n
 * @return double x^n
 **/
double powerIt(float x, int n)
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
 * Similaire à powerIt mais avec un double
 * @param double x
 * @param int n
 * @return double x^n
 **/
float powerItDouble(double x, int n)
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
 * Fonction d'Ackermann recursive
 * @param unsigned int m
 * @param unsigned int n
 * @return A(m, n)
 **/
unsigned int ackermannRec(unsigned int m, unsigned int n)
{
    if (m == 0)
        return n + 1;

    if (n == 0)
        return ackermannRec(m - 1, 1);

    return ackermannRec(m - 1, ackermannRec(m, n - 1));
}

/**
 * Fonction d'Ackermann iterative et recursive
 * @param unsigned int m
 * @param unsigned int n
 * @return A(m, n)
 **/
unsigned int ackermannIt(unsigned int m, unsigned int n)
{
    unsigned int output = n+1; // Cas ou m == 0
    while(m > 0)
    {
        if (n != 0)
            ackermannIt(m-1, ackermannIt(m, n-1));
    }
    return output;
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
    ////////////////////// Exercice puissance //////////////////////
    
    /* Comparaison des temps de calcul :  calcul de 1.001^1000 */
    clock_t start, end;
    float p;

    // Version iterative
    start = clock();
    p = powerIt(1.001, 1000);
    end = clock();
    printf("fonction puissance iterative, resultat : %f temps : %f ms\n", p, ((double) end - start) / 1000);

    // Version recursive
    start = clock();
    p = powerRec(1.001, 1000);
    end = clock();
    printf("fonction puissance recursive, resultat : %f temps : %f ms\n", p, ((double) end - start) / 1000);

    // Version p/2
    start = clock();
    p = powerP(1.001, 1000);
    end = clock();
    printf("fonction puissance p = (p^(1/2))^2, resultat : %f temps : %f ms\n", p, ((double) end - start) / 1000);

    // Version recursive terminale
    start = clock();
    p = powerRecTerm(1.001, 1000);
    end = clock();
    printf("fonction puissance recursive terminale, resultat : %f temps : %f ms\n", p, ((double) end - start) / 1000);

    // Comparaison float vs double
    float f = powerIt(1.001, 1000);
    double d = powerItDouble(1.001, 1000);
    printf("\nComparons la difference de precision entre float et double :\n float:  %f\n double: %lf\n\n", f, d);
    
    /* Observations:
        Rapidite :
        La plus rapide est la fonction qui utilise le resultat p = (p^(1/2))^2 
        et qui appelle donc recursivement en divisant le probleme en 2 parties a chaque fois.

        Precision :
        Le resultat obtenu n'est pas le meme en fonction de la precision
    */

    ////////////////////// Exercice Ackermann //////////////////////

    for (int m = 0; m < 5; m++ ) // La sixieme valeur est trop longue a calculer
        printf("A(%d, 0) = %d\n", m, ackermannRec(m, 0));

    //////////////////////     Exercice X     //////////////////////
    
    // Comparons le temps d'execution des deux versions
    // Version Iterative
    start = clock();
    double X1 = xIterative(100);
    end = clock();
    double timeIt = ((double) end - start) / 1000;

    // Version Recursive
    start = clock();
    double X2 = xRecursive(100);
    end = clock();
    double timeRec = ((double) end - start) / 1000;

    printf("\n\nLa version iterative met: %f ms a calculer %f\nLa version recursive met: %f ms a caculer %f", timeIt, X1, timeRec, X2);
    // La version iterative est plus rapide pour le meme resultat

    return 0;
}