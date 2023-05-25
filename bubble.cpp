#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble(int arr[], int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

void parallel_bubble(int arr[], int size)
{
    int i, j;
#pragma omp parallel shared(arr, size) private(i, j)
    {
        for (i = 0; i < size - 1; ++i)
        {
#pragma omp parallel for
            for (j = 0; j < size - i - 1; ++j)
            {
                if (arr[j] > arr[j + 1])
                    swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main()
{
    int size = 5;
    int arr[size] = {5, 4, 3, 2, 1};

    cout << "\nBefore sorting: ";
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;

    auto start = chrono::high_resolution_clock::now();
    bubble(arr, size);
    cout << "\nAfter sorting: ";
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
    auto end = chrono::high_resolution_clock::now();
    cout << "\nTime taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    int arr1[size] = {5, 4, 3, 2, 1};

    cout << "\nBefore sorting: ";
    for (int i = 0; i < size; ++i)
        cout << arr1[i] << " ";
    cout << endl;

    start = chrono::high_resolution_clock::now();
    parallel_bubble(arr1, size);
    cout << "\nAfter sorting: ";
    for (int i = 0; i < size; ++i)
        cout << arr1[i] << " ";
    cout << endl;
    end = chrono::high_resolution_clock::now();
    cout << "\nTime taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
}