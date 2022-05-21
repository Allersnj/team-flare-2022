#include "JobSuggest.h"
int main(){
	std::array<jobResult,11> jobs = jobSuggest();
	for(jobResult job : jobs){
		double perc = job.percentile*100;
		cout << job.jobName << ": " << perc << "% Match\n";
	}
	return 0;
}