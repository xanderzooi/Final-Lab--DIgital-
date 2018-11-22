int potPin = A9;
int potPin2 = A8;
int potPin3 = A7;
int potPin4 = A6;
int potArray[4] = {potPin, potPin2, potPin3, potPin4};


int potValArray[4] = {0, 0, 0, 0};
int lastPotValArray[4] = {0, 0, 0, 0};
int ccValArray[4] = {0, 0, 0, 0};
int ccNumberArray[4] = {0, 0, 0, 0};

int buttonArray[4] = {8, 9, 10, 11};

boolean buttonStateArray[4] = {LOW, LOW, LOW, LOW};
boolean lastButtonStateArray[4] = {LOW, LOW, LOW, LOW};
boolean on = false;
unsigned long lastButtonStateChange;



void setup() {
  for (int i = 0; i < 4; i ++) {
    pinMode(potArray[i], INPUT);
    pinMode(buttonArray[i], INPUT);
  }
  Serial.begin(9600);
}


void loop() {
  usbMIDI.read();
  parameterControl();
  activateControl();
}


void parameterControl () {
  for (int i = 0; i < 4; i ++) {
    if (potValArray[i] != lastPotValArray[i]) {
      lastPotValArray[i] = potValArray[i];
      potValArray[i] = analogRead(potArray[i]);
      ccValArray[i] = map(potValArray[i], 0, 1023, 0, 127);
      usbMIDI.sendControlChange(ccNumberArray[i], ccValArray[i], 1);
      Serial.println(ccValArray[i]);
    }
  }
}

void activateControl () {

  lastButtonStateArray[0] = buttonStateArray[0];
  buttonStateArray[0] = digitalRead(buttonArray[0]);

  if (buttonStateArray[0] == HIGH && lastButtonStateArray[0] == LOW) {
    if (on == false) {
      on = true;
      usbMIDI.sendNoteOn (1, 127, 1);
    } else if (on == true) {
      on = false;
      usbMIDI.sendNoteOff (1, 0, 1);
    }
  }

  lastButtonStateArray[1] = buttonStateArray[1];
  buttonStateArray[1] = digitalRead(buttonArray[1]);
  if (buttonStateArray[1] == HIGH && lastButtonStateArray[1] == LOW) {
    if (on == false) {
      on = true;
      usbMIDI.sendNoteOn (2, 126, 1);
    } else if (on == true) {
      on = false;
      usbMIDI.sendNoteOff (2, 0, 1);
    }
  }


  lastButtonStateArray[2] = buttonStateArray[2];
  buttonStateArray[2] = digitalRead(buttonArray[2]);

  if (buttonStateArray[2] == HIGH && lastButtonStateArray[2] == LOW) {
    if (on == false) {
      on = true;
      usbMIDI.sendNoteOn (3, 125, 1);
    } else if (on == true) {
      on = false;
      usbMIDI.sendNoteOff (3, 0, 1);
    }
  }

  lastButtonStateArray[3] = buttonStateArray[3];
  buttonStateArray[3] = digitalRead(buttonArray[3]);

  if (buttonStateArray[3] == HIGH && lastButtonStateArray[3] == LOW) {
    if (on == false) {
      on = true;
      usbMIDI.sendNoteOn (4, 124, 1);
    } else if (on == true) {
      on = false;
      usbMIDI.sendNoteOff (4, 0, 1);

    }
  }
}
