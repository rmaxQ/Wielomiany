using namespace std;
#include <iostream>
#include <cstring>
#include "KlasaWielomian.h"


int Wielomian::OkreslStopien(const char* napis) {
    int st = 0;
    int nStopien = 0;
    char* end;

    for (int i = 0; napis[i]; i++) {
        if (napis[i] == 'x') {
            if (napis[i + 1] == '^') {
                nStopien = strtol(napis + i + 2, &end, 10);
                i = end - napis;
            }
            else
                nStopien = 1;

            if (nStopien > st)
                st = nStopien;
        }
    }
    return st;
}

void Wielomian::StworzWielomian() {
    this->wsp = new float[stopien + 1];
    for (int i = 0; i <= this->stopien; i++)
        this->wsp[i] = 0;
}

char* Wielomian::AnalizujJednomian(char* napis) {
    int znak, wyk;
    float wsp1;

    //okreœlamy znak
    if (*napis == '-')
        znak = -1;
    else
        znak = 1;
    if (*napis == '+' || *napis == '-')
        napis++;

    //okreœlamy wspó³czynnik
    if (*napis == 'x')
        wsp1 = 1;
    else
        wsp1 = strtof(napis, &napis);
    //okreœlamy wyk³adnik
    if (*napis != 'x')
        wyk = 0;
    else
        if (*++napis != '^')
            wyk = 1;
        else
            wyk = strtol(++napis, &napis, 10);

    //dopisujemy do wielomianu
    this->wsp[wyk] += wsp1 * znak;

    return napis;
}

void Wielomian::PrzepiszWielomian(const float* tab, int st)
{
    for (int i = 0; i <= st; i++)
        this->wsp[i] += tab[i];
}

void Wielomian::WypelnijWielomian(char* napis) {
    while (*napis) {
        napis = this->AnalizujJednomian(napis);
    }
}

Wielomian::~Wielomian() {
    delete[] wsp;
}

Wielomian::Wielomian() {

    this->stopien = 0;

    this->StworzWielomian();

    this->wsp[0] = 0;
}

Wielomian::Wielomian(const char* napis) {
    char* napis2 = UsunSpacje(napis);

    this->stopien = OkreslStopien(napis2);

    this->StworzWielomian();

    this->WypelnijWielomian(napis2);
}

Wielomian::Wielomian(const float* tab, int st) {
    this->stopien = st;

    this->StworzWielomian();

    this->PrzepiszWielomian(tab, st);
}

Wielomian::Wielomian(const Wielomian& w) {
    this->stopien = w.stopien;

    this->StworzWielomian();

    this->PrzepiszWielomian(w.wsp, w.stopien);
}

Wielomian::Wielomian(int st, float ws) {
    this->stopien = st;

    this->StworzWielomian();

    this->wsp[st] = ws;
}

void Wielomian::Dodawanie(const Wielomian& result, const Wielomian& w) {
    for (int i = 0; i <= w.stopien; i++) {
        result.wsp[i] += w.wsp[i];
    }
    for (int i = 0; i <= this->stopien; i++) {
        result.wsp[i] += this->wsp[i];
    }
}

Wielomian Wielomian::operator+(const Wielomian& w) {
    Wielomian* result = new Wielomian();
    result->stopien = max(w.stopien, stopien);
    result->StworzWielomian();
    Dodawanie(*result, w);
    return *result;
}

Wielomian operator+(double k, const Wielomian& w) {
    Wielomian* result = new Wielomian(w);
    result->wsp[0] += k;
    return *result;
}

Wielomian Wielomian::operator+(double k) {
    Wielomian* result = new Wielomian(*this);
    result->wsp[0] += k;
    return *result;
}
/*nieefektywnie wykonany operator +=, -=, *=
lepiej by było zrobić a + b na podstawie += a nie odwrotnie
*/
void Wielomian::operator+=(const Wielomian& w) {
    *this = *this + w;
}

void Wielomian::operator+=(double k) {
    *this = *this + k;
}

void Wielomian::Odejmowanie(const Wielomian& result, const Wielomian& w) {
    for (int i = 0; i <= w.stopien; i++) {
        result.wsp[i] -= w.wsp[i];
    }
    for (int i = 0; i <= this->stopien; i++) {
        result.wsp[i] += this->wsp[i];
    }
}

Wielomian Wielomian::operator-(const Wielomian& w) {
    Wielomian* result = new Wielomian();
    result->stopien = max(w.stopien, stopien);
    result->StworzWielomian();
    Odejmowanie(*result, w);
    return *result;
}

Wielomian operator-(double k, const Wielomian& w) {
    Wielomian* result = new Wielomian(w);
    result->wsp[0] -= k;
    return *result;
}

Wielomian Wielomian::operator-(double k) {
    Wielomian* result = new Wielomian(*this);
    result->wsp[0] -= k;
    return *result;
}

void Wielomian::operator-=(const Wielomian& w) {
    *this = *this - w;
}

void Wielomian::operator-=(double k) {
    this->wsp[0] -= k;
}

void Wielomian::Mnozenie(const Wielomian& result, const Wielomian& w) {
    for (int i = 0; i <= this->stopien; i++) {
        for (int j = 0; j <= w.stopien; j++) {
            result.wsp[i + j] += (w.wsp[j] * wsp[i]);
        }
    }
}

