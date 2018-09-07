// Date: Wednesday, May 30th, 2018
// Author: Alan Vuong
// Seneca E-mail: avuong19@myseneca.ca
// Student Number: 149004178

#include "Product.h"
#define filename "ms3.txt"

namespace AMA {
	/*//////////////////////////////
	Protected Member Functions
	//////////////////////////////*/

	// Overwrite the existing name with the name passed through the function
	void Product::name(const char* nameF) {
		// Make sure that the existing name is valid before deleting it
		if (nameV != nullptr) {
			delete nameV;
			// Make sure that the passed name is valid before copying it
			if (nameF != nullptr) {
				// Checks to make sure the passed name's length isn't longer than what is set for max_name_length constant
				// If it does, cap the length to that constant
				nameV = (strlen(nameF + 1) < max_sku_length) ? new char[strlen(nameF + 1)] : new char[max_sku_length + 1];
				(strlen(nameF + 1) < max_sku_length) ? strncpy(nameV, nameF, strlen(nameF + 1)) : strncpy(nameV, nameF, max_sku_length);
				nameV[strlen(nameV)] = '\0';
			}
		}
	}

	// Next three functions have a check to return a 0 if fields are blank, specifically so garbage isn't printed if user also prints garbage
	// This is important by means of the load() function so the file can read proper values

	// Returns name of product. Does NOT return a potential nullptr as requested by instructions, as this will crash the program if you input gibberish
	const char* Product::name() const {
		return (nameV != nullptr) ? nameV : "0";
	}

	// Returns sku of product
	const char* Product::sku() const {
		return (strlen(skuV) > 0 ? skuV : "0");
	}

	// Returns unit of product
	const char* Product::unit() const {
		return (strlen(unitV) > 0 ? unitV : "0");
	}

	// Returns taxable status of product
	bool Product::taxed() const {
		return taxable;
	}

	// Returns price of single item of product
	double Product::price() const {
		return priceV;
	}

	// Returns price of single item of product plus tax
	double Product::cost() const {
		return (priceV * (1 + TAX));
	}

	// Returns error message and stores it in ErrorState object
	void Product::message(const char* errMsg) {
		err.message(errMsg);
	}

	// Returns boolean of ErrorState object to check if no messages
	bool Product::isClear() const {
		return err.isClear();
	}

	/*//////////////////////////////
	Public Member Functions
	//////////////////////////////*/

	// Zero-one argument constructor
	Product::Product(const char product) {
		pTypeV = product;
		skuV[0] = '\0';
		unitV[0] = '\0';
		nameV = nullptr;
		qtyHand = 0;
		qtyNeed = 0;
		priceV = 0.0;
		taxable = 0;
	}

	// Seven argument constructor
	Product::Product(const char* skuC, const char* nameC, const char* unitC, int qtyHandC, bool taxableC, double priceC, int qtyNeedC) {
		// Check to see if object is valid before copying information
		if (strlen(skuC) > 0) {
			strncpy(skuV, skuC, max_sku_length);
			skuV[strlen(skuC)] = '\0';

			nameV = new char[strlen(nameC) + 1];
			strncpy(nameV, nameC, strlen(nameC));
			nameV[strlen(nameC)] = '\0';

			strncpy(unitV, unitC, max_unit_length);
			unitV[strlen(unitC)] = '\0';
		}
		// Else, set to empty state
		else {
			skuV[0] = '\0';
			unitV[0] = '\0';
			nameV = nullptr;
		}
		// Copy the rest of the values (default is 0)
		qtyHand = qtyHandC;
		taxable = taxableC;
		priceV = priceC;
		qtyNeed = qtyNeedC;
	}

	// Calls the copy assignment function if copy is not the same as current object
	Product::Product(const Product& copy) {
		if (this != &copy) {
			*this = copy;
		}
	}

	Product& Product::operator=(const Product& copy) {
		// Check to see if object is valid before copying information
		if (this != &copy && strlen(copy.skuV) > 0) {
			strncpy(skuV, copy.skuV, max_sku_length);
			skuV[strlen(copy.skuV)] = '\0';

			nameV = new char[strlen(copy.nameV) + 1];
			strncpy(nameV, copy.nameV, strlen(copy.nameV));
			nameV[strlen(copy.nameV)] = '\0';

			strncpy(unitV, copy.unitV, max_unit_length);
			unitV[strlen(copy.unitV)] = '\0';
		}
		// Else, set to empty state
		else {
			skuV[0] = '\0';
			unitV[0] = '\0';
			nameV = nullptr;
		}
		// Copy the rest of the values
		//pTypeV = copy.pTypeV;
		qtyHand = copy.qtyHand;
		qtyNeed = copy.qtyNeed;
		priceV = copy.priceV;
		taxable = copy.taxable;

		return *this;
	}

	// If product contains valid data, delete the dynamic memory allocated by nameV
	Product::~Product() {
		if (strlen(skuV)) {
			delete[] nameV;
		}
		nameV = nullptr;
	}

	// Inserts the product information into the given file
	std::fstream& Product::store(std::fstream& file, bool newLine) const {
		if (!isEmpty()) {
			file << pTypeV << "," << sku() << "," << name() << "," << unit() << "," <<
				taxed() << "," << price() << "," << quantity() << "," <<
				qtyNeeded();
			// If the newline parameter is true, add a newline
			if (newLine) {
				file << endl;
			}
		}
		return file;
	}

