#ifndef SINGLETONCSV_H_
#define SINGLETONCSV_H_
#include <string>
#include <fstream>
#include <iostream>

namespace csci3081 { 
class SingletonCSV {
	private:
		static SingletonCSV* csvptr;
		SingletonCSV() {
			
		}//close constructor
		
	public:

//this function checks if csvptr is null, if it is creates a new instance of singletonCSV and assigns it to csvptr. If it is not null, it returns csvptr.
				static SingletonCSV* GetSingleton();

				void WriteToCSV(std::string name, float num);
				void helper_add_nl(std::string name);
				void helper_add_time(std::string name, float time);
				void CleanFile(std::string filename);

}; //close class

}//close namespace

#endif