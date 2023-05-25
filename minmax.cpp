#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void minimum(vector<int> arr)
{
    int min = INT_MAX;
    auto start = chrono::high_resolution_clock::now();
    for (auto i = arr.begin(); i != arr.end(); ++i)
    {
        if (*i < min)
            min = *i;
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "\nMinimum = " << min << endl;
    cout << "Time taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    int min_ele = INT_MAX;
    start = chrono::high_resolution_clock::now();
#pragma omp parallel for reduction(min : min_ele)
    for (auto i = arr.begin(); i != arr.end(); ++i)
    {
        if (*i < min_ele)
            min_ele = *i;
    }
    end = chrono::high_resolution_clock::now();
    cout << "\nMinimum (parallel reduction) = " << min_ele << endl;
    cout << "Time taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
}

void maximum(vector<int> arr)
{
    int max = INT_MIN;
    auto start = chrono::high_resolution_clock::now();
    for (auto i = arr.begin(); i != arr.end(); ++i)
    {
        if (*i > max)
            max = *i;
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "\nMaximum = " << max << endl;
    cout << "Time taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    int max_ele = INT_MIN;
    start = chrono::high_resolution_clock::now();
#pragma omp parallel for reduction(max : max_ele)
    for (auto i = arr.begin(); i != arr.end(); ++i)
    {
        if (*i > max_ele)
            max_ele = *i;
    }
    end = chrono::high_resolution_clock::now();
    cout << "\nMaximum (parallel reduction) = " << max_ele << endl;
    cout << "Time taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
}

void sum(vector<int> arr)
{
    int sum = 0;
    auto start = chrono::high_resolution_clock::now();
    for (auto i = arr.begin(); i != arr.end(); ++i)
    {
        sum += *i;
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "\nSum = " << sum << endl;
    cout << "Time taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    sum = 0;
    start = chrono::high_resolution_clock::now();
#pragma omp parallel for reduction(+ : sum)
    for (auto i = arr.begin(); i != arr.end(); ++i)
    {
        sum += *i;
    }
    end = chrono::high_resolution_clock::now();
    cout << "\nSum (parallel reduction) = " << sum << endl;
    cout << "Time taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
}

void avg(vector<int> arr)
{
    float sum = 0;
    auto start = chrono::high_resolution_clock::now();
    for (auto i = arr.begin(); i != arr.end(); ++i)
    {
        sum += *i;
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "\nAvg = " << (sum / arr.size()) << endl;
    cout << "Time taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    sum = 0;
    start = chrono::high_resolution_clock::now();
#pragma omp parallel for reduction(+ : sum)
    for (auto i = arr.begin(); i != arr.end(); ++i)
    {
        sum += *i;
    }
    end = chrono::high_resolution_clock::now();
    cout << "\nAvg (parallel reduction) = " << (sum / arr.size()) << endl;
    cout << "Time taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
}

int main()
{
    int MAX = 1000;
    int n;
    cout << "\nEnter number of elements: ";
    cin >> n;

    vector<int> array;
    array.resize(n);
    for (int i = 0; i < n; ++i)
    {
        array[i] = rand() % MAX;
    }

    cout << "\nArray: ";
    for (auto i : array)
        cout << i << " ";
    cout << endl;

    minimum(array);
    maximum(array);
    sum(array);
    avg(array);

    return 0;
}