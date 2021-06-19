#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#define INF 1000000

void	output (int count, int *result, int apex, int mode)
{
	int i;

	if (mode == 0)
		printf ("%s\n", "Deikstra:");
	else
		printf ("%s\n", "Ford-Bellman:");
	for (i = 0; i < count; i++)
	{
		// если существует путь
		if (result[i] < INF)
			printf("Minimal length for %d to %d = %d\n", apex, \
			i , result[i]);
		else
			printf("Minimal length for %d to %d = INF\n", apex, \
			i);
	}
}

void Ford_Ballman(int CountApex, int **SourceMatrix, int Start)
{
	int *MinPath; //выходной массив с расстояниями до всех вершин
	int i, j, k;
	int	count = 0;
	MinPath = (int *)malloc(CountApex * sizeof(int));

	for (i = 0; i < CountApex; i++)
		MinPath[i] = INF; //В начале минимальных путей до вершины не существует

	MinPath[Start] = 0;//Минимальное расстояние от старта до него самого 0

	i = 0;
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

	for (k = 0; k < CountApex; k++)
	{
		for (i = 0; i < CountApex; ++i)
		{
			for (j = 0; j < CountApex; ++j)
			{
				if (SourceMatrix[i][j] != 0) //если вершину не посещали
					if (MinPath[j] > MinPath[i] + SourceMatrix[i][j])
						MinPath[j] = MinPath[i] + SourceMatrix[i][j];
			}
		}
	}
	output(CountApex, MinPath, Start, 1);
}

void	deikstra(int CountApex, int **SourceMatrix, int Start)
{
	int	*metka; //Массив из меток с посещенными вершинами
	int	*MinPuth; //Выходной массив из минимальных расстояний до вершин
	int	temp, i;
	int	minindex, min;

	metka = (int *)malloc(CountApex * sizeof(int));
	MinPuth = (int *)malloc(CountApex * sizeof(int));

	for (i = 0; i < CountApex; i++)
	{
		MinPuth[i] = INF;
		metka [i] = 1;
	}

	MinPuth[Start] = 0;

	do
	{
		minindex = INF;
		min = INF;
		for (i = 0; i < CountApex; i++)
		{
			if ((metka[i] == 1) && (MinPuth[i] < min))
			{
				min = MinPuth[i];
				minindex = i;
			}
		}
		if (minindex != INF)
		{
			for (i = 0; i < CountApex; i++)
			{
				if (SourceMatrix[minindex][i] > 0)
				{
					temp = min + SourceMatrix[minindex][i];
					if (temp < MinPuth[i])
						MinPuth[i] = temp;
				}
			}
			metka[minindex] = 0;
		}
	} while (minindex < INF);
	output (CountApex, MinPuth, Start, 0);
}

int main()
{
	int apex;
	int CountApex;//количество вершин в графе
	int **mputh;//наша матрица с ребрами
	int i, j = 0;
	int negative = 0;
	float start, end;
	FILE *in;
	char filename[20];

	printf ("The name of file: ");
	scanf("%s", filename);
	in = fopen(filename, "r");

	if (!in)
		printf("Error!");
	else
		printf("Read graf!\n");

	fscanf(in, "%d", &CountApex);

	mputh = (int **)malloc(CountApex * sizeof(int *));
	for (int i = 0; i < CountApex; i++)
		mputh[i] = (int *)malloc(CountApex * sizeof(int));

	for (i = 0; i < CountApex; i++)
	{
		for (j = 0; j < CountApex; j++)
		{
			fscanf(in, "%d", &mputh[i][j]);
			if (mputh[i][j] < 0)
				negative++;
		}
	}

	printf("Succsesfull reading\n");
	printf("The start Apex is: ");
	scanf("%d", &apex);
	deikstra(CountApex, mputh, apex);

	if (negative != 0)
		printf("Incorrect work of Deickstra algoritm\n");

	printf("\n\n");
	Ford_Ballman(CountApex, mputh, apex);
	return 0;
}
