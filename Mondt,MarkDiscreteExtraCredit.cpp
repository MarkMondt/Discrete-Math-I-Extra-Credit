#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>
using namespace std;

void RotateLeft(short int OldSquare[1024][1024], short int ArraySize)
{
	int NewSquare[1024][1024];

	for (int row = 0; row <= ArraySize - 1; row++)
		for (int column = 0; column <= ArraySize - 1; column++)
			NewSquare[row][column] = OldSquare[column][ArraySize - 1 - row];

	for (int row = 0; row <= ArraySize - 1; row++)
		for (int column = 0; column <= ArraySize - 1; column++)
		{
			OldSquare[row][column] = NewSquare[row][column];
			if (OldSquare[row][column] == 1)
			{
				OldSquare[row][column] = 4;
				continue;
			}
			if (OldSquare[row][column] == 2)
			{
				OldSquare[row][column] = 3;
				continue;
			}
			if (OldSquare[row][column] == 3)
			{
				OldSquare[row][column] = 1;
				continue;
			}
			if (OldSquare[row][column] == 4)
			{
				OldSquare[row][column] = 2;
				continue;
			}
		}

}

void RotateRight(short int OldSquare[1024][1024], short int ArraySize)
{
	int NewSquare[1024][1024];

	for (int row = 0; row <= ArraySize - 1; row++)
		for (int column = 0; column <= ArraySize - 1; column++)
			NewSquare[row][column] = OldSquare[ArraySize - 1 - column][row];
			

	for (int row = 0; row <= ArraySize - 1; row++)
		for (int column = 0; column <= ArraySize - 1; column++)
		{
			OldSquare[row][column] = NewSquare[row][column];
			if (OldSquare[row][column] == 1)
			{
				OldSquare[row][column] = 3;
				continue;
			}
			if (OldSquare[row][column] == 2)
			{
				OldSquare[row][column] = 4;
				continue;
			}
			if (OldSquare[row][column] == 3)
			{
				OldSquare[row][column] = 2;
				continue;
			}
			if (OldSquare[row][column] == 4)
			{
				OldSquare[row][column] = 1;
				continue;
			}
		}

}

void DisplayArray(short int Square[1024][1024], short int ArraySize)
{
	for (int row = 0; row <= ArraySize - 1; row++)
	{
		for (int column = 0; column <= ArraySize - 1; column++)
			cout << Square[row][column] << " ";
		cout << endl;
	}
	cout << endl;
}

void GenerateTriomino(short int Smallest[2][2], short int EmptyX, short int EmptyY)
{
	if (EmptyX == 0 && EmptyY == 0)
	{
		Smallest[0][0] = 0;
		Smallest[0][1] = 3;
		Smallest[1][0] = 3;
		Smallest[1][1] = 3;
	}
	if(EmptyX == 0 && EmptyY == 1)
	{
		Smallest[0][0] = 2;
		Smallest[0][1] = 0;
		Smallest[1][0] = 2;
		Smallest[1][1] = 2;
	}
	if (EmptyX == 1 && EmptyY == 0)
	{
		Smallest[0][0] = 1;
		Smallest[0][1] = 1;
		Smallest[1][0] = 0;
		Smallest[1][1] = 1;
	}
	if (EmptyX == 1 && EmptyY == 1)
	{
		Smallest[0][0] = 4;
		Smallest[0][1] = 4;
		Smallest[1][0] = 4;
		Smallest[1][1] = 0;
	}

}

void ExpandPrimitave(short int Primitive[1024][1024], short int ArraySize)
{
	short int Sub[512][512] = { 0 };
	short int r = 0;
	short int c = 0;

	for (int row = 0; row <= (ArraySize/2)-1; row++)
		for (int column = 0; column <= (ArraySize / 2) - 1; column++)
			Sub[row][column] = Primitive[row][column];

	r = 0;
	for (int row = 0; row <= (ArraySize / 2) - 1; row++)
	{
		c = 0;

		RotateRight(Primitive, ArraySize / 2);

		for (int column = ArraySize/2; column <= ArraySize - 1; column++)
		{
			Sub[row][column] = Primitive[r][c];
			c++;
		}

		RotateLeft(Primitive, ArraySize / 2);

		r++;
	}

	r = 0;
	for (int row = ArraySize / 2; row <= ArraySize - 1; row++)
	{
		c = 0;
		for (int column = ArraySize / 2; column <= ArraySize - 1; column++)
		{
			Sub[row][column] = Primitive[r][c];
			c++;
		}
		r++;
	}

	r = 0;
	for (int row = ArraySize / 2; row <= ArraySize - 1; row++)
	{
		c = 0;

		RotateLeft(Primitive, ArraySize / 2);

		for (int column = 0; column <= (ArraySize / 2) - 1; column++)
		{
			Sub[row][column] = Primitive[r][c];
			c++;
		}

		RotateRight(Primitive, ArraySize / 2);

		r++;
	}

	Sub[ArraySize / 2 - 1][ArraySize / 2 - 1] = 4;
	Sub[ArraySize / 2 - 1][ArraySize / 2] = 4;
	Sub[ArraySize / 2][ArraySize / 2 - 1] = 4;

	for (int row = 0; row <= ArraySize - 1; row++)
		for (int column = 0; column <= ArraySize - 1; column++)
			Primitive[row][column] = Sub[row][column];
}

