// Name: Wonkeun No
// Seneca Student ID: 145095196
// Seneca email: wno@myseneca.ca
// Date of completion: July 24, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_LINE_MANAGER_H
#define SDDS_LINE_MANAGER_H
#include <vector>
#include "Workstation.h"

namespace sdds
{
	class LineManager
	{
		std::vector<Workstation*> activeLine;
		size_t m_cntCustomerOrder=0;
		Workstation* m_firstStation = nullptr;
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif // !SDDS_LINE_MANAGER_H
