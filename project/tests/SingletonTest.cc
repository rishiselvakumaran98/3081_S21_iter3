#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <vector>
#include <iostream>
#include "Vector3D.h"
//#include "Battery.h"
#include "SingletonCSV.h"
namespace csci3081 {

using entity_project::IEntity;

class SingletonCSVTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
}

  virtual void TearDown() {}
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(SingletonCSVTest, Write_To_csv_tests) {
	SingletonCSV* sing = SingletonCSV::GetSingleton();
	sing->CleanFile("testing.csv");
	sing->helper_add_time("testing.csv", 10.0f);
	sing->WriteToCSV("testing.csv", 100);
	sing->helper_add_nl("testing.csv");

	sing->helper_add_time("testing.csv", 20.0f);
	sing->WriteToCSV("testing.csv", 200);

}//end function

//};// end class
} //close namespace

