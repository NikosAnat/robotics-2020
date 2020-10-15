//ΒΙΒΛΙΟΘΗΚΕΣ:
//------------
#include <Servo.h>


//ΜΕΤΑΒΛΗΤΕΣ:
//-----------

//Μοτέρ Α Κίνησης:
int KIN1_PIN = 11;
int KIN2_PIN = 12;
int SPE_PIN = 9;

int speedMot = 255;

//Μοτέρ Β Στροφής:
int STR1_PIN = 6;
int STR2_PIN = 7;
int ROT_PIN = 10;

int speedRot = 255;


//Αισθητήρας απόστασης Υπερήχων: 
int ULTRASONIC_TRIG_PIN = 2;
int ULTRASONIC_ECHO_PIN = A1;

//Αισθητήρας απόστασης 2 
int ULTRASONIC2_TRIG_PIN = 1;
int ULTRASONIC2_ECHO_PIN = A2;


int Xronos;
int Apostasi;

int Xronos2;
int Apostasi2;

//Αισθητήρας υγρασίας:
int YGRASIA_PIN = 3;

int ygrasiaValue;

//Σέρβοκινητήρας
int SERVO_PIN = 3;

Servo makis;

//Μεταβλητές Σεναρίων
int ApostasiEmpodiou = 45;
int xronosStrofis = 5000;
int louloudiaAnaSeira = 3;

int counter = 0;

//Εκτέλεση μία φορά στην αρχή
void setup() {
  Serial.begin(9600);

  //Αρχικοποιήσεις PIN
  pinMode(KIN1_PIN, OUTPUT);
  pinMode(KIN2_PIN, OUTPUT);
  pinMode(STR1_PIN, OUTPUT);
  pinMode(STR2_PIN, OUTPUT);
  pinMode(SPE_PIN, OUTPUT);
  pinMode(ROT_PIN, OUTPUT);
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC2_TRIG_PIN, OUTPUT);

  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
  pinMode(ULTRASONIC2_ECHO_PIN, INPUT);
  pinMode(YGRASIA_PIN, INPUT);
  
  makis.attach(SERVO_PIN);


  //Αρχική κατάσταση-εκκίνηση του ρομπότ μας
  stopKinisi();
  stopStrofi();
  delay(1000);
  
  analogWrite(SPE_PIN, 255);
  analogWrite(ROT_PIN, 255);
  
}

//Εκτέλεση συνέχεια μετά την setup και μέχρι να κλείσει το arduino
void loop() {

apostasiMprosta();
apostasiDexia();

senarioMetrhshs();
mprosta();
//senarioAnastrofis();

}

//ΣΥΝΑΡΤΗΣΕΙΣ Σεναριων:
//------------------------------
void senarioAnastrofis(){
  
  if(Apostasi <= ApostasiEmpodiou && counter == louloudiaAnaSeira){
    Serial.println("---------Senario Anastrofis---------");  
    
    
    stopKinisi();
    stopStrofi();

    counter = 0;
    Serial.print("Resetting Counter: ");
    Serial.println(counter);
    
    aristera();
    delay(500);
    mprosta();
    delay(xronosStrofis * 2);
    stopStrofi();
    
    Serial.println("---------Telos Senario Anastrofis---------");  
    
  } 
}
  
  void senarioMetrhshs(){
  
  if(Apostasi2 >= 30 && Apostasi2 <= 40){
    Serial.println("---------Senario Metrisis---------");  
    
    stopKinisi();
    dexia();
    delay(1000);
    
    mprosta();
    delay(xronosStrofis);
    
    stopKinisi();
    diadikasiaMetrisisYgrasias();
    counter = counter + 1;
    Serial.print("Counter: ");
    Serial.println(counter);
    
    pisw();
    delay(xronosStrofis);
    
    Serial.println("---------Telos Senario Metrisis---------");  
  }
}

void senarioStop(){
 if(Apostasi <= ApostasiEmpodiou){
  stopKinisi();
  stopStrofi();
  pisw();
  delay(500);
  stopKinisi();
  }
  else {  
    mprosta(); 
  } 
}

