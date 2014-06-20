#include "Argument_Include.h"


int main (int argc, char **argv)
{
	Argument::Argument arg(argc, argv);

	bool release("release");
	arg.get("release", release);

	int width(50);
	arg.get("width", width);

	int height(100);
	arg.get("height", height);

	double rate(0.5);
	arg.get("rate", rate);

	std::vector<int> data;
	arg.get("data", data);

	std::vector<bool> process;
	process.push_back(true );
	process.push_back(false);
	process.push_back(false);
	arg.get("process", process);

	std::vector<std::string> str;
	str.push_back("a");
	str.push_back("b");
	str.push_back("c");
	arg.get("str", str);

	;

	arg.print ();

	return 0;
}

