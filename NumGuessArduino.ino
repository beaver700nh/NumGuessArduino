#include <LiquidCrystal.h>
#include <Keypad.h>

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#undef ENTER_KEY
#undef BKSPC_KEY
#undef QUITG_KEY
#undef NEXTB_KEY

const int ENTER_KEY = 'A';
const int BKSPC_KEY = 'B';
const int QUITG_KEY = 'C';
const int NEXTB_KEY = 'D';

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

Keypad kp(makeKeymap(KEYS), ROWPINS, COLPINS, ROWS, COLS);

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

int getGuess(void);
bool checkGuess(int *realnum, int guess);
void waitFor(char keyToWait);

void setup(void)
{
  randomSeed(analogRead(A0));

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("NumGuess");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  waitFor(NEXTB_KEY);
  lcd.clear();
}

void loop(void)
{
  int number = random(1, 1001);

  do
  {
    lcd.clear();
    lcd.print("Guess num 1-1000");

    input = getGuess();    
    match = checkGuess(&number, input);
  }
  while (!match);

  waitFor(NEXTB_KEY);
}

int getGuess(void)
{
  int curPos = 0;

  char guessedKey = '\0';
  char guessedNumber[5];

  while (true)
  {
    guessedKey = kp.getKey();

    if (isdigit(guessedKey) && curPos < 4)
    {
      lcd.setCursor(curPos, 1);
      lcd.print(guessedKey);

      guessedNumber[curPos] = guessedKey;
      guessedNumber[++curPos] = '\0';
    }
    else if (guessedKey == QUITG_KEY)
    {
      lcd.clear();
      lcd.print("You pressed QUIT");
      lcd.setCursor(0, 1);
      lcd.print("Program stopped.");

      while (true)
      {
        /* freeze; basically terminate program */;
      }
    }
    else if (guessedKey == BKSPC_KEY)
    { 
      guessedNumber[--curPos] = '\0';

      lcd.setCursor(curPos, 1);
      lcd.print(" ");
    }
    else if (guessedKey == ENTER_KEY)
    {
      break;
    }
  }

  int result = 0;

  for (int i = 0; i < curPos; ++i)
  {
    result = result * 10 + guessedNumber[i] - '0';
  }

  return result;
}

bool checkGuess(int *realnum, int guess)
{
  static int tries = 0;

  lcd.setCursor(0, 0);

  if (*realnum == guess)
  {
    lcd.print("Correct!        ");
    delay(1250);
    lcd.setCursor(0, 0);

    char triesStr[16];
    sprintf(triesStr, "Tries: %-9d", tries);

    lcd.print(triesStr);
    delay(1250);

    *realnum = random(1, 1001);

    tries = 0;
    return true;
  }
  else
  {
    ++tries;

    if (guess < 0 || guess > 1000)
    {
      lcd.print("Out of range.   ");
      delay(1250);
    }
    if (*realnum < guess)
    {
      lcd.print("Lower!          ");
      delay(1250);
    }
    if (*realnum > guess)
    {
      lcd.print("Higher!         ");
      delay(1250);
    }

    return false;
  }
}

void waitFor(char keyToWait)
{
  while (kp.getKey() != keyToWait)
  {
    /* wait for keyToWait to be pressed */;
  }
}
