void nunchukManager(){
  Serial.println("Begin Loop");
    if (nunchuk_read()) {
        // Work with nunchuk_data
        nunchuk_print();
    } else{
      nunchuk_init();
    }  
}


void serialInputManager(){
  if (Serial.available() > 0) {
    input = Serial.parseInt();
    Serial.println(input);
  }
}

