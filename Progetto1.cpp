#include <iostream>
#include <vector>
#include <stdlib.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

const double A = 1000;
const double B = pow(500.0, 0.01010101);

double getResolution() {
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;
    do {
        end = steady_clock::now();
    } while (start == end);
    typedef duration<double, seconds::period> duration;
    return duration_cast<duration>(end - start).count();
}

string createString(int n) {
    int x;
    string c;
    int q = rand() % n;
    cout << "q vale :" << q << endl;
    string s = "";
    for (int i = 0; i < q - 1; i++) {
        if (rand() % 2) {
            s.append("a");
        }
        else {
            s.append("b");
        }
    }
    s.append("c");

    for (int i = q; i < n; i++) {
        x = (i - 1) % (q + 1);
        c = string(1, s[x]);
        s.append(c);
    }
    cout << s << s.length() << endl;
    return s;
}



/*
void initializeStrings(){
    int n;
    for (int i = 0; i < 100; i++) {
        n = (int) A * pow(B, i);
        //cout << n << endl;
        createString(n);
    }
}
*/

bool period(string s, int p) {

    for (int i = 0; i < (s.length() - p); i++) {
        if (s[i] != s[i + p]) {
            return false;
        }
    }
    return true;
}

int PeriodNaive(string s) {

    for (int p = 1; p <= s.length(); p++) {
        if (period(s, p)) {
            return p;
        }
    }
}

int border(string s) {
    int n = s.length();
    vector<int> r;
    r.push_back(0);
    r.push_back(0);

    for (int i = 1; i < n - 1; i++) {
        //calcolo r[i+1]
        int z = r[i];
        while (z > 0 && s[i + 1] != s[z + 1]) {
            z = r[z];
        }
        if (s[z + 1] == s[i + 1]) {
            r.push_back(z + 1);
        }
        else {
            r.push_back(0);
        }
    }

    return r[n - 1];
}

// periodo minimo è n - bordo massimo

int PeriodSmart(string s) { // tempo lineare
    int r = border(" " + s);
    return s.length() - r;
}


void initializeStrings() {
    int n;
    for (int i = 0; i < 100; i++) {
        n = (int)A * pow(B, i);
        double somma = 0.0;
        for (int j = 0; j < 100; j++) {
            string s = createString(n);
            //start clock
            PeriodSmart(s);
            //end clock
            //aggiorno somma
        }
        //calcolo media

        //cout << n << endl;

    }
}
int main() {

    double r = getResolution();
    cout.precision(15);
    cout << fixed << r << endl;

    double tMin = r * (1 / 0.001 + 1);
    cout << fixed << tMin << endl;

    cout << fixed << B << endl;

    initializeStrings();
}
