// Name: Wonkeun No
// Seneca Student ID: 145095196
// Seneca email: wno@myseneca.ca
// Date of completion: July 8, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <sstream>
#include "Station.h"
#include "Utilities.h"
constexpr int size = 4;

namespace sdds
{
	unsigned int Station::id_generator=0;
	unsigned int Station::m_widthField=0;
	Station::Station(const std::string& src)
	{
		id_generator++;
		m_itemId = id_generator;

		std::istringstream inputStream(src);
		std::string tmpArr[size];
		char delim = Utilities::getDelimiter();
		
		int i = 0; 
		while (i < size)
		{
			std::getline(inputStream, tmpArr[i], delim);
			i++;
		}
		
		m_itemName = tmpArr[0];
		m_serialNum = std::stoul(tmpArr[1]);
		m_numInStock = std::stoul(tmpArr[2]);
		m_itemDesc = tmpArr[3];

		if (m_itemName.length() > m_widthField)
		{
			m_widthField = m_itemName.length();
		}
	}
	/*Station::Station(Station&& src) noexcept
	{
		*this = std::move(src);
	}
	Station& Station::operator=(Station&& src) noexcept
	{
		if (this != &src)
		{
			m_itemName = src.m_itemName;
			m_itemDesc = src.m_itemDesc;
			m_serialNum = src.m_serialNum;
			m_numInStock = src.m_numInStock;
		}
		return *this;
	}*/
	const std::string& Station::getItemName() const
	{
		return m_itemName;
	}
	size_t Station::getNextSerialNumber()
	{
		return m_serialNum++;
	}
	size_t Station::getQuantity() const
	{
		return m_numInStock;
	}
	void Station::updateQuantity()
	{
		if (m_numInStock > 1)
		{
			m_numInStock--;
		}
	}
	void Station::display(std::ostream& os, bool full) const
	{
		os << "[";
		os.width(3);
		os.fill('0');
		os << m_itemId << "] Item: ";
		os.width(m_widthField);
		os.fill(' ');
		os.unsetf(std::ios::right);
		os.setf(std::ios::left);
		os << m_itemName;
		os << " [";
		os.unsetf(std::ios::left);
		os.setf(std::ios::right);
		os.width(6);
		os.fill('0'); 
		os << m_serialNum;

		if (full)
		{
			os << "] Quantity: ";
			os.unsetf(std::ios::right);
			os.setf(std::ios::left);
			os.width(m_widthField);
			os.fill(' ');
			os << m_numInStock << " Description: " << m_itemDesc << std::endl;
			os.unsetf(std::ios::left);
		} 
		else
		{
			os << "]" << std::endl;

		}
		
	}
}
