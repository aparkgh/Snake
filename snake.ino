// libraries!
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

// pin stuff
int pinCS = 10;
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

// matrix initialisation
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

// game over message
String tape = "game over! :(";
int wait = 50;
int spacer = 1;
int width = 5 + spacer;

// snake stuff
int snakeX[64] = {0};   // snake's X positions
int snakeY[64] = {0};   // snake's Y positions
int snakeLength = 3;    // initial snake length
int foodX, foodY;       // food's position
int direction = 2;      // 0: up, 1: right, 2: down, 3: left
bool gameRunning = true;
int snakeLengthModified;

// button pins
int buttonUp = 3;
int buttonDown = 4;
int buttonLeft = 5;
int buttonRight = 2;
int buttonReset = 6;

// timing variables
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 150; // time interval between updates

bool isDisplayingGameOver = false; // track if game over message is being displayed
int justAte = 1;
unsigned long lastScrollTime = 0;  // timing for scrolling the message
int scrollIndex = 0;               // current scroll position

void spawnFood() {
  justAte = 1;
  foodX = random(0, matrix.width());
  foodY = random(0, matrix.height());
}

void setup() {
  matrix.setIntensity(7);
  matrix.fillScreen(LOW);
  matrix.write();

  // mapping panels to a 32x8 grid (horizontally)
  matrix.setRotation(0, 1);
  matrix.setRotation(1, 1);
  matrix.setRotation(2, 1);
  matrix.setRotation(3, 1);

  // button configurations
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  pinMode(buttonReset, INPUT_PULLUP);

  resetGame(); // initialising the game
}

void resetGame() {
  snakeLength = 3;
  direction = 1; 
  gameRunning = true;

  for (int i = 0; i < snakeLength; i++) {  // reset snake position
    snakeX[i] = 0;
    snakeY[i] = 0;
  }

  spawnFood(); // spawns a food pixel

  matrix.fillScreen(LOW); // clears display
  matrix.write(); // draws pixels
}

// checks for button inputs
void checkButtons() {
  if (digitalRead(buttonUp) == LOW && direction != 2) direction = 0;
  if (digitalRead(buttonDown) == LOW && direction != 0) direction = 2;
  if (digitalRead(buttonLeft) == LOW && direction != 1) direction = 3;
  if (digitalRead(buttonRight) == LOW && direction != 3) direction = 1;
}

// updates snake's position
void updateGame() {
  matrix.fillScreen(LOW);
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }
  if (direction == 0) snakeY[0]--;  // up
  if (direction == 1) snakeX[0]++;  // right
  if (direction == 2) snakeY[0]++;  // down
  if (direction == 3) snakeX[0]--;  // left

  // check edge collision
  if (snakeX[0] < 0 || snakeX[0] >= matrix.width() || snakeY[0] < 0 || snakeY[0] >= matrix.height()) {
    gameRunning = false;  // end the game
    return;
  }

  // check self-collision
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameRunning = false;  // end the game
      return;
    }
  }

  // check food collision
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength++; // add one to snake length
    spawnFood();  // spawn another food somewhere else
  }

  for (int i = 0; i < snakeLength - justAte; i++) {
    matrix.drawPixel(snakeX[i], snakeY[i], HIGH);
  }
  if (justAte == 1) justAte = 0; // fix i had to add to remove a stubborn pixel

  matrix.drawPixel(foodX, foodY, HIGH); // food position
  matrix.write(); // update the display
}

void loop() {
  if (digitalRead(buttonReset) == LOW) { // if reset button is pressed
    resetGame();  // reset game state
    isDisplayingGameOver = false; // stop the game over animation
    scrollIndex = 0; // reset scroll animation index
    delay(500);
    return;
  }

  // Handle game over state
  if (!gameRunning) {
    if (!isDisplayingGameOver) {
      // reset scrolling animation when game ends
      isDisplayingGameOver = true;
      scrollIndex = 0;
    }
    displayScrollingGameOverStep(); // scroll the message step-by-step
    return;
  }

  // Continuously check other buttons
  checkButtons();

  // Update the game at regular intervals
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;
    updateGame();
  }
}

void displayScrollingGameOverStep() {
  if (scrollIndex >= width * tape.length() + matrix.width() - 1 - spacer) {
    scrollIndex = 0;  // reset animation index
    isDisplayingGameOver = false;  // animation finished, ready for next reset
    return;  // stop further updates until re-triggered
  }

  matrix.fillScreen(LOW); // Clear the screen

  int letter = scrollIndex / width;  // determine which letter to display
  int x = (matrix.width() - 1) - scrollIndex % width; // x position of the character
  int y = (matrix.height() - 8) / 2;  // y position (centered vertically)

  while (x + width - spacer >= 0 && letter >= 0) {
    if (letter < tape.length()) {
      matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1); // draw character
    }
    letter--;
    x -= width; // move to the next character
  }

  matrix.write(); // update the display
  scrollIndex++;  // increment scroll position
  delay(wait);    // small delay for smooth scrolling
}