#include <chrono>
#include <iostream>

using namespace std;

class Meas {
   public:
    Meas() {
    }
    void start() {
        t1 = std::chrono::high_resolution_clock::now();
    }

    void end() {
        t2 = std::chrono::high_resolution_clock::now();
    }
    void meas() {
        std::chrono::duration<double> t_diff = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        cout << "diff: " << t_diff.count() << "\n\n";
    }

   private:
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
};
void nSquare(int n) {
    Meas m;
    cout << "nsquare: " << n << " ..meas.." << endl;
    m.start();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
        }
    }
    m.end();
    m.meas();
}

void n(int n) {
    Meas m;
    cout << "n: " << n << " ..meas.." << endl;
    m.start();
    for (int i = 0; i < n; ++i) {
    }
    m.end();
    m.meas();
}
int main() {
    nSquare(1'000);
    nSquare(10'000);
    n(500'000'000);
    n(1'000'000'000);
    return 0;
}
