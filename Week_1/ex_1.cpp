#include <iostream>

struct Point {
	int x;
	int y;
};

struct Triangle {
	Point p1;
	Point p2;
	Point p3;
};

void readPoint(Point& p)
{
	std::cin >> p.x >> p.y;
}

void readTriangle(Triangle& tr)
{
	readPoint(tr.p1);
	readPoint(tr.p2);
	readPoint(tr.p3);
}

double distance(const Point& p1, const Point& p2 )
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double area(const Triangle& tr) 
{
	double firstLength = distance(tr.p1, tr.p2);
	double secondLength = distance(tr.p1, tr.p3);
	double thirdLength = distance(tr.p2, tr.p3);

	double halfPerimeter = ((firstLength + secondLength + thirdLength) / 2);

	return sqrt(halfPerimeter * (halfPerimeter - firstLength) * 
		       (halfPerimeter - secondLength) * (halfPerimeter - thirdLength));
}

void swap(double &arg1, double &arg2)
{
	double temp = arg1;
	arg1 = arg2;
	arg2 = temp;
}

void swap(Triangle &tr1, Triangle &tr2)
{
	Triangle temp = tr1;
	tr1 = tr2;
	tr2 = temp;
}
void bubbleSort(Triangle*& arr, int n)
{
	double* areas = new double[n];

	for (int i = 0; i < n; i++)
	{
		areas[i] = area(arr[i]);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (areas[j] > areas[j + 1])
			{
				swap(areas[j], areas[j + 1]);
				swap(arr[j], arr[j + 1]);
			}
		}
	}

	delete[] areas;
}
int main()
{
	Triangle tr;

	int n = 0;
	std::cin >> n;

	//readTriangle(tr);
	//std::cout << area(tr);

	Triangle* triangles = new Triangle[n];
	for (int i = 0; i < n; i++)
	{
		std::cout << "triangle N" << i + 1 << std::endl;
		readTriangle(tr);
		triangles[i] = tr;
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << area(triangles[i]) << " ";
	}

	bubbleSort(triangles, n);

	for (int i = 0; i < n; i++)
	{
		std::cout << area(triangles[i]) << " ";
	}

	delete [] triangles;
}