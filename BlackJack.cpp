#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// Valori delle carte
enum ValoreCarta {
    ASSE = 1, DUE, TRE, QUATTRO, CINQUE, SEI, SETTE, OTTO, NOVE, DIECI, JACK, DONNA, RE
};

// Semi delle carte
enum SemeCarta {
    PICCHE, QUADRI, CUORI, FIORI
};

// Struttura della carta
struct Carta {
    ValoreCarta valore;
    SemeCarta seme;
};

// Funzione per stampare una carta
void stampaCarta(const Carta& carta) {
    string valoreStr;
    switch (carta.valore) {
        case ASSE: valoreStr = "Asso"; break;
        case JACK: valoreStr = "Jack"; break;
        case DONNA: valoreStr = "Donna"; break;
        case RE: valoreStr = "Re"; break;
        default: valoreStr = to_string(carta.valore);
    }

    string semeStr;
    switch (carta.seme) {
        case PICCHE: semeStr = "Picche"; break;
        case QUADRI: semeStr = "Quadri"; break;
        case CUORI: semeStr = "Cuori"; break;
        case FIORI: semeStr = "Fiori"; break;
    }

    cout << valoreStr << " di " << semeStr << endl;
}

// Funzione per creare un mazzo di carte
vector<Carta> creaMazzo() {
    vector<Carta> mazzo;
    for (int seme = PICCHE; seme <= FIORI; ++seme) {
        for (int valore = ASSE; valore <= RE; ++valore) {
            mazzo.push_back({static_cast<ValoreCarta>(valore), static_cast<SemeCarta>(seme)});
        }
    }
    return mazzo;
}

// Funzione per mescolare il mazzo di carte
void mescolaMazzo(vector<Carta>& mazzo) {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < mazzo.size(); ++i) {
        int j = rand() % mazzo.size();
        swap(mazzo[i], mazzo[j]);
    }
}

// Funzione per calcolare il valore della mano
int valoreMano(const vector<Carta>& mano) {
    int valore = 0;
    bool haAsso = false;
    for (const Carta& carta : mano) {
        if (carta.valore == ASSE) {
            haAsso = true;
        }
        valore += min(10, static_cast<int>(carta.valore));
    }
    if (haAsso && valore + 10 <= 21) {
        valore += 10;
    }
    return valore;
}

int main() {
    int fiches;
    cout << "Inserisci il numero di fiches con cui desideri giocare: ";
    cin >> fiches;

    while (fiches > 0) {
        int puntata;
        cout << "Fiches disponibili: " << fiches << endl;
        cout << "Inserisci la tua puntata: ";
        cin >> puntata;

        if (puntata > fiches || puntata <= 0) {
            cout << "Puntata non valida!" << endl;
            continue;
        }

        vector<Carta> mazzo = creaMazzo();
        mescolaMazzo(mazzo);

        vector<Carta> manoGiocatore;
        vector<Carta> manoDealer;

        // Distribuisci due carte a ciascun giocatore
        manoGiocatore.push_back(mazzo.back());
        mazzo.pop_back();
        manoDealer.push_back(mazzo.back());
        mazzo.pop_back();
        manoGiocatore.push_back(mazzo.back());
        mazzo.pop_back();
        manoDealer.push_back(mazzo.back());
        mazzo.pop_back();

        cout << "La tua mano:" << endl;
        for (const Carta& carta : manoGiocatore) {
            stampaCarta(carta);
        }
        cout << "Valore totale: " << valoreMano(manoGiocatore) << endl;

        cout << "Mano del dealer:" << endl;
        stampaCarta(manoDealer[0]);
        cout << "Valore totale: " << static_cast<int>(manoDealer[0].valore) << endl;

        // Logica del gioco
        while (true) {
            cout << "Vuoi pescare un'altra carta (p) o stare (s)?" << endl;
            char scelta;
            cin >> scelta;

            if (scelta == 'p') {
                manoGiocatore.push_back(mazzo.back());
                mazzo.pop_back();
                cout << "La tua nuova carta:" << endl;
                stampaCarta(manoGiocatore.back());
                cout << "Valore totale: " << valoreMano(manoGiocatore) << endl;

                if (valoreMano(manoGiocatore) > 21) {
                    cout << "Hai sballato! Hai perso." << endl;
                    fiches -= puntata;
                    break;
                }
            } else if (scelta == 's') {
                int valoreDealer = valoreMano(manoDealer);
                while (valoreDealer < 17) {
                    manoDealer.push_back(mazzo.back());
                    mazzo.pop_back();
                    valoreDealer = valoreMano(manoDealer);
                }

                cout << "Mano del dealer:" << endl;
                for (const Carta& carta : manoDealer) {
                    stampaCarta(carta);
                }
                cout << "Valore totale: " << valoreDealer << endl;

                int valoreGiocatore = valoreMano(manoGiocatore);
                if (valoreDealer > 21 || valoreGiocatore > valoreDealer) {
                    cout << "Hai vinto!" << endl;
                    fiches += puntata;
                } else if (valoreGiocatore < valoreDealer) {
                    cout << "Il dealer vince." << endl;
                    fiches -= puntata;
                } else {
                    cout << "È un pareggio." << endl;
                }

                break;
            }
        }

        if (fiches <= 0) {
            cout << "Hai finito le fiches! Il gioco è terminato." << endl;
            break;
        }

        char continua;
        cout << "Vuoi continuare a giocare? (s/n): ";
        cin >> continua;
        if (continua == 'n') {
            cout << "Grazie per aver giocato! Le tue fiches rimanenti sono: " << fiches << endl;
break;
}
}
cout << "Fine del gioco. Arrivederci!" << endl;

return 0;
}
