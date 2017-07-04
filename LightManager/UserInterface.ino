void navHandler( int up, int down , int left, int right, int but1, int but2)
{
  if (input == 8) {
    if (up != -9) {
      uiState = up;
    }
  } else if (input == 2) {
    if (down != -9) {
      uiState = down;
    }
  } else if (input == 4) {
    if (left != -9) {
      uiState = left;
    }
  } else if (input == 6) {
    if (right != -9) {
      uiState = right;
    }
  } else if (input == 7) {
    if (but1 != -9) {
      uiState = but1;
    }
  } else if (input == 9) {
    if (but2 != -9) {
      uiState = but2;
    }
  }
}

void arrowChars() {
  lcd.setCursor(15, 0);
  lcd.write(1);
  lcd.setCursor(15, 1);
  lcd.write(2);
  lcd.setCursor(7, 1);
  lcd.write(3);
  lcd.setCursor(8, 1);
  lcd.write(4);
  lcd.home();
}

void printValues() {
  lcd.setCursor(0, 0);
  lcd.print("S: " + (String)lightSpeed);
  lcd.setCursor(0, 1);
  lcd.print("C: " + col1Name + "," + col2Name);
}

void menuManager() {
  delay(50);
  if (uiState == 1) {
    lcd.clear();
    lcd.print("Welcome");
    lcd.setCursor(9, 0);
    lcd.write(5);
    arrowChars();
    navHandler(-9, 2, -9, 11, -9, -9);
  } else if (uiState == 2) {
    lcd.clear();
    lcd.print("-Solid Color-");
    arrowChars();
    navHandler(1, 3, -9, 12, -9, -9);
  } else if (uiState == 3) {
    lcd.clear();
    lcd.print("-Flash Color-");
    arrowChars();
    navHandler(2, 4, -9, 13, -9, -9);
  } else if (uiState == 4) {
    lcd.clear();
    lcd.print("-Blend Color-");
    arrowChars();
    navHandler(3, 5, -9, 14, -9, -9);
  } else if (uiState == 5) {
    lcd.clear();
    lcd.print("Scroll Colors");
    arrowChars();
    navHandler(4, 6, -9, 15, -9, -9);
  } else if (uiState == 6) {
    lcd.clear();
    lcd.print("-Bumper Mode-");
    arrowChars();
    navHandler(5, 7, -9, 16, -9, -9);
  } else if (uiState == 7) {
    lcd.clear();
    lcd.print("-END-");
    arrowChars();
    navHandler(6, 8, -9, -9, -9, -9);
  }
}

void settingManager() {
  if (uiState == 11) {
    lcd.clear();
    lcd.print("By Uzair Ahmed");
    navHandler(-9, -9, 1, -9, -9, -9);
  } else if (uiState == 12) {
    lcd.clear();
    printValues();
    lightMode = 1;
    navHandler(-9, -9, 2, -9, 22, 32);
  } else if (uiState == 13) {
    lcd.clear();
    printValues();
    lightMode = 2;
    //arrowChars();
    navHandler(-9, -9, 3, -9, 23, 33);
  } else if (uiState == 14) {
    lcd.clear();
    printValues();
    lightMode = 3;
    //arrowChars();
    navHandler(-9, -9, 4, -9, 24, 34);
  } else if (uiState == 15) {
    lcd.clear();
    printValues();
    lightMode = 4;
    //arrowChars();
    navHandler(-9, -9, 5, -9, 25, 35);
  } else if (uiState == 16) {
    lcd.clear();
    printValues();
    lightMode = 5;
    //arrowChars();
    navHandler(-9, -9, 6, -9, 26, 36);
  } 
}

