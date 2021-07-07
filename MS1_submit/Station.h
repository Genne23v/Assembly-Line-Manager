// Name: Wonkeun No
// Seneca Student ID: 145095196
// Seneca email: wno@myseneca.ca
// Date of completion: July 8, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
#include <iostream>

namespace sdds
{
	class Station
	{
		int m_itemId=0;
		std::string m_itemName;
		std::string m_itemDesc;
		size_t m_serialNum = 0;
		size_t m_numInStock = 0;
		static unsigned int m_widthField ;
		static unsigned int id_generator;
	public:
		Station(const std::string& src);
		/*Station(Station&& src) noexcept;
		Station& operator=(Station&& src) noexcept;*/
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif // !SDDS_STATION_H
