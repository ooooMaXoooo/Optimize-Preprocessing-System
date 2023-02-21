#include <iostream>
#include <fstream>
#include <string>

int main()
{
	// execute the gcc command in the file ...
	std::system("gcc -c C:/Dev/Cpp/OPS/target/src/main.cpp -S");

	std::ofstream cleanFile("C:/Dev/Cpp/OPS/target/main.ops");
	std::ofstream outFile("C:/Dev/Cpp/OPS/target/main.ops", std::ios::app);
	std::ifstream i_sourceFile("main.s");

	if(!i_sourceFile)
	{
		std::cout << "Le fichier source n'a pas pu être ouvert" << std::endl;
		return 1;
	}

	if (!outFile)
	{
		std::cout << "Le fichier de sortie n'a pas pu être ouvert" << std::endl;
		return 1;
	}
	cleanFile << "";
	cleanFile.close();

	std::string line;
	std::string word;
	while (std::getline(i_sourceFile, line))
	{
		if (line[0] == '\t')
		{
			continue;
		}
		outFile << line << '\n';
	}
}