#include <iostream>

using namespace std;

bool Comparator(int a, int b)
{
	return a < b;
}

void SelectionSort(int* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		int minID = i;
		for (int j = i + 1; j < n; j++)
		{
			if (Comparator(arr[j], arr[minID])) minID = j;
		}
		swap(arr[minID], arr[i]);
	}
}

void BubbleSort(int* arr, int n)
{
	for (int i = n - 1; i >= 1; i--)
	{
		for (int j = 0; j < i - 1; j++)
		{
			if (Comparator(arr[j + 1], arr[j]))
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void InsertionSort(int* arr, int n)
{
	for (int i = 1; i < n; i++)
	{
		int value = arr[i];
		int pos = i;
		for (int j = i - 1; j >= 0; j--)
		{
			if (Comparator(arr[j], value))
			{
				pos = j + 1;
				break;
			}
			else
			{
				arr[j + 1] = arr[j];
			}
		}
		arr[pos] = value;
	}
}

int arr[] = {1, 5, 2, 8, 4, 7, 6, 3, 9};
int n = 9;

int main()
{
	SelectionSort(arr, n);
	for (int i = 0; i < n; i++) cout << arr[i] << " ";
	return 0;
}