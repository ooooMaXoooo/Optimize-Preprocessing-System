#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <unordered_map>
#include "../lib/perso/module.h"


std::unordered_map<std::string, std::string> fx; // signature -- content
std::unordered_map<int, std::string> callPos; // callPos -- signature


void createSignature(std::string& signature, std::string& content) {
	content.pop_back(); // remove the \n
	fx[signature] = content;
	signature = "";
	content = "";
}

int main()
{
	std::string fileText = "";

	// execute the gcc command in the fileText ...
	std::system("gcc -c C:/Dev/Cpp/OPS/target/src/main.cpp -S");

	//prepare the fileTexts we deal with
	personal::File file("main.s");
	file.outPath("C:/Dev/Cpp/OPS/target/main.ops");

	if (!file)
	{
		std::cout << file.getError() << std::endl;
		return 1;
	}

	/*prepare fileText stream to write and read in
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
	}*/


	std::string line;

	std::string signature = "";
	std::string content = "";

	bool inContent = false;
	int count = 0;
	// detect lines to change and functions, many other thing will come in futur
	while (std::getline(file, line))
	{
		if (line[0] == '\t')
		{
			if (inContent)
			{
				if (line == "\tret") // last iteration
				{
					inContent = false;
					createSignature(signature, content);
				}
				else if (line != "\t.seh_setframe	%rbp, 0" && line != "\t.seh_endprologue")
				{
					content += line + "\n";
				}
			}

			if (line[1] == 'c' && line[2] == 'a' && line[3] == 'l' && line[4] == 'l'
				&& line != "\tcall\t__main") // call
			{
				std::string callFx = "";
				for (size_t i = 6; i < line.length(); i++)
				{
					callFx += line[i];
				}

				callPos[(int)i_sourceFile.tellg() - line.length() - 2 - count] = callFx;
				// tellg go to 1-->x and know the \0 char so we need to remove 1 for each which is 2
				// and the line doesn't take \n char so we remove 1 per line forgot  (count)
			}
		}

		// if we are in a content and we have a jump for example we start a new signature and content
		if (inContent && line[0] != '\t')
		{
			inContent = false;  // opti --> remove it bec we put it at true at the end

			//createSignature(signature, content);

			inContent = true;
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

		
		
		fileText += line + '\n';
		count++;
	}

	// change the call line by the content of the fx called
	for (auto posFx : callPos)
	{
		//std::string test = "\n\n************\n" + fx.at(posFx.second) + "\n************\n\n";

		fileText.replace(posFx.first, posFx.second.length()+6, fx.at(posFx.second));

		//std::cout << "fileText[posFx.first] : " << posFx.first << " ***" << fileText[posFx.first] << "***\n";
	}

	//update the output fileText
	file << fileText;
}