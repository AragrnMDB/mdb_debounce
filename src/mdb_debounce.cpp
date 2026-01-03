#include "Arduino.h"
#include "mdb_debounce.h"
#include "mdb_timer.h"

void mdb_debounce::begin() {
	_debounceTimer.resetTimer();                                        // Reset the timer
    _logicalInput = false;                          			        // Initialize the input state as LOW
    _lastLogicalInput = false;                                          // Initialize the last input state as LOW
	_toggleInput = false;
	_lastToggleInput = false;
	_toggleOutput = false;
	_edge = RISING;
	pinMode(_input, _inputType);                                        // Set the pinMode for the input
}

bool mdb_debounce::momentaryInput() {
	return debouncedInput();
}

bool mdb_debounce::toggleInput(uint8_t edge) {
	_edge = edge;
	_toggleInput = debouncedInput();
	if (_toggleInput != _lastToggleInput) {
		if (_toggleInput and !_lastToggleInput and _edge == RISING) {
			_toggleOutput = !_toggleOutput;
		}
		if (!_toggleInput and _lastToggleInput and _edge == FALLING) {
			_toggleOutput = !_toggleOutput;
		}
		_lastToggleInput = _toggleInput;
	}
	return _toggleOutput;
}

bool mdb_debounce::debouncedInput() {
	// Read the physical input
	_physicalInput = digitalRead(_input);
	// Convert the physical input into a logical input
	if (_physicalInput) {
		if (_inputType == INPUT_PULLUP) {
			_logicalInput = false;
		} else {
			_logicalInput = true;
		}
	} else {
		if(_inputType == INPUT_PULLUP) {
			_logicalInput = true;
		} else {
			_logicalInput = false;
		}
	}
	// See the logical state has been constant long enough to change the debounced state
	if (_logicalInput) {
		if (!_lastLogicalInput) {
			_lastLogicalInput = true;
			_debounceTimer.resetTimer();                                // Reset the timer
		}
		if (_debounceTimer.readTimer() >= _debounceDelay) {             // See if the logical input has been constant for the debounce delay
			_debouncedInput = true;
		}
	} else {
		if(_lastLogicalInput) {
			_lastLogicalInput = false;
			_debounceTimer.resetTimer();                                // Reset the timer
		}
		if (_debounceTimer.readTimer() >= _debounceDelay) {             // See if the logical input has been constant for the debounce delay
			_debouncedInput = false;
		}
	}
	return _debouncedInput;
}