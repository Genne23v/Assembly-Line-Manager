// Name: Wonkeun No
// Seneca Student ID: 145095196
// Seneca email: wno@myseneca.ca
// Date of completion: July 16, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_CUSTOMER_ORDER_H
#define SDDS_CUSTOMER_ORDER_H
#include <string>
#include <iostream>
#include "Station.h"

namespace sdds
{
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder
	{
		std::string m_name;
		std::string m_product;
		size_t m_cntItem = 0;
		Item** m_lstItem = nullptr;
		static size_t m_widthField;

	public:
		CustomerOrder(const CustomerOrder& src) { throw "Copy constructor not allowed"; };
		CustomerOrder& operator=(const CustomerOrder& src) = delete;

		CustomerOrder() {};
		CustomerOrder(const std::string& src);
		CustomerOrder(CustomerOrder&& src) noexcept ;
		CustomerOrder& operator=(CustomerOrder&& src) noexcept;
		~CustomerOrder();
		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;

		bool isUnfilledOrder();
		
	};
}
#endif // !SDDS_CUSTOMER_ORDER_H

