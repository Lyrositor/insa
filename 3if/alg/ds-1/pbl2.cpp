#include <stdio.h>

int main()
{
    const int NB_VALEURS = 21;
    int histogramme[NB_VALEURS] = {0};
    int max = 0;

    // Lire les valeurs
    for (int i = 0; i < NB_VALEURS; i++)
    {
        int val;
        fscanf(stdin, "%d", &val);
        histogramme[i] = val;
        if (val > max)
            max = val;
    }

    // Afficher l'histogramme
    for (int i = max; i > 0; i--)
    {
        for (int j = 0; j < NB_VALEURS; j++)
        {
            if (histogramme[j] >= i)
                printf("** ");
            else
                printf("   ");
        }
        printf("\r\n");
    }

    // Afficher les indices
    for (int i = 0; i < NB_VALEURS; i++)
    {
        printf("%2d ", i);
    }
    printf("\r\n");

    return 0;
}
