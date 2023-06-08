#include <iostream>
#include <vector>
#include <thread>

/**
 * @brief Merge two subarrays of arr[].
 * The first subarray is arr[left..mid].
 * The second subarray is arr[mid+1..right].
 * 
 * @param arr The input vector to be sorted
 * @param left The starting index of the left subarray
 * @param mid The ending index of the left subarray and the starting index of the right subarray
 * @param right The ending index of the right subarray
 */
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * @brief Implement the sequential merge sort algorithm.
 * The function uses divide-and-conquer method to divide the problem into smaller subproblems,
 * then solve the subproblems, and finally combine them to create the final sorted array.
 * 
 * @param arr The input vector to be sorted
 * @param left The starting index of the array to be sorted
 * @param right The ending index of the array to be sorted
 */
void merge_sort(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

/**
 * @brief Implement the parallel merge sort algorithm.
 * The function uses multi-threading to divide the problem into smaller subproblems,
 * which can be solved in parallel, then combine them to create the final sorted array.
 * 
 * @param arr The input vector to be sorted
 * @param left The starting index of the array to be sorted
 * @param right The ending index of the array to be sorted
 * @param threads_num The number of threads used for parallel processing
 */
void parallel_merge_sort(std::vector<int>& arr, int left, int right, int threads_num) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    if (threads_num > 1) {
        std::vector<std::thread> threads;
        threads.emplace_back(std::thread(parallel_merge_sort, std::ref(arr), left, mid, threads_num / 2));
        threads.emplace_back(std::thread(parallel_merge_sort, std::ref(arr), mid + 1, right, threads_num / 2));
        for (auto& t : threads) t.join();
    }
    else {
        merge_sort(arr, left, right);
    }
}

int main() {
    std::vector<int> arr = { 38, 27, 43, 3, 9, 82, 10 };
    int threads_num = 2; // set the number of threads to use
    parallel_merge_sort(arr, 0, arr.size() - 1, threads_num);
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}

