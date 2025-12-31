#ifndef mdb_debounce_h
#define mdb_debounce_h

#include "mdb_timer.h"

class mdb_debounce {
   public:
      mdb_debounce(uint8_t input, uint8_t inputType, unsigned long debounceDelay); // Constructor - input, inputType and debounce delay
      mdb_debounce(uint8_t input, uint8_t inputType);                              // Constructor - input and inputType (defaults debounce delay to 20ms)
      void begin();                                                                // Start debouncing
      bool inputState();                                                           // Debounced state of the input
   private:
      uint8_t       _input;
      uint8_t       _inputType;
      unsigned long _debounceDelay;
      bool          _inputState;
      bool          _lastInputState;
      mdb_timer     _debounceTimer;
};

#endif