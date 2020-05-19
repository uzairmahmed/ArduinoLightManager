void scrollNewCol(int r, int g, int b, int s) {
  for (int x = 0; x < 60; x++) {
    strip.setPixelColor(x, r, g, b);
    delay(s);
    strip.show();
  }
}

void solid(int r, int g, int b) {
  scrollNewCol(r, g, b, 1);
}

void blendscroll(int s) {
  scrollNewCol(255, 0, 0, s);
  scrollNewCol(255, 100, 0, s);
  scrollNewCol(255, 255, 0, s);
  scrollNewCol(0, 255, 0, s);
  scrollNewCol(0, 0, 255, s);
  scrollNewCol(25, 25, 255, s);
  scrollNewCol(255, 0, 255, s);
}

void lightManager() {
    solid(r1, g1, b1);
}
