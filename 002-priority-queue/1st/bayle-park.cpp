#include <iostream>

#define MAX 1000000

int PQ[MAX];
int count;

int get_count() {
    return count;
}
void increase() {
    count++;
}
void decrease() {
    count--;
}
int last_idx() {
    return count - 1;
}
int parent_idx(int cidx) {
    return (cidx-1) >> 1;
}
int left_idx(int cidx) {
    return ((cidx+1) << 1) - 1;
}
int right_idx(int cidx) {
    return (cidx+1) << 1;
}
bool has_left(int cidx) {
    return left_idx(cidx) <= last_idx();
}
bool has_right(int cidx) {
    return right_idx(cidx) <= last_idx();
}
bool has_children(int cidx) {
    return has_left(cidx) || has_right(cidx);
}
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    return;
}
void recursive_push(int cidx) {
    if (cidx == 0) return;
    int pidx = parent_idx(cidx);
    if (PQ[cidx] < PQ[pidx]) {
        swap(PQ[cidx], PQ[pidx]);
        recursive_push(pidx);
    }
    return;
}
void push(int value) {
    int cidx = last_idx() + 1;
    PQ[cidx] = value;
    increase();
    recursive_push(cidx);
    return;
}
int argmin(int idx1, int idx2) {
    return PQ[idx1] < PQ[idx2] ? idx1 : idx2;
}
void recursive_pop(int cidx) {
    if (has_children(cidx) == false) return;
    int min_idx = 0;
    if (has_left(cidx) && has_right(cidx)) {
        min_idx = argmin(left_idx(cidx), right_idx(cidx));
    }
    else if (has_left(cidx)) {
        min_idx = left_idx(cidx);
    }
    else if (has_right(cidx)) {
        min_idx = right_idx(cidx);
    }
    else {
        assert(0);
    }
    if (PQ[cidx] > PQ[min_idx]) {
        swap(PQ[cidx], PQ[min_idx]);
        recursive_pop(min_idx);
    }
    return;
}
int pop() {
    if (get_count() == 0) return -1;
    int ret = PQ[0];
    PQ[0] = PQ[last_idx()];
    PQ[last_idx()] = 0;  // for debugging
    decrease();
    recursive_pop(0);
    return ret;
}

int main() {
    int TC;
    std::cout << "TEST" << std::endl;
    std::cin >> TC;
    while(TC--) {
        int N;
        std::cin >> N;
        for(int i=0; i < N; i++) {
            int prio;
            std::cin >> prio;
            push(prio);
        }
        
        while(get_count() != 0) {
            int val = pop();
            printf("%d ", val);
        }
        printf("\n");
    }
    return 0;
}
