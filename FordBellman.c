#include <stdio.h>
#include <stdlib.h>
// Если не существует пути из одной вершины в другую, то расстояние между ними равно бесконечности
#define INF 1000000

void Ford_Bellman(int CountApex, int **SourceMatrix, int Start, int End)
{
    int *MinChek;//массив предшественников вершин
    int *MinPath;//выходной массив с расстояниями до всех вершин
    int *MinWay;//выходной массив с траекторией движения
    int i, j, k, l;

    // Если пути из одной вершины в другую не существует, то во входной матрице это указано, как -1;
    for (i = 0; i < CountApex; i++)
        for (j = 0; j < CountApex; j++)
            if (SourceMatrix[i][j] == -1)
                SourceMatrix[i][j] = INF;
    
    // Создание массива минимальных расстояний до всех вершин
    MinPath = (int *)malloc(CountApex * sizeof(int));
    if (MinPath == NULL)
    {
        printf("Error malloc for MinPath");
        return ;
    }
    //Изначально минимальных путей до вершин не существует
    for (i = 0; i < CountApex; i++)
        MinPath[i] = INF;
    //Минимальное расстояние от старта до него самого 0
    MinPath[Start] = 0;

    // Создание массива вершин предшественников
    MinChek = (int *)malloc (CountApex * sizeof(int));
    if (MinChek == NULL)
    {
        printf("Error malloc for MinChek");
        return ;
    }
    //изначально в массиве невозможные значения
    for (i = 0; i < CountApex; i++)
        MinChek[i] = -1;

    // Основная часть алгоритма
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

    // Создание массива под траекторию робота
    // Кол-во вершин в траектории не может быть больше CountApex:
    MinWay = (int *)malloc(sizeof(int) * CountApex);
    if (MinWay == NULL)
    {
        printf("Error MinWay");
        return ;
    }
    // изначально массив содержит невозможные значениея
    for (i = 0; i < CountApex; i++)
        MinWay[i] = -1;

    // Восстанавливаем путь от конца до старта через массив предшественников
    int u = End;
    i = 0;
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
    // добавляем последнее значение из массива предшественников
    MinWay[i] = u;
    // добавляем стартовое значение
    MinWay[++i] = Start;

    // распечатка траектории(делаем реверс, убираем оставшиеся -1)
    for (l = i; l >= 0; l--)
                printf ("%d ", MinWay[l]);
            printf("\n");

    //распечатка длины траектории
    printf ("%d\n", MinPath[End]);
}

int main()
{
    int apex;//стартовая вершина
    int end_apex;//конечная вершина
    int CountApex;//количество вершин в графе
    int **mputh;//входная матрица с весами ребер
    char filename[30];

    // открытие файла с входной матрицей
    FILE *in;
    printf ("The name of file: \n");
    scanf("%s", filename);
    in = fopen(filename, "r");
    if (!in)
        printf("Can't open a file!\n");
    else
        printf("Read graf!\n");

    // первый элемент файла указывает на количество вершин графа
    fscanf(in, "%d", &CountApex);
    // выделяем необходимое место в памяти под матрицу
    mputh = (int **)malloc(CountApex * sizeof(int *));
    for (int i = 0; i < CountApex; i++)
        mputh[i] = (int *)malloc(CountApex * sizeof(int));
    // заполняем созданную память матрицы значениями из файла
    for (int i = 0; i < CountApex; i++)
        for (int j = 0; j < CountApex; j++)
            fscanf(in, "%d", &mputh[i][j]);
    printf("Succsesfull reading\n");
    
    // считываем начальную вершину
    printf("The start Apex is: \n");
    scanf("%d", &apex);
    // считываем конечную вершину
    printf("The end Apex is: \n");
    scanf("%d", &end_apex);
    
    Ford_Bellman(CountApex, mputh, apex, end_apex);
    
    return 0;
}
