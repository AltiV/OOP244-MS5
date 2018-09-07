// Date: Tuesday, May 29th, 2018
// Author: Alan Vuong
// Seneca E-mail: avuong19@myseneca.ca
// Student Number: 149004178

#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H

#include <iostream>
#include <cstring>

using namespace std;

namespace AMA {
	class ErrorState {
		// Pointer that holds address of message
		char* msg;
	public:
		// Receives address of C-style null terminated string that holds error message
		// errorMessage = nullptr = safe empty state
		// errorMessage = "non-empty" = allocate memory for messsage and copies message to it
		explicit ErrorState(const char* errorMessage = nullptr);

		// Prevent copying of ErrorState object
		ErrorState(const ErrorState& em) = delete;

		// Prevent assignment of ErrorState object
		ErrorState& operator=(const ErrorState& em) = delete;

		// Function to de-allocate any dynamically allocated memory
		virtual ~ErrorState();

		// Function to clear any message stored by current object
		// Also sets object to safe empty state
		void clear();

		// Check if object is in safe empty state (returns true if empty)
		bool isClear() const;

		// Function to store copy of C-ctyle string pointed to by str
		// De-allocates any memory allocated to previously stored message
		// Allocates dynamic memory needed to store copy of str
		// Copies the string at address str to the allocated memory
		void message(const char* str);

		// Returns address of message stored in current object
		const char* message() const;
	};

	// Helper operator
	// If message exists, send ErrorState message to std::ostream object
	// If no message exists, do not send anything
	// Regardless, return reference to std::ostream object
	ostream& operator<<(ostream&, ErrorState&);
}

#endif