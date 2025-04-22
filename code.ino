// On nomme les broches 
#define donnee 4
#define verrou 5
#define horloge 6
#define k0 8
#define k1 9
#define k2 10
#define k3 11

// Configuration des broches en sortie
void setup() {
      pinMode(verrou, OUTPUT);
      pinMode(horloge, OUTPUT);
      pinMode(donnee, OUTPUT);
      pinMode(8, OUTPUT);
      pinMode(9, OUTPUT);
      pinMode(10, OUTPUT);
      pinMode(11, OUTPUT);
}

// Quand on envoie du courant dans une seule broche pour allumer une seule led (côté anode de la led), cela allume quatre leds qui sont reliées (chaque led 
// sera considérée comme un étage). 
// Pour contourner cela, on envoie également du courant dans les trois autres leds que l'on ne veut pas allumer (côté catode de la led). Ainsi, 
// la différence de potentiel est nulle pour les trois leds que l'on ne veut pas allumer et ainsi elles ne s'allument pas.

// Fonction pour selectionner un étage (et donc pas les autres).
void selectionner_k(int k){
        // On initialise en envoyant du courant côté catode dans chaque étage pour que aucun étage ne puisse être allumé.
        digitalWrite(k0, HIGH);
        digitalWrite(k1, HIGH);
        digitalWrite(k2, HIGH);
        digitalWrite(k3, HIGH);

        // Si on veut allumer l'étage 0, on enlève le courant envoyé côté catode de l'étage 0, ainsi, quand on enverra du courant côté anode de la led,
        // la différence de potentiel ne sera pas nulle donc la led de l'étage 0 s'allumera mais pas les autres.
        if (k == 0){                    
          digitalWrite(k0, LOW);
        } else if (k == 1) {
          digitalWrite(k1, LOW);
        } else if (k == 2) {
          digitalWrite(k2, LOW);
        } else if (k == 3) {
          digitalWrite(k3, LOW);
        }
}



void selectionner_i_j(int i, int j){
      int nb = i + 4*j;
      //1 << 1 = 00000010  (2 en décimal)
      //1 << 2 = 00000100  (4 en décimal)
      //1 << 3 = 00001000  (8 en décimal)
      
      if (nb <= 7){
        shiftOut(donnee, horloge, MSBFIRST, 0);
        shiftOut(donnee, horloge, MSBFIRST, 1 << (nb));
      }
      else if (nb>7){
        shiftOut(donnee, horloge, MSBFIRST, 1 << (nb-8));
        shiftOut(donnee, horloge, MSBFIRST, 0);
      }
}

void allumer_led_coordonnees(int i, int j, int k){
        digitalWrite(verrou, LOW);
        selectionner_k(k);
        selectionner_i_j(i, j);
        digitalWrite(verrou, HIGH); 
  }


void tout_allumer(){
  digitalWrite(verrou, LOW);
  digitalWrite(k0, LOW);
  digitalWrite(k1, LOW);
  digitalWrite(k2, LOW);
  digitalWrite(k3, LOW);
  shiftOut(donnee, horloge, LSBFIRST, 255);
  shiftOut(donnee, horloge, LSBFIRST, 255);
  digitalWrite(verrou, HIGH);
}

void tout_eteindre() {
  digitalWrite(verrou, LOW);
  digitalWrite(k0, LOW);
  digitalWrite(k1, LOW);
  digitalWrite(k2, LOW);
  digitalWrite(k3, LOW);
  shiftOut(donnee, horloge, LSBFIRST, 0);
  shiftOut(donnee, horloge, LSBFIRST, 0);
  digitalWrite(verrou, HIGH);
}
  void chenillard() {
    for (int k = 0; k<=3; k++){
      for (int j = 0; j<=3; j++){
        for (int i = 0; i<=3; i++){
          allumer_led_coordonnees(i, j, k);
          delay(500);
        }
      }
    }
  }

  void allumer_etage(int k){
    digitalWrite(verrou, LOW);
    selectionner_k(k);
    shiftOut(donnee, horloge, LSBFIRST, 255);
    shiftOut(donnee, horloge, LSBFIRST, 255);
    digitalWrite(verrou, HIGH);
  }

  void balayage_etage(){
    for (int k = 0; k<=3; k++){
      allumer_etage(k);
      delay(100);
    }
    for (int k = 3; k>=0; k--){
      allumer_etage(k);
      delay(100);
    }
  }

  void allumer_colone(int i, int j){
    digitalWrite(verrou, LOW);
    selectionner_i_j(i, j);
    digitalWrite(verrou, HIGH);
  }
  void contour(){
      for (int i = 0; i<=2; i++){
          allumer_colone(i, 0);
          delay(100);
      }
      for (int j = 0; j<=3; j++){
          allumer_colone(3, j);
          delay(100);
      }
    for (int i = 2; i >=0; i--) {
          allumer_colone(i, 3);
          delay(100);
    }
    for (int j = 2; j >=1; j--) {
          allumer_colone(0, j);
          delay(100);
    }
  }

  void thomas(){
    digitalWrite(verrou, LOW);
    selectionner_k(3);
    shiftOut(donnee, horloge, LSBFIRST, 102);
    shiftOut(donnee, horloge, LSBFIRST, 255);
    digitalWrite(verrou, HIGH);
    delay(1000);

    tout_eteindre();
    delay(500);


    digitalWrite(verrou, LOW);
    selectionner_k(3);
    shiftOut(donnee, horloge, LSBFIRST, 159);
    shiftOut(donnee, horloge, LSBFIRST, 249);
    digitalWrite(verrou, HIGH);
    delay(1000);

    tout_eteindre();
    delay(500);

  }
  void croix(){
      for (int k = 3; k >=0; k--) {
          digitalWrite(verrou, LOW);
          selectionner_k(k);
          shiftOut(donnee, horloge, LSBFIRST, 105);
          shiftOut(donnee, horloge, LSBFIRST, 150);
          digitalWrite(verrou, HIGH);
          delay(100);
      } 
}
  

// Quand on ne peut pas allumer deux leds en même temps sans en allumer d'autres, on allume les leds une par une en boucle mais à un intervalle de temps
// tellement court que notre oeil croit que les leds sont allumées en même temps
void multiplexage(){
  for (int a = 0; a<=3; a++){
    digitalWrite(verrou, LOW); 
    allumer_led_coordonnees(a, a, a);
    digitalWrite(verrou, HIGH); 
    delay(2);
  }
}



  void loop() {
    balayage_etage();
}