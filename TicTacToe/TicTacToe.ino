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
  bool full = false;
  int playr = 0;
  void set_x(int x_arg) {
    x = x_arg;
  }
  void set_y(int y_arg) {
    y = y_arg;
  }
  int get_x() {
    return x;
  }
  int get_y() {
    return y;
  }
  void drop(bool player) {
    if (player) {
      matrix.drawPixel(x, y, GREEN.to_333());
      matrix.drawPixel(x+1, y+1, GREEN.to_333());
      matrix.drawPixel(x+2, y+2, GREEN.to_333());
      matrix.drawPixel(x+3, y+3, GREEN.to_333());
      matrix.drawPixel(x, y+3, GREEN.to_333());
      matrix.drawPixel(x+1, y+2, GREEN.to_333());
      matrix.drawPixel(x+2, y+1, GREEN.to_333());
      matrix.drawPixel(x+3, y, GREEN.to_333());
      playr = 1;
    }
    else {
      matrix.drawPixel(x+1, y, ORANGE.to_333());
      matrix.drawPixel(x+2, y, ORANGE.to_333());
      matrix.drawPixel(x, y+1, ORANGE.to_333());
      matrix.drawPixel(x, y+2, ORANGE.to_333());
      matrix.drawPixel(x+1, y+3, ORANGE.to_333());
      matrix.drawPixel(x+2, y+3, ORANGE.to_333());
      matrix.drawPixel(x+3, y+1, ORANGE.to_333());
      matrix.drawPixel(x+3, y+2, ORANGE.to_333());
      playr = 2;
    }
  }

  private:
  int x;
  int y;
};


class DrawChoice {
  public:
  DrawChoice() {
    x = 9;
    y = 14;
  }

  void set_x(int x_arg) {
    x = x_arg;
  }
  void set_y(int y_arg) {
    y = y_arg;
  }
  int get_x() {
    return x;
  }
  int get_y() {
    return y;
  }

  void draw(bool player) {
    if (player) {
      draw_with_rgb(GREEN);
    }
    else {
      draw_with_rgb(ORANGE);
    }
  }
  void erase() {
    draw_with_rgb(BLACK);
  }
  private:
    int x;
    int y;
    void draw_with_rgb(Color color) {
      matrix.drawPixel(x, y, color.to_333());
      matrix.drawPixel(x, y+1, color.to_333());
      matrix.drawPixel(x, y+2, color.to_333());
      matrix.drawPixel(x, y+3, color.to_333());
      matrix.drawPixel(x+1, y, color.to_333());
      matrix.drawPixel(x+1, y+1, color.to_333());
      matrix.drawPixel(x+1, y+2, color.to_333());
      matrix.drawPixel(x+1, y+3, color.to_333());
      matrix.drawPixel(x+2, y, color.to_333());
      matrix.drawPixel(x+2, y+1, color.to_333());
      matrix.drawPixel(x+2, y+2, color.to_333());
      matrix.drawPixel(x+2, y+3, color.to_333());
      matrix.drawPixel(x+3, y, color.to_333());
      matrix.drawPixel(x+3, y+1, color.to_333());
      matrix.drawPixel(x+3, y+2, color.to_333());
      matrix.drawPixel(x+3, y+3, color.to_333());
    }
};

