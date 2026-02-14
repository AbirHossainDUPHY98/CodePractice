// Demonstrate cache-friendly vs. cache-unfriendly memory access patterns in matri   x multiplication.


#include <iostream>
#include <vector>
// <chrono> : Time and clocks library -> timing, benchmarking, high-resolution clo   cks.
#include <chrono>
#include <random>
#include <cstring>   // Memory and string utilities: raw memory operations, byte l                        evel control, low-level performance code. 
#include <cmath>
// creates a new name Clock, for a long type: Type alias.
using Clock = std::chrono::high_resolution_clock;

/*
===========================================================
CONCEPTS:
-----------------------------------------------------------
Memory layout: row-major (C/C++)
A[i][j] is contiguous in j direction

Cache:
- Cache lines ≈ 64 bytes
- double = 8 bytes
- 1 cache line = 8 doubles

So sequential access reuses cache lines
Stride access wastes cache lines

Locality:
- Spatial locality: nearby memory reused
- Temporal locality: same data reused
===========================================================
*/

using Matrix = std::vector<std::vector<double>>;

Matrix make_matrix(int N) {
    Matrix M(N, std::vector<double>(N));
    // mt19937_64 = Mersenne Twister 64-bit pseudo-random number generator (PRNG).
    // std::mt19937_64 rng; creates a generator object that produces deterministic       pseudo-random numbers.
    std::mt19937_64 rng(123);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            M[i][j] = dist(rng);
    return M;
}

void zero(Matrix& C) {
    for (auto& row : C)
      // memset() : cstring library function. Sets a block of memory to a specific         byte value.
        std::memset(row.data(), 0, row.size() * sizeof(double));
}

/*
===========================================================
❌ CACHE-UNFRIENDLY
-----------------------------------------------------------
Access pattern:
A[i][k]  -> row access (good)
B[k][j]  -> column access (BAD)

Memory stride = N * sizeof(double)
=> every access = new cache line
=> cache miss storm
=> TLB pressure
=> memory stalls
===========================================================
*/
void matmul_bad(const Matrix& A, const Matrix& B, Matrix& C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < N; ++k) {
                sum += A[i][k] * B[k][j];   // B[k][j] = column access (stride)
            }
            C[i][j] = sum;
        }
    }
}

/*
===========================================================
✅ CACHE-FRIENDLY (LOOP REORDERING)
-----------------------------------------------------------
Access pattern:
A[i][k]  -> row
B[k][j]  -> row
C[i][j]  -> row

Sequential memory traversal
Cache-line reuse
Prefetch friendly
===========================================================
*/
void matmul_good(const Matrix& A, const Matrix& B, Matrix& C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            double aik = A[i][k];  // register reuse
            for (int j = 0; j < N; ++j) {
                C[i][j] += aik * B[k][j];
            }
        }
    }
}

/*
===========================================================
🔥 CACHE-OPTIMAL (BLOCKING / TILING)
-----------------------------------------------------------
Keeps working set in L1/L2 cache
Real HPC strategy

BS = block size
Typical values: 16, 32, 64
===========================================================
*/
// Study the below section::
void matmul_blocked(const Matrix& A, const Matrix& B, Matrix& C, int N, int BS) {
    for (int ii = 0; ii < N; ii += BS)
        for (int kk = 0; kk < N; kk += BS)
            for (int jj = 0; jj < N; jj += BS)
                for (int i = ii; i < ii + BS && i < N; ++i)
                    for (int k = kk; k < kk + BS && k < N; ++k) {
                        double aik = A[i][k];
                        for (int j = jj; j < jj + BS && j < N; ++j) {
                            C[i][j] += aik * B[k][j];
                        }
                    }
}

/*
===========================================================
BENCHMARK TOOL
===========================================================
*/
template<typename F>
double benchmark(F&& func) {
    auto start = Clock::now();
    func();
    auto end = Clock::now();
    return std::chrono::duration<double>(end - start).count();
}

int main() {
    int N = 512;      // adjust for your machine (256, 512, 1024)
    int BS = 32;      // block size

    std::cout << "Matrix size: " << N << " x " << N << "\n";

    Matrix A = make_matrix(N);
    Matrix B = make_matrix(N);
    Matrix C(N, std::vector<double>(N));

    // BAD
    zero(C);
    double t_bad = benchmark([&]{
        matmul_bad(A, B, C, N);
    });
    std::cout << "Cache-unfriendly: " << t_bad << " sec\n";

    // GOOD
    zero(C);
    double t_good = benchmark([&]{
        matmul_good(A, B, C, N);
    });
    std::cout << "Cache-friendly:   " << t_good << " sec\n";

    // BLOCKED
    zero(C);
    double t_block = benchmark([&]{
        matmul_blocked(A, B, C, N, BS);
    });
    std::cout << "Blocked:          " << t_block << " sec\n";

    std::cout << "\nSpeedups:\n";
    std::cout << "Good / Bad:   " << (t_bad / t_good) << "x\n";
    std::cout << "Block / Bad:  " << (t_bad / t_block) << "x\n";

    return 0;
}

