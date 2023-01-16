// Esercitazione 3 : Alberi
// Studente: Luca Zepponi
// Programma che stampa e chiede l'inserimento da tastiera di:
// - una nazione;
// - la sua capitale;
// - il numero dei suoi abitanti;
// - la sua superficie in chilometri quadrati;
// - la latitudine della capitale;
// - la longitudine della capitale.
// 

// Librerie richieste
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
using std::string;
using std::transform;
using std::toupper;

#define DPRINT(VAR) cout << #VAR << " = " << (VAR) << endl;

// Struttura
struct stato {
  string nazione;
  string capitale;
  unsigned long int abitanti;
  float superficie;
  float latitudine;
  float longitudine;

  stato* ramoSx;
  stato* ramoDx;
};

stato* radice = NULL;
stato* iteratore = NULL;

// Funzioni di istanza
void descrizione();
int latOLong();
char menu();
void creaAlbero(int ordine);
string scherzo(string capitale);
void creaRamoSx(stato* iteratore, string nazione, string capitale, unsigned long int abitanti, float superficie, float latitudine, float longitudine);
void creaRamoDx(stato* iteratore, string nazione, string capitale, unsigned long int abitanti, float superficie, float latitudine, float longitudine);
void elencaNazioni(stato* radice);
// https://www.delftstack.com/it/howto/cpp/how-to-convert-string-to-uppercase-cpp/
string str2STR(string stringa);



int main() {
  setlocale(LC_ALL, "");

  // Descrizione del programma
  descrizione();

  // Dichiarazione variabile
  char scelta;

  // La scelta dell'ordinamento va effettuata una e una sola volta all'inizio
  int ordine = latOLong();

    do {
        // scelta dell'operazione da effettuare
        scelta = menu();

        switch (scelta)
        {
        case '1':
            // Crea nodo
            creaAlbero(ordine);
            break;
        case '2':
            // Elenca albero
            elencaNazioni(radice);
            break;
        case '0':
            // Termina esecuzione
            cout << "Uscita del programma..." << endl;
            cout << "Fine." << endl;
            break;
        default:
            break;
        }

        cout << "\n";
    } while (scelta != '0');
}



// Descrizione del programma
void descrizione() {
  cout << "%------------------------%" << endl;
  cout << "Descrizione del programma." << endl;
  cout << "Il seguente codice permette di memorizzare una lista di" << endl;
  cout <<"stati inserendo:" << endl;
  cout << "- la nazione;" << endl;
  cout << "- la capitale;" << endl;
  cout << "- il numero di abitanti;" << endl;
  cout << "- la superficie in chilometri quadrati;" << endl;
  cout << "- la latitudine della capitale" << endl;
  cout << "  (positiva a nord, negativa a sud);" << endl;
  cout << "- la longitudine della capitale" << endl;
  cout << "  (positiva ad est, negativa a ovest)." << endl;
  cout << "\n";
  cout << "Il programma chiederà all'inizio dell'esecuzione di" << endl;
  cout << "scegliere subito il criterio di ordinamento desiderato fra" <<endl; 
  cout << "due possibilità (latitudine o longitudine), non sarà" << endl;
  cout << "possibile modificare tale scelta in futuro, dopodiché sarà" << endl;
  cout << "richiesta un'ulteriore scelta all'utente:" << endl; 
  cout << "1 - inserire un nuovo stato;" << endl; 
  cout << "2 - elencare gli stati in base all'ordinamento chiesto" << endl; 
  cout << "  all'inizio del programma" << endl;
  cout << "0 - terminare l'esecuzione." << endl;
  cout << "Tale scelta verrà richiesta al termine dell'inserimento di" << endl; 
  cout << "un nuovo stato o dopo aver stampato le nazioni fino a" << endl;
  cout << "quando l'utente non deciderà di interrompere il" << endl; 
  cout << "programma." << endl;
  cout << "%------------------------%" << endl;
  cout << "\n";
}



