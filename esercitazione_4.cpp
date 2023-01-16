// Esercitazione 4
// Studente: Luca Zepponi
//
// Data una funzione predefinita, il programma calcola:
// - il valore della funzione in un punto;
// - il valore della derivata in un punto;
// - l'integrakle definito in un intervallo della funzione utilizzando il metodo dei trapezi;
// Inoltre, vengono anche fornite le rappresentazioni grafiche normalizzate rispetto l'asse y della funzione e della sua derivata prima.
//
// Da fare:
//
// Fatto:
// - Migliorata l'estetica;
// - Aggiunti commenti introduttivi;
// - Tolto "double inc" dalla classe;
// - Modificato metodo incremento;
// - Modificato metodo derivataPunto;
// - unificare metodo massimo per funzione e derivata;
// - unificare metodo rappresentazione per funzione e derivata.

#include <iostream>
#include <cmath>

using namespace std;

using pFun = double(*)(double);

#define DPRINT(VAR) cout << #VAR << " = " << (VAR) << endl
// #define DPRINT(VAR)
#define NUM_PARTIZIONE 1e5
#define C 10 // Campione
#define ASSEY 40 // Doppio dell'ampiezza asse y

// Definizione funzione
double retta(double x){ return 5 * x + 6; };



// Definizione classe "funzione"
class funzione{
  pFun pFunz;
  float inferiore;
  float superiore;
  
public:
  //costruttore
  funzione (pFun fun, float i, float s) : pFunz(fun), superiore(s), inferiore(i) {};

  double incremento();

  // metodi per il calcolo
  double valore(double x);
  double derivataPunto(double x);
  double integrale(double i, double s);

  // Metodo per il massimo
  double massimo(int i);
  
  // Stampa grafico funzione
  void disegnaFunzione(int i);
};



int main(){
  setlocale(LC_ALL, "");
  
  // Definisco fun1
  funzione fun1(retta, -10, 10);
  
  // Dichiarazione variabili
  // Variabile per il menu
  char scelta;
  // Variabile per immagazzinare i punti
  double punto;
  // Variabili per gli estremi dell'integrale
  double eInf = 0.0;
  double eSup = 0.0;
  int ordine = 0;
  
  // Menu
  do {
    cout << "%------------------------------------------------------------------------%" << endl;
    cout << "Menu:" << endl;
    cout << "1 - Valore della funzione in un punto inserito dall'utente;" << endl;
    cout << "2 - Valore della derivata in un punto inserito dall'utente;" << endl;
    cout << "3 - Valore dell'integrale definito in un intervallo definito dall'utente;" << endl;
    cout << "4 - Visualizzazione grafica della funzione;" << endl;
    cout << "5 - Visualizzazione grafica della derivata;" << endl;
    cout << "0 - Esci." << endl;
    cout << "%------------------------------------------------------------------------%" << endl;
    
    cout << "\n";
    
    cout << "Inserisci la scelta: ";
    cin >> scelta;
    
    while ((scelta != '0') && (scelta != '1') && (scelta != '2') &&
           (scelta != '3') && (scelta != '4') && (scelta != '5')) {
      cout << "ATTENZIONE!" << endl;
      cout << "Scelta non valida, riprovare." << endl;
      
      cout << "\n";
      
      cout << "Inserisci la scelta: ";
      cin >> scelta;
    }
    
    // Opzione
    switch (scelta) {
      case '1':
        cout << "Inserisci il punto dove vuoi calcolare la funzione: x = ";
        cin >> punto;
        cout << "Il valore della funzione valutata nel punto di ascissa x = " << punto << " è f(x) = " << fun1.valore(punto) << "." << endl;
        cout << "\n";
      break;
      case '2':
        cout << "Inserisci il punto dove vuoi calcolare la derivata prima della funzione: ";
        cin >> punto;
        cout << "Il valore della derivata prima della funzione valutata nel punto di ascissa x = " << punto << " è f(x) = " << fun1.derivataPunto(punto) << "." << endl;
        cout << "\n";
      break;
      case '3':
        do {
          cout << "Inserisci estremo inferiore: ";
          cin >> eInf;
          cout << "Inserisci estremo superiore: ";
          cin >> eSup;
          
          if (eInf > eSup) {
            cout << "Attenzione!" << endl;
            cout << "L'estremo inferiore è maggiore dell'estremo superiore." << endl;
            ordine = 0;
          } else ordine = 1;
        } while (ordine == 0);
        cout << "L'integrale è " << fun1.integrale(eInf, eSup) << endl;
        cout << "\n";
      break;
      case '4':
        cout << "Il grafico della funzione è:" << endl;
        fun1.disegnaFunzione(1);
        cout << "\n";
      break;
      case '5':
        cout << "Il grafico della derivata prima della funzione è:" << endl;
        fun1.disegnaFunzione(2);
        cout << "\n";
      break;
      case '0':
      break;
      default:
        cout << "Nessuna scelta disponibile." << endl;
        cout << "\n";
      break;
    }
  } while (scelta != '0');
}



