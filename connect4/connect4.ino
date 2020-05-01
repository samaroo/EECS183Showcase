#include <gamma.h>
#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h>
// define the wiring of the LED screen
const uint8_t CLK  = 8;
const uint8_t LAT = A3;
const uint8_t OE = 9;
const uint8_t A = A0;
const uint8_t B = A1;
const uint8_t C = A2;
// define the wiring of the inputs
const int POTENTIOMETER_PIN_NUMBER = 5;
const int BUTTON_PIN_NUMBER = 10;
const int NUM_ROWS = 5;
const int NUM_COLS = 10;
// a global variable that represents the LED screen
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
    
class Color {
  public:
    int red;
    int green;
    int blue;
    Color() {
      red = 0;
      green = 0;
      blue = 0;
    }
  
    Color(int r, int g, int b) {
      red = r;
      green = g;
      blue = b;
    }
    int get_red(){
      return red;
    }
    int get_green(){
      return green;
    }
    int get_blue(){
      return blue;
    }
    bool is_equal_to(Color color){
      if(red == color.get_red() && green == color.get_green() && blue == color.get_blue()){
        return true;
      }
      return false;
    }
    uint16_t to_333() const {
     return matrix.Color333(red, green, blue);
   }
};
const Color BLACK(0, 0, 0);
const Color RED(6, 0, 0);
const Color ORANGE(6, 1, 0);
const Color YELLOW(4, 4, 0);
const Color GREEN(0, 4, 0);
const Color BLUE(0, 0, 4);
const Color PURPLE(1, 0, 2);
const Color WHITE(4, 4, 4);
const Color LIME(2, 4, 0);
const Color AQUA(0, 4, 4);
 
class Piece {
  public:
    // Constructors
    Piece() {
      x = 0;
      y = 0;
      drawn = false;
      color = BLACK;
    }
    // sets values for private date members x and y
    Piece(int x_arg, int y_arg) {
      x = x_arg;
      y = y_arg;
      drawn = false;
      color = BLACK;
      }
    
    // getters
    int get_x() const {
      return x;
    }
    int get_y() const {
      return y;
    }
    Color get_color(){
      return color;
    }
    bool is_drawn() const {
      return drawn;
    }

    void fall() {
      erase();
      y++;
      draw(color);
    }
   

    void draw(Color colors) {
      color = colors;
      draw_with_rgb(colors);
      drawn = true;
    }
    
    void erase() {
      draw_with_rgb(BLACK);
    } 
      

  private:
    int x;
    int y;
    bool drawn;
    Color color;
    
