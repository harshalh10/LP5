#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void mergeSeq(vector<int> &arr)
{
    if (arr.size() <= 1)
        return;

    int mid = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

    mergeSeq(left);
    mergeSeq(right);

    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < left.size())
        arr[k++] = left[i++];
    while (j < right.size())
        arr[k++] = right[j++];
}

void mergePar(vector<int> &arr)
{
    if (arr.size() <= 1)
        return;

    int mid = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

#pragma omp parallel sections
    {
#pragma omp section
        {
            mergePar(left);
        }
#pragma omp section
        {
            mergePar(right);
        }
    }

    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < left.size())
        arr[k++] = left[i++];
    while (j < right.size())
        arr[k++] = right[j++];
}

int main()
{
    vector<int> arr = {5, 4, 3, 2, 1};
    cout << "\nBefore: ";
    for (auto i : arr)
        cout << i << " ";
    cout << endl;

    auto start = chrono::high_resolution_clock::now();
    mergeSeq(arr);
    cout << "\nAfter: ";
    for (auto i : arr)
        cout << i << " ";
    cout << endl;
    auto end = chrono::high_resolution_clock::now();
    cout << "\nTime taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    vector<int> arr1 = {5, 4, 3, 2, 1};
    cout << "\nBefore: ";
    for (auto i : arr1)
        cout << i << " ";
    cout << endl;

    start = chrono::high_resolution_clock::now();
    mergePar(arr1);
    cout << "\nAfter: ";
    for (auto i : arr1)
        cout << i << " ";
    cout << endl;
    end = chrono::high_resolution_clock::now();
    cout << "\nTime taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
}