// Scelta ordinamento albero
int latOLong() {
  // Variabile per decidere l'ordinamento
  char ordine;
  // Variabile per confermarela scelta dell'ordinamento
  char sicuro;

  // Controllo decisione di ordinamento
  do {
    // Scelta ordinamento
    cout << "Vuoi ordinare secondo:" << endl;
    cout << "\"0\" - la longitudine;" << endl;
    cout << "\"1\" - la latitudine." << endl;
    cout << "ATTENZIONE! La scelta è permanente." << endl;
    cout << "Scelgi attentamente..." << endl;
    cin >> ordine;

    // ordine è char per controllare eventuali errori con lettere
    while ((ordine != '0') && (ordine != '1')) {
      cout << "Attenzione, inserimento non corretto." << endl;
      cout << "Prova ancora: ";
      // Rinserire ordine
      cin >> ordine;
    }

    // controllo decisione ordinamento
    cout << "Sei sicuro della tua scelta?" << endl;
    cout << "Non potrai tornare più indietro..." << endl;
    cout << "Digita \"s\" per confermare." << endl;
    cout << "Digita un qualsiasi altro tasto per ripensarci." << endl;
    cin >> sicuro;
  } while (sicuro != 's');


  // da Char a Int
  int ordineInt;
  if (ordine == '1') ordineInt = 1;
  else ordineInt = 0;

  // Stampa scelta effettuata
  if (ordineInt) cout << "Ordino secondo la latitudine." << endl;
  else cout << "Ordino secondo la longitudine." << endl;

  return ordineInt;
}



// Scelta da fare:
// scelta = 1: si inserisce una nuova nazione con tutte le informazioni;
// scelta = 2: si stampa l'albero con tutti i nodi finora creati;
// scelta = 0: si termina l'esecuzione del programma.
// Solo con scelta = 0 il programma termina, dopo la stampa dell'albero sarà
// comunque possibile inserire nuovi nodi.
char menu() {
  char scelta;

  do {
    cout << "MENU" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "1 - Inserisci nuova nazione " << endl;
    cout << "2 - Elenca le nazioni" << endl;
    cout << "0 - Esci" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Scelta: ";
    cin >> scelta;
    } while ((scelta != '1') && (scelta != '2') && (scelta != '0'));
    // Se si digita un carattere diverso da questi tre, il menu viene
    // ristampato per chiedere un nuovo inserimento

    return scelta;
}



// Crea albero
void creaAlbero(int ordine) {
  // Dichiarazione variabili
  string nazione;
  string capitale;
  unsigned long int abitanti;
  float superficie;
  float latitudine;
  float longitudine;
  
  // L'utente inserisce tutte le informazioni da tastiera
  cout << "Inserisci nazione: ";
  cin >> nazione;
  cout << "Inserisci la capitale: ";
  cin >> capitale;
  if (str2STR(nazione) == "ITALIA") capitale = scherzo(capitale);
  cout << "Inserisci il numero di abitanti: ";
  cin >> abitanti;
  cout << "Inserisci la superficie [km^2]: ";
  cin >> superficie;
  cout << "Inserisci latitudine: ";
  cin >> latitudine;
  cout << "Inserisci longitudine: ";
  cin >> longitudine;

  iteratore = radice;

  // Se radice = NULL
  if (!radice) {
    // radice = new stato(...) non funziona
    radice = new stato;
    radice->nazione = nazione;
    radice->capitale = capitale;
    radice->abitanti = abitanti;
    radice->superficie = superficie;
    radice->latitudine = latitudine;
    radice->longitudine = longitudine;
    radice->ramoSx = NULL;
    radice->ramoDx = NULL;
}

  // Finché iteratore è non vuoto
  while (iteratore) {
    // Ordinamento per latitudine 
    if (ordine) {
      if (latitudine > iteratore->latitudine) {
        // Latitudine inserita maggiore => nuovo ramo a sinistra
        // Se ramoSx puntato da iteratore è non vuoto, riassegna iteratore
        if (iteratore->ramoSx) iteratore = iteratore->ramoSx;
        // altrimenti crea nuovo ramo
        else {
          //iteratore ->ramoSx = new stato(); non funziona
          creaRamoSx(iteratore, nazione, capitale, abitanti, superficie, latitudine, longitudine);

          iteratore = NULL;
        }
       }
       else {
         // Latitudine inserita minore => nuovo ramo a destra
         if (iteratore->ramoDx) iteratore = iteratore->ramoDx;
         // altrimenti crea nuovo ramo
         else {
           creaRamoDx(iteratore, nazione, capitale, abitanti, superficie, latitudine, longitudine);

           iteratore = NULL;
         }
       }
     }
     else {// ordinamento per longitudine
        // longitudine positiva a est, negativa a ovest
        // Longitudine inserita maggiore => nuovo ramo a sinistra
        if (longitudine > iteratore->longitudine) {
          // longitudine inserita minore
          if (iteratore->ramoSx) iteratore = iteratore->ramoSx;
          else {
            creaRamoSx(iteratore, nazione, capitale, abitanti, superficie, latitudine, longitudine);

            iteratore = NULL;
          }
        }
        else {// longitudine inserita minore => nuovo ramo a destra
          if (iteratore->ramoDx) iteratore = iteratore->ramoDx;
        else {
          creaRamoDx(iteratore, nazione, capitale, abitanti, superficie, latitudine, longitudine);

          iteratore = NULL;
        }
      }
    }
  }
}



