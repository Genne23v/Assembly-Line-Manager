// Name: Wonkeun No
// Seneca Student ID: 145095196
// Seneca email: wno@myseneca.ca
// Date of completion: July 8, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <string>

namespace sdds
{
	class Utilities
	{
		unsigned int m_widthField = 1;
		static char m_delimiter;
	public:
		Utilities() {};
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}
#endif // !SDDS_UTILITIES_H

