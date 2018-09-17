#include <stdint.h>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

void drawLine(vector<uint8_t> &screen, int width, int x1, int x2, int y) {
    y--;
    int s, e, s_r, e_r;
    s = x1 / 8;
    s_r = 8 - (x1 % 8);
    for (int i = 0; i < s_r; ++i) {
        screen[y * (width / 8) + s] |= 1 << i;
    }
    e = x2 / 8;
    e_r = 8 - x2 % 8;
    for (int i = 0; i < e_r; ++i) {
        screen[y * (width / 8) + e] |= 1 << i;
    }

    for (int i = s + 1; i < e; ++i) {
        screen[y * (width / 8) + i] = 0xFF;
    }
    cout << "s: " << s << " e:" << e << endl;
    screen[y * (width / 8) + e] = ~screen[y * (width / 8) + e];
}

int main() {
    /* x = 32 = 8bit * 4
       y = 32
    */
    int w = 32;
    int h = 10;
    int x1 = 3;
    int x2 = 30;
    int y = 5;
    vector<uint8_t> screen;
    screen.resize(w / 8 * h);
    for (auto &&it : screen) {
        it = 0;
    }
    drawLine(screen, w, x1, x2, y);

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w / 8; ++j) {
            cout << hex << setfill('0') << setw(2) << static_cast<int>(screen[i * (w / 8) + j]) << " ";
            //cout << static_cast<int>(screen[i * (w / 8) + j]) << " ";
        }
        cout << ";\n";
    }

    return 0;
}
