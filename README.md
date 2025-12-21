# mdb_debounce


This is an Arduino library that debounces an input.  

To use the functions in the library include the file mdb_debounce.h.  

## Constructors

There are two constructors that you can use to instantiate your debouncer.
- mdb_debounce(uint8_t input, uint8_t inputType, unsigned long debounceDelay); // Constructor - input, inputType and debounce delay
- mdb_debounce(uint8_t input, uint8_t inputType);                              // Constructor - input and inputType (defaults debounce delay to 20ms)

## Functions

There is one public function available for your debouncer.
- bool inputState();                                                           // Debounced state of the input

## Sample code (blinks the on-board led once per second)

```` c++
    #include <mdb_debounce.h>                       // Include my debounce library

    uint8_t led               = 13;                 // Define the led pin
    uint8_t onButton          = 7;                  // Define the on button pin (pinmode set in debounce)
    mdb_debounce debouncedOn(onButton,  INPUT_PULLUP, 20); // Debounced input for onButton

    void setup() {                                  // Setup function runs once
      pinMode(led,    OUTPUT);
      digitalWrite(led, LOW);                       // Turn the led off
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
