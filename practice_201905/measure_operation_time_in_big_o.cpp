/* computer under the test
 * - quad core : Intel(R) Core(TM) i5-4200U CPU @ 1.60GHz
 * - MemTotal:        8078732 kB
 *
 * test result:
 * 
 * 1'000'000: consume.. 0.004919
 * 100'000'000: consume.. 0.462394
 * 1'000'000'000: consume.. 4.630777
 *
 *
 */
#include <cstdio>
#include <time.h>

class measure {
    public:
        measure() {
            start = clock();
        }
        virtual ~measure() {
            end = clock();
            duration = static_cast<double>(end-start);
            printf("consume.. %lf\n", duration/CLOCKS_PER_SEC);
        }
    private:
        time_t start, end;
        double duration;
};

void pass(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}

class nMillion {
    public:
        nMillion () {
            printf("1'000'000: ");
            measure m;
            for(int i=0; i<1'000'000; ++i) {
                pass(i, i);
            }
        }
};


class n100million {
   public:
        n100million () {
            measure m;
            printf("100'000'000: ");
            for(int i=0; i<100'000'000; ++i) {
                pass(i, i);
            }
        }

};

class nBillion {
    public:
        nBillion () {
            measure m;
            printf("1'000'000'000: ");
            for(int i=0; i<1'000'000'000; ++i) {
                pass(i, i);
            }
        }
};

void solve() {
    nMillion t1;
    n100million t2;
    nBillion t3;
}

int main() {
    solve();
    return 0;
}
