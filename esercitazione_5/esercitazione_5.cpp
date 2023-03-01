#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Costanti
#define MAX_PLAYER 6
#define MAX_VITALITY 3
#define PROB_BEAST 10
#define PERC_DIRECTION 50
#define PROB_POTION 10
#define PROB_VICTORY 1

#define DPRINT(VAR) cout << #VAR << " = " << (VAR) << endl;

// Definizione di Pathtype
using Pathtype = enum { Start, Beast, Potion, Victory, Normal };
// Definizione di Direction
using Direction = enum { N, E, S, W, none };

// Variabile che conta il numero di giocatori in vita
int playerAlive;

// Dichiaro la classe altrimenti il metodo "actionOnPlayer" della classe "Path" non funziona
class Player;

// SARA
// Classe percorso
class Path {
  string pathName;
  string text;
  Pathtype type;
  Path* north = NULL;
  Path* south = NULL;
  Path* east = NULL;
  Path* west = NULL;

  public:
    // Costruttore
    Path(const string &name = "Name", const string &t = "Text", Path* from = NULL, Direction d = Direction::none, Pathtype p = Pathtype::Start);

    // Per ottenere il "name"
    string getName() const { return pathName; }
    // Per ottenere il "text"
    string getText() const { return text; }
    // Per ottenere il puntatore
    Path* getPath(Direction d);
    // Il percorso è aperto?
    Path* isAvailable(); // DELETE : Non funziona
    // Cosa c'è sul territorio?
    Path* extractNewPath(Direction d);
    // C'è una bestia?
    bool isBeast() { return ((rand() % 100) < PROB_BEAST); }
    // C'è una pozione?
    bool isPotion() { return ((rand() % 100) < PROB_POTION); }
    // C'è la vittoria?
    bool isVictory() { return ((rand() % 100) < PROB_VICTORY); }
    // Il territorio è stato scoperto?
    bool isNew(Direction d);
    // Azione sul giocatore : creata nelle sottoclassi
    virtual void actionOnPlayer(Player* p) { ; }
    Pathtype getPathType() { return type; }
};

// LUCA
// Classe giocatore
class Player {
  bool win;
  int vitality;
  Path* position;
  string playerName;
  string moveList;
  
  public:
    // Costruttore
    Player(string pn = "Name") : playerName(pn), vitality(MAX_VITALITY), win(false) {}

    // get vittoria
    bool getWin() { return win; }
    // Il giocatore ha vinto
    void setWin() { win = true; }

    // get per la vitalità
    int getVitality() { return vitality; }
    // Aumenta vitality
    int increaseVitality();
    // Diminuisci vitality
    int decreaseVitality() { if (vitality) --vitality; return vitality; }
    // Il giocatore è morto?
    bool isDeath() { return (!vitality); }

    // Impostare il path iniziale
    Path* setPath(Path* p) { return (position = p); }
    // Ottenere la posizione
    Path* getPath() { return position; }
    // Muovere il giocatore
    Path* goToward(Direction d);

    // get per il nome
    string getName() { return playerName; }
    // set per il nome
    void setName(string newName) { playerName = newName; }
    
    // Aggiornare moveList
    void aggiornaMosse(Direction d);
    // Ottenere moveList
    string getMosseFatte() { return moveList; }
};

// SARA
class PathWithBeast : public Path {
  public:
    // Costruttore
    PathWithBeast(Path* from, Direction d) : Path("Beast", "Beast is Here", from, d, Pathtype::Beast) {}
    // Azione sul giocatore : diminuisce vitality
    void actionOnPlayer(Player* p) { p->decreaseVitality(); }
};

// SARA
class PathWithPotion : public Path {
  public:
    // Costruttore
    PathWithPotion(Path* from, Direction d) : Path("Potion", "Potion is Here", from, d, Pathtype::Potion) {}
    // Azione sul giocatore : aumenta vitality
    void actionOnPlayer(Player* p) { p->increaseVitality(); }
};

// LUCA
// Sottoclasse vittoria
class PathVictory : public Path {
  public:
    // Costruttore
    PathVictory(Path* from, Direction d) : Path("Victory", "Victory is Here", from, d, Pathtype::Victory) {}

    // Azione sul giocatore : il giocatore ha vinto
    void actionOnPlayer(Player* p) {
      while (!p->isDeath()) {
        p->decreaseVitality();
      }
      // Assegno all'attributo "win" del giocatore il valore "true"
      p->setWin();
      
      // Diminuisco giocatori attivi
      playerAlive -= 1;
      cout << "Complimenti!\nSei arrivato all'uscita.\nI minotauri non ti hanno preso." << endl;
    }
};

// Funzioni
int numberPlayers();
Player* createPlayers(int num);

