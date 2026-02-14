# Slove the 'Two-sum' problem using a hash map for O(n) time.

""" Problem:Given an array nums and a target, return indices of two numbers such t    hat::nums[i] + nums[j] = target
    
    Algorithm:
    For each value x
    Compute needed = target - x
    If needed already seen → solution found
    Else store x in a map
"""
def two_sum(nums, target):
    seen = {}   # value -> index

    for i, x in enumerate(nums):
        needed = target - x
        if needed in seen:
            return [seen[needed], i]
        seen[x] = i

    return None

nums = [2, 7, 11, 15]
target = 9

indices = two_sum(nums, target)
if indices:
    print(f"Indices found: {indices}")
    print(f"Values: {nums[indices[0]]} + {nums[indices[1]]} = {target}")
else:
    print("No solution found")

"""
# sorted + two-pointer (O(n log n))
def two_sum_sorted(nums, target):
    arr = sorted([(v, i) for i, v in enumerate(nums)])
    l, r = 0, len(arr) - 1
    while l < r:
        s = arr[l][0] + arr[r][0]
        if s == target:
            return [arr[l][1], arr[r][1]]
        elif s < target:
            l += 1
        else:
            r -= 1
    return None

# bitset version (bounded integers)
def two_sum_bitset(nums, target, offset=10000):
    size = 2 * offset + 1
    seen = [False] * size
    idx = [-1] * size

    for i, x in enumerate(nums):
        needed = target - x
        ni = needed + offset
        if 0 <= ni < size and seen[ni]:
            return [idx[ni], i]
        xi = x + offset
        if 0 <= xi < size:
            seen[xi] = True
            idx[xi] = i
    return None

# streaming version (generator-safe)
def two_sum_stream(stream, target):
    seen = {}
    i = 0
    for x in stream:
        needed = target - x
        if needed in seen:
            return [seen[needed], i]
        seen[x] = i
        i += 1
    return None

# multi-solution version (all valid index pairs)
def two_sum_multi(nums, target):
    seen = {}
    results = []

    for i, x in enumerate(nums):
        needed = target - x
        if needed in seen:
            for j in seen[needed]:
                results.append((j, i))
        seen.setdefault(x, []).append(i)

    return results

# all-pairs version (brute force)
def two_sum_all_pairs(nums, target):
    res = []
    n = len(nums)
    for i in range(n):
        for j in range(i + 1, n):
            if nums[i] + nums[j] == target:
                res.append((i, j))
    return res
"""

