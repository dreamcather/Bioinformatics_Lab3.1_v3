// Lab5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <vector>

int Size_Motiv;
int Count_Examples;
int Exaples_Lenght;
char ** Examples;
int* Counter;
bool CountPlus(int *mas, int count, int lenght, int size)
{
	for (int i = count - 1; i >= 0; i--)
	{
		if (mas[i] < (lenght - size))
		{
			mas[i]++;
			return true;
		}
		else
		{
			mas[i] = 0;
		}
	}
	return false;
}
int LocalScore(int step,int count)
{
	char* mas = new char[count];
	int * col = new int[4];
	for (int i = 0; i < count; i++)
	{
		mas[i] = Examples[i][Counter[i] + step];
	}
	for (int i = 0; i < 4; i++)
	{
		col[i] = 0;
	}
	for (int i = 0; i < count; i++)
	{
		if (mas[i] == 'A')
			col[0]++;
		else
			if (mas[i] == 'C')
				col[1]++;
			else
				if (mas[i] == 'G')
					col[2]++;
				else
					if (mas[i] == 'T')
						col[3]++;
	}
	int max = col[0];
	for (int i = 1; i < 4; i++)
	{
		if (col[i] > max)
			max = col[i];
	}
	delete(mas);
	delete(col);
	return max;
}
int Score(int count)
{
	int res = 0;
	for (int i = 0; i < Size_Motiv; i++)
	{
		res += LocalScore(i,count);
	}
	return res;
}
void Shift(int k)
{
	for (int i = k; i < Count_Examples; i++)
	{
		Counter[i] = Exaples_Lenght;
	}
}
int main()
{
	FILE * pFile;
	errno_t err;
	err = fopen_s(&pFile, "input.txt", "r");
	fscanf_s(pFile, "%i", &Size_Motiv);
	fscanf_s(pFile, "%i", &Count_Examples);
	char chr = '*';
	int k = 0;
	fseek(pFile, 2, SEEK_CUR);
	while ((chr != '\n') && (k<20))
	{
		fscanf_s(pFile, "%c", &chr);
		k++;
	}
	k--;
	Exaples_Lenght = k;
	Examples = new char*[Count_Examples];
	for (int i = 0; i < Count_Examples; i++)
	{
		Examples[i] = new char[Exaples_Lenght];
	}
	fseek(pFile, -Exaples_Lenght - 2, SEEK_CUR);
	Counter = new int[Count_Examples];
	for (int i = 0; i < Count_Examples; i++)
	{
		Counter[i] = 0;
		for (int j = 0; j < Exaples_Lenght; j++)
		{
			fscanf_s(pFile, "%c", &Examples[i][j]);
		}
		fscanf_s(pFile, "%c", &chr);
	}
	fclose(pFile);
	int max = Score(Count_Examples);
	int* res_mas = new int[Count_Examples];
	for (int i = 0; i < Count_Examples; i++)
	{
		res_mas[i] = Counter[i];
	}
	while (CountPlus(Counter, Count_Examples, Exaples_Lenght, Size_Motiv))
	{
		int res = 0;
		for (int i = 2; i <= Count_Examples-1; i++)
		{
			res = Score(i);
			if (res + Size_Motiv*(Count_Examples - i) < max)
			{
				res = 0;
				Shift(i);
				break;
			}
		}
		if(res!=0)
		res= Score(Count_Examples);
		if (res > max)
		{
			for (int i = 0; i < Count_Examples; i++)
			{
				res_mas[i] = Counter[i];
			}
			max = res;
		}
	}
	err = fopen_s(&pFile, "output.txt", "w");
	for (int i = 0; i < Count_Examples; i++)
	{
		for (int j = 0; j < Size_Motiv; j++)
		{
			fprintf_s(pFile, "%c", Examples[i][res_mas[i] + j]);
		}
		fprintf_s(pFile, "\n");
	}
	fclose(pFile);
	delete(Examples);
	delete(Counter);
	return 0;
}

