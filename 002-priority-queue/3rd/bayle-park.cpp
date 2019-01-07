#include <iostream>
#include <string>
using namespace std;
#define MAX_SIZE 100

template <typename T>
struct MinHeap {
public:
    T pop() {
        const T retval = pq[0];
        if (count != 0) {
            count--;
            pq[0] = pq[count];
            recursive_pop(0);
        }
        return retval;
    }
    void push(const T& val) {
        count++;
        pq[count - 1] = val;
        recursive_push(count - 1);
    }
    void init() {
        count = 0;
    }
    int get_count() {
        return count;
    }
    T* raw() { return pq; }
private:
    inline int left(int cidx) {
        return (cidx + 1) * 2 - 1;
    }
    inline int right(int cidx) {
        return (cidx + 1) * 2;
    }
    inline int parent(int cidx) {
        return (cidx - 1) / 2;
    }
    inline bool has_children(int cidx) {
        return has_left(cidx) && has_right(cidx);
    }
    inline bool has_left(int cidx) {
        return left(cidx) < count;
    }
    inline bool has_right(int cidx) {
        return right(cidx) < count;
    }
    void swap(int idx1, int idx2) {
        T temp = pq[idx2];
        pq[idx2] = pq[idx1];
        pq[idx1] = temp;
    }
    void recursive_pop(int cidx) {
        if (has_children(cidx)) {
            int minidx = pq[left(cidx)] < pq[right(cidx)] ? left(cidx) : right(cidx);
            if (pq[minidx] < pq[cidx]) {
                swap(minidx, cidx);
                recursive_pop(minidx);
            }
        }
        else if (has_left(cidx)) {
            if (pq[left(cidx)] < pq[cidx]) {
                swap(left(cidx), cidx);
                recursive_pop(left(cidx));
            }
        }
        return;
    }
    void recursive_push(int cidx) {
        if (cidx == 0) return;
        int pidx = parent(cidx);
        if (pq[pidx] > pq[cidx]) {
            swap(pidx, cidx);
            recursive_push(pidx);
        }
    }
private:
    int count;
    T pq[MAX_SIZE];
};

#ifdef NORMAL_TEST
MinHeap<int> pq;

int main() {
    pq.init();
    cout << "MinHeap" << endl;
    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;
        for(int i=0; i <N; i++) {
            int priority;
            cin >> priority;
            pq.push(priority);
        }
        while(pq.get_count()) {
            cout << pq.pop() << " ";
        }
        cout << endl;
    }
    return 0;
}
#else
struct Node {
    Node() { }
    Node(const string& val, int prio) : val(val), prio(prio) { }
    string val;
    int prio;
    bool enable;
    bool operator < (const Node& node) const {
        return prio < node.prio;
    }
    bool operator > (const Node& node) const {
        return prio > node.prio;
    }
    friend ostream& operator << (ostream& os, const Node& node) {
        os << "(" << node.val << ", " << node.prio << ")";
        return os;
    }
};
MinHeap<Node> pq;

int main() {
    cout << "MinHeap" << endl;
    int TC;
    cin >> TC;
    while(TC--) {
        pq.init();
        int N;
        cin >> N;
        for (int i = 0; i < N; i++) {
            string val;
            int prio;
            cin >> val >> prio;
            Node node(val, prio);
            node.enable = true;
            pq.push(node);
        }
        int D;
        cin >> D;
        for (int i = 0; i < D; i++) {
            string del_val;
            cin >> del_val;
            int count = pq.get_count();
            for(int j = 0; j < count; j++) {
                if (pq.raw()[j].enable == false) continue;
                if (pq.raw()[j].val != del_val) continue;
                pq.raw()[j].enable = false;
            }
        }
        cout << endl;
        while(pq.get_count()) {
            Node node = pq.pop();
            if (node.enable)
                cout << node << " > ";
        }
        cout << endl;
    }
}

#endif
