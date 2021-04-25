#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <vector>
#include <iostream>
#include "Customer.h"
#include "Vector3D.h"
#include "IStrategy.h"
#include <fstream>
#include "SingletonCSV.h"

namespace csci3081{
    using entity_project::IEntity;
    class Singleton_test : public ::testing::Test {
        protected:
        virtual void setup() {
            sing = SingletonCSV::GetSingleton();
        }
        virtual void TearDown() {}
        SingletonCSV *sing;

    };

    TEST_F(Singleton_test, get_instance) {
        ASSERT_NE(nullptr,  sing);
    }
    TEST_F(Singleton_test,write_to_file) {
        sing->CleanFile("file.txt");
        sing->WriteToCSV("file.txt",20);
        std::string line;
        std::ifstream my_file("file.txt");
        if (my_file.is_open()) {
            getline(my_file, line);
            EXPECT_EQ(line,"20, ");
        }
    }
    TEST_F(Singleton_test,WriteStandardTitleToCSV) {
        sing->CleanFile("file.txt");
        sing->WriteStandardTitleToCSV("file.txt");
        std::string line;
        std::ifstream my_file("file.txt");
        if (my_file.is_open()) {
            getline(my_file, line);
            EXPECT_EQ(line,"x-axis, y-axis, z-axis, time, Battery level");
        }
    }

    TEST_F(Singleton_test,WritePositionToCSV) {
        sing->CleanFile("file.txt");
        std::vector<float> pos = {10,20,30};
        sing->WritePositionToCSV("file.txt",pos,10,1000);
        std::string line;
        std::ifstream my_file("file.txt");
        if (my_file.is_open()) {
            getline(my_file, line);
            EXPECT_EQ(line,"10,20,30,10,1000");
        }
    }

    TEST_F(Singleton_test,helper_add_nl) {
        sing->CleanFile("file.txt");
        sing->helper_add_nl("file.txt");
        std::string line;
        std::ifstream my_file("file.txt");
        if (my_file.is_open()) {
            getline(my_file, line);
            EXPECT_EQ(line,"");
        }
    }
    TEST_F(Singleton_test,CleanFile) {
        sing->CleanFile("file.txt");
        std::string line;
        std::ifstream my_file("file.txt");
        if (my_file.is_open()) {
            getline(my_file, line);
            EXPECT_EQ(line,"");
        }
    }
    TEST_F(Singleton_test,helper_add_time) {
        sing->CleanFile("file.txt");
        sing->helper_add_time("file.txt",20);
        std::string line;
        std::ifstream my_file("file.txt");
        if (my_file.is_open()) {
            getline(my_file, line);
            EXPECT_EQ(line,"20\t");
        }
    }
    TEST_F(Singleton_test,ClearFiles) {
        std::vector<std::string> files =  {"file_.txt","file_2.txt", "file_3.txt"};
        sing->ClearFiles(files);
        std::string line;
        for (int i = 0; i < files.size();i++) {
            std::ifstream file(files[i]);
            if (file.is_open()) {
                getline(file,line);
                EXPECT_EQ(line, "");
            }
        }
    }
    TEST_F(Singleton_test,AddLineToFiles) {
        std::vector<std::string> files =  {"file_.txt","file_2.txt", "file_3.txt"};
        sing->ClearFiles(files);
        sing->AddLineToFiles(files);
        std::string line;
        for (int i = 0; i < files.size();i++) {
            std::ifstream file(files[i]);
            if (file.is_open()) {
                getline(file,line);
                EXPECT_EQ(line, "");
            }
        }
    }

    TEST_F(Singleton_test,AddTimeToFiles) {
        std::vector<std::string> files =  {"file_.txt","file_2.txt", "file_3.txt"};
        sing->ClearFiles(files);
        sing->AddTimeToFiles(files,20);
        std::string line;
        for (int i = 0; i < files.size();i++) {
            std::ifstream file(files[i]);
            if (file.is_open()) {
                getline(file,line);
                EXPECT_EQ(line, "20\t");
            }
        }
    }
}
