# Use '__slots__' in a class to reduce memory footprint for millions of instances.

# Placement new + custom memory management : python:: __slots__ 
# Problem:
# Each Python object has a __dict__ storing its attributes dynamically.
# For millions of objects, __dict__ adds a lot of memory overhead.
# Solution:
# Use __slots__ to predefine attributes, avoiding __dict__ per instance.
# This reduces memory footprint and can slightly improve attribute access speed.
# Normal class:
# Each instance has a __dict__ → dynamic attributes
# High memory usage per object (~200–300 bytes per object for small classes)
# Class with __slots__:
# Python pre-allocates fixed storage for attributes
# No per-instance __dict__
# Saves hundreds of bytes per object → massive memory reduction when N is large

import time
import sys

# ------------------------
# Normal class
# ------------------------
class Particle:
    def __init__(self, x, y, vx, vy):
        self.x = x
        self.y = y
        self.vx = vx
        self.vy = vy

    def update(self, dt):
        self.x += self.vx * dt
        self.y += self.vy * dt

# ------------------------
# Memory-efficient class with __slots__
# ------------------------
class ParticleSlots:
    __slots__ = ('x', 'y', 'vx', 'vy')

    def __init__(self, x, y, vx, vy):
        self.x = x
        self.y = y
        self.vx = vx
        self.vy = vy

    def update(self, dt):
        self.x += self.vx * dt
        self.y += self.vy * dt

# ------------------------
# Helper: estimate memory per object
# ------------------------
def estimate_memory(obj):
    if hasattr(obj, '__dict__'):
        return sys.getsizeof(obj) + sys.getsizeof(obj.__dict__)
    else:
        return sys.getsizeof(obj)  # __slots__ objects

# ------------------------
# Benchmark function
# ------------------------
def benchmark(cls, N):
    start_time = time.time()
    particles = [cls(i*0.1, i*0.1, 0.01, 0.02) for i in range(N)]
    create_time = time.time() - start_time

    start_time = time.time()
    for p in particles:
        p.update(0.1)
    update_time = time.time() - start_time

    # Estimate memory
    mem_per_instance = estimate_memory(particles[0])
    total_mem = mem_per_instance * N

    return create_time, update_time, total_mem

# ------------------------
# Main
# ------------------------
if __name__ == "__main__":
    N = 1_000_000  # 1 million particles

    t_create, t_update, mem = benchmark(Particle, N)
    print(f"Normal class: create {t_create:.3f}s, update {t_update:.3f}s, estimated memory {mem/1024/1024:.2f} MB")

    t_create, t_update, mem = benchmark(ParticleSlots, N)
    print(f"With __slots__: create {t_create:.3f}s, update {t_update:.3f}s, estimated memory {mem/1024/1024:.2f} MB")

# estimate_memory() manually accounts for the __dict__ in normal objects.
# For __slots__ objects, there is no __dict__, so sys.getsizeof(obj) is enough.
# This does not require any external library.
# Multiply per-object size by N to get total memory estimate.
