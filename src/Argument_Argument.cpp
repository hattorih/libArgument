#include "Argument_Argument.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


#define STRING_TO_INT(X) (atoi(X.c_str()))
#define STRING_TO_FLOAT(X) ((float)atof(X.c_str()))
#define STRING_TO_DOUBLE(X) (atof(X.c_str()))
#define STRING_TO_BOOL(X) ((X == "t" || X == "true" || X == "on" || X == "active" || X == "enable") ? true : false)

#define TAG " <default>"


namespace Argument
{


Argument::Argument (int argc, char **argv)
{
	for (int i=1; i<argc; i++)
		mArgument += std::string(argv[i]);

	parse (mArgument);
}


Argument::~Argument (void)
{
	std::string temp;
	get("save", temp);

	if (temp != "") save (temp);
}


void Argument::get (const std::string &name, std::string &value)
{
	std::string temp;

	for (unsigned int i=0; i<mName.size(); i++)
		if (mName[i] == name)
			temp = mValue[i];

	if (temp != "") value = temp;
	else
	{
		mName.push_back(name);
		mValue.push_back(value);
		mTag.push_back(TAG);
	}
}


void Argument::get (const std::string &name, int &value)
{
	char v[BUFSIZ];
	sprintf_s(v, BUFSIZ, "%d", value);
	std::string temp(v);

	get(name, temp);

	if (temp != "") value = STRING_TO_INT(temp);
}


void Argument::get (const std::string &name, float &value)
{
	char v[BUFSIZ];
	sprintf_s(v, BUFSIZ, "%f", value);
	std::string temp(v);

	get(name, temp);

	if (temp != "") value = STRING_TO_FLOAT(temp);
}


void Argument::get (const std::string &name, double &value)
{
	char v[BUFSIZ];
	sprintf_s(v, BUFSIZ, "%f", value);
	std::string temp(v);

	get(name, temp);

	if (temp != "") value = STRING_TO_DOUBLE(temp);
}


void Argument::get (const std::string &name, bool &value)
{
	char v[BUFSIZ];
	sprintf_s(v, BUFSIZ, "%s", value ? "true" : "false");
	std::string temp(v);

	get(name, temp);

	std::transform(temp.begin(), temp.end(), temp.begin(), tolower);

	if (temp != "") value = STRING_TO_BOOL(temp);
}


void Argument::get (const std::string &name, std::vector<std::string> &value)
{
	std::vector<std::string> temp;

	for (unsigned int i=0; i<mName.size(); i++)
		if (mName[i] == name)
			temp.push_back(mValue[i]);

	if (temp.size() != 0)
		for (unsigned int i=0; i<temp.size(); i++) value.push_back(temp[i]);
	else
	{
		for (unsigned int i=0; i<value.size(); i++)
		{
			mName.push_back(name);
			mValue.push_back(value[i]);
			mTag.push_back(TAG);
		}
	}
}


void Argument::get (const std::string &name, std::vector<int> &value)
{
	std::vector<std::string> temp;
	for (unsigned int i=0; i<value.size(); i++)
	{
		char v[BUFSIZ];
		sprintf_s(v, BUFSIZ, "%d", value[i]);
		temp.push_back(v);
	}

	get(name, temp);

	for (unsigned int i=0; i<temp.size(); i++)
		value.push_back(STRING_TO_INT(temp[i]));
}


void Argument::get (const std::string &name, std::vector<float> &value)
{
	std::vector<std::string> temp;
	for (unsigned int i=0; i<value.size(); i++)
	{
		char v[BUFSIZ];
		sprintf_s(v, BUFSIZ, "%f", value[i]);
		temp.push_back(v);
	}

	get(name, temp);

	for (unsigned int i=0; i<temp.size(); i++)
		value.push_back(STRING_TO_FLOAT(temp[i]));
}


void Argument::get (const std::string &name, std::vector<double> &value)
{
	std::vector<std::string> temp;
	for (unsigned int i=0; i<value.size(); i++)
	{
		char v[BUFSIZ];
		sprintf_s(v, BUFSIZ, "%f", value[i]);
		temp.push_back(v);
	}

	get(name, temp);

	for (unsigned int i=0; i<temp.size(); i++)
		value.push_back(STRING_TO_DOUBLE(temp[i]));
}


void Argument::get (const std::string &name, std::vector<bool> &value)
{
	std::vector<std::string> temp;
	for (unsigned int i=0; i<value.size(); i++)
	{
		char v[BUFSIZ];
		sprintf_s(v, BUFSIZ, "%s", value[i] ? "true" : "false");
		temp.push_back(v);
	}

	get(name, temp);

	for (unsigned int i=0; i<temp.size(); i++)
		value.push_back(STRING_TO_BOOL(temp[i]));
}


void Argument::load (const std::string &filename)
{
	std::ifstream in(filename.c_str());

	if (!in)
	{
		;
	}
	else
	{
		std::string argument;

		while (!in.eof())
		{
			std::string line;
			std::getline(in, line);

			if (0 < line.size() && line[0] != '#')
				argument += line;
		}

		parse (argument);

		in.close();
	}
}


void Argument::save (const std::string &filename)
{
	std::ofstream out(filename.c_str());

	if (!out)
	{
		;
	}
	else
	{
		for (unsigned int i=0; i<mName.size(); i++)
			out << mName[i] << " : " << mValue[i] << ";"<< std::endl;

		out.close();
	}
}


void Argument::print (void)
{
#if 0
	std::cout << mArgument << std::endl;
#endif

	for (unsigned int i=0; i<mName.size(); i++)
		std::cout << mName[i] << mTag[i] << " : " << mValue[i] << std::endl;
}


void Argument::parse (const std::string &argument)
{
	std::string arg(argument);

	size_t pos;

	while ((pos = arg.find_first_of(";")) != std::string::npos)
	{
		std::string a(arg.substr(0, pos));

		size_t p;

		if ((p = a.find_first_of(":")) != std::string::npos)
		{
			std::string name = a.substr(0, p);

			std::string value = (p+1 < a.size()) ? a.substr(p+1, a.size() - (p+1)) : "";

			while (0<name.size() && name[name.size()-1] == ' ')
				name = name.substr(0, name.size()-1);

			while (0<value.size() && value[0] == ' ')
				value = value.substr(1, value.size()-1);

			if (0 < value.size() && value[0] != '#')
			{
				mName.push_back(name);
				mValue.push_back(value);
				mTag.push_back("");

				if (name == "load")
				{
					load (value);
				}
			}
		}

		arg = arg.substr(pos+1);
	}
}


} // namespace Argument

