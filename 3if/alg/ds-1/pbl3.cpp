#include <stdio.h>

int main()
{
    const   int MAX_VALEURS = 5000;
    int sequence[MAX_VALEURS] = {0};
    int max = 0;

    // Lire le nombre de valeurs
    int n;
    fscanf(stdin, "%d", &n);

    // Lire les valeurs
    for (int i = 0; i < n; i++)
    {
        int val;
        fscanf(stdin, "%d", &val);
        sequence[i] = val;
        max += val;
    }

    // Trouver le maximum.
    for (int debut = 0; debut < n; debut++)
    {
        if (sequence[debut] <= 0) {
            continue;
        }
        for (int fin = n; fin > debut; fin--)
        {
            if (sequence[fin - 1] <= 0)
                continue;

            int somme = 0;
            for (int i = debut; i < fin; i++)
                somme += sequence[i];

            if (somme > max)
                max = somme;
        }
    }

    printf("%d\r\n", max);
    return 0;
}
