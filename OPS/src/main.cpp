#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <unordered_map>

int main()
{
	std::string file = "";

	// execute the gcc command in the file ...
	std::system("gcc -c C:/Dev/Cpp/OPS/target/src/main.cpp -S");

	//prepare file stream to write and read in
	std::ofstream outFile("C:/Dev/Cpp/OPS/target/main.ops");
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

	std::unordered_map<std::string, std::string> fx; // signature -- content
	std::unordered_map<int, std::string> callPos; // callPos -- signature

	std::string signature = "";
	std::string content = "";

	bool inContent = false;
	int count = 0;
	// detect lines to change and functions, many other thing will come in futur
	while (std::getline(i_sourceFile, line))
	{
		if (line[0] == '\t')
		{
			if (inContent)
			{
				if (line == "\t.seh_endproc") // last iteration
				{
					inContent = false;
					content.pop_back();
					std::array<std::string,2> func = {signature, content};
					fx[signature] = content;
					signature = "";
					content = "";
				}

				content += line + "\n";
			}

			if (line[1] == 'c' && line[2] == 'a' && line[3] == 'l' && line[4] == 'l'
				&& line != "\tcall\t__main") // call
			{
				std::string callFx = "";
				for (int i = 6; i < line.length(); i++)
				{
					callFx += line[i];
				}

				callPos[(int)i_sourceFile.tellg() - line.length() - 2 - count] = callFx;
				// tellg go to 1-->x and know the \0 char so we need to remove 1 for each which is 2
				// and the line doesn't take \n char so we remove 1 per line forgot  (count)
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
		}

		if (line == "main:")
		{
			inContent = true;
			signature = "main";
		}
		
		file += line + '\n';
		count++;
	}

	// change the call line by the content of the fx called
	for (auto posFx : callPos)
	{
		//std::string test = "\n\n************\n" + fx.at(posFx.second) + "\n************\n\n";

		file.replace(posFx.first, posFx.second.length()+6, fx.at(posFx.second));

		//std::cout << "file[posFx.first] : " << posFx.first << " ***" << file[posFx.first] << "***\n";
	}

	//update the output file
	outFile << file;
}