// SARA + LUCA
int main() {
  cout <<"\n\n\n";

  cout << "\u2620\uFE0F  \u2620\uFE0F  \u2620\uFE0F  BENVENUTI AVVENTURIERI! \u2620\uFE0F  \u2620\uFE0F  \u2620\uFE0F" << endl;
  
  cout << "Il sole splende, gli uccellini cantano e i minotauri vi rincorrono! ";
  cout << "Vi starete chiedendo perché vi abbiamo riuniti qui oggi.\n" << endl;
  
  cout << "Prima di spiegarvelo è debita una presentazione. ";
  cout << "Io sono il Giuallare Messaggero e porto le veci del grande Mefisto! ";
  cout << "Ma bando alle ciance e ciancio alle bande.\n" << endl;
  
  cout << "Vi ritrovate nel Grande Labirinto di Baalzebul, Signore delle Mosche. ";
  cout << "Un luogo pieno di pericolose creature mistiche, pozioni dagli effetti straordinari, ";
  cout << "scale incantate e tesori perduti.\n"  << endl;
  cout << "Per riuscire a fuggire avete solo un modo: ";
  cout << "trovare l'uscita segreta situata nella sala del tesoro, ";

  cout << "Ricordate però: 'l'uinone fa la forza'. ";
  cout << "State attenti a non lasciare i vostri compagni indietro ";
  cout << "o le conseguenze per tutti voi saranno drastiche.";
  cout << "Un ultimo avvertimento: 'attenzione a dove mettete i piedi, alle scale piace cambiare'.\n" << endl;
  
  cout << "Ma perché dovreste fare tutto questo? ";
  cout << "Ovviamente per il diletto del nostro Padrone e Signore Assoluto!" << endl;

  for (int t = 0; t < 30; t++) {
    cout << "\u2620\uFE0F  ";
  }
  cout << "\n\n\n";
  
  
  
  string newPlayerName;
  char move;
  Direction dir;
  int turnNumber = 1;
  bool controlMove;

  // Imposto numero di giocatori
  int num_players = numberPlayers();
  // Creo array di giocatori
  Player* players = createPlayers(num_players);
  // Assegno il numero di giocatori in vita
  playerAlive = num_players;

  // Creo l'origine
  Path* startPath = new Path("Start Path", "Start Path", NULL, Direction::none, Pathtype::Start);
  // Posiziono tutti i giocatori sull'origine
  for (int j = 0; j < num_players; j++) { 
    // Impostiamo la posizione iniziale del giocatore
    players[j].setPath(startPath);
  }

  // Svolgimento dei vari turni
  // Finchè c'è almeno un giocatore attivo
  do {
    cout << "\n%-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-%\n\n\n" << endl;
    cout << "Turno " << turnNumber << "." << endl;

    // Per far giocare tutti i giocatori
    for (int i = 0; i < num_players; i++) {
      // Controllo se il giocatore è morto (o ha vinto)
      if (players[i].getVitality() > 0) {
        cout << "\n";
        cout << "Tocca al giocatore '" << players[i].getName() << "' (vitalità: " << players[i].getVitality() << ")." << endl;
        cout << "Mosse fatte: " << players[i].getMosseFatte() << endl;

        do {
          controlMove = false;
          // Il giocatre inserisce la mossa da tastiera
          cout << "Inserisci 'N' per Nord, 'S' per Sud, 'E' per Est E 'W' per Ovest: "; //TOFIX : solo direzioni possibili
          cin >> move;
          // Assegniamo la direzione scelta
          if (move == 'N')
            dir = Direction::N;
          else if (move == 'E')
            dir = Direction::E;
          else if (move == 'S')
            dir = Direction::S;
          else if (move == 'W')
            dir = Direction::W;
          else {
            cout << "Mossa non disponibile" << endl;
            controlMove = true;
          }
        } while (controlMove);
        
        // Il giocatore si sposta
        players[i].goToward(dir);

        // Controllo che il giocatore sia morto nel turno corrente
        // Se il giocatore ha vinto, non gioca (e quindi non può morire)
        if ((players[i].isDeath()) && (!players[i].getWin())) {
          cout << "Il giocatore " << players[i].getName() << " è morto :(" << endl;
          // In tal caso diminuisco il numero di giocatori attivi
          playerAlive -= 1;
        }
      }
    }

    // Contatore turni
    turnNumber += 1;
  } while (playerAlive != 0);

  // Alla fine del programma elimino l'array di giocatori
  delete[] players;
  cout << "\n";
}

// SARA
// Costruttore classe Path
Path::Path(const string &name, const string &t, Path* from, Direction d, Pathtype p) {
  pathName = name;
  text = t;
  type = p;
  switch (d) {
    case Direction::N:
      // Se la direzione è north, provengo da south.
      // From punta a nord perché nella prossima mossa io sarò "a north"
      south = from;
      from->north = this;
      break;
    case Direction::E:
      west = from;
      from->east = this;
      break;
    case Direction::S:
      north = from;
      from->south = this;
      break;
    case Direction::W:
      east = from;
      from->west = this;
      break;
    case Direction::none:
      break;
  }
}

