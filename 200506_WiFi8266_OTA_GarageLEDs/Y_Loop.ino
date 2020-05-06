void loop() {
    ArduinoOTA.handle();
    Blynk.run();

	// flash D4 to signal loop is running
	flashD4(1);
    // first check for manualOnOffButton getPirPinState
    if (manualOnOffButton) {
        // manually force LEDs on
        setSirenOn();
        Front.setOn();
        Back.setOn();
    } else {
        // poll the pirPins
        if (Front.getPirPinState()) Front_ISR();
        if (Back.getPirPinState()) Back_ISR();

        // check if leds on, and if so is time up
        bool front = Front.isPirTimeUp();
        bool back = Back.isPirTimeUp();
        if (!(front || back)) setSirenOff();
        if (lastSirenValue != sirenValue) {
          // change since last check
          Blynk.virtualWrite(V0,sirenValue);
          lastSirenValue = sirenValue;
          if (sirenValue > 200) {
             if (eMailButtonState) Blynk.email("Subject: Outside LEDs","Outside PIRs activated");
             terminalWrite(" Outside LEDs ON");
          }
        }
    }
}

// ----------------------------------------------
/*
void loop() {
  ArduinoOTA.handle();

//loop to blink without delay
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
  // save the last time you blinked the LED
  previousMillis = currentMillis;
  // if the LED is off turn it on and vice-versa:
  ledState = not(ledState);
  // set the LED with the ledState of the variable:
  digitalWrite(led,  ledState);
  }
}
*/
// --------------------------------------------------
