int Razz [4] = {227, 11, 22, 0};    int Mage [4] = {238, 0, 238, 1};  int Purp [4] = {148, 0, 211, 2};
int LPurp [4] = {132, 112, 255, 3};  int Blue [4] = { 0, 0, 255, 4};   int RBlu [4] = { 72, 118, 255, 5};
int Turq [4] = { 0, 245, 255, 6};   int DGre [4] = { 0, 201, 87, 7};  int Gree [4] = { 0, 255, 0, 8};
int Lime [4] = {124, 252, 0, 9};    int Yell [4] = {255, 255, 0, 10};  int Oran [4] = {255, 165, 0, 11};
int DOran [4] = {255, 127, 0, 12};    int OrRed [4] = {255, 69, 0, 13};   int Red [4] = {255, 0, 0, 14};
int DRed [4] = {139, 0, 0, 15};     //int DarkBlack [3]= {-255,-255,-255}; <--Thats a joke dont worry.

int* colors[16] = {Razz, Mage, Purp, LPurp, Blue, RBlu, Turq, DGre, Gree, Lime, Yell, Oran, DOran, OrRed, Red, DRed};
int color1Index = 0;int color2Index = 0;


void setColName(int colArray, int index, String colName) {
  if (colArray == 0) {
    if (colors[color1Index][3] == index) {
      col1Name = colName;
    }
  }
  if (colArray == 1) {
    if (colors[color2Index][3] == index) {
      col2Name = colName;
    }
  }
}

void colorManager() {
  r1 = colors[color1Index][0];
  g1 = colors[color1Index][1];
  b1 = colors[color1Index][2];
  r2 = colors[color2Index][0];
  g2 = colors[color2Index][1];
  b2 = colors[color2Index][2];
  setColName(0,0,"Razz"); setColName(0,4,"Blue"); setColName(0,8,"Gree"); setColName(0,12,"DOran");
  setColName(0,1,"Mage"); setColName(0,5,"RBlu"); setColName(0,9,"Lime"); setColName(0,13,"OrRed");
  setColName(0,2,"Purp"); setColName(0,6,"Turq"); setColName(0,10,"Yell"); setColName(0,14,"Red");
  setColName(0,3,"LPurp"); setColName(0,7,"DGre"); setColName(0,11,"Oran"); setColName(0,15,"DRed");

  setColName(1,0,"Razz"); setColName(1,4,"Blue"); setColName(1,8,"Gree"); setColName(1,12,"DOran");
  setColName(1,1,"Mage"); setColName(1,5,"RBlu"); setColName(1,9,"Lime"); setColName(1,13,"OrRed");
  setColName(1,2,"Purp"); setColName(1,6,"Turq"); setColName(1,10,"Yell"); setColName(1,14,"Red");
  setColName(1,3,"LPurp"); setColName(1,7,"DGre"); setColName(1,11,"Oran"); setColName(1,15,"DRed");

  if (color1Index == 16){
    color1Index = 0;
  }
}

