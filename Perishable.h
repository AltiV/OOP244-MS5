// Date: Wednesday, August 8th, 2018
// Author: Alan Vuong
// Seneca E-mail: avuong19@myseneca.ca
// Student Number: 149004178

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H

#include <iostream>
#include <fstream>
#include "Date.h"
#include "Product.h"

namespace AMA {
	class Perishable : public Product {
		Date date;
	public:
		// No argument constructor
		Perishable();

		// Stores a single file record for current object
		std::fstream& store(std::fstream& file, bool newLine = true) const;

		// Extracts the data fields for a single record from the fstream object
		std::fstream& load(std::fstream& file);

		// Passes the saved variables into a readable format
		std::ostream& write(std::ostream& os, bool linear) const;

		// Populates current object with data extracted from istream object
		std::istream& read(std::istream& is);

		// Returns expiry date for perishable product
		const Date& expiry() const;
	};
}

#endif