// SARA
// Restituisce un puntatore se la direzione è disponibile, nulla altrimenti
Path* Path::isAvailable() {
  Path pathAvailable;
  // assegno la posizione di memoria di pathAvailable in una costante puntatore "AVAILABLE"
  Path* const AVAILABLE = &pathAvailable;
  return (((rand() % 100) < PERC_DIRECTION) ? AVAILABLE : NULL);
}

// SARA
Path* Path::getPath(Direction d) {
  // Se d == <punto_cardinale>, restituisce il puntatore a quel <punto_cardinale>
  if (d == Direction::N) return north;
  else if (d == Direction::E) return east;
  else if (d == Direction::S) return south;
  else if (d == Direction::W) return west;
  else return NULL;
}

// LUCA
// sposta il giocatore nella nuova posizione
Path* Player::goToward(Direction d) {
  // Imposto la destinazione
  auto destination = position->getPath(d);
  // Se la posizione è nuova
  if (position->isNew(d)) {
    if(position->isAvailable()){
      // creo un nuovo path
      position = position->extractNewPath(d);
      // eventuale azione sul giocatore
      position->actionOnPlayer(this);
      //DPRINT(position);

      // Aggiorno mossa
      aggiornaMosse(d);

    }
    else {
        cout << "Direzione non disponibile." << endl;
        //DPRINT(position);
    }
  }
  else if (destination->getPathType() == Pathtype::Victory)
    destination->actionOnPlayer(this);
  // Altrimenti aggiorno solo la posizione 
  else {
    position = destination;
    cout << "Direzione già esplorata" << endl;

    // Aggiorno mossa 
    aggiornaMosse(d);
  }
  return destination;
}

// LUCA
// Incrementa di 1 la vitalità
int Player::increaseVitality() {
  if (vitality < MAX_VITALITY) return (++vitality);
  else {
    cout << "Vitalità massima." << endl;
    return vitality;
  }
}

// LUCA
// Crea stringa con mosse fatte
void Player::aggiornaMosse(Direction d) {
  // Aggiorno mossa
  if (d == Direction::N)
    moveList = moveList.append("N ");
  else if (d == Direction::E)
    moveList = moveList.append("E ");
  else if (d == Direction::S)
    moveList = moveList.append("S ");
  else if (d == Direction::W)
    moveList = moveList.append("W ");
}

// SARA
// Restituisce "false" se il territorio è stato già esplorato, "true" altrimenti
bool Path::isNew(Direction d) {
  if (d == Direction::N) {
    // Se il puntatore è nullo, la posizione è nuova
    if (north == NULL) return true;
    // Se il puntatore non è vuoto, la posizione è stata già esplorata
    else return false;
  }
  else if (d == Direction::E) {
    if (east == NULL) return true;
    else return false;
  }
  else if (d == Direction::S) {
    if (south == NULL) return true;
    else return false;
  }
  else if (d == Direction::W) {
    if (west == NULL) return true;
    else return false;
  }
  else return false;
}

// LUCA
Path* Path::extractNewPath(Direction d) {
  // Creo un nuovo path

  // Se isBeast() = true
  if (isBeast()) {
    // creo un nuovo Path con bestia
    cout << "Scoperto percorso con \U0001f4a3 minotauro \U0001f4a3." << endl;
    cout << "Oh no!! Sei stato attaccato dal minotauro!";
    cout << "La tua vitalità è diminuita di 1." << endl;
    
    // Creo Path con bestia
    return new PathWithBeast(this, d);
  }
  // Analogamente sotto
  else if (isPotion()) {
    cout << "Scoperto percorso con \U0001f31f pozione \U0001f31f." << endl;
    cout << "Che fortuna!! Hai trovato una pozione!";
    cout << "La tua vitalità è aumentata di 1." << endl;
    
    return new PathWithPotion(this, d);
  }
  else if (isVictory()) {

    cout << "Scoperto percorso con \U0001f308 vittoria \U0001f308." << endl;
    
    return new PathVictory(this, d);
  }
  else {
    cout << "Scoperto percorso normale." << endl;
    cout << "Ti è andata bene... per ora..." << endl;

    return new Path("Walk", "walk freely", this, d, Pathtype::Normal);
  }
}

// LUCA
// Inserimento numero giocatori
int numberPlayers() {
  int num;
  // Controllo sul numero di giocatori inseriti
  do {
    cout << "Attenzione! Massimo numero di giocatori consentiti: " << MAX_PLAYER << endl;
    cout << "Inserisci il numero di giocatori: ";
    cin >> num;
  } while (num > MAX_PLAYER);

  return num;
}

// LUCA
// Per creare l'array di giocatori
Player* createPlayers(int num) {
  // Creo array di giocatori
  Player* players = new Player[num];

  // Riassegno il nome ad ogni giocatore
  for (int i = 0; i < num; i++) {
    // Scelta nome al giocatore i-esimo
    string pName;
    cout << "Inserisci il nome del giocatore " << i + 1 << ": ";
    cin >> pName;

    // Assegno al giocatore i-esimo il nome
    players[i].setName(pName);
  }

  // Restituisco l'array di giocatori creato
  return players;
}
