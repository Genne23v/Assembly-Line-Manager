// Name: Wonkeun No
// Seneca Student ID: 145095196
// Seneca email: wno@myseneca.ca
// Date of completion: July 8, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"

namespace sdds
{
	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		char delim = Utilities::getDelimiter();
		size_t startPos = next_pos;
		size_t findPos = str.find_first_of(delim, startPos);
			
		if (findPos == next_pos)
		{
			more = 0;
			throw "Delimiter is found at" + next_pos;
		}
		else if (findPos != std::string::npos)
		{
			more = true;
			next_pos = findPos+1;
		}
		else
		{
			more = 0;
			findPos = str.length();
		}

		if ((findPos - startPos) > m_widthField)
		{
			setFieldWidth(findPos - startPos);
		}

		return str.substr(startPos, (findPos - startPos));
	}

	char Utilities::m_delimiter;
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	};
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	};
}