	// Extracts fields from fstream object, creates temporary object, and assigns it to current object
	std::fstream& Product::load(std::fstream& file) {
		char sku_[max_sku_length + 1];
		char name[max_name_length + 1];
		char unit[max_unit_length + 1];
		int  quantity, qtyNeeded;
		double price_;
		bool taxed_;

		if (file.is_open())
		{
			file.getline(sku_, max_sku_length, ',');
			sku_[strlen(sku_)] = '\0';

			file.getline(name, max_name_length, ',');
			name[strlen(name)] = '\0';

			file.getline(unit, max_unit_length, ',');
			unit[strlen(unit)] = '\0';

			file >> taxed_;
			file.ignore();
			file >> price_;
			file.ignore();
			file >> quantity;
			file.ignore();
			file >> qtyNeeded;
			file.ignore();
			*this = Product(sku_, name, unit, quantity, taxed_, price_, qtyNeeded);
		}
		return file;
	}

	// Inserts data fields into ostream object
	std::ostream& Product::write(std::ostream& os, bool linear) const {
		// If there is an error present, feed the ostream the error message
		if (!(err.isClear())) {
			os << err.message();
		}
		else {
			// Reset the padding character
			os.fill(' ');
			// Outputs on single line if linear is true
			if (linear) {
				// setf and unsetf as per formatting requirements in tester
				os.setf(ios::left);
				os << setw(max_sku_length) << sku() << "|";
				os << setw(20) << ((name()) ? name() : "") << "|";
				os.unsetf(ios::left);
				os << setw(7) << setprecision(2) << fixed << (taxed() ? cost() : price()) << "|";
				os << setw(4) << quantity() << "|";
				os.setf(ios::left);
				os << setw(10) << unit() << "|";
				os.unsetf(ios::left);
				os << setw(4) << qtyNeeded() << "|";
			}
			// Inserts fields on separate lines if not linear
			else {
				os << " Sku: " << sku() << endl;
				os << " Name (no spaces): " << ((name()) ? name() : "") << endl;
				os << " Price: " << priceV << endl;
				os << " Price after tax: ";
				if (taxed()) {
					os << cost() << endl;
				}
				else {
					os << " N/A" << endl;
				}
				os << " Quantity on Hand: " << quantity() << " " << unit() << endl;
				os << " Quantity needed: " << qtyNeeded();
			}
		}

		return os;
	}

	// Extracts data fields for current object to be copy assigned to current object
	// Stops receiving input if there is any input that doesn't match the expected data types
	std::istream& Product::read(std::istream& is) {
		char sku_[max_sku_length + 1];
		char name[max_name_length + 1];
		char unit[max_unit_length + 1];
		int  quantity, qtyNeeded;
		double price_;
		char taxed_;

		is.istream::setstate(std::ios::goodbit);
		err.clear();

		cout << " Sku: ";
		is >> sku_;
		cout << " Name (no spaces): ";
		is >> name;
		cout << " Unit: ";
		is >> unit;
		cout << " Taxed? (y/n): ";
		is >> taxed_;
		if (taxed_ != 'Y' && taxed_ != 'y' && taxed_ != 'N' && taxed_ != 'n') {
			err.message("Only (Y)es or (N)o are acceptable");
			is.istream::setstate(std::ios::failbit);
		}

		// Multiple checks that stop input when an error flag is set
		if (err.isClear()) {
			cout << " Price: ";
			is >> price_;
			if (is.fail()) {
				err.message("Invalid Price Entry");
				is.istream::setstate(std::ios::failbit);
			}
		}

		if (err.isClear()) {
			cout << " Quantity on hand: ";
			is >> quantity;
			if (is.fail()) {
				err.message("Invalid Quantity Entry");
				is.istream::setstate(std::ios::failbit);
			}
		}

		if (err.isClear()) {
			cout << " Quantity needed: ";
			is >> qtyNeeded;
			if (is.fail()) {
				err.message("Invalid Quantity Needed Entry");
				is.istream::setstate(std::ios::failbit);
			}
		}

		is.ignore();

		if (err.isClear()) {
			*this = Product(sku_, name, unit, quantity, (taxed_ == 'Y' || taxed_ == 'y'), price_, qtyNeeded);
		}
		else {
			*this = Product();
		}
		return is;
	}

	// Returns true if string is identical to sku of object
	bool Product::operator==(const char* skuF) const {
		return (sku() == skuF);
	}

	// Returns total cost of all items on hand
	double Product::total_cost() const {
		return cost() * qtyHand;
	}

	// Resets number of units on hand to number received
	void Product::quantity(int onHand) {
		qtyHand = onHand;
	}

	// Check if object is in empty state
	bool Product::isEmpty() const {
		return !skuV;
	}

	// Returns number of units of product that are needed
	int Product::qtyNeeded() const {
		return qtyNeed;
	}

	// Returns number of units of product that are on hand
	int Product::quantity() const {
		return qtyHand;
	}

	// Returns true if sku of current object is greater than sku of referenced product
	bool Product::operator>(const char* skuF) const {
		return (sku() > skuF);
	}

	// Returns true if name of current object is greater than name of referenced product
	bool Product::operator>(const iProduct& prd) const {
		return (name() > prd.name());
	}

	// Adds given number to number of units on hand (only if integer received is positive-valued)
	int Product::operator+=(int add) {
		return (qtyHand + add > qtyHand ? (qtyHand += add) : qtyHand);
	}

	// Insert given Product record into ostream
	std::ostream& operator<<(std::ostream& os, const iProduct& prd) {
		return prd.write(os, true);
	}

	// Extract given Product record from istream
	std::istream& operator>>(std::istream& is, iProduct& prd) {
		return prd.read(is);
	}

	// Adds total cost of Product to double received and returns updated double
	double operator+=(double& add, const iProduct& prd) {
		return (add + prd.total_cost());
	}
}