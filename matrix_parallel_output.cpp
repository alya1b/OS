#include <iostream>
#include <thread>
#include <vector>

using namespace std;

const int MAXN = 1000;

int n, m, k;
int A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN];

inline void multiply_element(int i, int j){
    C[i][j] = 0;
    for (int l = 0; l < m; l++) {
        C[i][j] += A[i][l] * B[l][j];
    }
    cout << "[" << i << "," << j << "]=" << C[i][j] << " ";
}

void multiply(int start_work, int end_work) {
    for (int a =start_work; a<end_work; a++){
        int i = a/n;
        int j = a%n;
        multiply_element(i,j);
    }
}

int main() {
    // read input
    cout<<"Enter N: ";
    cin >> n;
    cout<<"Enter M: ";
    cin >> m;
    cout<<"Enter K: ";
    cin >> k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            A[i][j] = i + j; // example auto-generated data
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            B[i][j] = i * j; // example auto-generated data
        }
    }

    // parallel multiplication
    int num_threads = 5;
    vector<thread> threads(num_threads);
    int chunk_size = n*k / num_threads;
    int start = 0, end = chunk_size;
    for (int i = 0; i < num_threads; i++) {
        start = i*chunk_size;
        end = start+chunk_size;
        threads[i] = thread(multiply, start, end);
    }
    for (int i = 0; i < num_threads; i++) {
        threads[i].join();
    }

    return 0;
}