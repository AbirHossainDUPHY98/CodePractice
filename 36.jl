# Implement quicksort with median-of -three pivot selection and compare to 'sort'.

# --- Median-of-three pivot selection ---
function median_of_three!(arr, lo, hi)
    mid = lo + (hi - lo) ÷ 2
    # sort lo, mid, hi
    if arr[lo] > arr[mid]
        arr[lo], arr[mid] = arr[mid], arr[lo]
    end
    if arr[lo] > arr[hi]
        arr[lo], arr[hi] = arr[hi], arr[lo]
    end
    if arr[mid] > arr[hi]
        arr[mid], arr[hi] = arr[hi], arr[mid]
    end
    # place median at hi-1 for partitioning
    arr[mid], arr[hi-1] = arr[hi-1], arr[mid]
    return arr[hi-1]  # pivot
end

# --- Partition function ---
function partition!(arr, lo, hi)
    pivot = median_of_three!(arr, lo, hi)
    i, j = lo, hi - 1

    while true
        # move i right while arr[i] < pivot
        while arr[i] < pivot && i < hi-1
            i += 1
        end

        # move j left while arr[j] > pivot
        while arr[j] > pivot && j > lo
            j -= 1
        end

        if i >= j
            break
        end

        arr[i], arr[j] = arr[j], arr[i]
    end

    arr[i], arr[hi-1] = arr[hi-1], arr[i]  # restore pivot
    return i
end

# --- Quicksort function ---
function quicksort!(arr, lo=1, hi=length(arr))
    if lo + 10 <= hi  # small arrays can use insertion sort
        p = partition!(arr, lo, hi)
        quicksort!(arr, lo, p-1)
        quicksort!(arr, p+1, hi)
    else
        # insertion sort for small partitions
        for i in lo+1:hi
            key = arr[i]
            j = i-1
            while j >= lo && arr[j] > key
                arr[j+1] = arr[j]
                j -= 1
            end
            arr[j+1] = key
        end
    end
    return arr
end

# --- Demonstration ---
using Random

arr = rand(1:100, 20)          # random integer array
arr_copy = copy(arr)

println("Original array: ", arr)

quicksort!(arr)
println("Quicksort result: ", arr)

sort!(arr_copy)
println("Built-in sort!: ", arr_copy)

println("Arrays are equal: ", arr == arr_copy)

