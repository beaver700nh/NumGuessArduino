#include <LiquidCrystal.h>
#include <Keypad.h>

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#undef ENTER_KEY

const int ENTER_KEY = '#';

int realn = 0;
int input = 0;
bool match = false;

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

/*
 * TODO:
 * > add delete feature
 * > add giveup feature
 */

int getGuess(void);

void setup(void)
{
  randomSeed(analogRead(A0));

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("NumGuess");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(1000);
  lcd.clear();
}

void loop(void)
{
  do
  {
    input = getGuess();
    match = checkGuess(input);
  }
  while (!match);

//  lcd.setCursor(0, 0);
//  lcd.print("Guess num 1-1000");
//
//  for (int i = 0; i < 4; ++i)
//  {
//    inputn = getGuess(i);
//
//    lcd.setCursor(i, 1);
//    lcd.print(inputn);
//  }
}

int getGuess(void)
{
  int curPos = 0;

  char guessedKey = ' ';
  char guessedNumber[5];

  bool valid;

  do
  {
    guessedKey = key.getKey();

    valid = isdigit(guessedKey) || (guessedKey == ENTER_KEY && curPos > 0);

    if (!valid)
    {
      continue
    }

    if (guessedKey == ENTER_KEY)
    {
      if 
    }
    else if (guessedKey == BKSPC_KEY)
    {
      guessedNumber[--curPos] = ' ';
    }
    else if (

    /*
     * getKey
     * checkVal
     * if not valid continue
     * check keys
     * store val
     * 
     */
  }
  while (!done)

//  char guessedKey = '\0';
//  static bool enterKeyPressed = false;
//  static int numbersEntered = 0;
//
//  do
//  {
//    guessedKey = key.getKey();
//  }
//  while (!(isdigit(guessedKey) || (guessedKey == ENTER_KEY && i != 0)));
//
//  if (guessedKey == ENTER_KEY)
//  {
//    enterKeyPressed = true;
//  }
//  else
//  {
//    guessedKey -= '0';
//    ++numbersEntered;
//  }
//
//  if (i == 4 && !enterKeyPressed)
//  {
//    while (key.getKey() != ENTER_KEY)
//    {
//      /* wait for ENTER */;
//    }
//  }
//
//  return guessedKey;
}

bool checkGuess(int guess)
{
  
  return false;
}
