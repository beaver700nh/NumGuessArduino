#include <LiquidCrystal.h>
#include <Keypad.h>

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#undef ENTER_KEY

const int ENTER_KEY = '#';

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

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

char getGuess(int i);

void setup(void)
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("NumGuess");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(1500);
  lcd.clear();
}

void loop(void)
{
  lcd.setCursor(0, 0);
  lcd.print("Guess num 1-1000");

  number = random(1, 1001);

  for (int i = 0; i < 4; ++i)
  {
    inputn = getGuess(i);

    lcd.setCursor(0, i + 1);
    lcd.print(inputn);
  }
}

char getGuess(int i)
{
  char guessedKey = '\0';
  static bool enterKeyPressed = false;
  static int numbersEntered = 0;

  do
  {
    guessedKey = key.getKey();
  }
  while (!isdigit(guessedKey) || (guessedKey != ENTER_KEY && i != 0));

  if (guessedKey == ENTER_KEY)
  {
    enterKeyPressed = true;
  }
  else
  {
    guessedKey -= '0';
    ++numbersEntered;
  }

  if (i == 4 && !enterKeyPressed)
  {
    while (key.getKey() != ENTER_KEY)
    {
      /* wait for ENTER */;
    }
  }

  return guessedKey;
}
