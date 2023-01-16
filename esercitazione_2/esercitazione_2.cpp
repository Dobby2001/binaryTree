// Esercitazione 2 : Convoluzione
// Studente: Luca Zepponi
//
// Il programma effettua il prodotto di convoluzione tra due funzioni reali limitate s(t) e r(t) campionate
// ad intervallo fisso T. In particolare, la funzione campionata ha valori nulli ovunque tranne in un
// intervallo di 100 campioni, a partire da t = 0.

#include <iostream>
#include <cmath>

using namespace std;

#define DPRINT(VAR) cout << #VAR << " = " << (VAR) << endl;

// definizione costanti di istanza
#define C 100 // Campione
#define T 1 // Intervallo campionamento
#define ASSEY 40 // Doppio dell'ampiezza asse y


// dichiarazione funzioni che useremo
void descrizione();
float funcS(float t);
float funcR(float t);
float costruisciProdottoConvoluzionale(float tau);
float maxFunc(float (*funzione)(float t));
void disegnaFunzione(float(*funzione)(float x));

int main(){
  setlocale(LC_ALL, "");

  // Presentazione programma
  descrizione();

  // Disegno funzione s
  cout << "Il grafico della funzione s è:" << endl;
  disegnaFunzione(funcS);

  cout << '\n';

  // Programma in pausa
  char pausa;
  cout << "Premi un pulsante (e poi invio) per continuare: ";
  cin >> pausa;

  // Disegno funzione r
  cout << "Il grafico della funzione r è:" << endl;
  disegnaFunzione(funcR);

  cout << '\n';

  // Programma in pausa
  cout << "Premi un pulsante (e poi invio) per continuare: ";
  cin >> pausa;

  // Disegno funzione s*r
  cout << "Il grafico della funzione s*r è:" << endl;
  disegnaFunzione(costruisciProdottoConvoluzionale);

  cout << '\n';
}

// Descrizione programma
void descrizione(){
  // Elenco "unicode escape characters" utilizzati
  // • \u2124: insieme dei numeri interi;
  // • \u03C4: tau (lettera greca minuscola);
  // • \u2211: simbolo di sommatoria;
  // • \u221E: simbolo di infinito;
  // • \u2208: simbolo di appartenenza insiemistica.
  
  cout << endl;
  
  cout << "%------------------------------%" << endl;
  cout << "Il programma effettua il prodotto di convoluzione tra" << endl;
  cout << "due funzioni reali limitate s(t) e r(t) campionate ad" << endl;
  cout << "intervallo fisso T." << endl;
  cout << "In particolare, la funzione campionata ha valori nulli" << endl;
  cout << "ovunque tranne in un intervallo di 100 campioni, a" << endl;
  cout << "partire da t = 0." << endl;

  cout << endl;
  
  cout << "Convoluzione discreta." << endl;
  cout << "Date due funzioni s[t] e r[t] definite sull'insieme dei" << endl;
  cout << "numeri interi \u2124, il prodotto di convoluzione per" << endl;
  cout << "segnali campionati, nulle per t < 0, associate a" << endl;
  cout << "serie numeriche, abbiamo" << endl;
  cout << " C_T[\u03C4] = (s*r)[\u03C4]" << endl;
  cout << "  = (\u2211_{k=0}^{\u221E}(s[k]r[\u03C4-k]))/T," << endl; 
  cout << "in cui T è il periodo di campionamento." << endl;
  cout << "In particolare, si può notare che" << endl;
  cout << "\u03C4 \u2208 [-100, 100]." << endl;
  cout << "Al di fuori dell'intervallo C_T[\u03C4] è nulla." << endl;
   
  cout << "%------------------------------%" << endl;

  cout << endl;
}

// Funzione s[t]
float funcS(float t){
  float risultato;

  // controllo se l'input è fuori dall'intervallo [0, C[.
  // Se sì, restituisco 0, altrimenti valuto l'espressione
  if((t < 0) || (t >=  C)) return 0;
  risultato = t/2;

  // restituisco il risultato
  return risultato;
}

// Funzione r[t]
float funcR(float t){
  float risultato;

  // controllo se l'input è fuori dall'intervallo [0, C[.
  // Se sì, restituisco 0, altrimenti valuto l'espressione
  if((t < 0) || (t >= C)) return 0;
  risultato = t*t;

  // restituisco il risultato
  return risultato;
}

// Calcolo prodotto convoluzionele
float costruisciProdottoConvoluzionale(float tao){
  float prod = 0;
  
  for(int indice = 0; indice <= C; indice++){
    // static_cast<float> per passare un float alla funzione
    prod += (funcS(static_cast<float>(indice)) * funcR(static_cast<float>(tao - indice)));
  }
  prod = prod/T;
  return prod;
}

// Valuta la funzione data in input (puntatore)
float maxFunc(float (*funzione)(float t)){
  float funzValutata;

  // La funzione va in moduo per non dover calcolare anche il minimo
  float max = abs(funzione(0));

  // Cerco il massimo della funzione in modulo
  for (int t = 1; t < C; t++) {
    funzValutata = abs(funzione(static_cast<float>(t)));
    if (funzValutata > max) max = funzValutata;
  }

  return max;
}

void disegnaFunzione(float (*funzione)(float x)) {
  // Calcolo massimo funzione
  float max = maxFunc(funzione);
  
  // Mi sposto sull'asse y
  for (int y = ASSEY; y >= 0; y--)
  {
    // Mi sposto sull'asse x
    for (int x = 0; x < C; x++)
    {
      if (y == round(funzione(static_cast<float>(x))/max*(ASSEY)/2) + ASSEY/2)
      {
        // Disegna punto funzione
        cout << '*';
      }
      else if ((y == ASSEY/2) && (x == 0))
      {
        // se si trova al centro del grafico, inserisci +
        cout << '+';
      }
      else if (y == ASSEY/2)
      {
        // se si trova sull'asse delle x, inserisci -
        cout << '-';
      }
      else if (x == 0)
      {
        // se si trova sull'asse delle y, inserisci |
        cout << '|';
      } else {
        // Se non c'è nulla da rappresentare, inserisci spazio vuoto
        cout << ' ';
      }
    }
    // Fine y-esima riga
    cout << '\n';
  }
}