// Metodo per il calcolo ell'incremento
double funzione::incremento(){
  // inc = (superiore - inferiore)/(NUM_PARTIZIONE);
  // return inc;
  return ( (superiore - inferiore)/(NUM_PARTIZIONE) );
}



// Metodo per il calcolo del valore della funzione nel punto x
double funzione::valore(double x){
  // Controllo punto in intervallo
  if ((x > inferiore) && (x < superiore)) return (5 * x + 6);
  else {
    cout << "Il punto non appartiene all'intervallo inserito."<< endl;
    return 0;
  } 
}



// metodo per il calcolo della derivata nel punto x
double funzione::derivataPunto(double x){
  // Calcolo incremento inc
  double inc = incremento();
  
  // Controllo punto in intervallo
  // Restituisco valore derivata
  if ( (x >= inferiore) && (x <= superiore) ) return( (retta(x + inc) - retta(x))/inc );
  else {
    cout << "Il punto non appartiene all'intervallo inserito."<< endl;
    // Derivata nulla
    return 0;
  }
}



// Metodo per il calcolo dell'integrale definito della funzione nell'intervallo [i, s]
double funzione::integrale(double i, double s){
  // Inizializzazione variabile
  double inc = incremento();
  double integ = 0.0;
  
  // Controllo estremi di integrazione
  if (s > superiore) s = superiore;
  if (i < inferiore) i = inferiore;

  // Calcolo valore integrale
  while (i < s) {
    // Incremento variabile integ
    integ += ((retta(i + inc) + retta(i)) * inc)/2;
    // i -> s
    i += inc;
  }
  return integ;
}



// Metodo per il calcolo del massimo
double funzione::massimo(int i){
  double funzValutata;

  // La funzione va in moduo per non dover calcolare anche il minimo
  double max = 0;
  
  // Cerco il massimo della funzione in modulo
  for (double t = inferiore; t <= superiore; t++) {
    if (i == 1) funzValutata = abs(retta(t));
    else if (i == 2) funzValutata = abs(derivataPunto(t));
    if (funzValutata > max) max = funzValutata;
  }
  return max;
}



// Disegna grafico della funzione
void funzione::disegnaFunzione(int i) {
  double yFun;
      
  // Calcolo massimo funzione
  double max = massimo(i);
  
  // Mi sposto sull'asse y
  for (int y = ASSEY+2; y >= 0; y--)
  {
    // Mi sposto sull'asse x
    for (double x = round(inferiore); x <= round(superiore); x++)
    {
      // Retta o derivata?
      if (i == 1) yFun = retta(x);
      else if (i == 2) yFun = derivataPunto(x);
      
      // Disegna punto funzione
      if (y == (round(yFun/max*(ASSEY/2))) + ASSEY/2) cout << '*';
      // se si trova al centro del grafico, inserisci +
      else if ((y == ASSEY/2) && (x == 0)) cout << '+';
      // se si trova alla fine dell'asse delle x, inserisci -> x
      else if ((y == ASSEY/2) && (x == round(superiore))) cout << "->x";
      // se si trova sull'asse delle x, inserisci -
      else if (y == ASSEY/2) cout << '-';
      // se si trova sull'asse delle y a quota ASSEY+2, inserisci y
      else if ((x == 0) && (y == (ASSEY + 2))) cout << 'y';
      // se si trova sull'asse delle y a quota ASSEY+1, inserisci "\u2227"
      else if ((x == 0) && (y == (ASSEY + 1))) cout << "\u2227";
      // se si trova sull'asse delle y, inserisci |
      else if (x == 0) cout << '|';
      // Se non c'è nulla da rappresentare, inserisci spazio vuoto
      else cout << ' ';
    }
    // Fine y-esima riga
    cout << '\n';
  }
}