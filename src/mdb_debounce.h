#ifndef mdb_debounce_h
#define mdb_debounce_h

#include "mdb_timer.h"

#define RISING  1
#define FALLING 2

class mdb_debounce {
   public:
      mdb_debounce(uint8_t input, uint8_t inputType=INPUT_PULLUP, unsigned long debouceDelay=20)
	       : _input(input), _inputType(inputType), _debounceDelay(debouceDelay) {}  // Constructor with defaults for parameters not specified
      void begin();                                                                // Start debouncing
      bool debouncedInput();                                                       // Debounced state of the input
      bool momentaryInput();
      bool toggleInput(uint8_t edge);
   private:
      uint8_t       _input;
      uint8_t       _inputType;
      unsigned long _debounceDelay;
      bool          _physicalInput;
      bool          _logicalInput;
      bool          _lastLogicalInput;
      bool          _debouncedInput;
      mdb_timer     _debounceTimer;
      bool          _toggleInput;
      bool          _lastToggleInput;
      bool          _toggleOutput;
      uint8_t       _edge;
};

#endif