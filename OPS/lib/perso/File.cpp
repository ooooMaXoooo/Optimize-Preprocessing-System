#include "module.h"
#include <iostream>


personal::File::~File()
{
	delete(m_text);
}

personal::File::File(const char* path, const char* text) :
	m_path(path), m_mode(std::ios::out), m_outPath(path), m_text(nullptr)
{
	isError = false;
	errorMessage = "";
	m_out.open(path);
	m_file.open(path);
	if (!m_file || !m_out)
	{
		errorMessage = "The file can't be open";
		isError = true;
		return;
	}

	// heap allocation for memory
	m_text = new std::string(text);
}

personal::File::File(File& const file) :
	m_path(file.m_path), m_mode(file.m_mode), m_outPath(file.m_outPath), isError(false), errorMessage(""), m_text(nullptr)
{
	m_out.open(file.m_outPath, file.m_mode);
	m_file.open(file.m_path);

	if (!m_file || !m_out)
	{
		errorMessage = "The file can't be open";
		isError = true;
		return;
	}

	m_text = new std::string(*file.m_text);
}

bool personal::File::path(const char* path)
{
	m_path = path;

	m_file.close();
	m_file.open(path);

	if (!m_file)
	{
		errorMessage = "The file can't be open";
		isError = true;
		return false;
	}
	return true;
}

bool personal::File::outPath(const char* path)
{
	m_path = path;

	m_out.close();
	m_out.open(path, m_mode);

	if (!m_out)
	{
		errorMessage = "The file can't be open";
		isError = true;
		return false;
	}
	return true;
}

bool personal::File::changeMode(std::ios::_Openmode mode)
{
	m_out.close();
	m_out.open(m_outPath, mode);

	if (!m_out)
	{
		errorMessage = "The file can't be open";
		isError = true;
		return false;
	}
	return true;
}

void personal::File::write(std::string text, int pos, WriteMode mode)
{
	if (pos < 0)
	{
		pos = m_text->length() - 1;
	}

	std::string finalText = *m_text;
	if (mode == File::INSERT)
	{
		finalText.insert(pos, text);
	}
	else if (mode == File::REPLACE)
	{
		finalText.replace(pos, text.length(), text);
	}
	clear();
	m_out << finalText;
	*m_text = finalText;
}

void personal::File::clear()
{
	std::ofstream clear(m_outPath);
	clear << "";
	clear.close();
}