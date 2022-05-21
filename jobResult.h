#include <string>
using namespace std;
struct jobResult {
	string jobName;
	double percentile; // This specifically refers to percentile away from the mean. 
					   // It can go in either direction, doesn't matter, so the value will just be a positive distance. 
					   // And remember, it's a percent so 0.5 = 50%
};