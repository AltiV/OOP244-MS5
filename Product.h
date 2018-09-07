// Date: Tuesday, May 29th, 2018
// Author: Alan Vuong
// Seneca E-mail: avuong19@myseneca.ca
// Student Number: 149004178

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#define max_sku_length 7
#define max_unit_length 10
#define max_name_length 75
#define TAX 0.13

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "ErrorState.h"
#include "iProduct.h"

namespace AMA {
	class Product : public iProduct {
		char pTypeV; // Product Type
		char skuV[max_sku_length + 1]; // Product SKU
		char unitV[max_unit_length + 1]; // Product Description
		char * nameV; // Product Name
		int qtyHand; // Quantity on Hand
		int qtyNeed; // Quantity Needed
		double priceV; // Single Unit Price
		bool taxable; // Taxable Status
	protected:
    ErrorState err; // Error State
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;
	public:
		explicit Product(const char product = 'N');
		Product(const char*, const char*, const char*, int qtyHandC = 0, bool taxableC = 0, double priceC = 0, int qtyNeedC = 0);
		Product(const Product&);
		Product& operator=(const Product&);
		~Product();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const iProduct&) const;
		int operator+=(int);
	};

	std::ostream& operator<<(std::ostream&, const iProduct&);
	std::istream& operator>>(std::istream&, iProduct&);
	double operator+=(double&, const iProduct&);
}

#endif