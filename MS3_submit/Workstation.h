// Name: Wonkeun No
// Seneca Student ID: 145095196
// Seneca email: wno@myseneca.ca
// Date of completion: July 24, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <deque>
#include "CustomerOrder.h"

namespace sdds
{
	extern std::deque<CustomerOrder> pending;
	extern std::deque<CustomerOrder> completed;
	extern std::deque<CustomerOrder> incomplete;

	class Workstation :public Station
	{
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation = nullptr;
	public:
		Workstation(const std::string& src) : Station(src) {};
		Workstation(const Workstation& src) = delete;
		void operator=(const Workstation& src) = delete;
		Workstation(Workstation&& src) = delete;
		void operator=(Workstation&& src) = delete;
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNexStation() const;
		void display(std::ostream& os);
		Workstation& operator+=(CustomerOrder&& newOrder);

		size_t orderSize();
	};
}
#endif // !SDDS_WORKSTATION_H