class TicTacToe {
  public:
  void setUpTTT() {
    //drawing grid in PURPLE
    for (int i = 8; i <= 23; i++) {
      matrix.drawPixel(i, 15, PURPLE.to_333());
      matrix.drawPixel(i, 10, PURPLE.to_333());
      matrix.drawPixel(i, 5, PURPLE.to_333());
      matrix.drawPixel(i, 0, PURPLE.to_333());
      if (i == 8 || i == 13 || i == 18 || i == 23) {
        for (int j = 15; j >= 0; j--) {
          matrix.drawPixel(i, j, PURPLE.to_333());
        }
      }
    }

    //drawing scoreboard in ORANGE
    for (int i = 2; i <= 5; i++) {
      matrix.drawPixel(i, 15, ORANGE.to_333());
      matrix.drawPixel(i, 10, ORANGE.to_333());
      matrix.drawPixel(i, 5, ORANGE.to_333());
      matrix.drawPixel(i, 0, ORANGE.to_333());
      if (i == 2 || i == 5) {
        for (int j = 15; j >= 0; j--) {
          matrix.drawPixel(i, j, ORANGE.to_333());
        }
      }
    }

    //drawing scoreboard in GREEN
    for (int i = 26; i <= 29; i++) {
      matrix.drawPixel(i, 15, GREEN.to_333());
      matrix.drawPixel(i, 10, GREEN.to_333());
      matrix.drawPixel(i, 5, GREEN.to_333());
      matrix.drawPixel(i, 0, GREEN.to_333());
      if (i == 26 || i == 29) {
        for (int j = 15; j >= 0; j--) {
          matrix.drawPixel(i, j, GREEN.to_333());
        }
      }
    }
    Piece p00;
    Piece p01;
    Piece p02;

    Piece p10;
    Piece p11;
    Piece p12;

    Piece p20;
    Piece p21;
    Piece p22;

    pieces[0][0] = p00;
    pieces[1][0] = p10;
    pieces[2][0] = p20;

    pieces[0][1] = p01;
    pieces[1][1] = p11;
    pieces[2][1] = p21;

    pieces[0][2] = p02;
    pieces[1][2] = p12;
    pieces[2][2] = p22;
  }

  
  void update(int potentiometer_value, bool button_pressed) {
    int xcorner = 9;
    int ycorner = 11;
    potentiometer_value /= 127;
    if (potentiometer_value == 0) {
      xcorner = 9;
      ycorner = 11;
      row = 0;
      col = 0;
    }
    else if (potentiometer_value == 1) {
      xcorner = 14;
      ycorner = 11;
      row = 0;
      col = 1;
    }
    else if (potentiometer_value == 2) {
      xcorner = 19;
      ycorner = 11;
      row = 0;
      col = 2;
    }
    else if (potentiometer_value == 3) {
      xcorner = 9;
      ycorner = 6;
      row = 1;
      col = 0;
    }
    else if (potentiometer_value == 4) {
      xcorner = 14;
      ycorner = 6;
      row = 1;
      col = 1;
    }
    else if (potentiometer_value == 5) {
      xcorner = 19;
      ycorner = 6;
      row = 1;
      col = 2;
    }
    else if (potentiometer_value == 6) {
      xcorner = 9;
      ycorner = 1;
      row = 2;
      col = 0;
    }
    else if (potentiometer_value == 7) {
      xcorner = 14;
      ycorner = 1;
      row = 2;
      col = 1;
    }
    else if (potentiometer_value == 8) {
      xcorner = 19;
      ycorner = 1;
      row = 2;
      col = 2;
    }

    if (!button_pressed) {
      if(!pieces[row][col].full) {
        choice.set_x(xcorner);
        choice.set_y(ycorner);
        choice.draw(turn);
        delay(20);
        choice.erase();
      }
    }
    if (button_pressed) {
      if(!pieces[row][col].full) {
        choice.erase();
        delay(50);
        pieces[row][col].set_x(xcorner);
        pieces[row][col].set_y(ycorner);
        pieces[row][col].drop(turn);
        totalChips++;
        turn = !turn;
        pieces[row][col].full = true;
      }
      if (checkWin()) {
        totalChips = 0;
        matrix.fillScreen(BLACK.to_333());
        matrix.setCursor(32,0);
        matrix.setTextSize(2);
        matrix.setTextColor(PURPLE.to_333());
        if (pieces[row][col].playr == 1) {
          matrix.print("GREEN WIN!");
          greenWins++;
        }
        else if (pieces[row][col].playr == 2) {
          matrix.print("ORANGE WIN!");
          orangeWins++;
        }
        delay(100);

        for(int q = 32; q > -200; q--) {
          matrix.fillScreen(BLACK.to_333());
          matrix.setCursor(q, 0);
          if (pieces[row][col].playr == 1) {
            matrix.print("GREEN WIN!");
          }
          else if (pieces[row][col].playr == 2) {
            matrix.print("ORANGE WIN!");
          }
          delay(10);
        }
        matrix.setCursor(0,0);
        matrix.fillScreen(BLACK.to_333());

        if (greenWins == 3) {
          matrix.setCursor(32,0);
          matrix.setTextSize(2);
          matrix.setTextColor(GREEN.to_333());
          matrix.print("GREEN WON!");
          delay(100);

          for(int q = 32; q > -200; q--) {
            matrix.fillScreen(BLACK.to_333());
            matrix.setCursor(q, 0);
            matrix.print("GREEN WON!");
            delay(10);
          }
          matrix.fillScreen(GREEN.to_333());
          matrix.setCursor(4,0);
          matrix.setTextColor(BLACK.to_333());
          matrix.setTextSize(1);
          matrix.print("GAME OVER");
        }
        else if (orangeWins == 3) {
          matrix.setCursor(32,0);
          matrix.setTextSize(2);
          matrix.setTextColor(ORANGE.to_333());
          matrix.print("ORANGE WON!");
          delay(100);

          for(int q = 32; q > -200; q--) {
            matrix.fillScreen(BLACK.to_333());
            matrix.setCursor(q, 0);
            matrix.print("ORANGE WON!");
            delay(10);
          }
          matrix.fillScreen(ORANGE.to_333());
          matrix.setCursor(4,0);
          matrix.setTextColor(BLACK.to_333());
          matrix.setTextSize(1);
          matrix.print("GAME OVER");
        }
        else {
          setUpTTT();
          for (int gWs = greenWins * 5; gWs > 0; gWs--) {
            matrix.drawPixel(27, gWs, GREEN.to_333());
            matrix.drawPixel(28, gWs, GREEN.to_333());
          }
          for (int oWs = orangeWins * 5; oWs > 0; oWs--) {
            matrix.drawPixel(3, oWs, ORANGE.to_333());
            matrix.drawPixel(4, oWs, ORANGE.to_333());
          }
        }
      }
      else if (totalChips == 9) {
        matrix.fillScreen(BLACK.to_333());
        matrix.setCursor(8,5);
        matrix.setTextSize(1);
        matrix.setTextColor(WHITE.to_333());
        String tie = "TIE";
        for (int i = 0; i < 3; i++) {
          matrix.print(tie[i]);
          delay(200);
        }

        matrix.setCursor(8,5);
        matrix.setTextColor(PURPLE.to_333());
        for (int i = 0; i < 3; i++) {
          matrix.print(tie[i]);
          delay(200);
        }

        matrix.setCursor(8,5);
        matrix.setTextColor(ORANGE.to_333());
        for (int i = 0; i < 3; i++) {
          matrix.print(tie[i]);
          delay(200);
        }

        matrix.setCursor(8,5);
        matrix.setTextColor(GREEN.to_333());
        for (int i = 0; i < 3; i++) {
          matrix.print(tie[i]);
          delay(200);
        }
        delay(500);
        
        matrix.setCursor(0,0);
        matrix.fillScreen(BLACK.to_333());
        
        setUpTTT();
        for (int gWs = greenWins * 5; gWs > 0; gWs--) {
            matrix.drawPixel(27, gWs, GREEN.to_333());
            matrix.drawPixel(28, gWs, GREEN.to_333());
        }
        for (int oWs = orangeWins * 5; oWs > 0; oWs--) {
            matrix.drawPixel(3, oWs, ORANGE.to_333());
            matrix.drawPixel(4, oWs, ORANGE.to_333());
        }
        totalChips = 0;
      }
    }
  }

