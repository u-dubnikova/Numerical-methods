// ћетод_якоби.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define  _USE_MATH_DEFINES
#include <cmath>
#include <memory>

void FindMaxCoordinate(double ** matrix,int size, int& p, int& q)
{
	double max = 0;

	for(int i = 1; i < size; ++i)
		for (int j = i-1;j<size; ++j)
			if (abs(max)<abs(matrix[i][j]))
			{
				p = i;
				q = j;
				max = matrix[i][j];
			}
}

double FindAngle(double apq,double app,double aqq)
{
	return app == aqq ? M_PI_4 : atan(2 * apq / (app - aqq)) / 2;
}

void PrintMatrix(double ** matrix, int size)
{
	for(auto i = 0;i<size;++i)
	{
		for (auto j = 0; j < size; ++j)
			printf("%f\t", matrix[i][j]);

		printf("\n");
	}
}

void RotateMatrix(double ** matrix, int size, int p, int q, double phi)
{
	auto apq = matrix[p][q];
	auto app = matrix[p][p];
	auto aqq = matrix[q][q];
	auto api = 0.;
	auto aqi = 0.;
	
	for (auto i = 0; i < size; ++i)
	{
		if(i == p)
			matrix[p][i] = app * cos(phi)*cos(phi) + apq*sin(2*phi) + aqq*sin(phi)*sin(phi);
		else if (i == q)
			matrix[q][i] = app*sin(phi)*sin(phi) - apq*sin(2*phi) + aqq*cos(phi)*cos(phi);
		else
		{
			api = matrix[p][i];
			aqi = matrix[q][i];

			matrix[p][i] = api*cos(phi) + aqi*sin(phi);
			matrix[q][i] = -1 * api*sin(phi) + aqi*cos(phi);

			matrix[i][p] = matrix[p][i];
			matrix[i][q] = matrix[q][i];
		}
	}

	matrix[p][q] = 0;
	matrix[q][p] = 0;

}

bool IsNotDiagonal(double ** matrix, int size)
{
	for (auto i = 0; i < size; ++i)
		for (auto j = 0; j < size; ++j)
			if (matrix[i][j]!=0 && i != j)
				return true;

	return false;
}

void JacobiRotate(double ** matrix, int size)
{
	int p = 0;
	int q = 0;

	FindMaxCoordinate(matrix, size, p, q);

	double phi = FindAngle(matrix[p][q], matrix[p][p], matrix[q][q]);

	RotateMatrix(matrix, size, p, q, phi);
}

int main()
{
	const auto size = 4;
	
	//все функции только дл€ симметричных матриц
	double matrix[size][size] = {
		{ 4, 9, 5, 4},
		{ 9, -7, -8, 8},
		{ 5, -8, 5, 1},
		{ 4, 8, 1, 7},
	};

	auto usefullArr = new double *[size];
	for (auto i = 0; i < size; ++i)
	{
		usefullArr[i] = new double[size];
		for (auto j = 0; j < size; ++j)
		{
			usefullArr[i][j] = matrix[i][j]; // запись в обрабатываемую матрицу именно тут
		}
	}

	while (IsNotDiagonal(usefullArr, size))
		JacobiRotate(usefullArr, size);

	PrintMatrix(usefullArr, size);
    return 0;
}