void senarioApofhghKinoumenou(){
 if(Apostasi <= ApostasiEmpodiou){
  stopKinisi();
  stopStrofi();
  pisw();
  delay(500);
  stopKinisi();
   
  delay(10000);
  if(Apostasi <= ApostasiEmpodiou){
    senarioApofhghStasimou();
  }
}
else {  
  mprosta(); 
}     
}


void senarioApofhghStasimou(){
 if(Apostasi <= ApostasiEmpodiou){
  stopKinisi();
  stopStrofi();
   
  pisw();
  delay(500);
  stopKinisi();
   
  dexia();
  mprosta();
  delay(1000); 
   
  aristera();
  mprosta();
  delay(2000);
   
  aristera();
  mprosta();
  delay(2000);
  }
   else {  
    mprosta(); 
  } 
}

//ΣΥΝΑΡΤΗΣΕΙΣ ΑΙΣΘΗΤΗΡΩΝ
  
//Συνάρτηση μέτρησης απόστασης [Βελτίωση με χρήση μέσου όρου, ή εξωτερικής βιβλιοθήκης NewPing]
void apostasiMprosta(){
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

  
  Xronos = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
  Apostasi = (Xronos/2)/29.1;
  
  Serial.print("Mprosta: ");
  Serial.println(Apostasi);  
}

//Συνάρτηση μέτρησης απόστασης [Βελτίωση με χρήση μέσου όρου, ή εξωτερικής βιβλιοθήκης NewPing]
void apostasiDexia(){
  digitalWrite(ULTRASONIC2_TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(ULTRASONIC2_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC2_TRIG_PIN, LOW);

  
  Xronos2 = pulseIn(ULTRASONIC2_ECHO_PIN, HIGH);
  Apostasi2 = (Xronos2/2)/29.1;
  
  Serial.print("Dexia: ");
  Serial.println(Apostasi2);  
}

//Ολόκληρη η διαδικασία μέτρησης Υγρασίας (Servo + Αισθητήρας) [Βελτίωση με αποφυγη του delay και έλεγχο επιθυμητών τιμών]
void diadikasiaMetrisisYgrasias(){
  makis.write(0);
  delay(5000);
  metrisiYgrasias();
  makis.write(180);
  delay(2000);
}

//Μέτρηση Υγρασίας με τον αισθητήρα [Εναλλακτικές του μέσου όρου ?]
void metrisiYgrasias(){
ygrasiaValue = 0.0;
 for (int i = 0; i < 100; i++) 
 { 
   ygrasiaValue = ygrasiaValue + analogRead(YGRASIA_PIN); 
   delay(1); 
 } 
 ygrasiaValue = ygrasiaValue/100.0;
 Serial.print("Ygrasia: "); 
 Serial.println(ygrasiaValue); 
 delay(30); 
}


//ΣΥΝΑΡΤΗΣΕΙΣ ΚΙΝΗΣΗΣ:
//-------------------------

//Motor Κίνησης
void mprosta(){
  digitalWrite(KIN1_PIN, HIGH);
  digitalWrite(KIN2_PIN, LOW);
}

void pisw(){
  digitalWrite(KIN1_PIN, LOW);
  digitalWrite(KIN2_PIN, HIGH);
}

void stopKinisi(){
  digitalWrite(KIN1_PIN, LOW);
  digitalWrite(KIN2_PIN, LOW);
}

void breakKinisi(){
  digitalWrite(KIN1_PIN, HIGH);
  digitalWrite(KIN2_PIN, HIGH);

}

//Motor Στροφής
void aristera(){
  digitalWrite(STR1_PIN, LOW);
  digitalWrite(STR2_PIN, HIGH);
}

void dexia(){
  digitalWrite(STR1_PIN, HIGH);
  
  digitalWrite(STR2_PIN, LOW);
}

void stopStrofi(){
  digitalWrite(STR1_PIN, LOW);
  digitalWrite(STR2_PIN, LOW);
}

void breakStrofi(){
  digitalWrite(STR1_PIN, HIGH);
  digitalWrite(STR2_PIN, HIGH);

}
