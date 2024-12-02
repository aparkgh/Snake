#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10;
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

int snakeX[64] = {0}; // Snake's X positions
int snakeY[64] = {0}; // Snake's Y positions
int snakeLength = 3; // Initial snake length
int foodX, foodY; // Food position
int direction = 2; // 0: up, 1: right, 2: down, 3: left
bool gameRunning = true;

int matrixWidth = numberOfHorizontalDisplays * 8; // Total width of the matrix
int matrixHeight = numberOfVerticalDisplays * 8; // Total height of the matrix
// Button pins
int buttonUp = 3;
int buttonDown = 4;
int buttonLeft = 5;
int buttonRight = 2;

void spawnFood() {
  foodX = random(0, matrix.width());
  foodY = random(0, matrix.height());
}

void setup() {
  Serial.begin(9600); // baud rate
  matrix.setIntensity(7);
  matrix.fillScreen(LOW);
  matrix.write();

  Serial.print("Matrix width: ");
  Serial.println(matrix.width());
  Serial.print("Matrix height: ");
  Serial.println(matrix.height());

  // Initialize snake position
  for (int i = 0; i < snakeLength; i++) {
    snakeX[i] = i;
    snakeY[i] = 0;
  }

  // Spawn the first food
  spawnFood();

  // Configure buttons
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
}

void loop() {
  if (!gameRunning) {
    matrix.fillScreen(LOW);
    matrix.write();
    delay(1000);
    return;
  }

  // Check button input
  if (digitalRead(buttonUp) == LOW && direction != 2) direction = 0;
  if (digitalRead(buttonDown) == LOW && direction != 0) direction = 2;
  if (digitalRead(buttonLeft) == LOW && direction != 1) direction = 3;
  if (digitalRead(buttonRight) == LOW && direction != 3) direction = 1;

  // Move the snake
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }
  if (direction == 0) snakeY[0]--;       // Up
  if (direction == 1) snakeX[0]++;       // Right
  if (direction == 2) snakeY[0]++;       // Down
  if (direction == 3) snakeX[0]--;       // Left

  // Check boundaries
  if (snakeX[0] < 0 || snakeX[0] >= numberOfHorizontalDisplays * 8 || 
      snakeY[0] < 0 || snakeY[0] >= numberOfVerticalDisplays * 8) {
    gameRunning = false; // Game over
    return;
  }

  // Check self-collision
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameRunning = false; // Game over
      return;
    }
  }

  // Check food collision
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength++;
    spawnFood();
  }

  // Update the display
  matrix.fillScreen(LOW);
  for (int i = 0; i < snakeLength; i++) {
    matrix.drawPixel(snakeX[i], snakeY[i], HIGH);
  }
  matrix.drawPixel(foodX, foodY, HIGH); // Draw food
  matrix.write();

  delay(200); // Adjust speed
}
