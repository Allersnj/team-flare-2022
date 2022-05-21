#include <iostream>
#include <fstream>
#include <math.h>
#include <array>

double percentMatch(std::array<double, 6> popMeans, std::array<double, 6> popStDevs, std::array<int, 6> userScores) {
	double zScore0 = (userScores[0] - popMeans[0])/popStDevs[0];
	double zScore1 = (userScores[1] - popMeans[1])/popStDevs[1];
	double zScore2 = (userScores[2] - popMeans[2])/popStDevs[2];
	double zScore3 = (userScores[3] - popMeans[3])/popStDevs[3];
	double zScore4 = (userScores[4] - popMeans[4])/popStDevs[4];
	double zScore5 = (userScores[5] - popMeans[5])/popStDevs[5];

	double avgZ = (zScore0+zScore1+zScore2+zScore3+zScore4+zScore5)/6;

	double percent = (0.5-abs(erf(avgZ)/2))*2;

	return percent;
}