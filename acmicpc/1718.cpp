#include <iostream>
#include <cstring>
using namespace std;

#define N_ALPHA 26
#define SZ_MAX 30001
char vigenere(char p, char k)
{
    char c = p - k - 1;
    c = c % N_ALPHA;
    if (c < 0)
    {
        c = c + N_ALPHA;
    }
    return c + 'a';
}
void ciphering(const char *plain, size_t sz_plain, const char *key, size_t sz_key)
{
    for (int i = 0; i < sz_plain; ++i)
    {
        if (plain[i] == ' ')
        {
            cout << " ";
        }
        else
        {
            cout << vigenere(plain[i], key[i % sz_key]);
        }
    }
}
void test()
{
    char plain[SZ_MAX];
    char key[SZ_MAX];
    cin.getline(plain, SZ_MAX);
    cin.getline(key, SZ_MAX);
    ciphering(plain, strlen(plain), key, strlen(key));
}
int main()
{
    test();
    return 0;
}
