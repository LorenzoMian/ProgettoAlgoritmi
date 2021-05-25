#include <iostream>
#include <fstream>
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
    return s;
}

string createString2(int n) {
    int x;
    string c;
    int q = rand() % n;
    string s = "";
    for (int i = 0; i < q; i++) {
        if (rand() % 2) {
            s.append("a");
        }
        else {
            s.append("b");
        }
    }
    for (int i = q; i < n; i++) {
        x = (i - 1) % (q + 1);
        c = string(1, s[x]);
        s.append(c);
    }
    return s;
}

string createString1(int n) {
    int x;
    string s = "";
    for (int i = 0; i < n; i++) {
        if (rand() % 2) {
            s.append("a");
        }
        else {
            s.append("b");
        }
    }
    return s;
}

string createStringBest(int n) {
    string s = "";
    for (int i = 0; i < n; i++) {
        s.append("a");
    }
    return s;
}

string createStringWorst(int n) {
    string s = "";
    for (int i = 0; i < n-1; i++) {
        s.append("a");
    }
    s.append("b");
    return s;
}

// funzione ausialiaria di period naive
bool period(string s, int p) {
    for (int i = 0; i < (s.length() - p); i++) {
        if (s[i] != s[i + p]) {
            return false;
        }
    }
    return true;
}

/*
* Funzione che restituisce il periodo frazionario
* di una stringa in tempo quadratico
*/
int PeriodNaive(string s) {

    for (int p = 1; p <= s.length(); p++) {
        if (period(s, p)) {
            return p;
        }
    }
}

// Funzione ausiliaria di Period Smart
int border(string s) {
    int n = s.length();
    vector<int> r;
    r.push_back(0);
    r.push_back(0);

    for (int i = 1; i < n - 1; i++) {
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

/*
* Funzione che restituisce il periodo frazionario di
* una stringa in tempo lineare
*/
int PeriodSmart(string s) {
    int r = border(" " + s);
    return s.length() - r;
}

/*
* Restituisce un vettore di stringhe
* generate con un determinato metodo
* 1 - 2 - 3 = metodi base
* 4 = caso peggiore naive
* 5 = caso migliore naive
*/
 vector<string> generaStringhe(int metodo) {
     cout << "Inizio generazione Stringhe con metodo " << metodo << endl;
    int n;
    string s;
    vector<string> risultato;
    for (int i = 0; i < 100; i++) {
        n = (int)A * pow(B, i);
        switch (metodo) {
            case 1: s = createString1(n);
            case 2: s = createString2(n);
            case 3: s = createString3(n);
            case 4: s = createStringWorst(n);
            case 5: s = createStringBest(n);
        }
        risultato.push_back(createString2(n));
    }
    return risultato;
}

/*
* Sostituisce il punto con la virgola nei risultati
*/
string aggiungiVirgola(string s) {
    for (size_t pos = 0; ; pos++) {
        pos = s.find(".", pos);
        if (pos == string::npos)
            break;
        s.erase(pos, 1);
        s.insert(pos, ",");

        return s;
    }
}

/*
* Calcola la distribuzione di frequenza dei periodi frazionari
* utilizzando periodSmart su stringhe di diversa lunghezza
*/
void calcolaDistr(int n, int r, string nomeFile) {
    double freq[100];
    int res = 0;
    ofstream f;
    string out;
    f.open(nomeFile);
    for (int i = 0; i < 100; i++) { freq[i] = 0.0; };
    for (int j = 1; j <= n; j++) {
        for (int i = 0; i < r; i++) {
            res = PeriodSmart(createString3(j));
            freq[res - 1]++;
        }
    }
    for (int i = 0; i < 100; i++) {
        out = to_string(freq[i]);
        out = aggiungiVirgola(out);
        f << out << endl;
    }
    f.close();
}

 /*
 * Stampa sul file "nomeFile" i tempi impiegati dall'algoritmo
 * specificato su ogni stringa del vettore
 * true = periodNaive
 * false = periodSmart
 */
void calcolaTempi(bool algoritmo, vector<string> stringhe, string nomeFile) {
    cout << "inizio misurazione tempi con metodo ";
    if (algoritmo) { cout << "Period Naive"; }
    else { cout << "Period Smart"; }
    cout << " su " << stringhe.size() << "stringhe." << endl;
    cout << "Scrivo su " << nomeFile << endl;
    double r = getResolution();
    double eMax = 0.001;
    double tempo, media;
    int n, k;
    typedef duration<double, seconds::period> duration;
    steady_clock::time_point start, end;
    ofstream f;
    string out;
    f.open(nomeFile);

    start = steady_clock::now();
    for (int i = 0; i < 100; i++) {
        k = 0;
        do {
            if (algoritmo) {
                PeriodNaive(stringhe[i]);
            }
            else {
                PeriodSmart(stringhe[i]);
            }
            end = steady_clock::now();
            k++;
            tempo = duration_cast<duration>(end - start).count();
        } while ((tempo) < ((r / eMax) + r));
        media = (tempo / k) * 100; // trasformo in millisecondi
        out = to_string(media); // converto in stringa e sosotituisco virgole con punti
        out = aggiungiVirgola(out);
        f << out << endl;
    }
    f.close();
    cout << "fine misurazione." << endl;
}

int main() {

    string  out = to_string(0.3421213); // converto in stringa e sosotituisco virgole con punti
    out = aggiungiVirgola(out);
    cout << out << endl;

    vector<string> stringhe1 = generaStringhe(1);
    vector<string> stringhe2 = generaStringhe(2);
    vector<string> stringhe3 = generaStringhe(3);
    vector<string> stringhePeggiori = generaStringhe(4);
    vector<string> stringheMigliori = generaStringhe(5);
    calcolaTempi(true, stringhe1, "naive1.txt");
    calcolaTempi(false, stringhe1, "smart1.txt");
    calcolaTempi(true, stringhe2, "naive2.txt");
    calcolaTempi(false, stringhe2, "smart2.txt");
    calcolaTempi(true, stringhe3, "naive3.txt");
    calcolaTempi(false, stringhe3, "smart3.txt");
    calcolaTempi(true, stringhePeggiori, "peggiore.txt");
    calcolaTempi(true, stringheMigliori, "migliore.txt");
    calcolaDistr(100, 100000, "distribuzione.txt");


}
