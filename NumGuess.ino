#include <LiquidCrystal.h>
#include <Keypad.h>

const int ENTER_KEY = '#';

int pressedKey;

int number;
int inputn;

char usrgue[4];

const byte ROWS = 4, COLS = 4;

char KEYS[ROWS][COLS] = {
  {'1', '2', '3', 'A',},
  {'4', '5', '6', 'B',},
  {'7', '8', '9', 'C',},
  {'*', '0', '#', 'D',},
};

byte ROWPINS[ROWS] = { 28, 29, 30, 31 };
byte COLPINS[COLS] = { 32, 33, 34, 35 };

Keypad key(makeKeymap(KEYS), ROWPINS, COLPINS, ROWS, COLS);

const int RS = 22, EN = 23, DA = 24, DB = 25, DC = 26, DD = 27;

LiquidCrystal lcd(RS, EN, DA, DB, DC, DD);

int getGuess(void);
bool keyIsValid(int keyToCheck, int iterator);

void setup(void) {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("NumGuess");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(1500);
  lcd.clear();
}

void loop(void) {
  lcd.setCursor(0, 0);
  lcd.print("Guess num 1-1000");

  number = random(1, 1001);
  inputn = getGuess();

  if (inputn == -1)
  {
    lcd.setCursor(0, 1);
    lcd.print("FATAL ERROR");
    delay(1000);
    return;
  }

  sprintf(usrgue, "%-4d", inputn);

  lcd.setCursor(0, 1);
  lcd.print(usrgue);
}

int getGuess(void)
{
  char guessDigits[4] = { '.', '.', '.', '.', };
  bool enterKeyPressed = false;
  int numbersEntered = 0;

  for (int i = 0; i < 4; ++i)
  {
    while (!keyIsValid((pressedKey = key.getKey()), i));

    if (pressedKey == ENTER_KEY)
    {
      enterKeyPressed = true;
      break;
    }

    guessDigits[i] = pressedKey - '0';
    ++numbersEntered;
  }

  if (!enterKeyPressed)
  {
    while ((pressedKey = key.getKey()) != ENTER_KEY)
    {
      /* wait for ENTER */;
    }
  }

  int result = 0;

  for (int j = 0; j < numbersEntered; ++j)
  {
    if (guessDigits[j] != '.')
    {
      result = result * 10 + guessDigits[j];
    }
  }

  return result;
}

bool keyIsValid(int keyToCheck, int iterator)
{
  return (keyToCheck >= '0' && keyToCheck <= '9') || \
         (keyToCheck == ENTER_KEY && iterator != 0) || \
         (keyToCheck == '*') || \
         (keyToCheck == 'A' || keyToCheck == 'B');
}
