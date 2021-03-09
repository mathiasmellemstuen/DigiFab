const int ledPins[6] = {2,3,4,5,6,7};
const int buttonPin = 8;
const int sensorPin = 9; 

int currentLed = 0;
bool blink = false; 

unsigned long int startTime; 
unsigned long int timePerLed = 1000 * 3; // 3 seconds
unsigned long int blinkTimer;
unsigned long int blinkTime = 250; // 0.25 second
unsigned long int waitTime = 0; 
unsigned long int waitStart = 0; 
unsigned long int waitStop = 0; 

void reset() {
    startTime = millis(); 
    currentLed = 0;
    waitTime = 0; 

    for(int i = 0; i < 6; i++) {
        digitalWrite(ledPins[i], LOW); 
    }
}
void setup() {

    for(int i = 0; i < 6; i++) {
        pinMode(ledPins[i], OUTPUT);
    }

    pinMode(sensorPin, INPUT); 
    pinMode(buttonPin, INPUT); 

    startTime = millis(); 
}

void loop() {

    int sensorValue = digitalRead(sensorPin);
    int buttonValue = digitalRead(buttonPin);

    if(buttonValue) {
        reset();
    }

    if(sensorValue) {

        blinkTimer = blinkTimer == 0 ? millis() : blinkTimer; 

        if(blinkTimer + blinkTime < millis()) {
            blink = !blink;
            blinkTimer = 0; 
        }


        if(waitStart != 0) {
            waitTime += waitStop - waitStart; 
            waitStart = 0;
        }

        currentLed = (millis() - startTime - waitTime) > timePerLed * (currentLed + 1) ? (currentLed + 1) : currentLed;

        for(int i = 0; i < 6; i++) {

            digitalWrite(ledPins[i], i < currentLed ? HIGH : LOW); 
            digitalWrite(ledPins[currentLed], blink ? HIGH : LOW); 
        }

    } else {
        waitStart = waitStart == 0 ? millis() : waitStart;
        waitStop = millis(); 

        digitalWrite(ledPins[currentLed], LOW); 
    }

}