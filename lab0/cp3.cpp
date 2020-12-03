#include <iostream>
using namespace std;

int main()
{
	int num;
	float array[100];
	float sum = 0;
	float avg;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		cin >> array[i];
		sum += array[i];
	}
	avg = sum / float(num);
	cout << avg << "  ";
	for (int i = 0; i < num; i++)
	{
		if (array[i] < avg)
		{
			cout << array[i] << "  ";
		}
	}
	cout << endl;
}