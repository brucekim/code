/* 0 empty, 1 wall, 2 virus 
 * n(row) x m(col)
 * no. of new walls to be built: 3
 * virus can pollute to up/down/left and right
 * given map , find max. size of safety zone with best construction of 3 walls
 *
 * design:
 * 1. dfs for possible permutation regarding virus given to map
 * 2. once building up 3 walls in possible permutation, start bfs for polluting empty zones
 * 3. get the size of safety zone after step. 2
 * 4. repeat from step 1 till exhausting all possible permutation
 *
 * required ds: stack, queue, list
 *
 * */
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>

const int const_empty = 0;
const int const_wall = 1;
const int const_virus = 2;
const int const_max_map = 8;
const int const_max_virus = 10;

int row_diff[] = {-1, 1, 0, 0};
int col_diff[] = {0, 0, -1, 1};
bool valid(int r, int c) {
    return (r >= 0 && r <= 8 && c >= 0 && c <= 8);
}

struct coord {
    coord(int _row=-1, int _col=-1) : row(_row), col(_col) {}
    int row;
    int col;
    std::string tostring() {
        std::stringstream ss;
        ss << "(" << row << " " << col << ")";
        return ss.str();
    }
};

template <typename T>
struct node {
    node(T _data) : data(_data), prev(nullptr), next(nullptr) {}
    T data;
    node<T> *prev;
    node<T> *next;
};

template <typename T>
class xlist_iterator {
   public:
    xlist_iterator(node<T> *it) : current(it) {}
    xlist_iterator<T> &operator++() {
        current = current->next;
        return *this;
    }
    T &operator*() {
        return current->data;
    }
    bool operator!=(const xlist_iterator<T> &it) {
        return current != it.current;
    }
    bool operator==(const xlist_iterator<T> &it) {
        return current == it.current;
    }

   private:
    node<T> *current;
};
template <typename T>
class xlist {
   public:
    using iterator = xlist_iterator<T>;
    xlist() : head(nullptr), tail(nullptr), sz(0) {}
    virtual ~xlist() {
        while (head != nullptr) {
            node<T> *tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    void push_back(T data) {
        node<T> *tmp = new node<T>(data);
        ++sz;
        if (head == nullptr) {
            head = tail = tmp;
        } else {
            tail->next = tmp;
            tmp->prev = tail;
            tail = tail->next;
        }
    }
    void pop_back() {
        if (tail != nullptr) {
            node<T> *tmp = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
            delete tmp;
            --sz;
        }
    }
    void pop_front() {
        if (head != nullptr) {
            node<T> *tmp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            delete tmp;
            --sz;
        }
    }
    T &top() {
        return tail->data;
    }
    T &front() {
        return head->data;
    }
    bool isEmpty() {
        return sz == 0;
    }
    int getSize() {
        return sz;
    }
    iterator begin() {
        return iterator(head);
    }
    iterator end() {
        return iterator(nullptr);
    }

   private:
    int sz;
    node<T> *head;
    node<T> *tail;
};

template <typename T>
class xstack : public xlist<T> {
   public:
   T &front() = delete;
   void pop_front() = delete;
};

template <typename T>
class xqueue : public xlist<T> {
   public:
    T &top() = delete;
    void pop_back() = delete;
};

class labinvirus {
    public:
    labinvirus() {
        visited = new bool[const_max_map]{false};
    }
    virtual ~labinvirus() {
        delete[] visited;
    }
    void dfs(coord _cwalls[], int _sz_walls) {
        cwalls = _cwalls;
        sz_walls = _sz_walls;
        dfsutil(0);
    }
    void dfsutil(int idx) {
        if (stack.getSize() == max_walls) {
            printf("candidate set:");
            for (int i = 0; i < max_walls; ++i) {
                std::cout << stack.top().tostring() << " ";
                comb.push_back(stack.top());
                stack.pop_back();
            }
            std::cout << std::endl;
            return;
        }
        for (int i=idx; i<sz_walls; ++i) {
            if (visited[i] == false) {
                visited[i] = true;
                stack.push_back(cwalls[i]);
                dfsutil(idx+1);
                stack.pop_back();
                visited[i] = false;
            }
        }
    }
    int find_max_safezone(int (&_arr)[const_max_map][const_max_map], int r, int c, coord viruses[], int sz_viruses, int sz_safezone) {
        /* init and copy */

        int arr[const_max_map][const_max_map]{0};
        int max_safezone = 0;

        while(comb.isEmpty() != true) {
            int local_safezone = sz_safezone;
            printf("local_safezone: %d\n", local_safezone);
            for (int i=0; i<r; ++i) {
                for (int j=0; j<c; ++j) {
                    arr[i][j] = _arr[i][j];
                    printf("%d ", arr[i][j]);
                }
                printf("\n");
            }
            for (int i=0; i<max_walls; ++i) {
                coord wall = comb.top();
                comb.pop_back();
                arr[wall.row][wall.col] = const_wall;
                printf("build wall at (%d %d)\n", wall.row, wall.col);
            }
            local_safezone = local_safezone - max_walls;

            xqueue<coord> q;
            for (int i=0; i<sz_viruses; ++i) {
                q.push_back(viruses[i]);
            }
            while(q.isEmpty() != true) {
                coord t = q.front();
                q.pop_front();
                for(int i=0; i<4; ++i) {
                    int rr = t.row + row_diff[i];
                    int cc = t.col+ col_diff[i];
                    if (valid(rr, cc) == true && arr[rr][cc] == const_empty) {
                        arr[rr][cc] = const_virus;
                        q.push_back(coord(rr, cc));
                        --local_safezone;
                    }
                }
            }
            if (max_safezone < local_safezone) {
                max_safezone = local_safezone;
            }
        }
        return max_safezone;
    }
    private:
    int max_walls = 3;
    bool *visited;
    xstack<coord> stack;
    xlist<coord> comb;
    coord *cwalls = nullptr;
    int sz_walls = 0;
};

void solve() {
    int n, m;
    int arr[const_max_map][const_max_map]{0};
    bool arrwall[const_max_map][const_max_map]{false};
    coord cwalls[const_max_virus];
    coord viruses[const_max_virus];
    int sz_cwalls = 0;
    int sz_viruses = 0;
    int sz_safezone = 0;
    labinvirus lab; 


    scanf("%d", &n);
    scanf("%d", &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &arr[i][j]);
        }
    }