int main()
{
	short int Square[1024][1024] = { 0 };
	short int SquarePrime[1024][1024] = { 0 };
	short int Smallest[2][2];
	short int Primitive[1024][1024] = { 0 };
	short int EmptyPosition[2];
	short int ArraySize;
	short int Quadrant;
	short int n;
	short int r;
	short int c;
	int RandomSeed;

	cout << "This program will make a checkerboard of size 2^n" << endl
		<< "Enter a value between 1 and 10 for n: " << endl;
	cin >> n;
	cout << endl;

	while (n < 1 || n > 10)
	{
		cout << "Invalid value for n (not between 1 and 10)" << endl
			<< "Enter a value for n: " << endl;
		cin >> n;
		cout << endl;
	}

	ArraySize = pow(2, n);

	RandomSeed = time(0);
	srand(RandomSeed);

	EmptyPosition[0] = rand() % ArraySize;
	EmptyPosition[1] = rand() % ArraySize;

	//cout << EmptyPosition[0] << endl;
	//cout << EmptyPosition[1] << endl << endl;

	GenerateTriomino(Smallest, EmptyPosition[0] % 2, EmptyPosition[1] % 2);
	
	for (int row = 0; row <= 1; row++)
		for (int column = 0; column <= 1; column++)
			Square[row][column] = SquarePrime[row][column] = Smallest[row][column];
	
	GenerateTriomino(Smallest, 1, 1);

	for (int row = 0; row <= 1; row++)
		for (int column = 0; column <= 1; column++)
			Primitive[row][column] = Smallest[row][column];
	
	//DisplayArray(SquarePrime, 2);

	for (int Pow = 4; Pow <= ArraySize; Pow *= 2)
	{

		for (int row = 0; row <= Pow / 2 - 1; row++)
			for (int column = 0; column <= Pow / 2 - 1; column++)
				SquarePrime[row][column] = Square[row][column];

		r = 0;
		for (int row = EmptyPosition[0] % Pow - EmptyPosition[0] % (Pow / 2); row <= EmptyPosition[0] % Pow - EmptyPosition[0] % (Pow / 2) + (Pow / 2) - 1; row++)
		{
			c = 0;
			for (int column = EmptyPosition[1] % Pow - EmptyPosition[1] % (Pow / 2); column <= EmptyPosition[1] % Pow - EmptyPosition[1] % (Pow / 2) + (Pow / 2) - 1; column++)
			{
				Square[row][column] = SquarePrime[r][c];
				c++;
			}
			r++;
		}

		Quadrant = 0;

		if ((EmptyPosition[0] % Pow) >= (Pow / 2) || (EmptyPosition[1] % Pow) >= (Pow / 2))
		{
			for (int row = 0; row <= Pow / 2 - 1; row++)
				for (int column = 0; column <= Pow / 2 - 1; column++)
					Square[row][column] = Primitive[row][column];

			Quadrant += 1;
		}

		if ((EmptyPosition[0] % Pow) >= (Pow / 2) || (EmptyPosition[1] % Pow) < (Pow / 2))
		{
			RotateRight(Primitive, Pow / 2);

			r = 0;
			for (int row = 0; row <= Pow / 2 - 1; row++)
			{
				c = 0;
				for (int column = Pow / 2; column <= Pow - 1; column++)
				{
					Square[row][column] = Primitive[r][c];
					c++;
				}
				r++;
			}

			RotateLeft(Primitive, Pow / 2);

			Quadrant += 2;
		}

		if ((EmptyPosition[0] % Pow) < (Pow / 2) || (EmptyPosition[1] % Pow) < (Pow / 2))
		{
			RotateRight(Primitive, Pow / 2);
			RotateRight(Primitive, Pow / 2);

			r = 0;
			for (int row = Pow / 2; row <= Pow - 1; row++)
			{
				c = 0;
				for (int column = Pow / 2; column <= Pow - 1; column++)
				{
					Square[row][column] = Primitive[r][c];
					c++;
				}
				r++;
			}

			RotateLeft(Primitive, Pow / 2);
			RotateLeft(Primitive, Pow / 2);

			Quadrant += 3;
		}

		if ((EmptyPosition[0] % Pow) < (Pow / 2) || (EmptyPosition[1] % Pow) >= (Pow / 2))
		{
			RotateLeft(Primitive, Pow / 2);

			r = 0;
			for (int row = Pow / 2; row <= Pow - 1; row++)
			{
				c = 0;
				for (int column = 0; column <= Pow / 2 - 1; column++)
				{
					Square[row][column] = Primitive[r][c];
					c++;
				}
				r++;
			}

			RotateRight(Primitive, Pow / 2);

			Quadrant += 4;
		}

		Quadrant = 10 - Quadrant;

		if (Quadrant == 1)
		{
		Square[Pow / 2][Pow / 2] = 3;
		Square[Pow / 2 - 1][Pow / 2] = 3;
		Square[Pow / 2][Pow / 2 - 1] = 3;
		}
		else if (Quadrant == 2)
		{
			Square[Pow / 2][Pow / 2] = 2;
			Square[Pow / 2 - 1][Pow / 2 - 1] = 2;
			Square[Pow / 2][Pow / 2 - 1] = 2;
		}
		else if (Quadrant == 3)
		{
			Square[Pow / 2 - 1][Pow / 2] = 4;
			Square[Pow / 2 - 1][Pow / 2 - 1] = 4;
			Square[Pow / 2][Pow / 2 - 1] = 4;
		}
		else if (Quadrant == 4)
		{
			Square[Pow / 2 - 1][Pow / 2] = 1;
			Square[Pow / 2 - 1][Pow / 2 - 1] = 1;
			Square[Pow / 2][Pow / 2] = 1;
		}

		//DisplayArray(Square, Pow);

		if (Pow == ArraySize)
			break;

		ExpandPrimitave(Primitive, Pow);
	}


	DisplayArray(Square, ArraySize);

	system("pause");
	return 0;
}