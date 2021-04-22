#ifndef SINGLETONCSV_H_
#define SINGLETONCSV_H_
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
namespace csci3081 { 
	class SingletonCSV {
		private:
			static SingletonCSV* csvptr;
			SingletonCSV() {
			}//close constructor

		public:
			~SingletonCSV() {
				delete csvptr;;
			}


			//this function checks if csvptr is null, if it is creates a new instance of singletonCSV and assigns it to csvptr. If it is not null, it returns csvptr.
			static SingletonCSV* GetSingleton();

			void WriteToCSV(std::string filename, float num);
			void WriteStandardTitleToCSV(std::string filename);
			void WritePositionToCSV(std::string filename, std::vector<float> pos, float time);
			void helper_add_nl(std::string filename);
			void helper_add_time(std::string filename, float time);
			void CleanFile(std::string filename);
			void ClearFiles(std::vector<std::string> filenames);
			void AddLineToFiles(std::vector<std::string> filenames);
			void AddTimeToFiles(std::vector<std::string> filenames, float t);
	}; //close class

}//close namespace

#endif