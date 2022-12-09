using namespace std;
#include <iostream>
#include "KlasaWielomian.h"

int main()
{
    int i, st = 1;
    float *ws = new float[st + 1] { 1, 1 };
    Wielomian w("3x^2+5-2x^13+x");
    Wielomian w1(w);
    Wielomian w2(ws, st);
    Wielomian w4;
    cout << w1 << endl;
    cout << w2 << endl;
    cout << (w1 + w2) << endl;
    cout << w2 << endl;
    cout << ((double)4 + w2) << endl;
    cout << (w1 + (double)4) << endl;
    cout << (w2 - w2) << endl;
    Wielomian w3 = w2;
    cout << w3 << endl;
    w2 *= w2;
    cout << w2;
    cout << ((w2 * w2) / w2) << endl;
    cin >> w4;
    cout << w4 <<endl;
    Wielomian w5 = w4.Pochodna();
    cout << w5 <<endl;
    cin >> i;
    return 0;
}
