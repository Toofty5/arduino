int led_pins[] = {2,3,4,5,6};
int button_pin = 12;
long led_start = 0;
int led_lit = 0;
const long DELAY = 100;

//gmaj abmaj bbmaj

int buzzer = 8;


int a = 698;
int b = 659;
int c = 622;
int d = 587;
const int songLength = 17;
int song[songLength][3] = {  
      {a,125,125},
      {a,125,125},
      {a,175,50},
      {b,150, 0},
      {a,125,125},
      {a,125,225},
      
      {a,100,150},
      {a,100,150},
      
      {b,125,125},
      {b,125,125},
      {b,175,50},
      {d,150, 0},
      {b,125,125},
      {b,125,225},

      {b,125,125},
      {b,125,125},

}; // freq, duration,pause


 int freq;
 int duration;
 int rest;
 long noteStart;
 long noteEnd;
 long nextNote;
 


void setup() {
  for (int i=0; i < 6; i++) {
    pinMode(led_pins[i], OUTPUT);
  }
  pinMode(buzzer, OUTPUT);
  pinMode(button_pin, INPUT);
}

void loop(){
  
      if(digitalRead(button_pin) == HIGH) {
        powerup();
        delay(200);
        playSong(2);
      }
      
}
void playSong(int reps){
  for(int r = 0; r < reps; r++){
     for (int i = 0 ; i < songLength; i++){
       freq = song[i][0];
       duration = song[i][1];
       rest = song[i][2];
       
       noteStart = millis();
       noteEnd = noteStart + duration;
       nextNote = noteEnd + rest;
       
       tone(buzzer, freq);
       while(millis() < nextNote){
         if (millis() >= noteEnd){
           noTone(buzzer);
         }
         
         //do something here
         if(millis() - DELAY >= led_start){ //time to change LED
           digitalWrite(led_pins[led_lit], LOW);
           led_lit = (led_lit + 1) % 5;
           led_start = millis();
           digitalWrite(led_pins[led_lit], HIGH);
         }
       }
     }
     digitalWrite(led_pins[led_lit], LOW);
     noTone(buzzer);
  }
}

void powerup() {
  float root = 690;
  float freq;
  float roots[3] = {0, 1.0/12.0, 1/4.0} ;

  
  for( int i = 0; i < 3; i++) {
    if(i % 2 == 0)
      lightsOn();
    else
      lightsOff();
    for(float j = 0; j < 4; j++) {
        int power_duration = 50;
        freq = root * pow(2.0, roots[i]) * pow(2.0, j/4);
        Serial.println(roots[i]);
        tone(buzzer, freq, power_duration);
        delay(power_duration);
    }
  }

}
void lightsOn(){
  for(int i = 0; i < 5; i++){
    digitalWrite(led_pins[i], HIGH);
  }
}

void lightsOff(){
  for(int i = 0; i < 5; i++){
    digitalWrite(led_pins[i], LOW);
  }
}
