#include <boost/regex.hpp>
#include <iostream>
#include <string>

int main()
{
<<<<<<< HEAD
	std::cout << "hoi";
	system("pause");
	return 0;
=======
    std::string line;
    boost::regex pat( "^Subject: (Re: |Aw: )*(.*)" );

    while (std::cin)
    {
        std::getline(std::cin, line);
        boost::smatch matches;
        if (boost::regex_match(line, matches, pat))
            std::cout << matches[2] << std::endl;
    }
>>>>>>> origin/Makefile-/-dependencies-fix
}