    // draws the Piece
    void draw_with_rgb(Color colors) {
      //draws body

      for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
          matrix.drawPixel((x+i), (y+j), colors.to_333());
        }
      }
    }
};

 class Player_X {
     public:

    Player_X() {
      x = 0;
      y = 15;
    }

    Player_X(int x_arg) {
      x = x_arg;
      y = 15;
    }
    
     int get_x() const {
       return x;
     }
    
    void set_x(int x_arg) {
      x = x_arg;
    }
    
    void draw() {
       draw_with_rgb(WHITE);
     }

     void erase() {
      draw_with_rgb(BLACK);
    }
    
   private:
    int x;
    int y;

    void initialize(int x_arg, int y_arg) {
      x = x_arg;
       y = y_arg;
     }
     
     void draw_with_rgb(Color color) {
       matrix.drawPixel(x, y, color.to_333());
       matrix.drawPixel((x+1), y, color.to_333());
     }
 };

  class Player_Y {
     public:

    Player_Y() {
      x = 0;
      y = 0;
    }

    Player_Y(int y_arg) {
      x = 0;
      y = y_arg;
    }
    
     int get_x() const {
       return x;
     }
    
    void set_y(int y_arg) {
      y = y_arg;
    }
    
    void draw() {
       draw_with_rgb(WHITE);
     }

     void erase() {
      draw_with_rgb(BLACK);
    }
    
   private:
    int x;
    int y;

    void initialize(int x_arg, int y_arg) {
      x = x_arg;
       y = y_arg;
     }
     
     void draw_with_rgb(Color color) {
       matrix.drawPixel(x, y, color.to_333());
       matrix.drawPixel(x, (y + 1), color.to_333());
     }
 };

 class Connect4 {
     public:

    Connect4() {
      time = 0;
      turn = 0;
    }

    int get_lowest_row(int col){
      for(int i = (NUM_ROWS - 1); i <= 0; i--){
        if(!(pieces[col][i].is_drawn())){
          return i;
        }
      }
      return 0;
    }

    void setup_game(){
      for(int i = 1; i < 32; i++){
        matrix.drawPixel(i, 14, BLUE.to_333());
        if(i == 1 || i == 4 || i == 7 || i == 10 || i == 13 || i == 16 || i == 19 || i == 22 || i == 25 || i == 28 || i == 31){
          for(int j = 13; j >= 0; j--){
            matrix.drawPixel(i, j, BLUE.to_333());
            if(j == 11 || j == 8 || j == 5 || j == 2){
              for(int x = 1; x < 32; x++){
                matrix.drawPixel(x, j, BLUE.to_333());
              }
            }
          }
        }
      }

      //fill array

      Piece p00(2, 0);
      Piece p10(5, 0);
      Piece p20(8, 0);
      Piece p30(11, 0);
      Piece p40(14, 0);
      Piece p50(17, 0);
      Piece p60(20, 0);
      Piece p70(23, 0);
      Piece p80(26, 0);
      Piece p90(29, 0);
      Piece p01(2, 3);
      Piece p11(5, 3);
      Piece p21(8, 3);
      Piece p31(11, 3);
      Piece p41(14, 3);
      Piece p51(17, 3);
      Piece p61(20, 3);
      Piece p71(23, 3);
      Piece p81(26, 3);
      Piece p91(29, 3);
      Piece p02(2, 6);
      Piece p12(5, 6);
      Piece p22(8, 6);
      Piece p32(11, 6);
      Piece p42(14, 6);
      Piece p52(17, 6);
      Piece p62(20, 6);
      Piece p72(23, 6);
      Piece p82(26, 6);
      Piece p92(29, 6);
     /* Piece p03(2, 9);
      Piece p13(5, 9);
      Piece p23(8, 9);
      Piece p33(11, 9);
      Piece p43(14, 9);
      Piece p53(17, 9);
      Piece p63(20, 9);
      Piece p73(23, 9);
      Piece p83(26, 9);
      Piece p93(29, 9); 
      Piece p04(2, 12);
      Piece p14(5, 12);
      Piece p24(8, 12);
      Piece p34(11, 12);
      Piece p44(14, 12);
      Piece p54(17, 12);
      Piece p64(20, 12);
      Piece p74(23, 12);
      Piece p84(26, 12);
      Piece p94(29, 12); */
/*
      pieces[0][0] = p00;
      pieces[0][1] = p01;
      pieces[0][2] = p02;
      pieces[0][3] = p03;
      pieces[0][4] = p04;
      pieces[1][0] = p10;
      pieces[1][1] = p12;
      pieces[1][2] = p13;
      pieces[1][3] = p14;
      pieces[1][4] = p20;
      pieces[2][0] = p21;
      pieces[2][1] = p22;
      pieces[2][2] = p23;
      pieces[2][3] = p24;
      pieces[2][4] = p30;
      pieces[3][0] = p31;
      pieces[3][1] = p32;
      pieces[3][2] = p33;
      pieces[3][3] = p34;
      pieces[3][4] = p40;
      pieces[4][0] = p41;
      pieces[4][1] = p42;
      pieces[4][2] = p43;
      pieces[4][4] = p44;
      pieces[4][4] = p50;
      pieces[5][0] = p51;
      pieces[5][1] = p52;
      pieces[5][2] = p53;
      pieces[5][3] = p54;
      pieces[5][4] = p60;
      pieces[6][0] = p61;
      pieces[6][1] = p62;
      pieces[6][2] = p63;
      pieces[6][3] = p64;
      pieces[6][4] = p70;
      pieces[7][0] = p71;
      pieces[7][1] = p72;
      pieces[7][2] = p73;
      pieces[7][3] = p74;
      pieces[7][4] = p80;
      pieces[8][0] = p81;
      pieces[8][1] = p82;
      pieces[8][2] = p83;
      pieces[8][3] = p84;
      pieces[8][4] = p90;
      pieces[9][0] = p91;
      pieces[9][1] = p92;
      pieces[9][2] = p93;
      pieces[9][3] = p94;
      pieces[9][4] = p94; */
      
    }

    void update(int potentiometer_value, bool button_pressed){
      player_x.erase();
      potentiometer_value = potentiometer_value / 32;
      if(potentiometer_value == 0){
        potentiometer_value = 1;
      }
      if(potentiometer_value > 10){
        potentiometer_value = 10;
      }
      player_x.set_x((3 * potentiometer_value) - 1);
      player_x.draw();

      player_y.erase();
      player_y.set_y(12 - (3 *(get_lowest_row(potentiometer_value))));
      player_y.draw();

      /*if(button_pressed){
        turn++;
        if((turn % 2) == 1){
          
        }
      }*/
    }

    private:

    int turn;
    unsigned long time;
    Player_X player_x;
    Player_Y player_y;
    Piece pieces[NUM_COLS][NUM_ROWS];

    bool diag_win() {
      for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 10; col++) {
         if ((pieces[col][row].get_color().is_equal_to(pieces[col+1][row+1].get_color())) && (pieces[col][row].get_color().is_equal_to(pieces[col+2][row+2].get_color())) && (pieces[col][row].get_color().is_equal_to(pieces[col+3][row+3].get_color()))) {
           return true;
         }
       }
     }
     for (int row = 4; row >= 0; row--) {
       for (int col = 0; col < 10; col++) {
         if ((pieces[col][row].get_color().is_equal_to(pieces[col+1][row-1].get_color())) && (pieces[col][row].get_color().is_equal_to(pieces[col+2][row-2].get_color())) && (pieces[col][row].get_color().is_equal_to(pieces[col+3][row-3].get_color()))) {
           return true;
         }
       }
    }
    return false;
    }

    bool col_win() {
      for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 10; col++) {
         if ((pieces[col][row].get_color().is_equal_to(pieces[col][row+1].get_color())) && (pieces[col][row].get_color().is_equal_to(pieces[col][row+2].get_color())) && (pieces[col][row].get_color().is_equal_to(pieces[col][row+3].get_color()))) {
           return true;
         }
       }
      }
      return false;
    }

    bool row_win() {
      for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 10; col++) {
         if ((pieces[col][row].get_color().is_equal_to(pieces[col+1][row].get_color())) && (pieces[col][row].get_color().is_equal_to(pieces[col+2][row].get_color())) && (pieces[col][row].get_color().is_equal_to(pieces[col+3][row].get_color()))) {
           return true;
         }
       }
      }
      return false;
    }

    bool game_won() {
      if(diag_win() || col_win() || row_win()){
        return true;
      }
      matrix.fillScreen(BLACK.to_333());
      matrix.print("YOU WIN, BITCH");
      delay(2000);
    }
 };

 Connect4 connect4;
    
 void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN_NUMBER, INPUT);
  matrix.begin();
  connect4.setup_game();
}
 void loop() {
   int potentiometer_value = analogRead(POTENTIOMETER_PIN_NUMBER);
    bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER) == HIGH);
    
    connect4.update(potentiometer_value, button_pressed);
   
 }
