/********************************************************************************
Copyright (c) 2013-2014 Hironori Hattori <hattorih@cs.cmu.edu>.
All rights reserved.
---------------------------------------------------------------------------------
$Id: $
********************************************************************************/

// "libArgument - Argument"

// Hironori Hattori, Carnegie Mellon University
// hattorih@cs.cmu.edu


#ifndef __LIB_ARGUMENT_H__
#define __LIB_ARGUMENT_H__


#include <string>
#include <vector>


namespace Argument
{


class Argument
{
public:
	Argument (int argc, char **argv);

	~Argument (void);

	void get (const std::string &name, std::string &value);
	void get (const std::string &name, int &value);
	void get (const std::string &name, float &value);
	void get (const std::string &name, double &value);
	void get (const std::string &name, bool &value);

	void get (const std::string &name, std::vector<std::string> &value);
	void get (const std::string &name, std::vector<int> &value);
	void get (const std::string &name, std::vector<float> &value);
	void get (const std::string &name, std::vector<double> &value);
	void get (const std::string &name, std::vector<bool> &value);

	void load (const std::string &filename);
	void save (const std::string &filename);

	void print (void);

private:
	void parse (const std::string &argument);

	std::string mArgument;

	std::vector<std::string> mName;
	std::vector<std::string> mValue;
	std::vector<std::string> mTag;
};


} // namespace Argument


#endif // __LIB_ARGUMENT_H__

