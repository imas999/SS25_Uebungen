#include <iostream>
#include <string>
#include <vector>
#include "Fahrt.cpp"
#include "Mietwagen.cpp"

using namespace std;

class Autovermietung {
private:
    vector<Mietwagen> fahrzeuge;

public:
    Autovermietung() : fahrzeuge(vector<Mietwagen>()) {}

    // Getter und Setter
    vector<Mietwagen> getFahrzeuge() { return fahrzeuge; }
    void setFahrzeuge(vector<Mietwagen> neueFahrzeuge) { fahrzeuge = neueFahrzeuge; }

    vector<Fahrt> getFahrtenbuch() { return fahrtenbuch; }

    void setFahrtenbuch(vector<Fahrt> neueFahrten) { fahrtenbuch = neueFahrten; }

    //Destruktor für Mietwagen, welche
    ~Autovermietung() {
            fahrzeuge.clear();
            cout << "Vielen Dank!" << endl;
    }

    //Fügt ein Fahrzeug zur Fahrzeugliste hinzu
    void addFahrzeug(Mietwagen wagen) {
        fahrzeuge.push_back(wagen);
        cout << "Fahrzeug hinzugefügt: " << wagen.getMarke() << endl;
    }

    //Eröffnet einen Konsolendialog zum Verwalten der Autovermietung
    void dialog() {
        int auswahl = 1;
        while (auswahl != 0) {
            cout << "1. Fahrzeug mieten" << endl;
            cout << "2. Fahrt anzeigen" << endl;
            cout << "3. Alle Fahrten anzeigen" << endl;
            cout << "0. Programm Beenden" << endl;
            cin >> auswahl;

            switch (auswahl) {
                case 1: // Fahrzeug mieten
                {
                    int nummer, abholdatum, abgabedatum;
                    string kundenname, kennzeichen;
    
                    cout << "Bitte geben Sie das KFZ-Kennzeichen ein: ";
                    cin >> kennzeichen;

                    Mietwagen* w = findeFahrzeug(kennzeichen);

                    cout << "Bitte geben Sie die Fahrtnummer ein: ";
                    cin >> nummer;

                    if (w->nummerPruefen(nummer)) {
                        cout << "Fahrtnummer existiert bereits." << endl;
                        break;
                    } 

                    cout << "Bitte geben Sie den Namen des Kunden ein: ";
                    cin.ignore();
                    getline(cin, kundenname);

                    cout << "Bitte geben Sie das Abholdatum (im Format JJJJMMTT) ein: ";
                    cin >> abholdatum;

                    cout << "Bitte geben Sie das Abgabedatum (im Format JJJJMMTT) ein: ";
                    cin >> abgabedatum;

                    Fahrt f(nummer, kundenname, abholdatum, abgabedatum); 
                
                    w->anmieten(f); 
                    break;
                }
                case 2: // Fahrt anzeigen
                {
                    int fahrtennummer;
                    cout << "Buchungsnummer? ";
                    cin >> fahrtennummer;

                    bool gefunden = false;
                    for (Mietwagen wagen : fahrzeuge) {
                        for (Fahrt f : wagen.getFahrtenbuch()) {
                            if (f.getNummer() == fahrtennummer) {
                                gefunden = true;
                                //f.anzeigen();
                                Fahrt fahrt(f.getNummer(), f.getKunde(), f.getAbholdatum(), f.getAbgabedatum());
                                fahrt.anzeigen();
                                break;
                            }
                        }
                    }
                    if (gefunden = 0) cout << "Fahrt existiert nicht." << endl;
                    break;
                }
                case 3: // Alle Fahrten anzeigen
                {  
                    for(Mietwagen w : fahrzeuge) {
                        w.alleFahrtenAnzeigen();
                        cout << "--------------------------" << endl;
                    }
                    break;
                }
                case 0: 
                {
                    cout << "Auf Wiedersehen!" << endl;
                    break;
                }
                default: 
                    cout << "Ungültige Auswahl, bitte versuchen Sie es erneut." << endl;
            }
        }
    }

    Mietwagen* findeFahrzeug(string kennzeichen) {
        for (Mietwagen& w : fahrzeuge) {
            if (w.getKennzeichen() == kennzeichen) {return &w; }
        }
        throw runtime_error("Fahrzeug mit dem angegebenen Kennzeichen wurde nicht gefunden.");
    }

};

int main() {
    string marke, kennzeichen;
    int sitze;
    cout << "Neues Fahrzeug: " << endl;
    cout << "Automarke? ";
    cin >> marke;
    cout << "KFZ-Kennzeichen? ";
    cin >> kennzeichen;
    cout << "Sitze? ";
    cin >> sitze;
    
    Mietwagen wagen(marke, kennzeichen, sitze);
    Mietwagen wagen2("Porsche", "KA-AS-1012", 2);
    Mietwagen wagen3("Opel", "KA-AS-1013", 4);

    Fahrt testfahrt(1, "Nikola,Tesla", 20251001, 20251002);
    Fahrt testfahrt2(2, "Charles,Darwin", 20250101, 20250212);

    wagen.anmieten(testfahrt);

    Autovermietung KarlsruheCars;

    KarlsruheCars.addFahrzeug(wagen); 
    KarlsruheCars.addFahrzeug(wagen2);

    Mietwagen* w = KarlsruheCars.findeFahrzeug("KA-AS-1012");
    w->anmieten(testfahrt2);
  
    KarlsruheCars.dialog(); 

    return 0;
}
