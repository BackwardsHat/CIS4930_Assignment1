// Author: Jospeh Furiate
// FSUID:  jaf13j

#include <iostream>
#include <fstream>
#include <algorithm>	// sort()
#include <math.h>		// ceil(), floor()
#include <iomanip>
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
		// Sorting is needed to find quartiles
		sort(midtermScores.begin(), midtermScores.end());
		sort(finalScores.begin(), finalScores.end());

		cout << "\nMidterm Stats";
		calcStatistics(midtermScores);
		cout << "\nFinals Stats";
		calcStatistics(finalScores);
	}

	return exitStatus;
}

// Reads and parses given file
// Expected file format: <ignore>\t<midterm>\t<final>\n
int readInput(
		const char * filename,
	   	vector<int>& midtermScores,
	   	vector<int>& finalScores) {
	ifstream inFile(filename);
	char str[255];
	int mtScore, fScore;

	// Error checking
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

// Calculates 1st quartile
double calcQ1(const vector<int>& scores) {
	int n = scores.size();
	int a, b;

	// a and b will be the same value if n is odd
	a = (floor((n-1) * .25));
	b = (ceil((n-1) * .25));

	return (scores[a] + scores[b]) / 2.0;
}

// Calculates 3rd quartile
double calcQ3(const vector<int>& scores) {
	int n = scores.size();
	int a, b;

	// a and b will be the same value if n is odd
	a = (floor((n-1)* .75));
	b = (ceil((n-1) * .75));

	return (scores[a] + scores[b]) / 2.0;
}

// Calculates standard deviation
double calcStdDev(const vector<int>& scores, double mean) {
	double variance = 0;

	// Sums (mean - x_i)^2
	for(vector<int>::const_iterator it = scores.begin();
			it != scores.end(); ++it) {
		variance += pow(mean - *it, 2);
	}

	return sqrt(variance / scores.size());
	
	// variance /= scores.size();
	// cout << "\nVariance: \t" << variance;
	// return sqrt(variance);
}

void calcStatistics(const vector<int>& scores) {
	int max, min, n;	
	double mean, std_dev, median, q1, q3; 
	int buckets[102] = {0}; // Enough for 0 to 100  	
	int maxModeCount = 0;
	
	n = scores.size(); // Score numbers

	// Set to `impossible` values before calculating 
	mean = 0;
	min = 99999;
	max = -99999;

	// Quartiles
	median = scores[(n-1)/2]; 
	q1 = calcQ1(scores);
	q3 = calcQ3(scores);

	// Calculates min, max, and sums mean and fills mode buckets
	for(vector<int>::const_iterator it = scores.begin();
			it != scores.end(); ++it) {
		if(*it > max) max = *it;
		if(*it < min) min = *it;
		mean += *it;

		// Counts occurences of each score
		buckets[*it]++;
		// Tracks highest occurence of some score
		if(maxModeCount < buckets[*it])
		   	maxModeCount = buckets[*it];
	}

	// Mean and standard deviation
	mean /= n;
	std_dev = calcStdDev(scores, mean);

	cout << fixed;
	cout << setprecision(3);
	cout << "\nMax:\t\t" 	<< max 
		 << "\nMin:\t\t" 	<< min
		 << "\nMedian:\t\t"<< median
		 << "\nMean:\t\t" 	<< mean
		 << "\nStd Dev:\t"	<< std_dev
		 << "\nQ1:\t\t"		<< q1
		 << "\nQ3:\t\t"		<< q3;
	
	cout << "\nMode:\t\t";
	// Outputs scores with the highest occurence 
	for(int i = 0; i < 101; ++i)
		if(buckets[i] == maxModeCount)
			cout << i << ' ';

	cout << '\n';
}
