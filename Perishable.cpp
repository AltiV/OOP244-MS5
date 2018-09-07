// Date: Wednesday, August 8th, 2018
// Author: Alan Vuong
// Seneca E-mail: avuong19@myseneca.ca
// Student Number: 149004178

#include "Perishable.h"

namespace AMA {
	// No argument constructor (sets product code to 'P' for perishable in Product class)
	Perishable::Perishable() : Product('P') {
	}

	// Stores a single file record for current object
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		// Call the store function in Product class with a false for newLine to make potential room
		Product::store(file, false);
		file << "," << expiry();
		if (newLine) {
			file << endl;
		}
		return file;
	}

	// Extracts the data fields for a single record from the fstream object
	std::fstream& Perishable::load(std::fstream& file) {
		Product::load(file);
		date.read(file);
		file.ignore();
		return file;
	}

	// Passes the saved variables into a readable format
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		Product::write(os, linear);
		if (err.isClear()) {
			if (linear) {
				os << expiry();
			}
			else {
				os << endl << " Expiry date: " << expiry();
			}
		}
		return os;
	}

	// Populates current object with data extracted from istream object
	std::istream& Perishable::read(std::istream& is) {
		Date expiry;

		Product::read(is);

		// If the Product has validated, check the date
		if (Product::isClear()) {
			cout << " Expiry date (YYYY/MM/DD): ";
			expiry.read(is);

			if (expiry.bad()) {
				is.istream::setstate(std::ios::failbit);

				// Different scenarios for the error message depending on bad input
				switch (expiry.errCode()) {
				case 1: err.message("Invalid Date Entry"); break;
				case 2: err.message("Invalid Year in Date Entry"); break;
				case 3: err.message("Invalid Month in Date Entry"); break;
				case 4: err.message("Invalid Day in Date Entry"); break;
				}
			}
			// If date is valid, save variable
			else {
				date = expiry;
				is.istream::fail();
			}
		}
		return is;
	}

	// Returns expiry date for perishable product
	const Date& Perishable::expiry() const {
		return date;
	}
}