#define I0 A0
#define I1 A1
#define I2 A2
#define I3 A3
#define I4 A4
#define I5 A5
#define I6 0
#define I7 1

#define J0 2
#define J1 3
#define J2 4
#define J3 5
#define J4 6
#define J5 7
#define J6 8
#define J7 9

#define RED 10
#define BLUE 11
#define WHITE 12

#define MATRIX_SIZE 8
#define TETRIS_PIECES 7
#define ROTATIONS 4
#define CHARACTERS 2

unsigned char matrix[MATRIX_SIZE] = {158, 232, 11, 249, 34, 168, 0, 216};
unsigned char positions[TETRIS_PIECES] = { 1, 2, 2, 2, 4, 4, 4 };
unsigned char pieces[TETRIS_PIECES][ROTATIONS][CHARACTERS] =
{ { { 102, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
  { { 15, 0 }, { 34, 34 }, { 0, 0 }, { 0, 0 } },
  { { 3, 96 }, { 35, 16 }, { 0, 0 }, { 0, 0 } },
  { { 6, 48 }, { 19, 32 }, { 0, 0 }, { 0, 0 } },
  { { 7, 64 }, { 34, 48 }, { 23, 0 }, { 98, 32 } },
  { { 7, 16 }, { 50, 32 }, { 71, 0 }, { 34, 96 } },
  { { 7, 32 }, { 35, 32 }, { 39, 0 }, { 38, 32 } }
};

void setup() {
  pinMode(I0, OUTPUT);
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);
  pinMode(I5, OUTPUT);
  pinMode(I6, OUTPUT);
  pinMode(I7, OUTPUT);

  pinMode(J0, OUTPUT);
  pinMode(J1, OUTPUT);
  pinMode(J2, OUTPUT);
  pinMode(J3, OUTPUT);
  pinMode(J4, OUTPUT);
  pinMode(J5, OUTPUT);
  pinMode(J6, OUTPUT);
  pinMode(J7, OUTPUT);

  pinMode(RED, INPUT);
  pinMode(BLUE, INPUT);
  pinMode(WHITE, INPUT);

  digitalWrite(I0, LOW);
  digitalWrite(I1, LOW);
  digitalWrite(I2, LOW);
  digitalWrite(I3, LOW);
  digitalWrite(I4, LOW);
  digitalWrite(I5, LOW);
  digitalWrite(I6, LOW);
  digitalWrite(I7, LOW);
  digitalWrite(J0, LOW);
  digitalWrite(J1, LOW);
  digitalWrite(J2, LOW);
  digitalWrite(J3, LOW);
  digitalWrite(J4, LOW);
  digitalWrite(J5, LOW);
  digitalWrite(J6, LOW);
  digitalWrite(J7, LOW);
}

void turnOnLed(unsigned char row, unsigned char col) {
  if (row == 0) {
    digitalWrite(I0, HIGH);
  }
  if (row == 1) {
    digitalWrite(I1, HIGH);
  }
  if (row == 2) {
    digitalWrite(I2, HIGH);
  }
  if (row == 3) {
    digitalWrite(I3, HIGH);
  }
  if (row == 4) {
    digitalWrite(I4, HIGH);
  }
  if (row == 5) {
    digitalWrite(I5, HIGH);
  }
  if (row == 6) {
    digitalWrite(I6, HIGH);
  }
  if (row == 7) {
    digitalWrite(I7, HIGH);
  }

  if (col == 0) {
    digitalWrite(J0, HIGH);
  }
  if (col == 1) {
    digitalWrite(J1, HIGH);
  }
  if (col == 2) {
    digitalWrite(J2, HIGH);
  }
  if (col == 3) {
    digitalWrite(J3, HIGH);
  }
  if (col == 4) {
    digitalWrite(J4, HIGH);
  }
  if (col == 5) {
    digitalWrite(J5, HIGH);
  }
  if (col == 6) {
    digitalWrite(J6, HIGH);
  }
  if (col == 7) {
    digitalWrite(J7, HIGH);
  }
}

void turnOffLed(unsigned char row, unsigned char col) {
  if (row == 0) {
    digitalWrite(I0, LOW);
  }
  if (row == 1) {
    digitalWrite(I1, LOW);
  }
  if (row == 2) {
    digitalWrite(I2, LOW);
  }
  if (row == 3) {
    digitalWrite(I3, LOW);
  }
  if (row == 4) {
    digitalWrite(I4, LOW);
  }
  if (row == 5) {
    digitalWrite(I5, LOW);
  }
  if (row == 6) {
    digitalWrite(I6, LOW);
  }
  if (row == 7) {
    digitalWrite(I7, LOW);
  }

  if (col == 0) {
    digitalWrite(J0, LOW);
  }
  if (col == 1) {
    digitalWrite(J1, LOW);
  }
  if (col == 2) {
    digitalWrite(J2, LOW);
  }
  if (col == 3) {
    digitalWrite(J3, LOW);
  }
  if (col == 4) {
    digitalWrite(J4, LOW);
  }
  if (col == 5) {
    digitalWrite(J5, LOW);
  }
  if (col == 6) {
    digitalWrite(J6, LOW);
  }
  if (col == 7) {
    digitalWrite(J7, LOW);
  }
}

void printMatrixAndPiece(char xCoord, char yCoord, unsigned char currentPiece, unsigned char currentRotation) {
  for (unsigned char i = 0; i < 8; ++i) {
    for (unsigned char j = 0; j < 8; ++j) {
      if (matrix[i] & 1 << j) {
        turnOnLed(i, MATRIX_SIZE - 1 - j);
        turnOffLed(i, MATRIX_SIZE - 1 - j);
      }
    }
  }
  for (char i = 0; i < 8; ++i) {
    char tempX = i % 4 + xCoord;
    char tempY = i / 4 + yCoord;
    if (pieces[currentPiece][currentRotation][0] & 1 << (MATRIX_SIZE - 1 - i)) {
      turnOnLed(tempY, tempX);
      turnOffLed(tempY, tempX);
    }
  }
  for (char i = 0; i < 8; ++i) {
    char tempX = i % 4 + xCoord;
    char tempY = i / 4 + yCoord + 2;
    if (pieces[currentPiece][currentRotation][1] & 1 << (MATRIX_SIZE - 1 - i)) {
      turnOnLed(tempY, tempX);
      turnOffLed(tempY, tempX);
    }
  }
}

bool checkPosition(char xCoord, char yCoord, unsigned char currentPiece, unsigned char currentRotation) {
  bool switchChar = false;
  char x = xCoord;
  char y = yCoord;
  char iter = 7;
  char iter2 = MATRIX_SIZE - (xCoord + 1);
  unsigned char adder = 0;
  unsigned char currentChar = pieces[currentPiece][currentRotation][0];

  while (iter >= 0) {
    char tempIter = (MATRIX_SIZE - 1) - iter;
    if (currentChar & 1 << iter) {
      if (matrix[y] & 1 << iter2) {
        return false;
      }
      if ((tempIter % 4) + xCoord < 0 || (tempIter % 4) + xCoord >= MATRIX_SIZE) {
        return false;
      }
      if ((tempIter / 4) + yCoord + adder < 0 || (tempIter / 4) + yCoord + adder >= MATRIX_SIZE) {
        return false;
      }
    }
    ++x;
    --iter2;
    if (x > xCoord + 3) {
      ++y;
      x = xCoord;
      iter2 = MATRIX_SIZE - (xCoord + 1);
    }
    --iter;
    if (!switchChar && iter < 0) {
      iter = 7;
      adder = 2;
      switchChar = true;
      iter2 = MATRIX_SIZE - (xCoord + 1);
      currentChar = pieces[currentPiece][currentRotation][1];
    }
  }
  return true;
}

void addPieceToMatrix(char xCoord, char yCoord, unsigned char currentPiece, unsigned char currentRotation) {
  for (char i = 0; i < 8; ++i) {
    char tempX = i % 4 + xCoord;
    char tempY = i / 4 + yCoord;
    if (pieces[currentPiece][currentRotation][0] & 1 << (MATRIX_SIZE - 1 - i)) {
      matrix[tempY] = matrix[tempY] | 1 << (MATRIX_SIZE - 1 - tempX);
    }
  }
  for (char i = 0; i < 8; ++i) {
    char tempX = i % 4 + xCoord;
    char tempY = i / 4 + yCoord + 2;
    if (pieces[currentPiece][currentRotation][1] & 1 << (MATRIX_SIZE - 1 - i)) {
      matrix[tempY] = matrix[tempY] | 1 << (MATRIX_SIZE - 1 - tempX);
    }
  }
}

void applyGravity() {
  unsigned char newMatrix[MATRIX_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};
  char positionToWrite = MATRIX_SIZE - 1;
  for (char i = MATRIX_SIZE - 1; i >= 0; --i) {
    if (matrix[i] > 0) {
      newMatrix[positionToWrite--] = matrix[i];
    }
  }
  for (char i = 0; i < MATRIX_SIZE; ++i) {
    matrix[i] = newMatrix[i];
  }
}

void removeCompletedRows() {
  for (char i = 0; i < MATRIX_SIZE; ++i) {
    if (matrix[i] == 255) {
      matrix[i] = 0;
    }
  }
  applyGravity();
}

void resetGame() {
  for (int i = 0; i < MATRIX_SIZE; ++i) {
    matrix[i] = 0;
  }
}

void printMatrix() {
  for (unsigned char i = 0; i < 8; ++i) {
    for (unsigned char j = 0; j < 8; ++j) {
      if (matrix[i] & 1 << j) {
        turnOnLed(i, MATRIX_SIZE - 1 - j);
        turnOffLed(i, MATRIX_SIZE - 1 - j);
      }
    }
  }
}

void startGame() {
  //select piece
  char xCoord;
  char yCoord;
  unsigned char currentRotation;
  unsigned char currentPiece;
  unsigned int iterator = 0;
  while (++iterator < 2000 || (digitalRead(BLUE) == HIGH)) {
    printMatrix();
  }
  iterator = 0;
  resetGame();
  while (1) {
    currentPiece = random(TETRIS_PIECES);
    currentRotation = 0;
    xCoord = 2;
    yCoord = 0;
    iterator = 0;
    unsigned int pieceIterator = 700;
    if (!checkPosition(xCoord, yCoord, currentPiece, currentRotation)) {
      break;
    }
    while (checkPosition(xCoord, yCoord + 1, currentPiece, currentRotation)) {
      iterator = 0;
      while (++iterator < 2800) {
        printMatrixAndPiece(xCoord, yCoord, currentPiece, currentRotation);
        if (pieceIterator < 700) {
          pieceIterator++;
          continue;
        }
        if (digitalRead(RED) == HIGH) {
          if (checkPosition(xCoord - 1, yCoord, currentPiece, currentRotation)) {
            xCoord--;
          }
          pieceIterator = 0;
          continue;
        }
        if (digitalRead(BLUE) == HIGH) {
          char tempRotation = currentRotation + 1;
          if (tempRotation == positions[currentPiece]) {
            tempRotation = 0;
          }
          if (checkPosition(xCoord - 1, yCoord, currentPiece, tempRotation)) {
            currentRotation = tempRotation;
          }
          pieceIterator = 0;
          continue;
        }
        if (digitalRead(WHITE) == HIGH) {
          if (checkPosition(xCoord + 1, yCoord, currentPiece, currentRotation)) {
            xCoord++;
          }
          pieceIterator = 0;
          continue;
        }
      }
      yCoord++;
    }
    addPieceToMatrix(xCoord, yCoord, currentPiece, currentRotation);
    removeCompletedRows();
  }
  while (digitalRead(BLUE) == LOW) {
    printMatrix();
  }
  resetGame();
}

void loop() {
  startGame();
}

























