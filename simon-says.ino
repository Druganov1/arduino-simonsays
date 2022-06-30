#include <EEPROM.h> //Voor highscore :)

//Very simple simon says game.
//Made by Nawid. GitHub: https://github.com/Druganov1


//    
//     _____ _                                             
//    /  ___(_)                                            
//    \ `--. _ _ __ ___   ___  _ __    ___  __ _ _   _ ___ 
//     `--. \ | '_ ` _ \ / _ \| '_ \  / __|/ _` | | | / __|
//    /\__/ / | | | | | | (_) | | | | \__ \ (_| | |_| \__ \
//    \____/|_|_| |_| |_|\___/|_| |_| |___/\__,_|\__, |___/
//                                                __/ |    
//                                               |___/     
//  

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

uint8_t EEPROMaddress = 130;
 

const int MAX_LEVEL = 100; // Hoogste level
int sequence[MAX_LEVEL]; //Dit is de juiste volgorde dus
int your_sequence[MAX_LEVEL]; //Reeks van de user die later word ingevuld bij het drukken van de knoppen
int level = 1; //Level van de speler
int score = 0; //Score
int scoreEEPROM = EEPROM.read(EEPROMaddress); //Score van rom
bool gameOver = false;

int velocity = 1000; //Snelheid voor delays

const int buzzer = 11; //buzzer pin die in het midden zit nice eve!


const int yellow_btn = 10;  //Yellow led button
const int green_btn = 8;   //Green led button
const int red_btn = 7;    //Red led button
const int blue_btn = 9;  //Blue led button




const int yellow_led = 6;   //yellow led
const int green_led = 2;   //green led
const int red_led = 3;    // red led
const int blue_led = 5;  // blue led

bool gameStarted = false;



void setup() {
  Serial.begin(9600);
lcd.begin(16, 2);
lcd.setRGB(0, 255, 0);
DisplayScore();

pinMode(yellow_btn, INPUT); //yellow
pinMode(green_btn, INPUT); //Green
pinMode(red_btn, INPUT);  // red
pinMode(blue_btn, INPUT);      // blue

pinMode(yellow_led, OUTPUT);
pinMode(green_led, OUTPUT);
pinMode(red_led, OUTPUT);
pinMode(blue_led, OUTPUT);

digitalWrite(yellow_led, LOW); //omdat arduino soms beetje kut is doen we gewoon alles ff uit voor de leuk
digitalWrite(green_led, LOW);
digitalWrite(red_led, LOW);
digitalWrite(blue_led, LOW);

}


void blinkLampjesLoop()
{
  if(!gameStarted){
      int kaas[4] = {6, 2, 3, 5};
  
  for(int i=0; i<4; i++){
    digitalWrite(kaas[i], HIGH);
    delay(100);
    digitalWrite(kaas[i], LOW);
    delay(200);
  }
  }

}

void loop() // loop loop loop looooooooooooooop
{
//  while(!gameOver){
    
  
      if (level == 1)
      generate_sequence();//Maak een nieuwe random sequence (reeks) aan;
      
      //while(!gameStarted){
      //    int kaas[4] = {6, 2, 3, 5};
      //  
      //  for(int i=0; i<4; i++){
      //    digitalWrite(kaas[i], HIGH);
      //    delay(200);
      //    digitalWrite(kaas[i], LOW);
      //    delay(200);
      //  }
      //}
      blinkLampjesLoop();
      
      if (digitalRead(blue_btn) == HIGH || digitalRead(green_btn) == HIGH || digitalRead(red_btn) == HIGH || digitalRead(yellow_btn) == HIGH || level != 1) //Op blauwe knop klikken = spel starten. dont ask why heb het gewoon zo gedaan
      {
        gameStarted = true;
        Serial.println("Spel is gestart!");
      show_sequence();    //Laat de lampjes zien, die in de array al dus staan (Eerder aangeroepen door generate_sequence())
      get_sequence();     //Wacht voor de input van de user
      }
      }
      
      void show_sequence()
      {
      digitalWrite(yellow_led, LOW);
      digitalWrite(green_led, LOW);
      digitalWrite(red_led, LOW);
      digitalWrite(blue_led, LOW);
      
      for (int i = 0; i < level; i++)
      {
      
      digitalWrite(sequence[i], HIGH);
      playBuzzer(sequence[i]);
      delay(200);
      digitalWrite(sequence[i], LOW);
      delay(velocity);
      
      }
      }
      
      void get_sequence()
      {
      int flag = 0; //Checkt of de ingevoerde knopjes matchen
      
      for (int i = 0; i < level; i++)
      {
      flag = 0;
      while(flag == 0)
      {
      
      if (digitalRead(yellow_btn) == HIGH)
      {
      
      digitalWrite(yellow_led, HIGH);
      playBuzzer(6);
      your_sequence[i] = yellow_led;
      flag = 1;
      delay(500);
      if (your_sequence[i] != sequence[i])
      {
      wrong_sequence();
      return;
      }
      digitalWrite(yellow_led, LOW);
      }
      
      if (digitalRead(green_btn) == HIGH)
      {
        Serial.println("Groen werkt toch wel??!");
      
      digitalWrite(green_led, HIGH);
      playBuzzer(2);
      your_sequence[i] = green_led;
      flag = 1;
      delay(500);
      if (your_sequence[i] != sequence[i])
      {
      wrong_sequence();
      return;
      }
      digitalWrite(green_led, LOW);
      }
      
      if (digitalRead(red_btn) == HIGH)
      {
      
      digitalWrite(red_led, HIGH);
      playBuzzer(3);
      your_sequence[i] = red_led;
      flag = 1;
      delay(500);
      if (your_sequence[i] != sequence[i])
      {
      wrong_sequence();
      return;
      }
      digitalWrite(red_led, LOW);
      }
      
      if (digitalRead(blue_btn) == HIGH)
      {
      
      digitalWrite(blue_led, HIGH);
      playBuzzer(5);
      your_sequence[i] = blue_led;
      flag = 1;
      delay(500);
      if (your_sequence[i] != sequence[i])
      {
      wrong_sequence();
      return;
      }
      digitalWrite(blue_led, LOW);
      }
      
      }
      }
      right_sequence();
//    }
}

