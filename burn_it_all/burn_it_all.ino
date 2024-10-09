const int REN = 5;
const int LEN = 6;
const int EMERGENCY_BTN = 2;
const int STOP_BTN = 3;
const int START_BTN = 4;
const int LAMP_RED = 7;
const int LAMP_GRN = 8;

bool emergencyState = false;

void setup() {
  Serial.begin(115200);
  pinMode(REN, OUTPUT);
  pinMode(LEN, OUTPUT);
  pinMode(LAMP_GRN, OUTPUT);
  pinMode(LAMP_RED, OUTPUT);
  pinMode(START_BTN, INPUT_PULLUP);
  pinMode(EMERGENCY_BTN, INPUT_PULLUP);
  pinMode(STOP_BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(EMERGENCY_BTN), onEmergency, RISING);
  pullActuator();
  emergencyState = !emergencyBtn();
}
int nStart;
int lStart;
int nStop;
int lStop;
void loop() {
  Serial.println(emergencyState);
  digitalWrite(LAMP_GRN,!emergencyState);
  digitalWrite(LAMP_RED,emergencyState);
  if (!emergencyState) {
    nStart = readStartBtn();
    if (nStart != lStart) {
      if (!nStart) {
        pushActuator();
        delay(100);
      }
      lStart = nStart;
    }

    nStop = readStopBtn();
    if (nStop != lStop) {
      if (!nStop) {
        pullActuator();
        delay(100);
      }
      lStop = nStop;
    }
  }
  else{
    emergencyState = !emergencyBtn();
  }
}

void onEmergency() {
  emergencyState = true;
  stopActuator();
}

int readStartBtn() {
  return digitalRead(START_BTN);
}
int readStopBtn() {
  return !digitalRead(STOP_BTN);
}
int emergencyBtn() {
  return !digitalRead(EMERGENCY_BTN);
}

void pushActuator() {
  digitalWrite(REN, HIGH);
  digitalWrite(LEN, LOW);
}
void pullActuator() {
  digitalWrite(LEN, HIGH);
  digitalWrite(REN, LOW);
}
void stopActuator() {
  digitalWrite(LEN, LOW);
  digitalWrite(REN, LOW);
}