  private:
  bool turn = true;
  DrawChoice choice;
  Piece pieces[3][3];
  int row = 0;
  int col = 0;
  int totalChips = 0;
  int greenWins = 0;
  int orangeWins = 0;
  
  bool checkRows() {
    for (int c = 0; c < 3; c++) {
      for (int r = 0; r < 3; r++) {
        if ((pieces[r][c].playr == pieces[r][c+1].playr) && (pieces[r][c].playr == pieces[r][c+2].playr) && (pieces[r][c+1].playr != 0)) {
          return true;
        }
      }
    }
    return false;
  }
  bool checkCols() {
    for (int r = 0; r < 3; r++) {
      for (int c = 0; c < 3; c++) {
        if ((pieces[r][c].playr == pieces[r+1][c].playr) && (pieces[r][c].playr == pieces[r+2][c].playr) && (pieces[r+1][c].playr != 0)) {
          return true;
        }
      }
    }
    return false;
  }
  bool checkDiags() {
    if ((pieces[0][0].playr == pieces[1][1].playr) && (pieces[0][0].playr == pieces[2][2].playr) && (pieces[0][0].playr != 0)) {
      return true;
    }
    if ((pieces[0][2].playr == pieces[1][1].playr) && (pieces[0][2].playr == pieces[2][0].playr) && (pieces[0][2].playr != 0)) {
      return true;
    }
    return false;
  }
  bool checkWin() {
    if (checkRows() || checkCols() || checkDiags()) {
      return true;
    }
    return false;
  }

  
};

TicTacToe ticTacToe;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON_PIN_NUMBER, INPUT);
  matrix.begin();
  matrix.fillScreen(BLACK.to_333());
      //scrolling text of TIC TAC TOE!
    matrix.setCursor(32,0);
    matrix.setTextSize(2);
    matrix.setTextColor(PURPLE.to_333());
    matrix.print("TIC TAC TOE!");
    delay(100);

    for(int q = 32; q > -425; q--) {
      matrix.fillScreen(BLACK.to_333());
      matrix.setCursor(q, 0);
      matrix.print("TIC TAC TOE!  FIRST TO 3 WINS");
      delay(10);
    }
    matrix.setCursor(0,0);
    matrix.fillScreen(BLACK.to_333());
  ticTacToe.setUpTTT();
}

void loop() {
  // put your main code here, to run repeatedly:
  int potentiometer_value = analogRead(POTENTIOMETER_PIN_NUMBER);
  bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER) == HIGH);

  ticTacToe.update(potentiometer_value, button_pressed);
}