    /* scanning candidate walls and coord of virus */
    /* 1nd: wrong approach to identify candidate walls 
    fail
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (arr[i][j] == const_empty) {
                ++sz_safezone;
            }
            else if (arr[i][j] == const_virus) {
                viruses[sz_viruses++] = coord(i, j);
                for (int k=0; k<4; ++k) {
                    int r = i+row_diff[k];
                    int c = j+col_diff[k];
                    if (valid(r, c) == true && arr[r][c] == const_empty) {
                        cwalls[sz_cwalls++] = coord(r, c);
                    }
                }
            }
        }
    }
    */

    /* 2nd approach - brute force
    fail
    * nCk 35C3 = 35! / (3! * (35-3)!) = (35 * 34 * 33) / 6 -> 6545
    * fail
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (arr[i][j] == const_empty) {
                ++sz_safezone;
            } else if (arr[i][j] == const_virus) {
                viruses[sz_viruses++] = coord(i, j);
                int r = i+1;
                int c = j;
                while (valid(r, c) == true && arr[r][c] == const_empty) {
                    cwalls[sz_cwalls++] = coord(r, c);
                    r++;
                }
                r = i-1;
                c = j;
                while (valid(r, c) == true && arr[r][c] == const_empty) {
                    cwalls[sz_cwalls++] = coord(r, c);
                    r--;
                }
                r = i;
                c = j+1;
                while (valid(r, c) == true && arr[r][c] == const_empty) {
                    cwalls[sz_cwalls++] = coord(r, c);
                    c++;
                }
                r = i;
                c = j-1;
                while (valid(r, c) == true && arr[r][c] == const_empty) {
                    cwalls[sz_cwalls++] = coord(r, c);
                    c--;
                }
            }
        }
    }
    */

   /* 3rd approach
   * choose all posible empty walls as candidates
   * then find combination, not permutation, for 3 walls in the all possible candidates
   */
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (arr[i][j] == const_empty) {
                ++sz_safezone;
                cwalls[sz_cwalls++] = coord(i, j);
            } else if (arr[i][j] == const_virus) {
                viruses[sz_viruses++] = coord(i, j);
            }
        }
    }

    // coord of viruses
    std::cout << "viruses.. " << std::endl;
    for (int i = 0; i < sz_viruses; ++i) {
        std::cout << viruses[i].tostring() << std::endl;
    }
    // candidate of walls to be constructed
    std::cout << "candidate walls.. " << std::endl;
    for (int i=0; i<sz_cwalls; ++i) {
        std::cout << cwalls[i].tostring() << std::endl;
    }
    return;
    
    // get permutation of 3-walls candidates to try
    lab.dfs(cwalls, sz_cwalls);
    int ans = lab.find_max_safezone(arr, n, m, viruses, sz_viruses, sz_safezone);
    printf("ans: %d\n", ans);
}

int main() {
    freopen("inputs/acmicpc_14502_input.txt", "r", stdin);
    solve();
    return 0;
}
