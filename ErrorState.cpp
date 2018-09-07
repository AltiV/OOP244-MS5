// Date: Tuesday, May 29th, 2018
// Author: Alan Vuong
// Seneca E-mail: avuong19@myseneca.ca
// Student Number: 149004178

#include "ErrorState.h"

using namespace std;

namespace AMA {
	// Receives address of C-style null terminated string that holds error message
	// errorMessage = nullptr = safe empty state
	// errorMessage = "non-empty" = allocate memory for messsage and copies message to it
	ErrorState::ErrorState(const char* errorMessage) {
		if (errorMessage == nullptr) {
			clear();
		}
		else {
			msg = new char[strlen(errorMessage) + 1];
			strncpy(msg, errorMessage, strlen(errorMessage));
			msg[strlen(errorMessage)] = '\0';
		}
	}

	// Function to de-allocate any dynamically allocated memory
	ErrorState::~ErrorState() {
		delete[] msg;
		clear();
	}

	// Function to clear any message stored by current object
	// Also sets object to safe empty state
	void ErrorState::clear() {
		msg = nullptr;
	}

	// Check if object is in safe empty state (returns true if empty)
	bool ErrorState::isClear() const {
		return (msg == nullptr);
	}

	// Function to store copy of C-style string pointed to by str
	// De-allocates any memory allocated to previously stored message
	// Allocates dynamic memory needed to store copy of str
	// Copies the string at address str to the allocated memory
	void ErrorState::message(const char* str) {
		delete[] msg;
		msg = new char[strlen(str) + 1];
		strncpy(msg, str, strlen(str));
		msg[strlen(str)] = '\0';
	}

	// Returns address of message stored in current object
	const char* ErrorState::message() const {
		return msg;
	}

	// Helper operator
	// If message exists, send ErrorState message to std::ostream object
	// If no message exists, do not send anything
	// Regardless, return reference to std::ostream object
	ostream& operator<<(ostream& os, ErrorState& errorMessage) {
		if (!errorMessage.isClear()) {
			os << errorMessage.message();
		}
		return os;
	}
}