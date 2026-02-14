//Use 'std::priority_queue' to find the k-th largest element in an unsorted array.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Function to find k-th largest element
int k-thLargest(const vector<int>& nums, int k) {
    // Min-heap of size k
    // priority_queue<,> is a c++ container that acts like a heap. 
    // First parameter: Type of elements. 
    // Second parameter: Underlying container to store elements.
    // Third parameter: Comparison function. priority_queue is a max-heap(uses les       s<int>internally), greater<int> flips it into min-heap: smallest on top.
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) {
            minHeap.pop();  // keep only k largest elements
        }
    }

    // The top of the min-heap is the k-th largest element
    return minHeap.top();
}

int main() {
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 4;

    int result = k-thLargest(nums, k);
    cout << k << "-th largest element is " << result << endl;

    return 0;
}

