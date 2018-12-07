int potPin = A9;
int potPin2 = A8;
int potPin3 = A7;
int potPin4 = A6;
int potArray[4] = {potPin, potPin2, potPin3, potPin4};

int potValArray[4] = {0, 0, 0, 0};
int lastPotValArray[4] = {0, 0, 0, 0};
int ccVal[4] = {0, 0, 0, 0};
int ccNumber[4] = {1, 2, 3, 4};

int ccAdder = 0;
int ccAdd = 0;

int leftButton = 14;
boolean leftbuttonState = (LOW);
boolean lastleftbuttonState = (LOW);
int rightButton = 13;
boolean rightbuttonState = (LOW);
boolean lastrightbuttonState = (LOW);

unsigned long directionalButtonChange;

int lButton = 12;
boolean lbuttonState = (LOW);
boolean lastlbuttonState = (LOW);
int rButton = 24;
boolean rbuttonState = (LOW);
boolean lastrbuttonState = (LOW);

unsigned long lastCCtime[4] = {0, 0, 0, 0};

int buttonArray[4] = {8, 9, 10, 11};

boolean buttonStateArray[4] = {LOW, LOW, LOW, LOW};
boolean lastButtonStateArray[4] = {LOW, LOW, LOW, LOW};
boolean on = false;
unsigned long lastButtonStateChange;



void setup() {
  for (int i = 0; i < 4; i ++) {
    pinMode(potArray[i], INPUT);
    pinMode(buttonArray[i], INPUT);
    pinMode(leftButton, INPUT);
    pinMode(rightButton, INPUT);
    pinMode(lButton, INPUT);
    pinMode(rButton, INPUT);
  }
  Serial.begin(9600);
}


void loop() {
  usbMIDI.read();
  potCheck();
  buttonCheck();
}

void potCheck() {
  lastleftbuttonState = leftbuttonState;
  leftbuttonState = digitalRead(leftButton);
  lastrightbuttonState = rightbuttonState;
  rightbuttonState = digitalRead(rightButton);

  if (rightbuttonState == HIGH && lastrightbuttonState == LOW) {
    ccAdder = ccAdder + 4;
  }

  if (leftbuttonState == HIGH && lastleftbuttonState == LOW) {
    ccAdder = ccAdder - 4;
  }

  if (ccAdder < 0) {
    ccAdder = 0;
  }
  if (ccAdder > 120) {
    ccAdder = 120;
  }

  for (int i = 0; i < 4; i ++) {
    parameterControl (i);
  }
}



void parameterControl (int ccNum) {

  lastPotValArray[ccNum] = potValArray[ccNum];
  potValArray[ccNum] = analogRead(potArray[ccNum]) / 8;

  if ((potValArray[ccNum] != lastPotValArray[ccNum])) {
    ccVal[ccNum] = map(potValArray[ccNum], 0, 127, 0, 127);

    usbMIDI.sendControlChange(ccNumber[ccNum] + (ccAdder), ccVal[ccNum], 1);
    Serial.println(potValArray[ccNum]);
    Serial.print(ccNum);
    Serial.print(", ");
    Serial.println(ccVal[ccNum]);
  }
}

void buttonCheck() {

  lastlbuttonState = lbuttonState;
  lbuttonState = digitalRead(lButton);
  lastrbuttonState = rbuttonState;
  rbuttonState = digitalRead(rButton);

  if (rbuttonState == HIGH && lastrbuttonState == LOW) {
    ccAdd = ccAdd + 4;
  }

  if (lbuttonState == HIGH && lastlbuttonState == LOW) {
    ccAdd = ccAdd - 4;
  }
  if (ccAdd < 0) {
    ccAdd = 0;
  }
  if (ccAdd > 120) {
    ccAdd = 120;
  }
  for (int i = 0; i < 4; i ++) {
    activateControl (i);
  }
}



void activateControl(int ccNum) {

  lastButtonStateArray[ccNum] = buttonStateArray[ccNum];
  buttonStateArray[ccNum] = digitalRead(buttonArray[ccNum]);

  if (buttonStateArray[ccNum] == HIGH && lastButtonStateArray[ccNum] == LOW) {
    if (on == false) {
      on = true;
      usbMIDI.sendNoteOn (ccNumber[ccNum] + (ccAdd), 127, 1);
    } else if (on == true) {
      on = false;
      usbMIDI.sendNoteOff (ccNumber[ccNum] + (ccAdd), 0, 1);
    }
  }
}
