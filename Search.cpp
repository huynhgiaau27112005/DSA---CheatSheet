#include <iostream>

using namespace std;

bool BinarySearch(int* arr, int first, int last, int value)
{
	if (first > last) return false;
	int mid = (first + last) / 2;
	if (arr[mid] > value) return BinarySearch(arr, first, mid - 1, value);
	if (arr[mid] < value) return BinarySearch(arr, mid + 1, last, value);
	if (arr[mid] == value) return true;
}

int arr[] = {1, 2, 3, 4, 5, 7, 8, 9, 10};
int main()
{
	if (BinarySearch(arr, 0, 8, 1)) cout << "YES";
	else cout << "NO";
	return 0;
}