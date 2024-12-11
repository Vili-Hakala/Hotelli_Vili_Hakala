//3p Vili Hakala
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <locale>
#include <clocale>
using namespace std;


//m��ritet��n huoneille rakenne
struct Huoneinfo {
    int numero;
    bool issingle;
    bool isBooked;
    string varaaja;
    int varausnumero;
};

// Luodaan aloitusvalikko.
int menu() {
    int menuvalinta = 0;
    bool sy�tteentarkistus = false;
    // Tarkistetaan, ett� sy�te on numero v�lilt� 0-3
    while (!sy�tteentarkistus) {
        cout << "Tervetuloa hotelli ohjelmaan. Mit� haluat tehd�?" << endl << "[1] Varaa huone." << endl << "[2] Tarkastele varauksia." << endl << "[3] Arvo uudet huoneet" << endl << "[0] Lopeta varausten k�sittely : ";
        cin >> menuvalinta;
        if (cin.fail() || menuvalinta > 3 || menuvalinta < 0) {
            cout << "Anna valikossa m��ritetty arvo 1 tai 2!";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else {
            sy�tteentarkistus = true;
        }
    }
    return menuvalinta;
}

void huoneenvaraus(vector<Huoneinfo>& huoneet, int hinta) {
    int huonenumero = 0;
    int varausaika = 0;
    int huoneenkoko = 0;
    int varaushinta = 0;
    bool sy�tteentarkistusvaraus = false;

    while (!sy�tteentarkistusvaraus) {
        cout << "Haluatko varata [1] vai [2] hengen huoneen? ";
        cin >> huoneenkoko;
        if (cin.fail() || huoneenkoko > 2 || huoneenkoko < 1) {
            cout << "Anna valikossa m��ritetty arvo 1 tai 2!" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else {
            sy�tteentarkistusvaraus = true;
        }

        // Valitaan huone numeron perusteella
        if (huoneenkoko == 1) {
            huonenumero = rand() % (huoneet.size() / 2) + 1;
        }
        else {
            huonenumero = rand() % (huoneet.size() / 2) + (huoneet.size() / 2) + 1;
        }
    }

    bool sy�tteentarkistusaika = false;
    while (!sy�tteentarkistusaika) {
        cout << "Kuinka monta vuorokautta haluat varata?" << endl;
        cin >> varausaika;
        if (cin.fail() || varausaika < 1) {
            cout << "Anna valikossa m��ritetty arvo 1 tai 2!" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else {
            sy�tteentarkistusaika = true;
        }
    }

    // Lasktaan varauksen hinta.
    varaushinta = varausaika * hinta;
    cout << "Hinta: " << varaushinta << " euroa.";
    // Pyydet��n varaajan nimi
    string varaajanNimi;
    cout << " Anna varaajan nimi: ";
    cin.ignore();
    getline(cin, varaajanNimi);

    // Etsit��n vapaa huone
    bool varausTehty = false;
    for (auto& huone : huoneet) {
        if (huone.numero == huonenumero && !huone.isBooked) {
            huone.isBooked = true;  // Merkit��n huone varatuksi
            huone.varaaja = varaajanNimi;
            huone.varausnumero = rand() % 90000 + 10000;  // Generoidaan satunnainen varausnumero

            // Tallennetaan varauksen tiedot huoneet.txt tiedostoon
            ofstream tiedosto("huoneet.txt", ios::trunc);  // Avaa tiedoston kirjoittamista varten ja tyhjent�� sen
            if (tiedosto.is_open()) {
                for (const auto& huone : huoneet) {
                    tiedosto << "Huone numero: " << huone.numero
                        << (huone.issingle ? " (yhdelle)" : " (kahdelle)")
                        << "\nVaraaja: " << huone.varaaja
                        << "\nVarausnumero: " << huone.varausnumero
                        << "\n" << (huone.isBooked ? "Varattu" : "Vapaa") << "\n\n";
                }
                tiedosto.close();
                cout << "Varaus onnistui! Tiedot on tallennettu 'huoneet.txt' -tiedostoon." << endl;
            }
            else {
                cout << "Virhe tiedoston avaamisessa." << endl;
            }

            varausTehty = true;
            break;  // Lopetetaan huoneen etsiminen, koska varaus on tehty
        }
    }

    // Jos huonetta ei l�ytynyt
    if (!varausTehty) {
        cout << "Valittu huone on jo varattu tai ei l�ytynyt!" << endl;
    }
}
// Varauksen tarkistaminen
void varaustarkastelu(const vector<Huoneinfo>& huoneet) {
    int tarkasteluvalinta = 0;
    cout << "Haluatko tarkistaa varauksen varaajan nimell� [1] vai varausnumerolla [2]? ";
    cin >> tarkasteluvalinta;

    // Varauksen tarkistaminen varaajan nimell�
    if (tarkasteluvalinta == 1) {
        string nimi;
        cout << "Anna varaajan nimi: ";
        cin.ignore();
        getline(cin, nimi); // Lukee my�s v�lily�ntej� sis�lt�v�n nimen

        // Etsit��n varausta nimell�.
        bool loytyi = false;
        for (const auto& huone : huoneet) { // For silmukka k�y l�pi kaikki huoneet-vektorin huoneet 
            if (huone.varaaja == nimi) {
                cout << "Varaus l�ytyi: Huone " << huone.numero
                    << (huone.issingle ? " (yhdelle)" : " (kahdelle)")
                    << " - Varaaja: " << huone.varaaja
                    << " - Varauksen numero: " << huone.varausnumero << endl;
                loytyi = true;
                break;
            }
        }
        if (!loytyi) {
            cout << "Varaajaa ei l�ydy." << endl;
        }
    }

    // Etsit�n varausta varausnumerolla.
    else if (tarkasteluvalinta == 2) {
        int varausnumero;
        cout << "Anna varausnumero: ";
        cin >> varausnumero;


        bool loytyi = false;
        for (const auto& huone : huoneet) {
            if (huone.varausnumero == varausnumero) {
                cout << "Varaus l�ytyi: Huone " << huone.numero
                    << (huone.issingle ? " (yhdelle)" : " (kahdelle)")
                    << " - Varaaja: " << huone.varaaja
                    << " - Varauksen numero: " << huone.varausnumero << endl;
                loytyi = true;
                break;
            }
        }
        if (!loytyi) {
            cout << "Varausnumeroa ei l�ydy." << endl;
        }
    }
    else {
        cout << "Virheellinen valinta." << endl;
    }
}

// Tulostetaan huoneet vektori huoneet.txt tiedostoon
void huoneidentulostus(const vector<Huoneinfo>& huoneet) {
    ofstream tiedosto("huoneet.txt");
    if (tiedosto.is_open()) {
        tiedosto << "Huonetiedot:\n";
        for (const auto& huone : huoneet) { //k�y l�pi huoneet vektorin
            tiedosto << "Huone " << huone.numero // tulostaa huoneen numeron
                << (huone.issingle ? " yhdelle" : " kahdelle") //Tulostaa onko huone yhdelle vai kahdelle
                << (huone.isBooked ? " - Varattu" : " - Vapaa")// Tulostaa onko huone varattu
                << "\n";
        }
        tiedosto.close();
        cout << "Tiedot tallennettu tiedostoon 'huoneet.txt'.\n";
    }
}


//Arvotaan parillinen m��r� huoneita
int huonemaarageneraattori() {
    int luku;
    do {
        luku = rand() % 41 + 30; // Satunnaisluku v�lilt� 30-70
    } while (luku % 2 != 0); //Arpoo lukua, kunnes huonem��r� on parillinen.
    return luku;    // Huonem��r�generaattori palauttaa luvun
};

int main() {
    setlocale(LC_ALL, "FI_fi");
    srand(time(0));
    int hinta = rand() % 21 + 80;
    int huonemaara = huonemaarageneraattori(); // Tuodaan huoneiden m��r� huonem��r�generaattorista
    vector<Huoneinfo> huoneet(huonemaara); // Luodaan vektori
    // Alustetaan huoneet
    for (int i = 0; i < huonemaara; ++i) {
        huoneet[i].numero = i + 1;
        huoneet[i].issingle = (i < huonemaara / 2); // ensimm�inen puolisko huoneista 1 hengen toinen puolisko 2 hengen.
        huoneet[i].isBooked = false;     // Kaikki huoneet vapaita
        huoneet[i].varaaja = "";         // Varaaja tyhj�
        huoneet[i].varausnumero = 0;     // Ei varausta
    }
    huoneidentulostus(huoneet);
    while (true) {  // Valitaan funktio menun perusteella
        int menuvalinta = menu();
        switch (menuvalinta) {
        case 1: // Huoneen varaus
            huoneenvaraus(huoneet, hinta);
            break;
        case 2: // Varaustarkastelu
            varaustarkastelu(huoneet);
            break;
        case 3: //Huoneiden uudelleen arvonta
            huonemaara = huonemaarageneraattori();
            huoneet = vector<Huoneinfo>(huonemaara);
            for (int i = 0; i < huonemaara; ++i) {  //Huoneiden alustus uudestaan
                huoneet[i].numero = i + 1;
                huoneet[i].issingle = (i < huonemaara / 2);
                huoneet[i].isBooked = false;
                huoneet[i].varaaja = "";
                huoneet[i].varausnumero = 0;
            }
            huoneidentulostus(huoneet);
            break;
        case 0:
            return 0;
        default:
            cout << "Virhe sy�tteess�!" << endl;
        }
    }
}