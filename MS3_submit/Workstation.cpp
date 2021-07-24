// Name: Wonkeun No
// Seneca Student ID: 145095196
// Seneca email: wno@myseneca.ca
// Date of completion: July 24, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"

namespace sdds
{
	std::deque<CustomerOrder> pending;
	std::deque<CustomerOrder> completed;
	std::deque<CustomerOrder> incomplete;
	Workstation::Workstation(const std::string& src) : Station(src) { }
	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
			updateQuantity();
		}
	}
	bool Workstation::attemptToMoveOrder()
	{
		bool moved = false;

		if (!m_orders.empty())
		{
			if (!m_orders.front().isItemFilled(getItemName()))
			{
				fill(std::cout);

				if (m_pNextStation == nullptr)
				{
					if(m_orders.front().isFilled())
						completed.push_back(std::move(m_orders.front()));
					else
						incomplete.push_back(std::move(m_orders.front()));
				}
				else
				{
					m_pNextStation->m_orders.push_back(std::move(m_orders.front()));
				}
				m_orders.pop_front();
			}
			else 
			{	
				if (m_orders.front().isUnfilledOrder())
				{
					m_pNextStation->m_orders.push_back(std::move(m_orders.front()));
					m_orders.pop_front();
				}
				else
				{	
					Workstation* pNext = m_pNextStation;
					Workstation* pCurrent = this;

					if (!m_orders.front().isFilled() && pNext != nullptr)
					{
						do 
						{
							pNext->m_orders.push_back(std::move(pCurrent->m_orders.front()));
							pCurrent->m_orders.pop_front();
							pCurrent = pNext;
							pNext = pNext->m_pNextStation;
						} while (pCurrent->m_orders.front().isItemFilled(pCurrent->getItemName()));
						pCurrent->fill(std::cout);

						if (pNext != nullptr)
						{
							pNext->m_orders.push_back(std::move(pCurrent->m_orders.front()));
							pCurrent->m_orders.pop_front();
						}
						else
						{
							if (pCurrent->m_orders.front().isFilled())
								completed.push_back(std::move(pCurrent->m_orders.front()));
							else
								incomplete.push_back(std::move(pCurrent->m_orders.front()));

							pCurrent->m_orders.pop_front();
						}
					}
					else
					{
						while (pNext != nullptr)
						{
							pNext->m_orders.push_back(std::move(pCurrent->m_orders.front()));
							pCurrent->m_orders.pop_front();
							pCurrent = pNext;
							pNext = pNext->m_pNextStation;
						}

						pCurrent->fill(std::cout);

						if (pCurrent->m_orders.front().isFilled())
							completed.push_back(std::move(pCurrent->m_orders.front()));
						else
							incomplete.push_back(std::move(pCurrent->m_orders.front()));

						pCurrent->m_orders.pop_front();
					}
				}
			}
			moved = true;
		}
		return moved;
	}
	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}
	Workstation* Workstation::getNexStation() const
	{
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os)
	{
		if (m_pNextStation != nullptr)
		{
			os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
		}
		else
		{
			os << getItemName() << " --> END OF LINE" << std::endl;
		}
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
	size_t Workstation::orderSize()
	{
		return m_orders.size();
	}
}