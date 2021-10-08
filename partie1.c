// Exercice 1

int factorielle(long unsigned int n) {
    return n == 0 ? 1 : n * factorielle(n-1);
}

float exponentielle(long unsigned int lim) {
    return lim == 0 ? 1 : 1/factorielle(lim) + exponentielle(lim-1);
}

// int Puissance(float x, int n) {}

