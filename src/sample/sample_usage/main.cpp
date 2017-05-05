#include "utvl/arg.h"


int main (int argc, char** argv)
{
	// Load values from arguments
	utvl::arg::Argument a(argc, argv);

	// Set values if there is input from argments,
	// else default values
	const std::string mode = a.get("mode", std::string("normal"));

	const int number = a.get("number", 1);

	const float  threshold1 = a.get("threshold1", 0.1f);
	const double threshold2 = a.get("threshold2", 0.01);

	const bool debug = a.get("debug", false);

	const std::vector<int> id = a.get("id", std::vector<int> (3, 0));

	// Print values
	a.print();


	/* Call something to process here */


	return 0;
}

