#include <iostream>
#include <time.h>
#include <string>

// Funzioni che verranno utilizzate in seguito
void hanoi(int, std::string, std::string, std::string);
void spostamento(int, std::string, std::string, std::string);


int counter = 1; // Contatore per la funzione Hanoi.
// Conta il numero di mosse che la funzione esegue

using namespace std;

int main(){
  setlocale(LC_ALL, "");

  // Dichiarazione variabile numero di dischi
  int nDischi;

  // Presentazione gioco
  cout << "%--------------------%" << endl;
  cout << "La Torre di Hanoi, anche conosciuta come Torre di" << endl;
  cout << "Lucas dal nome del suo inventore, è un rompicapo" << endl;
  cout << "matematico composto da tre paletti e un certo" << endl;
  cout << "numero di dischi di grandezza decrescente, che possono" << endl;
  cout << "essere infilati in uno qualsiasi dei paletti." << endl;
  
  cout << endl;
  
  // Regole del gioco
  cout << "Regole e scopo." << endl;
  cout << "Il gioco inizia con tutti i dischi incolonnati su un" << endl;
  cout << "paletto in ordine decrescente, in modo da formare un" << endl;
  cout << "cono. Lo scopo del gioco è portare tutti i dischi su un" << endl;
  cout << "paletto diverso, potendo spostare solo un disco alla" << endl;
  cout << "volta e potendo mettere un disco solo su un altro" << endl;
  cout << "disco più grande, mai su uno più piccolo." << endl;
  cout << "Fonte: Wikipedia" << endl;
  cout << "%--------------------%" << endl;
  
  cout << endl;

  // Controllo numero dischi immessi
  // Dischi accettati: da 1 a 10
  do {
    cout << "Attenzione!" << endl;
    cout << "Inserire un numero di dischi compreso fra 1 e 10." << endl;

    cout << "Con quanti dischi vuoi giocare? ";
    cin >> nDischi;
  }
  while ((nDischi < 1) || (nDischi > 11));
  
  // Disegno i dischi
  string disco;
  for (int k = 0; k < nDischi; k++){
    disco = "-OO-";
    // Aggiungo il numero giusto di trattini
    for(int z = 0; z < k; z++){
      // Aggiungo un trattino all'inizio e alla fine ad ogni ciclo
      disco = "-" + disco + "-";
    }
    for(int j = 1; j<=(1+nDischi-k); j++){
      // Aggiungo la corretta spaziatura (solo a sinistra)
      // per centrare il disco
      disco = " " + disco;
    }
    cout << disco << endl;
  }

  // Disegniamo la base
  string base = "II";
  // Disegno la base
  for (int i = 0; i <= nDischi; i++){
    base = "-" + base + "-";
    //cout << base << endl;
  }
  base = "|" + base + "|" + base + "|" + base + "|";
  cout << base << endl;

  // Inizio risoluzione torre Hanoi
  cout << endl;
  cout << "Soluzione:" << endl;
  // Inizio cronometro
  clock_t start = clock();
  //hanoi(nDischi, "a sinistra", "a destra", "al centro");
   hanoi(nDischi, "A", "C", "B");

  // Fine cronometro
  clock_t end = clock();
  // Tempo risoluzione torre Hanoi
  printf("Tempo di esecuzione = %f secondi \n", ((double)(end - start)) / CLOCKS_PER_SEC);
}

void hanoi(int n,std::string partenza,std::string arrivo,std::string ausilio){
  if(n==1){
    // Mossa da fare
    spostamento(n, partenza, arrivo, ausilio);
  }
  else{
    // Richiamo la funzione per spostare n-1 dischi
    // Dal piolo partenza si arriva al piolo ausilio
    hanoi(n-1, partenza, ausilio, arrivo);
    // Mossa da fare
    spostamento(n, partenza, arrivo, ausilio);
    // Dal piolo ausilio si arriva al piolo arrivo
    hanoi(n-1, ausilio, arrivo, partenza);
  }
}

void spostamento(int n,string partenza,std::string arrivo,std::string ausilio){
  // Stampo il numero della mossa e incremento il contatore
  cout << "- Mossa " << counter++ << ":\t";
  // Quale disco devo spostare?
  cout << "Spostare il disco " << n;
  // Da quale piolo?
  cout << "\t dal piolo " << partenza;
  // A quale piolo?
  cout << "\t al piolo " << arrivo << "." << endl;
}