// Use placement new and custom allocators to reduce allocation overhead in a part   icle simulation.

// In a particle simulation, objects(particles) have to be created/destroyed frequ   ently. Allocating with new/delete repeatedly is slow, causes memory fragmentati   on.
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <new>      // for placement new
#include <chrono>

using Clock = std::chrono::high_resolution_clock;

// ---------------- Particle Definition ----------------
struct Particle {
    float x, y, vx, vy;

    Particle(float _x, float _y, float _vx, float _vy)
        : x(_x), y(_y), vx(_vx), vy(_vy) {}

    void update(float dt) {
        x += vx * dt;
        y += vy * dt;
    }

    void print() const {
        std::cout << "(" << x << "," << y << ") ";
    }
};

// ---------------- Particle Pool ----------------
// Pre-allocated memory for N particles
class ParticlePool {
    size_t capacity;
    size_t used;
    char* buffer;             // raw memory buffer
public:
    ParticlePool(size_t N) : capacity(N), used(0) {
        buffer = new char[sizeof(Particle) * N];  // allocate raw memory
    }

    ~ParticlePool() {
        // call destructors for all constructed particles
        for (size_t i = 0; i < used; ++i) {
            Particle* p = reinterpret_cast<Particle*>(buffer + i * sizeof(Particle));
            p->~Particle();
        }
        delete[] buffer;
    }

    Particle* create(float x, float y, float vx, float vy) {
        assert(used < capacity && "Pool full!");
        // placement new: construct Particle in pre-allocated buffer
        // Construct object directly in pre-allocated memory.
        // Not per-object heap allocation.
        // Destructor manually called during pool destruction.
        // Much faster for large number of particles.
        void* ptr = buffer + used * sizeof(Particle);
        Particle* p = new(ptr) Particle(x, y, vx, vy);
        ++used;
        return p;
    }

    void reset() {
        // call destructors
        for (size_t i = 0; i < used; ++i) {
            Particle* p = reinterpret_cast<Particle*>(buffer + i * sizeof(Particle));
            p->~Particle();
        }
        used = 0;
    }

    size_t size() const { return used; }
};

// ---------------- Benchmark ----------------
double benchmark(int iterations, size_t N, bool use_pool) {
    auto start = Clock::now();

    for (int iter = 0; iter < iterations; ++iter) {
        std::vector<Particle*> particles;
        particles.reserve(N);

        if (use_pool) {
            ParticlePool pool(N);
            for (size_t i = 0; i < N; ++i) {
                particles.push_back(pool.create(i*0.1f, i*0.1f, 0.01f, 0.02f));
            }
            // update
            for (auto p : particles) p->update(0.1f);
            // pool destructor automatically cleans up
        } else {
            for (size_t i = 0; i < N; ++i) 
            // Every particle allocates memory individually: heap fragmentation.
            // High overhead when N is large and frequent.
            {
                particles.push_back(new Particle(i*0.1f, i*0.1f, 0.01f, 0.02f));
            }
            for (auto p : particles) p->update(0.1f);
            for (auto p : particles) delete p;
        }
    }

    auto end = Clock::now();
    return std::chrono::duration<double>(end - start).count();
}

// ---------------- Main ----------------
int main() {
    size_t N = 100000;        // particles per iteration
    int iterations = 10;

    double t_raw = benchmark(iterations, N, false);
    std::cout << "Raw new/delete: " << t_raw << " sec\n";

    double t_pool = benchmark(iterations, N, true);
    std::cout << "Placement new + pool: " << t_pool << " sec\n";

    std::cout << "Speedup: " << t_raw / t_pool << "x\n";

    return 0;
}

