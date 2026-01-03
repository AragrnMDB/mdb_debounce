# mdb_debounce

This is an Arduino library that debounces an input.  

To use the functions in the library include the file mdb_debounce.h.  

## Constructors

There is one constructor that you can use to instantiate your debouncer. If not specified, 
inputType will default to INPUT_PULLUP. If not specified, debounceDelay will default to 20ms.
-  mdb_debounce(uint8_t input, uint8_t inputType=INPUT_PULLUP, unsigned long debounceDelay=20)

## Functions

There are two public functions available for your debouncer.
- void begin();                                                                // Resets the debounce timer and initializes variables
- bool inputState();                                                           // Debounced state of the input

## Sample code (turns on an output when a button is pressed, off when not pressed)

```` c++
    #include <mdb_debounce.h>                       // Include my debounce library

    uint8_t led               = 13;                 // Define the led pin
    uint8_t onButton          = 7;                  // Define the on button pin (pinmode set in debounce)
    mdb_debounce debouncedOn(onButton,  INPUT_PULLUP, 20); // Debounced input for onButton

    void setup() {                                  // Setup function runs once
      pinMode(led,    OUTPUT);
      digitalWrite(led, LOW);                       // Turn the led off
      debouncedOn.begin();
    }

    void loop() {
      if (debouncedOn.inputState()) {               // If the ON button is pressed
        digitalWrite(led, HIGH);
      } else {                                      // Else
        digitalWrite(led, LOW);
      }
    }
````

## Note:

The mdb_debounce library uses (depends on) the mdb_timer library.

## Remote repository

The remote repository for this project is hosted on GitHub at the following address: https://github.com/AragrnMDB/mdb_debounce.   
