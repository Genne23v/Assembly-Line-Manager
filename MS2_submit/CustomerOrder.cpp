// Name: Wonkeun No
// Seneca Student ID: 145095196
// Seneca email: wno@myseneca.ca
// Date of completion: July 16, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <list>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder(const std::string& src)
	{

		Utilities util;
		size_t pos = 0u;
		bool more = true;
		std::list<std::string> tmp;

		while (more)
		{
			std::string extracted = util.extractToken(src, pos, more);
			tmp.push_back(extracted);
		}
		m_name = tmp.front();
		tmp.pop_front();
		m_product = tmp.front();
		tmp.pop_front();

		m_lstItem = new Item*[tmp.size()];
		size_t size = tmp.size();

		for (auto i = 0u; i < size; i++)
		{
			m_lstItem[i] = new Item(tmp.front());
			m_cntItem++;
			tmp.pop_front();
		}
		
		if (CustomerOrder::m_widthField < util.getFieldWidth())
		{
			m_widthField = util.getFieldWidth();
		}
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
	{
		*this = std::move(src);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
	{
		if (this != &src)
		{
			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;

			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder()
	{
		//for (auto i = 0u; i < m_cntItem; i++)
			//delete m_lstItem[i];
		delete[] m_lstItem;
	}
	bool CustomerOrder::isFilled() const
	{
		bool filled = true;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (!m_lstItem[i]->m_isFilled)
			{
				filled = false;
			}
		}
		return filled;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool filled = true;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				if (!m_lstItem[i]->m_isFilled)
				{
					filled = false;
				}
			}
		}
		return filled;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		bool itemContained = false;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName())
			{
				itemContained = true;
				station.getNextSerialNumber();
				m_lstItem[i]->m_isFilled = true;

				os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[";
			os.width(6);
			os.fill('0');
			os << m_lstItem[i]->m_serialNumber << "] ";
			os.fill(' ');
			os.setf(std::ios::left);
			os.width(m_widthField);
			os << m_lstItem[i]->m_itemName << " - ";

			if (m_lstItem[i]->m_isFilled)
			{
				os << "FILLED" << std::endl;
			}
			else
			{
				os << "TO BE FILLED" << std::endl;
			}
		}
	}
}