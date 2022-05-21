#include <iostream>
#include <fstream>
#include <math.h>
#include <array>

double percentMatch(std::array<double, 6> popMeans, std::array<double, 6> popStDevs, 
					std::array<int, 6> userScores) 
{
	double zScore0 = (userScores[0] - popMeans[0])/popStDevs[0]; // A z-score is defined as "how many standard deviations
	double zScore1 = (userScores[1] - popMeans[1])/popStDevs[1]; // away from the mean a certain datapoint is."
	double zScore2 = (userScores[2] - popMeans[2])/popStDevs[2];
	double zScore3 = (userScores[3] - popMeans[3])/popStDevs[3]; // In this case, the datapoint is the user's score for a characteristic.
	double zScore4 = (userScores[4] - popMeans[4])/popStDevs[4];
	double zScore5 = (userScores[5] - popMeans[5])/popStDevs[5];

	double avgZ = (zScore0+zScore1+zScore2+zScore3+zScore4+zScore5)/6; // The average of each characteristic is used 
																	   // to give an idea of overall fit

	double percent = (0.5-abs(erf(avgZ)/2))*2; // This function turns the z-score into the percentage of all people 
											   // who are as close or closer than you to the mean, 
											   // then turns that into a positive value between 0% and 100%
											   // where 100% means you are exactly the mean
											   // and 0% means you are (technically) infinitely far from the mean

	return percent;
}