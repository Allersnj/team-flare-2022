#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <array>
#include "jobResult.h"
#include "nlohmann/json.hpp"
#include "stdev.cpp"

using json = nlohmann::json; // our JSON parsing library

bool compare (jobResult job1, jobResult job2){ // used to sort results later
	return(job1.percentile > job2.percentile);
}

std::array<jobResult,11> jobSuggest() {
	// step one: yoink all data from the json
	std::ifstream data {"MockJobCharacteristics.json"};
    json j{json::parse(data)};

	// step two: "take" an "input" (we just hard coded these for the demo)
	std::array<int, 6> userScores{{8,7,6,5,4,6}};

	// step three: calculate matches for each job
	std::array<jobResult,11> jobMatches;
	for(int i = 0; i < 11; i++){
		// yoink the datapoints from the i-th jobResult into arrays
		std::array<double, 6> popMeans;
		popMeans[0] = j[i]["Bmean"];
		popMeans[1] = j[i]["Tmean"];
		popMeans[2] = j[i]["Cmean"];
		popMeans[3] = j[i]["Hmean"];
		popMeans[4] = j[i]["Pmean"];
		popMeans[5] = j[i]["Omean"];
		std::array<double, 6> popStDevs;
		popStDevs[0] = j[i]["Bsd"];
		popStDevs[1] = j[i]["Tsd"];
		popStDevs[2] = j[i]["Csd"];
		popStDevs[3] = j[i]["Hsd"];
		popStDevs[4] = j[i]["Psd"];
		popStDevs[5] = j[i]["Osd"];

		// percentMatch is found in stdev.cpp
		double percMatch = percentMatch(popMeans, popStDevs, userScores);

		// put answer into jobMatches array as a jobResult
		jobResult temp;
		temp.jobName = j[i]["JobName"].get<string>();
		temp.percentile = percMatch;
		jobMatches[i] = temp;
	}

	// step four: sort jobMatches
	std::sort(jobMatches.begin(), jobMatches.end(), compare);

	return jobMatches;
}