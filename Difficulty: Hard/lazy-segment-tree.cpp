#include <bits/stdc++.h>

using namespace std;

// Type alias for large sums to prevent overflow
using ll = long long;

/**
 * @brief Segment Tree with Lazy Propagation for Range Sum Queries and Range Addition Updates.
 * Uses 1-based indexing for the tree arrays.
 */
class LazySegmentTree {
private:
    vector<ll> tree; // Stores the segment sums
    vector<ll> lazy; // Stores the pending updates (values to be added)
    int N; // Size of the original array

    void build(const vector<ll>& arr, int start, int end, int node) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(arr, start, mid, 2 * node);
        build(arr, mid + 1, end, 2 * node + 1);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void push(int start, int end, int node) {
        if (lazy[node] != 0) {
            // Apply the lazy update to the current node's sum
            tree[node] += (ll)(end - start + 1) * lazy[node];

            if (start != end) {
                // Propagate the update to children
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            // Clear the lazy tag
            lazy[node] = 0;
        }
    }

    void updateRange(int start, int end, int node, int l, int r, ll val) {
        push(start, end, node); 

        // 1. Current segment is outside the update range [l, r]
        if (start > r || end < l) return;

        // 2. Current segment is completely inside the update range [l, r]
        if (l <= start && end <= r) {
            // Apply the update locally
            tree[node] += (ll)(end - start + 1) * val;
            
            if (start != end) {
                // Mark children with the lazy update
                lazy[2 * node] += val;
                lazy[2 * node + 1] += val;
            }
            return;
        }

        // 3. Partial overlap - recurse and update node sum
        int mid = start + (end - start) / 2;
        updateRange(start, mid, 2 * node, l, r, val);
        updateRange(mid + 1, end, 2 * node + 1, l, r, val);

        // Recombine the results from children
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    ll queryRange(int start, int end, int node, int l, int r) {
        push(start, end, node); 

        // 1. Current segment is outside the query range [l, r]
        if (start > r || end < l) return 0;

        // 2. Current segment is completely inside the query range [l, r]
        if (l <= start && end <= r) return tree[node];

        // 3. Partial overlap - recurse and sum results
        int mid = start + (end - start) / 2;
        ll p1 = queryRange(start, mid, 2 * node, l, r);
        ll p2 = queryRange(mid + 1, end, 2 * node + 1, l, r);

        return p1 + p2;
    }

public:
    LazySegmentTree(const vector<ll>& arr) {
        N = arr.size();
        // The tree array size is typically 4*N.
        tree.resize(4 * N, 0); 
        lazy.resize(4 * N, 0);
        if (N > 0) build(arr, 0, N - 1, 1);
    }

    void update(int l, int r, ll val) {
        if (l > r || l < 0 || r >= N) return; 
        updateRange(0, N - 1, 1, l, r, val);
    }

    ll query(int l, int r) {
        if (l > r || l < 0 || r >= N) return 0; 
        return queryRange(0, N - 1, 1, l, r);
    }
};

int main() {
    // Original array: 1, 3, 5, 7, 9, 11
    vector<ll> initial_array = {1, 3, 5, 7, 9, 11};
    
    cout << "Lazy Segment Tree Demo (Range Add / Range Sum)" << endl;
    
    LazySegmentTree st(initial_array);

    // Initial Queries
    cout << "Initial Query [1, 3]: " << st.query(1, 3) << " (Expected: 15)" << endl;
    cout << "Initial Query [0, 5]: " << st.query(0, 5) << " (Expected: 36)" << endl;
    
    // Update Operation: Add 10 to range [1, 5]
    st.update(1, 5, 10);
    cout << "Updated range [1, 5] by adding 10" << endl;

    // Post-Update Queries
    // Corrected Expected values: 45, 57, 86
    cout << "Post-Update Query [1, 3]: " << st.query(1, 3) << " (Expected: 45)" << endl;
    cout << "Post-Update Query [3, 5]: " << st.query(3, 5) << " (Expected: 57)" << endl;
    cout << "Post-Update Query [0, 5]: " << st.query(0, 5) << " (Expected: 86)" << endl;

    return 0;
}
