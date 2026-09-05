#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

// Custom IntroSort implementation used by Team::OrderPlayers.
//
// IntroSort = Quicksort, with:
//   - fallback to Insertion Sort for small partitions
//   - fallback to Heapsort if recursion depth gets too large
//     (guards against Quicksort's worst-case O(n^2))
//
// Templated + header-only since it needs to work generically for the
// comparator lambda passed in from Team.cpp.
namespace IntroSortDetail
{
    constexpr int kInsertionThreshold = 16;

    // Comparator returns true if "a" should be ordered BEFORE "b".
    template <typename T, typename Compare>
    void InsertionSort(std::vector<T>& arr, int lo, int hi, Compare comp)
    {
        for (int i = lo + 1; i <= hi; ++i)
        {
            T key = arr[i];
            int j = i - 1;
            while (j >= lo && comp(key, arr[j]))
            {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

    template <typename T, typename Compare>
    void SiftDown(std::vector<T>& arr, int lo, int root, int hi, Compare comp)
    {
        // Treat arr[lo..hi] as a heap, built with "comp" so the element that
        // should come FIRST ends up at arr[lo] once fully heapified.
        while (true)
        {
            int largest = root;
            int left = lo + 2 * (root - lo) + 1;
            int right = lo + 2 * (root - lo) + 2;

            if (left <= hi && comp(arr[left], arr[largest]))
                largest = left;
            if (right <= hi && comp(arr[right], arr[largest]))
                largest = right;

            if (largest == root)
                break;

            std::swap(arr[root], arr[largest]);
            root = largest;
        }
    }

    template <typename T, typename Compare>
    void HeapSort(std::vector<T>& arr, int lo, int hi, Compare comp)
    {
        int n = hi - lo + 1;
        if (n < 2) return;

        for (int i = lo + (n / 2) - 1; i >= lo; --i)
            SiftDown(arr, lo, i, hi, comp);

        for (int end = hi; end > lo; --end)
        {
            std::swap(arr[lo], arr[end]);
            SiftDown(arr, lo, lo, end - 1, comp);
        }
    }

    template <typename T, typename Compare>
    int Partition(std::vector<T>& arr, int lo, int hi, Compare comp)
    {
        // Median-of-three pivot selection to help avoid worst-case splits.
        int mid = lo + (hi - lo) / 2;
        if (comp(arr[mid], arr[lo])) std::swap(arr[mid], arr[lo]);
        if (comp(arr[hi], arr[lo])) std::swap(arr[hi], arr[lo]);
        if (comp(arr[hi], arr[mid])) std::swap(arr[hi], arr[mid]);
        std::swap(arr[mid], arr[hi]); // pivot placed at hi

        T pivot = arr[hi];
        int i = lo - 1;
        for (int j = lo; j < hi; ++j)
        {
            if (comp(arr[j], pivot))
            {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[hi]);
        return i + 1;
    }

    template <typename T, typename Compare>
    void IntroSortUtil(std::vector<T>& arr, int lo, int hi, int depthLimit, Compare comp)
    {
        while (hi - lo > 0)
        {
            int size = hi - lo + 1;

            if (size < kInsertionThreshold)
            {
                InsertionSort(arr, lo, hi, comp);
                return;
            }

            if (depthLimit == 0)
            {
                HeapSort(arr, lo, hi, comp);
                return;
            }

            --depthLimit;
            int p = Partition(arr, lo, hi, comp);

            // Recurse into the smaller side, loop on the larger side (tail-call trim)
            if (p - lo < hi - p)
            {
                IntroSortUtil(arr, lo, p - 1, depthLimit, comp);
                lo = p + 1;
            }
            else
            {
                IntroSortUtil(arr, p + 1, hi, depthLimit, comp);
                hi = p - 1;
            }
        }
    }
} // namespace IntroSortDetail

template <typename T, typename Compare>
void IntroSort(std::vector<T>& arr, Compare comp)
{
    if (arr.size() < 2) return;
    int depthLimit = static_cast<int>(2.0 * std::log2(static_cast<double>(arr.size())));
    IntroSortDetail::IntroSortUtil(arr, 0, static_cast<int>(arr.size()) - 1, depthLimit, comp);
}