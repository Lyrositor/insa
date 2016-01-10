#include <stdio.h>

int main()
{
    const int NB_VALEURS = 21;
    int histogramme[NB_VALEURS] = {0};
    int n;
    fscanf(stdin, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        float val;
        fscanf(stdin, "%f", &val);
        int indice = (int) val;
        histogramme[indice]++;
    }
    for (int i = 0; i < NB_VALEURS; i++)
        printf("%d\r\n", histogramme[i]);
    return 0;
}
