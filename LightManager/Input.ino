void inputManager(){
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    state = 1;
    delay(100);
  } else {
    // turn LED off:
    state = 0;
  }
  
}

