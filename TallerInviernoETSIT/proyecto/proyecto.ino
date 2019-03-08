#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int estado = 0;
int boton = 7;
int led = 13;
int ledA = 6;
int ldr = 0;
int piezo = 8;
int sing = 1;

int melody[] = { 262, 196,196, 220, 196,0, 247, 262};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = { 4, 8, 8, 4,4,4,4,4 };

void setup() {
  lcd.begin(16, 2);
  

  pinMode(boton, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(ledA, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(ldr, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  Serial.print(estado);
  switch (estado){
      case 0:
          estadoInicial();
          break;
      case 1:
          blinkLeds();
          break;
      case 2:
          dimLeds();
          break;
      default:
          estadoFinal();
          break;
  }
  checkBoton();
  
}

int checkBoton(){
    if (digitalRead(boton)==LOW){
      Serial.println("boton pulsado");
      estado = estado + 1;
      if (estado>=4){
        estado=0;
      }
      delay(200);
      return 1;
    } 
    return 0;
}

void estadoInicial(){
  if (sing==0){
    lcd.clear();
    sing = 1;
  }
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("Bienvenido a la");
  lcd.setCursor(0, 1);
  lcd.print("#SemanaCiencia");
}

void estadoFinal(){
  if (sing){
    lcd.clear();
    digitalWrite(ledA, LOW);
  }
  lcd.setCursor(0, 0);
  lcd.print("Gracias por ");
  lcd.setCursor(0, 1);
  lcd.print("Participar!!");
  if (sing){
      for (int thisNote = 0; thisNote < 8; thisNote++) {
        int noteDuration = 1000/noteDurations[thisNote];
        tone(piezo, melody[thisNote],noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(12);
      }
    sing = 0;
  }
}


void blinkLeds(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mira como lucen");
  lcd.setCursor(0, 1);
  lcd.print("los LEDs");
  digitalWrite(led, HIGH);
  delay(150); checkBoton();
  delay(150);
  digitalWrite(led, LOW);
  delay(150); checkBoton();
  delay(150);
  
}

void dimLeds(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tapa LDR y mira");
  lcd.setCursor(0, 1);
  lcd.print("el LED azul");
  int valLDR = analogRead(ldr);
  analogWrite(ledA, map(valLDR, 0, 1023, 0, 255));
  delay(100);
}

