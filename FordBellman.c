#include <stdio.h>
#include <stdlib.h>
#define INF 1000000

void Ford_Bellman(int CountApex, int **SourceMatrix, int Start, int End)
{
    int *MinChek;//массив предшественников вершин
    int *MinPath;//выходной массив с расстояниями до всех вершин
    int *MinWay;//выходной массив с траекторией движения
    int i, j, k, l;
    int    count = 0;


    MinPath = (int *)malloc(CountApex * sizeof(int));
    if (MinPath == NULL)
    {
        printf("Error MinPath");
        return ;
    }

    for (i = 0; i < CountApex; i++)
        MinPath[i] = INF;//В начале минимальных путей до вершины не существует

    MinPath[Start] = 0;//Минимальное расстояние от старта до него самого 0

    i = 0;// забиваем нужные элементы матрицы бесконечностями
    while (i < CountApex)
    {
        j = 0;
        while (j < CountApex)
        {
            if (SourceMatrix[i][j] == 999)
                SourceMatrix[i][j] = INF;
            j++;
        }
        i++;
    }

    //создание массива вершин предшественников
    MinChek = (int *)malloc (CountApex * sizeof(int));
    if (MinChek == NULL)
    {
        printf("Error MinChek");
        return ;
    }
    i = 0;
    while (i < CountApex)
    {
        //вначале забиваем массив невозможным значением вершин
        MinChek[i] = -1;
        i++;
    }

    for (k = 0; k < CountApex; k++)
    {
        for (i = 0; i < CountApex; ++i)
        {
            for (j = 0; j < CountApex; ++j)
            {
                if (SourceMatrix[i][j] != 0) //если вершину не посещали
                    if (MinPath[j] > MinPath[i] + SourceMatrix[i][j])
                    {
                        MinPath[j] = MinPath[i] + SourceMatrix[i][j];
                        MinChek[j] = i;//заполняем массив предшественников
                    }
            }
        }
    }
    for (l = 0; l < CountApex; l++)//распечатка результата с кратчайшими путями
                printf ("%d ", MinPath[l]);
            printf("\n");

    for (l = 0; l < CountApex; l++)//распечатка результата предшественников
                printf ("%d ", MinChek[l]);
            printf("\n");

    //создание массива под траекторию робота
    MinWay = (int *)malloc(sizeof(int) * CountApex);
    if (MinWay == NULL)
    {
        printf("Error MinWay");
        return ;
    }
    i = 0;
    while (i < CountApex)
    {
        //вначале забиваем массив невозможным значением вершин
        MinWay[i] = -1;
        i++;
    }

    i = 0;
    int u = End;//отдельная переменная под конечные значения
    while (MinChek[u] != Start)
    {
        MinWay[i] = u;
        u = MinChek[u];
        if (u == -1)
        {
            printf("The path does not exist!");
            break;
        }
        i++;
    }
    //вбиваем в массив последнее значение из массива предшественников
    if (MinChek[u] == Start)
    {
        MinWay[i] = u;
        i++;
    }
    //добавляем последнее значение
    MinWay[i] = Start;

    for (l = 0; l < CountApex; l++)//распечатка результата траектории
                printf ("%d ", MinWay[l]);
            printf("\n");

    int *RezWay;//Массив траектории в удобном виде
    int SizeWay = 0;//количество элементов итогового массива
    while (MinWay[SizeWay] != -1)
        SizeWay++;
    RezWay = (int *)malloc(sizeof(int) * SizeWay);
    if (RezWay == NULL)
    {
        printf("Error RezWay");
        return ;
    }
    i = SizeWay - 1;
    l = 0;
    while (i >= 0)
    {
        RezWay[i] = MinWay[l];
        i--;
        l++;
    }
    for (l = 0; l != SizeWay; l++)//распечатка результата в удобном виде
                printf ("%d ", RezWay[l]);
            printf("\n");
    printf ("%d\n", MinPath[End]);//распечатка значения кратчайшего пути
}

int main()
{
    int apex;//стартовая вершина
    int end_apex;//конечная вершина
    int CountApex;//количество вершин в графе
    int **mputh;//входная матрица с весами ребер
    int i, j = 0;
    float start, end;
    FILE *in;
    char filename[20];

    //открытие нужного файла с входной матрицей
    printf ("The name of file: ");
    scanf("%s", filename);
    in = fopen(filename, "r");

    if (!in)
        printf("Error!");
    else
        printf("Read graf!\n");

    //первый элемент файла указывает на количество вершин графа
    fscanf(in, "%d", &CountApex);
    //выделяем необходимое место в памяти под матрицу
    mputh = (int **)malloc(CountApex * sizeof(int *));//нулевой столбец указателей
    for (int i = 0; i < CountApex; i++)//память под каждую строку матрицы
        mputh[i] = (int *)malloc(CountApex * sizeof(int));
    //заполняем созданную память матрицы значениями из файла
    for (i = 0; i < CountApex; i++)
    {
        for (j = 0; j < CountApex; j++)
            fscanf(in, "%d", &mputh[i][j]);
    }

    printf("Succsesfull reading\n");
    printf("The start Apex is: ");
    scanf("%d", &apex);//считываем начальную вершину
    printf("The end Apex is: ");
    scanf("%d", &end_apex);//считываем конечную вершину
    Ford_Bellman(CountApex, mputh, apex, end_apex);
    return 0;
}
