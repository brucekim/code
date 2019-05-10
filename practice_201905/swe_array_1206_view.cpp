/* 조망권 구하기 */
#include <cstdio>

const int kWidth = 1000;
const int kHeight = 255;

struct Node {
    Node(bool *_room) : room(_room), next(nullptr) {}
    bool *room;
    Node *next;
};

class View {
   public:
    View() : head(nullptr), tail(nullptr) {}
    virtual ~View() {
        while (head != nullptr) {
            Node *tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    void add(bool *room) {
        Node *node = new Node(room);
        if (head == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = tail->next;
        }
    }
    int getViews() {
        Node *tmp = head;
        int views = 0;
        while (tmp != nullptr) {
            if (*(tmp->room) == true) {
                ++views;
            }
            tmp = tmp->next;
        }
        return views;
    }

   private:
    Node *head;
    Node *tail;
};

void solve() {
    bool bd[kWidth][kHeight]{false};
    int n = 0;
    int sh = 0;
    View v;

    /* init */
    for (int i = 0; i < kWidth; ++i) {
        for (int j = 0; j < kHeight; ++j) {
            bd[i][j] = true;
        }
    }

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &sh);
        for (int j = 0; j < sh; ++j) {
            bd[i - 1][j] = false;
            bd[i - 2][j] = false;
            bd[i + 1][j] = false;
            bd[i + 2][j] = false;
            v.add(&bd[i][j]);
        }
    }
    printf("%d\n", v.getViews());
}
int main() {
    freopen("02_1206_input.txt", "r", stdin);
    for (int i = 0; i < 10; ++i) {
        printf("#%d ", i + 1);
        solve();
    }
    return 0;
}