// Scherzetto
string scherzo(string capitale) {
  bool confronto;
  // Confronto capitale inserita con "ROMA"
  confronto = str2STR(capitale) == "ROMA";
  // Per migliorare il confronto, i caratteri della stringa inserita dall'utente verranno convertiti in maiuscoli

  while (!confronto) {
    // Confronto fra stringhe: fonte https://www.techiedelight.com/it/compare-two-strings-in-cpp/

    // Se <capitale> != roma\dots{}
    if (!confronto) {
      cout << "No, " << capitale << " non è caput mundi." << endl;
      cout << "Scherzetto ;)" << endl;
      cout << "Inserisci quella vera..." << endl;
      cout << "Inserisci la capitale: ";
      cin >> capitale;
    }
    confronto = str2STR(capitale) == "ROMA";
  }
  return capitale;
}



// Crea ramo sinistro
void creaRamoSx(stato* iteratore, string nazione, string capitale, unsigned long int abitanti, float superficie, float latitudine, float longitudine) {
  iteratore->ramoSx = new stato;
  iteratore->ramoSx->nazione = nazione;
  iteratore->ramoSx->capitale = capitale;
  iteratore->ramoSx->abitanti = abitanti;
  iteratore->ramoSx->superficie = superficie;
  iteratore->ramoSx->latitudine = latitudine;
  iteratore->ramoSx->longitudine = longitudine;
  iteratore->ramoSx->ramoSx = NULL;
  iteratore->ramoSx->ramoDx = NULL;
}



// Crea ramo destro
void creaRamoDx(stato* iteratore, string nazione, string capitale, unsigned long int abitanti, float superficie, float latitudine, float longitudine) {
  iteratore->ramoDx = new stato;
  iteratore->ramoDx->nazione = nazione;
  iteratore->ramoDx->capitale = capitale;
  iteratore->ramoDx->abitanti = abitanti;
  iteratore->ramoDx->superficie = superficie;
  iteratore->ramoDx->latitudine = latitudine;
  iteratore->ramoDx->longitudine = longitudine;
  iteratore->ramoDx->ramoSx = NULL;
  iteratore->ramoDx->ramoDx = NULL;
}

// Funzione che stampa l'albero
void elencaNazioni(stato* radice) {
  if (radice) {
    // Stampa tutte le informazioni
    elencaNazioni(radice->ramoSx);
    cout << "Nazione " << radice->nazione << ";" << endl;
    cout << "- " << "capitale " << radice->capitale << ";" << endl;
    cout << "- " << "abitanti " << radice->abitanti << ";" << endl;
    cout << "- " << "superficie " << radice->superficie << ";" << endl;
    cout << "- " << "latitudine " << radice->latitudine << ";" << endl;
    cout << "- " << "longitudine " << radice->longitudine << "." << endl;
    elencaNazioni(radice->ramoDx);
  }
}



// stringhe in maiuscolo
// da "stringa a "STRINGA"
string str2STR(string stringa) { 
  transform(stringa.begin(),stringa.end(),stringa.begin(),[](unsigned char c){ 
    return toupper(c);
  });
  
  return stringa;
}