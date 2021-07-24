// Name: Wonkeun No
// Seneca Student ID: 145095196
// Seneca email: wno@myseneca.ca
// Date of completion: July 24, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <fstream>
#include <list>
#include <algorithm>
#include "LineManager.h"

namespace sdds
{
	Workstation* getStation(Workstation* station, std::string itemName)
	{
		if (station->getItemName() == itemName)
		{
			return station;
		}
	}
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		std::ifstream fin(file);
		size_t i = 0;
		std::vector<Workstation*> tmpNextStation;

		if (fin.is_open())
		{
			while (!fin.eof())
			{
				std::string line;
				std::getline(fin, line);
				size_t foundPos = line.find('|');

				if (foundPos != std::string::npos)
				{
					std::string firstStation = line.substr(0, foundPos);
					std::string secondStation = line.substr(foundPos + 1);

					auto station = std::find_if(stations.begin(), stations.end(),
						[&firstStation](const Workstation* station)
						{
							if (station->getItemName() == firstStation)
								return station;
						});
					activeLine.push_back(*station);
	
					auto nStation = std::find_if(stations.begin(), stations.end(), 
						[&](const Workstation* station)
						{
							auto begin = stations.begin(), end = stations.end();
							if (station->getItemName() == secondStation)
							{
								return station;
							}
						});
					activeLine[i]->setNextStation(*nStation);
				}
				else if (foundPos == std::string::npos && !line.empty())
				{
					auto station = std::find_if(stations.begin(), stations.end(),
						[&](const Workstation* station)
						{
							auto begin = stations.begin(), end = stations.end();
							if (station->getItemName() == line)
								return station;
						});
					activeLine.push_back(*station);
				}
				i++;
			}

			for_each(activeLine.begin(), activeLine.end(), [&](Workstation* src)
				{
					auto allOfNotPointing = std::none_of(activeLine.begin(), activeLine.end(),
						[&src](const Workstation* line)
						{
							return line->getNexStation() == src;
						});
					if (allOfNotPointing)
						m_firstStation = src;
				});
						
			m_cntCustomerOrder = pending.size();
		}
		else
		{
			throw "Something's wrong while reading the file...";
		}
	}
	void LineManager::linkStations()
	{
		std::vector<Workstation*> tmpVtr(activeLine.size());

		size_t i = 0;
		tmpVtr.at(i++) = m_firstStation;
		Workstation* nextStation = m_firstStation->getNexStation();

		while (nextStation->getNexStation() != nullptr)
		{
			tmpVtr.at(i) = nextStation;
			nextStation = nextStation->getNexStation();
			i++;
		}
		tmpVtr[i] = nextStation;

		activeLine = tmpVtr;
	}
	bool LineManager::run(std::ostream& os)
	{
		static size_t iter;

		if (!pending.empty())
		{
			*m_firstStation += std::move(pending.front());
			pending.pop_front();
		}
		
		os << "Line Manager Iteration: " << ++iter << std::endl;

		bool orderMoved = false;
		size_t numOrderInLine = m_cntCustomerOrder - (pending.size() + completed.size() + incomplete.size());		size_t i = 0, orderMoveNum = 0;;
		while(orderMoveNum < numOrderInLine)
		{
			orderMoved = activeLine[i]->attemptToMoveOrder();

			if (orderMoved) orderMoveNum++;

			if (orderMoved && (i < activeLine.size()-2) && activeLine[i+1]->orderSize() == 1) i++;
			/*if (i < activeLine.size()-1)*/ i++;
		}

		bool allOrderFilled = !(m_cntCustomerOrder - (completed.size() + incomplete.size()));
			/*std::all_of(pending.begin(), pending.end(),
			[](CustomerOrder& order) { return order.isFilled(); });*/
		return allOrderFilled;
	}
	void LineManager::display(std::ostream& os) const
	{
		for_each(activeLine.begin(), activeLine.end(), [&os](Workstation* line)
			{ line->display(os); });
	}
}