void generate_sequence()
{
randomSeed(millis()); //in this way is really random!!!
int kaas[4] = {6, 2, 3, 5};
for (int i = 0; i < MAX_LEVEL; i++)
{
sequence[i] = kaas[random(0, 4)];

}
}
void wrong_sequence() //fout?
{
  Serial.println("Fout, game over!!");
for (int i = 0; i < 3; i++) //3 keer knipperen
{

  
digitalWrite(yellow_led, HIGH);
digitalWrite(green_led, HIGH);
digitalWrite(red_led, HIGH);
digitalWrite(blue_led, HIGH);
delay(250);
digitalWrite(yellow_led, LOW);
digitalWrite(green_led, LOW);
digitalWrite(red_led, LOW);
digitalWrite(blue_led, LOW);

delay(250);

}
  score=0; //reset score
  gameStarted = false; //Zodat die lampjes weer rond draaien
  tone(buzzer, 100); // game over geluidje voor 2 sec
lcd.clear();
lcd.print("GAME OVER!");
delay(2000);
noTone(buzzer);
DisplayScore();
blinkLampjesLoop(); // start lampjes loop weer en reset de rest
level = 1;
velocity = 1000;
}

void right_sequence() //goed?
{
  score++;


if(score>scoreEEPROM){ //Dus als je de highscore hebt verbroken dan zet die t nieuwe record erin
  EEPROM.write(EEPROMaddress, score); //hier write die naar byte 130
}

  Serial.println("Right!!");
  DisplayScore();
digitalWrite(yellow_led, LOW);
digitalWrite(green_led, LOW);
digitalWrite(red_led, LOW);
digitalWrite(blue_led, LOW);
delay(250);

digitalWrite(yellow_led, HIGH);
digitalWrite(green_led, HIGH);
digitalWrite(red_led, HIGH);
digitalWrite(blue_led, HIGH);
delay(500);
digitalWrite(yellow_led, LOW);
digitalWrite(green_led, LOW);
digitalWrite(red_led, LOW);
digitalWrite(blue_led, LOW);
delay(500);

if (level < MAX_LEVEL);
level++;

velocity -= 50; //increase difficulty
}






void playBuzzer(int button) {
  if (button == 6) {// Lampjes
      tone(buzzer, 950);
      delay(100);
      noTone(buzzer);
  }
  else if (button == 2) {
      tone(buzzer, 850);
      delay(100);
      noTone(buzzer);
  }
  else if (button == 3) {
      tone(buzzer, 750);
      delay(100);
      noTone(buzzer);
  }
  else if (button == 5) {
      tone(buzzer, 650);
      delay(100);
      noTone(buzzer);
  } 
  
  
}


void DisplayScore(){
  int scoreEEPROM2 = EEPROM.read(EEPROMaddress); //Score van rom
  lcd.clear();
  lcd.setCursor(0, 1);
lcd.print("Highscore: ");
lcd.print(scoreEEPROM2);
lcd.setCursor(0, 0);
lcd.print("Score: ");
lcd.print(score);

}
