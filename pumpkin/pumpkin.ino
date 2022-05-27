int led_pins[] = {2,3,4,5,6,7};
int button_pin = 12;
const long DELAY = 10;

int buzzer = 8;
 


void setup() {
  for (int i=0; i < 6; i++) {
    pinMode(led_pins[i], OUTPUT);
  }
  pinMode(buzzer, OUTPUT);
  pinMode(button_pin, INPUT);
  
  digitalWrite(13, HIGH);

}

void loop(){ 
    if(digitalRead(button_pin) == HIGH) {
          digitalWrite(13, LOW);

       playSound(10);
       digitalWrite(13, HIGH);
    }
    
}

void playSound(int times) {
  int degrees = 1;
  int basefreq = 440;
  int duration = 2;
  int slices = 100;
  
  for (int i = 0 ; i < times ; i++) {

    for(int j=0 ;  j < slices ; j++ ) {
      
      int thisLED = (j / 6) % 6;
      digitalWrite(led_pins[thisLED], HIGH);
      
      float angle = j*2*PI/slices;
      float freq = basefreq * (1 + sin(angle)); 
      tone(buzzer, freq);
  
      delay(duration);
      digitalWrite(led_pins[thisLED], LOW);
    }
    noTone(buzzer);
    
  }
}
