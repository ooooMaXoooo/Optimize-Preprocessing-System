#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

int main()
{
	// execute the gcc command in the file ...
	std::system("gcc -c C:/Dev/Cpp/OPS/target/src/main.cpp -S");

	std::ofstream cleanFile("C:/Dev/Cpp/OPS/target/main.ops");
	if (!cleanFile)
	{
		std::cout << "Le fichier de sortie n'a pas pu être vidé" << std::endl;
		return 1;
	}
	cleanFile.clear();
	cleanFile.close();

	std::ofstream outFile("C:/Dev/Cpp/OPS/target/main.ops", std::ios::app);
	std::ifstream i_sourceFile("main.s");

	if (!i_sourceFile)
	{
		std::cout << "Le fichier source n'a pas pu être ouvert" << std::endl;
		return 1;
	}

	if (!outFile)
	{
		std::cout << "Le fichier de sortie n'a pas pu être ouvert" << std::endl;
		return 1;
	}


	std::string line;
	std::vector<int> callPos;
	std::vector<std::array<std::string, 2>> fx;
	std::string signature = "";
	std::string content = "";

	bool inContent = false;
	int count = 0;
	while (std::getline(i_sourceFile, line))
	{
		count++;

		if (line[0] == '\t')
		{
			if (inContent)
			{
				if (line == "\t.seh_endproc") // last iteration
				{
					inContent = false;
					std::array<std::string,2> func = {signature, content};
					fx.emplace_back(func);
					signature = "";
					content = "";
				}

				content += line + "\n";
			}

			if (line[1] == 'c' && line[2] == 'a' && line[3] == 'l' && line[4] == 'l'
				&& line != "\tcall\t__main") // call
			{
				callPos.emplace_back(count); // give the n° of the line

				outFile << line << '\t' << count << '\n';
			}
			else
			{
				/*std::cout << count << "\t\t" << (line[1] == 'c')
					<< "\n\t\t" << (line[2] == 'a')
					<< "\n\t\t" << (line[3] == 'l')
					<< "\n\t\t" << (line[4] == 'l') << "\n\n\n";*/
			}
		}


		/*
		a function start with _Z
		then the number of letter of the name
		then the name
		then parameter( i = int, c = char, P = *, PK = const *, R = &, .....)
		idk for the type but doesn't matter

		ex : _Z3Logiii --> ??? Log(int a, int b, int c)
		ex : _Z4Logiii --> ??? Logi(int a, int b)  ####  see the trick ?
		*/
		if (line[0] == '_' && line[1] == 'Z')
		{
			//get the function's signature
			for (int i = 0; i < line.length() - 1; i++)
			{
				signature += line[i];
			}
			inContent = true;

			outFile << line << '\t' << count << '\n';
		}

		if (line == "main:")
		{
			inContent = true;
			signature = "main";

			outFile << line << '\t' << count << '\n';
		}
	}

	for (auto item : fx)
	{
		std::cout << "signature : " << item[0] << std::endl;
		std::cout << "content :\n" << item[1] << "\n\n\n";
	}
}