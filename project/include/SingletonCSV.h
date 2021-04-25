/**
 *@file Parabolic.h
 */
#ifndef SINGLETONCSV_H_
#define SINGLETONCSV_H_

/**
 * include
 */

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
namespace csci3081 { 
	/**
	 * @brief This class provides the necessary methods to write to an csv file that will store the data collected on the drone movements.
	 */
	class SingletonCSV {
		private:
			// a SingletonCSV object pointer.
			static SingletonCSV* csvptr;
			/**
			 * @brief private constructor that creates a single instance of the SingletonCSV class.
			 */
			SingletonCSV() {
			}//close constructor

		public:
			/**
			 * @brief a public constructor that destroys the single instance and the csvptr private varaible. 
			 */
			~SingletonCSV() {
				delete csvptr;;
			}

			/** 
			 * @brief this function checks if csvptr is null, if it is creates a new instance of singletonCSV and assigns it to csvptr. If it is not null, it returns csvptr.
			*/
			static SingletonCSV* GetSingleton();
			/**
			 * @brief this method writes data to the CSV file
			 * @param[In] filename: the name of the file to write the data to.
			 * @param[In] num: number of bytes to write to the file.
			*/
			void WriteToCSV(std::string filename, float num);
			/**
			 * @brief this method helps to write the standard title of the columns into the csv file
			 * such as "x-axis", "y-axis", "z-axis", "time", "Battery level"
			 * @param[In] filename: the name of the file to write the data to.
			*/
			void WriteStandardTitleToCSV(std::string filename);
			/**
			 * @brief this method writes the drone position data, time of simulation, drone battery_level to the CSV file
			 * @param[In] filename: the name of the file to write the data to.
			 * @param[In] pos: vector<float> position of the drone
			 * @param[In] battery_level: The current battery_level of the drone 
			*/
			void WritePositionToCSV(std::string filename, std::vector<float> pos, float time, float battery_level);
			/**
			 * @brief a helper method to write a newline character into a CSV file. This helper is used to move to the next row of data in a CSV file, ensuring proper CSV formatting of rows.
			 * @param[In] filename: the name of the csv file to add the new line to.
			*/
			void helper_add_nl(std::string filename);
			/**
			 * @brief a helper method to add time in seconds to a CSV file given the filename. This helper is used within delivery_simulation.cc to add times from the simulation onto a .csv file for data analysis.
			 * @param[In] filename: the name of the csv file to add the time to.
			*/
			void helper_add_time(std::string filename, float time);
			/** 
			 * @brief a method to empty the contents of a CSV file given the filename. This method is used if we need to reuse a CSV file for new data analysis or re-run a program that uses a constant csv file for data.
			 * @param[In] filename: the name of to be cleaned.
			 * @param[In] time: the time interval to be added to the file.
			*/
			void CleanFile(std::string filename);
			/** 
			 * @brief : a plural version of the CleanFile method that essentially uses CleanFile for every file given in a vector of .csv files. 
			 * @param[In] filenams: a vector of filenames that contains all the files to be cleaned.
			*/
			void ClearFiles(std::vector<std::string> filenames);
			/** 
			 * @brief a generic method to add a given line to a provided vector of files. This method is overloaded to also be able to add a given time to the files.
			 * @param[In] filenames: a vector containing all the files and the given line will be added to.
			*/
			void AddLineToFiles(std::vector<std::string> filenames);
			/** 
			 * @brief a method to add given time intervals to a provided vector of files.
			 * @param[In] filenames: a vector of files containing all the files that the given time interval will be added to.
			 * @param[In] t: the time interval to be added to the given filenames vector.
			*/
			void AddTimeToFiles(std::vector<std::string> filenames, float t);
	}; //close class
}//close namespace csci3081
#endif // SINGLETONCSV_H_