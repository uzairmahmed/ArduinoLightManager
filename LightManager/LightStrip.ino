void scrollNewCol(int r, int g, int b, int s) {
  for (int x = 0; x < 59; x++) {
    strip.setPixelColor(x, r, g, b);
    delay(s);
    strip.show();
  }
}

void solid(int r, int g, int b) {
  scrollNewCol(r, g, b, 1);
}

void flash(int r, int g, int b, int s) {
  scrollNewCol(r, g, b, 1);
  delay(s);
  scrollNewCol(0, 0, 0, 1);
  delay(s);
}

void blendscroll(int s) {
  scrollNewCol(255, 0, 0, 1);
  scrollNewCol(255, 100, 0, 1);
  scrollNewCol(255, 255, 0, 1);
  scrollNewCol(0, 255, 0, 1);
  scrollNewCol(0, 0, 255, 1);
  scrollNewCol(25, 25, 255, 1);
  scrollNewCol(255, 0, 255, 1);
}

void bumper(int r1, int g1, int b1, int r2, int g2, int b2, int s) {
  for (int x = 0; x < 59; x++) {
    strip.setPixelColor(x, r1, g1, b1);
    delay(s);
    strip.show();
  }
  for (int y = 59; y > 0; y--) {
    strip.setPixelColor(y, r2, g2, b2);
    delay(s);
    strip.show();
  }
}

void lightManager() {
  if (lightMode == 1) {
    solid(r1, g1, b1);
  } else if (lightMode == 2) {
    flash(r1, g1, b1, lightSpeed);
  } else if (lightMode == 3) {
    blendscroll(lightSpeed / 5);
  } else if (lightMode == 4) {
    blendscroll(lightSpeed * 2);
  } else if (lightMode == 5) {
    bumper(r1, g1, b1, r2, g2, b2, lightSpeed);
  }
}

