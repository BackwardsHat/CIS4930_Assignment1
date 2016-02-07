#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Record {
	int studentId;
	int midtermGrade;
	int finalGrade;
};

typedef vector< Record> RecordList;

int readInput(const char *, const RecordList&); 
double calcMean();

int main(int argc, char * argv[]) {
	if(argc != 2) {
		cout << "Error: Usage: ./<program> <inputFile>\n";
		return 1;
	}
	vector<Record> records;
	
	int exitStatus = readInput(argv[1], records);

	return exitStatus;
}

int readInput(const char * filename, const RecordList& records) {
	ifstream inFile(filename);
	if(!inFile) {
		cout << "Could not open " << filename << ".\n";
		return 1;
	}

	return 0;
}