Wielomian Wielomian::operator*(const Wielomian& w) {
    Wielomian* result = new Wielomian();
    result->stopien = w.stopien + stopien;
    result->StworzWielomian();
    Mnozenie(*result, w);
    return *result;
}

Wielomian operator*(double k, const Wielomian& w) {
    Wielomian* result = new Wielomian(w);
    for (int i = 0; i <= result->stopien; i++)
        result->wsp[i] *= k;
    return *result;
}

Wielomian Wielomian::operator*(double k) {
    Wielomian* result = new Wielomian(*this);
    for (int i = 0; i <= result->stopien; i++)
        result->wsp[i] *= k;
    return *result;
}

void Wielomian::operator*=(const Wielomian& w) {
    *this = *this * w;
}

void Wielomian::operator*=(double k) {
    *this = *this * k;
}

Wielomian Wielomian::operator/(const Wielomian& dzielnik) {
    Wielomian wynik;
    Wielomian dzielna = *this;
    wynik.stopien = stopien - dzielnik.stopien;
    if (wynik.stopien >= 0) {
        wynik.StworzWielomian();
        for (int i = wynik.stopien; i >= 0; i--) {
            Wielomian jedn(i, dzielna.wsp[i + dzielnik.stopien] / dzielnik.wsp[dzielnik.stopien]);
            wynik += jedn;
            dzielna -= jedn * dzielnik;
        }
        printf("\n");
        return wynik;
    }
    return 0;
}

Wielomian Wielomian::operator/(double k) {
    Wielomian wynik = *this;
    for (int i = 0; i <= stopien; i++) {
        wynik.wsp[i] /= k;
    }
    return wynik;
}

void Wielomian::operator/=(const Wielomian& dzielnik) {
    *this = *this / dzielnik;
}

void Wielomian::operator/=(double k) {
    *this = *this / k;
}

Wielomian Wielomian::operator%(const Wielomian& dzielnik) {
    Wielomian wynik, dzielna = *this;
    wynik.stopien = stopien - dzielnik.stopien;
    if (wynik.stopien >= 0) {
        wynik.StworzWielomian();
        for (int i = wynik.stopien; i >= 0; i = dzielna.stopien - dzielnik.stopien) {
            Wielomian jedn(i, dzielna.wsp[i - dzielnik.stopien] / dzielnik.wsp[dzielnik.stopien]);
            wynik += jedn;
            dzielna -= jedn * dzielnik;
        }
        return dzielna;
    }
    return 0;
}

void Wielomian::operator%=(const Wielomian& dzielnik) {
    *this = *this % dzielnik;
}

bool Wielomian::operator==(const Wielomian& w) {
    if (stopien != w.stopien) return false;
    else {
        for (int i = 0; i <= stopien; i++) {
            if (wsp[i] != w.wsp[i]) return false;
        }
    }
    return true;
}

void Wielomian::operator=(const Wielomian& w) {
    this->stopien = w.stopien;

    this->StworzWielomian();

    this->PrzepiszWielomian(w.wsp, w.stopien);
}

float Wielomian::operator()(double k) {
    float wynik = 0;
    for (int i = stopien; i >= 0; i--) {
        wynik += wsp[i];
        if (i > 0) wynik *= k;
    }
    return wynik;
}

float Wielomian::operator[](int k) {
    return wsp[k];
}

ostream& operator<<(ostream& o, const Wielomian& w) {
    w.Pokaz(o);
    return o;
}

istream& operator>>(istream& is, Wielomian& w) {
    string s;
    is >> s;
    int n = s.length();
    char *napis = new char[n+1], * napis2 = 0;
    strcpy(napis, s.c_str());
    napis2 = UsunSpacje(napis);
    Wielomian w1(napis2);
    w = w1;
    return is;
}

void Wielomian::Pokaz(ostream& o)const {
    for (int i = 0; i <= this->stopien; i++) {
        if (this->wsp[i] > 0) {
            if (i > 0) o << "+";
            if (this->wsp[i] != 1) o << this->wsp[i];
            else if (i == 0) o << this->wsp[i];
            if (i == 1) {
                o << "x";
            }
            else if (i != 0) {
                o << "x^" << i;
            }
        }
        else if (this->wsp[i] < 0) {
            if (this->wsp[i] != 1) o << this->wsp[i];
            else o << "-";
            if (i == 1) {
                o << "x";
            }
            else if (i != 0) {
                o << "x^" << i;
            }
        }
    }
    if (this->stopien==0 && this->wsp[0] == 0) o << "0";
}

char* UsunSpacje(const char* napis) {
    char* napis2;
    char* tmp = (char*)malloc(sizeof(char) * strlen(napis));
    strcpy(tmp, napis);
    napis2 = tmp;
    while (*napis != '\0') {
        if (*napis == ' ') {
            napis++;
            continue;
        }
        *tmp++ = *napis;
        napis++;
    }
    *tmp = '\0';
    return napis2;
}

Wielomian Wielomian::Pochodna() {
    Wielomian w;
    if (this->stopien != 0) {
        w.stopien = this->stopien - 1;
        w.StworzWielomian();
        for (int i = 1; i <= this->stopien; i++) {
            w.wsp[i - 1] = i * this->wsp[i];
        }
    }
    return w;
}