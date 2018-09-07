// Date: Friday, August 3rd, 2018
// Author: Alan Vuong
// Seneca E-mail: avuong19@myseneca.ca
// Student Number: 149004178

#ifndef AMA_IPRODUCT_H
#define AMA_IPRODUCT_H
#include <iostream>
#include <fstream>

namespace AMA {
	class iProduct {
	public:
		// Function to de-allocate any dynamically allocated memory
		virtual ~iProduct() {};

		// Inserts the product information into the given file
		virtual std::fstream& store(std::fstream& file, bool newLine = true) const = 0;

		// Extracts fields from fstream object, creates temporary object, and assigns it to current object
		virtual std::fstream& load(std::fstream& file) = 0;

		// Inserts data fields into ostream object
		virtual std::ostream& write(std::ostream& os, bool linear) const = 0;

		// Extracts data fields for current object to be copy assigned to current object
		// Stops receiving input if there is any input that doesn't match the expected data types
		virtual std::istream& read(std::istream& is) = 0;

		// Returns true if string is identical to sku of object
		virtual	bool operator==(const char*) const = 0;

		// Returns total cost of all items on hand
		virtual	double total_cost() const = 0;

		// Returns name of product
		virtual const char* name() const = 0;

		// Returns number of units of product that are on hand
		virtual void quantity(int) = 0;

		// Returns number of units of product that are needed
		virtual int qtyNeeded() const = 0;

		// Resets number of units on hand to number received
		virtual int quantity() const = 0;

		// Adds given number to number of units on hand (only if integer received is positive-valued)
		virtual int operator+=(int) = 0;

		// Returns true if name of current object is greater than name of referenced product
		virtual bool operator>(const iProduct&) const = 0;

	};
	// Extract given iProduct record from istream
	std::ostream& operator<<(std::ostream&, const iProduct&);

	// Insert given Product record into ostream
	std::istream& operator>>(std::istream&, iProduct&);
	
	// Adds given number to number of units on hand (only if integer received is positive-valued
	double operator+=(double&, const iProduct&);

	// Returns address of Product object
	iProduct* CreateProduct();
	
	// Returns address of Perishable object
	iProduct* CreatePerishable();
}

#endif