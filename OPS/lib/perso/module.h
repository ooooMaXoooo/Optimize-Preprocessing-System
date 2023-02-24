#pragma once

#include <string>
#include <fstream>
#include <memory>

namespace personal
{
	//create string class


	class File
	{
	public: // enums
		enum WriteMode : char
		{
			INSERT = 0,
			REPLACE
		};

	public : // methods
		/* 
		* Constructor of File
		* @param path : the path of the file you write and read in
		* @param mode : the mode of opening the file (default = std::ios::out)
		*/
		File(const char* path, const char* text = "");
		File(File& file);

		~File();

		/*
		Get the file's path you read in
		*/
		const char* path() const { return m_path;};
		/*
		Get the file's path you write in
		*/
		const char* outPath() const { return m_outPath; };

		/*
		Set the file's path you read in
		*/
		bool path(const char* path);
		/*
		Set the file's path you write in
		*/
		bool outPath(const char* path);

		/*
		* Write in the file
		* @param text : you seriously ask what is this param ???
		* @param pos : the position where you write your text
		* @param mode : the writing mode ( default = WriteMode.INSERT, can be REPLACE)
		*/
		void write(std::string text, int pos = -1, WriteMode mode = INSERT);

		/*
		* Remove all text of the file
		*/
		void clear();

		const char* getError() const { return errorMessage; };

		std::unique_ptr<std::ifstream> getIfstream() const { return (const std::ifstream*)m_file; }

	public : // operators

		File& operator<<(const std::string& text)
		{
			write(text);
			return *this;
		}

		File& operator=(const File& file)
		{
			if (&file != this)
			{
				m_out.open(file.m_outPath, file.m_mode);
				m_file.open(file.m_path);

				if (!m_file || !m_out)
				{
					errorMessage = "The file can't be open";
					isError = true;
					return *this;
				}

				m_text = new std::string(*file.m_text);
				m_path = file.m_path;
				m_mode = file.m_mode;
				m_outPath = file.m_outPath;
				isError = false;
				errorMessage = "";
			}
			return *this;
		}

		operator bool() const
		{
			return isError ? false : true;
		}

		bool operator!() const
		{
			return isError ? true : false;
		}

	private :  // attributes
		std::ofstream m_out;
		std::ios::_Openmode m_mode;
		const char* m_outPath;

		const char* m_path;
		std::ifstream m_file;

		std::string* m_text;

		bool isError;
		const char* errorMessage;

	private : // private functions

		/*
		Change the mode of the file stream you write in
		*/
		bool changeMode(std::ios::_Openmode mode);
	};

	
}