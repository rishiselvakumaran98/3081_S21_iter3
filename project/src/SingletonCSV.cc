#include "SingletonCSV.h"

namespace csci3081 {
		SingletonCSV* SingletonCSV::csvptr = nullptr;

SingletonCSV* SingletonCSV::GetSingleton() {
	if (SingletonCSV::csvptr == nullptr) {
		SingletonCSV::csvptr = new SingletonCSV();
		return SingletonCSV::csvptr;
	} //close if
	else {
		return SingletonCSV::csvptr;
	} //close else 
}//close function

void SingletonCSV::WriteToCSV(std::string name, float num) {
		std::ofstream file;
		file.open(name, std::ios::out|std::ios::app); //this is a output file and all operations are output are performed at the end of the file
			file << num << ", "; //write the float and a comma to the file 
		file.close();
} //close function

void SingletonCSV::helper_add_nl(std::string name) {
			std::ofstream file;
			file.open(name, std::ios::out|std::ios::app); //this is a output file and all operations are output are performed at the end of the file
				file << "\n"; //write a new line character
			file.close();
}

void SingletonCSV::CleanFile(std::string filename) {
	std::ofstream file;
	file.open(filename, std::ios::out|std::ios::trunc); //truncked the file so everytime we run the simulation it empties it.
//	file.clear(); //this function cleans the file everytime that the simulation runs
	file.close(); //closes the file
}

void SingletonCSV::helper_add_time(std::string name, float t) {
			std::ofstream file;
			file.open(name, std::ios::out|std::ios::app); //this is a output file and all operations are output are performed at the end of the file
				file << t << ", "; //write the time to the file 
			file.close();
		}//close function

void SingletonCSV::ClearFiles(std::vector<std::string> filenames) {
	for (int i = 0; i < filenames.size(); i++) {
		CleanFile(filenames.at(i));
	}// close for loop
} //close function  

void SingletonCSV::AddLineToFiles(std::vector<std::string> filenames) {

	for (int i = 0; i < filenames.size(); i++) {
		helper_add_nl( filenames.at(i) );
	}//close for loop
}//close function

void SingletonCSV::AddTimeToFiles(std::vector<std::string> filenames, float t) {
	for (int i = 0; i < filenames.size(); i++) {
		helper_add_time(filenames.at(i), t);
	}//close for loop
}//close function 

} //close namespace