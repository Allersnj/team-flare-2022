#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "jobResult.h"
#include <math.h>
#include "nlohmann/json.hpp"
#include "stdev.cpp"

using json = nlohmann::json;

bool compare (jobResult job1, jobResult job2){
	return(job1.percentile > job2.percentile);
}

jobResult * jobSuggest() {
	//step one: yoink all data from the json
	std::ifstream data {"MockJobCharacteristics.json"};
    json j{json::parse(data)};

	//step two: "take" an "input"
	int userScores[] = {8,7,6,5,4,6};

	//step three: calculate many times
	static jobResult jobMatches[11];
	for(int i = 0; i < 11; i++){
		//yoink the i-th datapoints into arrays
		double popMeans[6];
		popMeans[0] = j[i]["Bmean"];
		popMeans[1] = j[i]["Tmean"];
		popMeans[2] = j[i]["Cmean"];
		popMeans[3] = j[i]["Hmean"];
		popMeans[4] = j[i]["Pmean"];
		popMeans[5] = j[i]["Omean"];
		double popStDevs[6];
		popStDevs[0] = j[i]["Bsd"];
		popStDevs[1] = j[i]["Tsd"];
		popStDevs[2] = j[i]["Csd"];
		popStDevs[3] = j[i]["Hsd"];
		popStDevs[4] = j[i]["Psd"];
		popStDevs[5] = j[i]["Osd"];

		//chunch the arrays
		double percMatch = percentMatch(popMeans, popStDevs, userScores);

		//spit answer into jobMatches[]
		jobResult temp;
		temp.jobName = j[i]["JobName"].get<string>();
		temp.percentile = percMatch;
		jobMatches[i] = temp;
	}

	//step four: sort jobMatches
	std::sort(jobMatches, jobMatches+11, compare);

	// //step five: print some results, used for testing only
	// for(jobResult job : jobMatches){
	// 	double perc = job.percentile*100;
	// 	cout << job.jobName << ": " << perc << "%\n";
	// }

	return jobMatches;
}