#include <iostream>
#include <fstream>
#include <algorithm>	// sort()
#include <math.h>		// ceil(), floor()
#include <vector>

using namespace std;

int readInput(const char *, vector<int>&, vector<int>&); 
void calcStatistics(const vector<int>&);

int main(int argc, char * argv[]) {
	if(argc != 2) {
		cout << "Error: Usage: ./<program> <inputFile>\n";
		return 1;
	}
	
	vector<int> midtermScores;
	vector<int> finalScores;
	int exitStatus = readInput(argv[1], midtermScores, finalScores);

	if(!exitStatus) {
		sort(finalScores.begin(), finalScores.end());
		cout << "\nFinals Stats";
		calcStatistics(finalScores);
	}

	return exitStatus;
}

int readInput(
		const char * filename,
	   	vector<int>& midtermScores,
	   	vector<int>& finalScores) {
	ifstream inFile(filename);
	char str[255];
	int mtScore, fScore;

	if(!inFile) {
		cout << "Could not open " << filename << ".\n";
		return 1;
	}

	while(inFile.getline(str, 255)) {
		sscanf(str, "%*d\t%d\t%d", &mtScore, &fScore);	
		midtermScores.push_back(mtScore);
		finalScores.push_back(fScore);
	}

	inFile.close();
	return 0;
}

double calcQ1(const vector<int>& scores) {
	int n = scores.size();
	int medianPos, a, b;

	medianPos = n % 2 ? 
		(floor(n/2) + ceil(n/2)) / 2 :
		scores.size() / 2;

	// a and b will be the same value if medianPos is even
	a = (int)(floor(medianPos) / 2);
	b = (int)(ceil(medianPos) / 2);

	return (scores[a] + scores[b]) / 2.0;
}

double calcQ3(const vector<int>& scores) {
	int n = scores.size();
	int medianPos, a, b;

	medianPos = n % 2 ? 
		(floor(n/2) + ceil(n/2)) / 2 :
		scores.size() / 2;

	a = medianPos + (int)(floor(medianPos) / 2);
	b = medianPos + (int)(ceil(medianPos) / 2);

	return (scores[a] + scores[b]) / 2.0;
}

double calcStdDev(const vector<int>& scores, double mean) {
	double variance = 0;
	for(vector<int>::const_iterator it = scores.begin();
			it != scores.end(); ++it) {
		variance += pow(mean - *it, 2);
	}
	
	variance /= scores.size();
	cout << "\nVariance: \t" << variance;
	
	return sqrt(variance);
}


void calcStatistics(const vector<int>& scores) {
	int max, min;	
	double mean, std_dev, median, q1, q3; 
	int buckets[101] = {0};	
	int maxModeCount = 0;
	vector<int> mode;
	int length;

	length = scores.size();

	mean = 0;
	min = 9999;
	max = -9999;
	median = scores[(length-1)/2]; 
	q1 = calcQ1(scores);
	q3 = calcQ3(scores);

	for(vector<int>::const_iterator it = scores.begin();
			it != scores.end(); ++it) {
		if(*it > max) max = *it;
		if(*it < min) min = *it;
		mean += *it;

		buckets[*it]++;
		if(maxModeCount < buckets[*it])
		   	maxModeCount = buckets[*it];
	}


	cout << "\nMode: \t";
	for(int i = 0; i < length; ++i)
		if(buckets[i] == maxModeCount)
			cout << buckets[i] << ' ';

	mean /= scores.size();
	std_dev = calcStdDev(scores, mean);

	cout << "\nMax: \t" 	<< max 
		 << "\nMin: \t" 	<< min
		 << "\nMedian: \t"<< median
		 << "\nMean: \t" 	<< mean
		 << "\nStd Dev: "	<< std_dev
		 << "\nQ1: \t"		<< q1
		 << "\nQ3: \t"		<< q3
		 << '\n';
}
