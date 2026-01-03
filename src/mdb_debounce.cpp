#include "Arduino.h"
#include "mdb_debounce.h"
#include "mdb_timer.h"

void mdb_debounce::begin() {
	_debounceTimer.resetTimer();                                        // Reset the timer
    _inputState = false;                          			            // Initialize the input state as LOW
    _lastInputState = false;                                            // Initialize the last input state as LOW
	pinMode(_input, _inputType);
}

boolean mdb_debounce::inputState(){                                     // Public function to return the debounced input state
	if (_inputState) {                                                  // If we're currently reporting true
		if (digitalRead(_input)) {                                      // If the digital input is HIGH
			if (_lastInputState == false) {					            // If the digital input was HIGH last time
				if (_debounceTimer.readTimer() >= _debounceDelay) {     // See if digital input has been HIGH for the debounce delay
					_inputState = false;                                // If it has, set the input state to HIGH
				}
			} else {                                                    // If the last input state was not HIGH
				_debounceTimer.resetTimer();                            // Reset the timer
				_lastInputState = false;                                // Set the last input state to HIGH
			}
		} else {                                                        // If the digital input is LOW
			_lastInputState = true;                                     // Set the last input state to LOW
		}
	} else {                                                            // If we're currently reporting HIGH
		if (!digitalRead(_input)) {                                     // If the digital input is LOW
			if (_lastInputState == true)	{			       	        // If the digital input was LOW last time
				if (_debounceTimer.readTimer() >= _debounceDelay) {     // See if digital input has been LOW for the debounce delay
					_inputState = true;                                 // If it has, set the input state to LOW
				}
			}
			else {                                                      // If the last input state was HIGH
				_debounceTimer.resetTimer();                            // Reset the timer
				_lastInputState = true;                                 // Set the last input state to LOW
			}
		} else {                                                        // If the digital input is HIGH
			_lastInputState = false;                                    // Set the last input state to HIGH
		}
	}
	return _inputState;											        // Return the debounced input state
}
