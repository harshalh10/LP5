#include <bits/stdc++.h>
#include <cuda.h>
#define BLOCK_SIZE 64

using namespace std;

void cpu_add(int *arr1, int *arr2, int *res, int size)
{
    for (int i = 0; i < size; ++i)
        res[i] = arr1[i] + arr2[i];
}

__global__ void gpu_add(int *arr1, int *arr2, int *res, int size)
{
    int block_id = blockIdx.x * blockDim.x + threadIdx.x;
    if (block_id < size)
    {
        res[block_id] = arr1[block_id] + arr2[block_id];
    }
}

void print_vec(int *arr, int size)
{
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int *a_cpu, *b_cpu, *res_cpu, *a_gpu, *b_gpu, *res_gpu, *copy;
    int n = 1 << 4;

    a_cpu = new int[n];
    b_cpu = new int[n];
    res_cpu = new int[n];
    copy = new int[n];
    int size = n * sizeof(int);
    cudaMalloc(&a_gpu, size);
    cudaMalloc(&b_gpu, size);
    cudaMalloc(&res_gpu, size);

    for (int i = 0; i < n; ++i)
    {
        a_cpu[i] = rand() % 100;
        b_cpu[i] = rand() % 100;
    }
    cudaMemcpy(a_gpu, a_cpu, size, cudaMemcpyHostToDevice);
    cudaMemcpy(b_gpu, b_cpu, size, cudaMemcpyHostToDevice);

    cout << "\nVector A => ";
    print_vec(a_cpu, n);
    cout << "\nVector B => ";
    print_vec(b_cpu, n);

    cudaEvent_t start, stop;
    float elapsedTime;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);
    cpu_add(a_cpu, b_cpu, res_cpu, n);
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsedTime, start, stop);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cout << "\nCPU result:" << endl;
    print_vec(res_cpu, n);
    cout << "Elapsed Time = " << elapsedTime << " ms" << endl;

    int threads = 1024;
    int blocks = (n + threads - 1) / threads;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);
    gpu_add<<<blocks, threads>>>(a_gpu, b_gpu, res_gpu, n);
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsedTime, start, stop);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaMemcpy(copy, res_gpu, size, cudaMemcpyDeviceToHost);
    cout << "\nGPU result:" << endl;
    print_vec(copy, n);
    cout << "Elapsed Time = " << elapsedTime << " ms" << endl;

    cudaFree(a_gpu);
    cudaFree(b_gpu);
    cudaFree(res_gpu);

    return 0;
}