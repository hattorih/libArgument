/********************************************************************************
Copyright (c) 2013-2014 Hironori Hattori <hattorih@cs.cmu.edu>.
All rights reserved.
---------------------------------------------------------------------------------
$Id: $
********************************************************************************/

// "arg"

// Hironori Hattori, Carnegie Mellon University
// hattorih@cs.cmu.edu


#ifndef __UTVL_ARG_H__
#define __UTVL_ARG_H__


#include <string>
#include <vector>


namespace utvl
{

	
namespace arg
{


class Argument
{
public:
	Argument (int argc, char** argv);

	~Argument (void);

	// Set default values (String)
	const std::string get (
		const std::string &name, const std::string &default_value);
	const std::vector<std::string> get (
		const std::string &name, const std::vector<std::string> &default_value);

	// Set default values (Int)
	const int get (
		const std::string &name, const int &default_value);
	const std::vector<int> get (
		const std::string &name, const std::vector<int> &default_value);

	// Set default values (Float)
	const float get (
		const std::string &name, const float &default_value);
	const std::vector<float> get (
		const std::string &name, const std::vector<float> &default_value);

	// Set default values (Double)
	const double get (
		const std::string &name, const double &default_value);
	const std::vector<double> get (
		const std::string &name, const std::vector<double> &default_value);

	// Set default values (Bool)
	const bool get (
		const std::string &name, const bool &default_value);
	const std::vector<bool> get (
		const std::string &name, const std::vector<bool> &default_value);

	// Else
	void load (const std::string &filename);
	void save (const std::string &filename);

	void print (void);

private:
	void parse (const std::string &arg);

	std::string mArgument;

	std::vector<std::string> mName;
	std::vector<std::string> mValue;
	std::vector<std::string> mTag;
};

typedef Argument Arg;


} // namespace arg


} // namespace utvl


#endif // __UTVL_ARG_H__

