/*! \mainpage CSCI 3081 Delivery Simulation project
*
* 
*
* To generate documentation, first build the project with `make` in the `project` directory.
* Next, navigate to `project/docs` and run `doxygen Doxyfile`.


* \section Introduction
## Welcome to the CSCI 3081 Drone Simulation Project!

 \subsection documentation_demo To view the documentation for this project

    (Make sure to have python3 installed on your local machine)

~~~~~~~~~~~~~~
    # MUST be within project/docs/html directory
    cd /home/user/repo/project/docs/html
    python3 -m http.server
~~~~~~~~~~~~~~

To build and run the project make sure to have the right environment.
*****************************
Some of the common environments to run the projects include Docker, Linux platforms, CSE Lab Machines or VOLE/VOLE 3D

First open up a Terminal and cd into the `repo-selva053` directory,
Then,

- Build the docker image

~~~~~~~~~~~~~~{.sh}   
    bin/build-env.sh
~~~~~~~~~~~~~~

- Run docker image

~~~~~~~~~~~~~~
    #Usage bin/run-env.sh <port - optional(default 8081)>
    bin/run-env.sh
~~~~~~~~~~~~~~
    
- Build project web server (inside docker image) NOTE: You won't be able to `cd` here yet because the project directory does not exist. If you were able to launch the above commands you should now be inside the docker image. You can exit it with CTRL+D now.

~~~~~~~~~~~~~~
    # Inside docker image
    cd /home/user/repo/project
    make
~~~~~~~~~~~~~~
    
- Run web server (inside docker image)

~~~~~~~~~~~~~~
    # MUST be within project/ directory inside docker image
    cd /home/user/repo/project
    ./bin/run.sh
~~~~~~~~~~~~~~
    
- Open up Firefox and browse to http://127.0.0.1:8081/

 


## Getting Started using SSH on CSE Lab machines

- Initial Setup of remote web server (full copy)

~~~~~~~~~~~~~~
    #Example: ./project/bin/setup-server.sh dtorban 05
    ./project/bin/setup-server.sh <username> <computer_number>
~~~~~~~~~~~~~~

- Run remote web server (only copies src directory)

~~~~~~~~~~~~~~
    #Example: ./project/bin/server.sh dtorban 05 8081
    ./project/bin/server.sh <username> <computer_number> <port>
~~~~~~~~~~~~~~

    
- Open up Firefox and browse to http://127.0.0.1:8081/

## Getting Started with VOLE-3D or VOLE

- Log on to [VOLE-3D or VOLE](https://vole.cse.umn.edu/) (VOLE is slower for graphics, but is great for tests, etc...)

- Build project

~~~~~~~~~~~~~~
    cd /path/to/cloned/repository
    cd project
    make
~~~~~~~~~~~~~~
    
 - Run project

~~~~~~~~~~~~~~
    # MUST be within project/ directory <scenes/<scene>.json - optional(default umn.json)>
    ./bin/run.sh
~~~~~~~~~~~~~~
    
 - Open up Firefox and browse to http://127.0.0.1:8081/ 


  \section feature_singletoncsv Singleton Pattern feature Applied to Collect drone Route Data

  We wanted to analyze the efficiency of the three routes that we implemented in Iteration 2: the Smart Path, the Beeline Path, and the Parabolic Path. 
  In order to collect the data for this analysis, we implemented a CSV file writer class named `SingletonCSV` that, appropriately, used the Singleton Pattern in its design.

  The Singleton pattern is a design pattern based around a class that makes sure that only one instance of itself exists and it grants programs simple access to the instance. 
  The singleton pattern includes a private constructor and a static getter method for getting its SingletonCSV* pointer.
  In our specific case, we wanted to ensure that the CSV files were only able to be modified by the functions within the singletonCSV class, and that there was only one CSV file for a simulation. 
  We wanted to acquire Drone distance and battery drain data for each of the three routes. Thus, we wanted three separate CSV files worth of simulation data. The Singleton Pattern, in this case, was an excellent solution
  as it not only ensured that all of the simulation data from each route/path (Smart, Beeline, Parabolic) could go into its own CSV file, but that the modifications to store the simulation data would be minimal 
  and simple to implement within the delivery_simulation class.
  
  \section simulationscenes Scenes that were chosen to run for testing the SingletonCSV pattern:

    The following scenes were used for testing the SingletonCSV pattern:
    - smart_drone.json
    - beeline_drone.json 
    - parabolic_drone.json 

    To run the specific scenes for the project:
~~~~~~~~~~~~~~
    # MUST be within project/ directory <scenes/<scene>.json - optional (default umn.json)>
    ./bin/run.sh scenes/<scenes_listed_above_1_by_1>
~~~~~~~~~~~~~~

   \section singletonPatternImplementation Singleton Pattern implementation for Iteration 3:

    This was how Lucas implemented the Singleton Pattern to access and modify a given CSV file:

  \htmlonly
    <embed src="SingletonCSV.PNG" width="50%" height="50%" href="SingletonCSV.PNG"></embed>
  \endhtmlonly

  The implementation consists of 10 methods to facilitate the modification of data on a CSV file.

  `GetSingleton()`: This function checks if csvptr is null, if it is creates a new instance of singletonCSV and assigns it to csvptr. If it is not null, it returns csvptr.

  `WriteToCSV()`: This method takes in the filename and a float number to write to the file. This method was used as a tester to check if float numbers could be added to a csv file 
  
  `WriteStandardTitleToCSV()`: This method helps to write the standard title of the columns into the csv file such as "x-axis", "y-axis", "z-axis", "time", "Battery level"

  `WritePositionToCSV()`: This method takes in the drone position data, time of simulation, drone battery_level and writes it to the CSV file

  `helper_add_nl()`: A helper method to write a newline character into a CSV file. This helper is used to move to the next row of data in a CSV file, ensuring proper CSV formatting of rows.

  `helper_add_time()`: A helper method to add time in seconds to a CSV file given the filename. This helper is used within delivery_simulation.cc to add times from the simulation onto a .csv file for data analysis.

  `CleanFile()`: A method to empty the contents of a CSV file given the filename. This method is used if we need to reuse a CSV file for new data analysis or re-run a program that uses a constant csv file for data
  
  `ClearFiles()`: A multi-file version of the CleanFile method that essentially runs CleanFile on every file present in a given vector of .csv files.
  
  `AddLineToFiles()`: A generic method to add a given line to a provided vector of files. This method is overloaded to also be able to add a given time to the files.

  `AddTimeToFiles()`: Method to add given time intervals to a provided vector of files. This method updates multiple files with the same time given for analysis on simulations with multiple entities

  After implemnting the SingletoCSV Pattern, we utilized it within the deliverysimulation class to analyze the drone position for each individual simulation ran on 
  - Beeline_drone.json 
  - smart_drone.json 
  - parabolic_drone.json

  For the each of the simulation analysis, we changed the filename according to the name of the scene that we analyzed which in this case translates to 3 CSV files generated called:

  - Beeline_drone.csv 
  - smart_drone.csv 
  - parabolic_drone.csv 

  We then used these csv files above for analyzing the drone movements and distinguishing which path would be the most efficient in helping the drone conserve battery life
  while delivering the package to the customers. 

  \htmlonly
  <embed src="dp2.png" width="50%" height="50%" href="dp2.png"></embed>
  \endhtmlonly

  These methods are used in synergy to populate .csv files with the real-times from the Delivery Simulation we run, while also providing the distances traveled by the Drone for each path in the simulation.


  \section team_sec Team Documentation

    The roles for Iteration 3 were split as follows:

    Lucas: Implementing singletonCSV.h and singletonCSV.cc, as well as adding time statistics to CSV file.

    Rishi: Utilizing singletonCSV source files to collect statistics in CSV files for all three routes (beeline, smart, parabolic).

    Hamza: Utilizing Plotly to generate graphs from data collected for CSV files, ensuring proper documentation of header files, assisting in writing the Team Documentation section, creating google tests for singletonCSV

    Shreyas: Completing all documentation requirements for the iteration: writing discussions for Singleton Pattern and Team Documentation, as well as writing the Slides for the Presentation

    Meeting Day 1 - 4/20/2021:
    We held this meeting to go over Iteration 3 requirements, and clarify individual roles.
    Lucas, who wanted to implement the Singleton pattern for data analysis, understood the implementation well and wanted the group to reconvene once he was finished.
    Lucas ended up finalizing the Singleton pattern implementation (singletonCSV.h, singletonCSV.cc) at around 4 PM. Thus, we held a second meeting to discuss his implementation.
    Lucas explained the functionality and proper use of the methods in singletonCSV.cc to Rishi, who wanted to work on analyzing distance and battery drain data for the three routes.
    After this meeting, Rishi began data collection.

    Meeting 2 - 4/21/2021:
    We held this meeting because Rishi had finished data collection. Rishi explained how he added distance and battery data to the CSV files using Lucas's singletonCSV design. 
    The group searched for data analysis methods/platforms on the internet and settled on using Plotly (chart-studio.plotly.com) to create graphs.
    Hamza wanted to perform data analysis, and thus Rishi provided Hamza the CSV files from his data collection, and the group agreed to meet once Hamza was finished with his data analysis.
    Hamza finished his data analysis at around 10 PM on Thursday, and the group decided to meet the next day to discuss what the data showed, and talk about documenting the Iteration.

    Meeting Day 3 - 4/23/2021: 
    This meeting was held in order to understand which route was shown to be the most battery-efficient from both the graphs and the data on distance traveled and to understand why this was the case.
    After looking at all the data as a group, it was clear that the Parabolic Path was the most battery-efficient route for the Drone to travel when picking up packages and delivering them to customers.
    Once we arrived at this conclusion, Shreyas revealed that he had taken notes during every meeting and had a solid thesis/argument for why the Parabolic Path was the most efficient, and that he had already began writing the Documentation for the Iteration.
    Shreyas wanted to write the bulk of the documentation/design section as he had a good idea of the work each team member had done, and already had detailed notes on how the main feature in the Iteration - Singleton Pattern - functioned.
    Additionally, Hamza wanted to assist in writing the Team Documentation section, as well as ensuring the header files were well-documented. The group agreed to meet once the Documentation was finalized by Shreyas and Hamza.

    Meeting Day 4 - 4/25/2021:
    Once both Shreyas and Hamza were finished writing large parts of the Documentation Section, the group went through the entire project in a meeting to ensure that all the requirements were met.


   \section graph_an Data Analysis

   The following are the visualizations from the data we gathered on the distance the Drone traveled for each of the routes.

    \htmlonly
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~hamza122000/1.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~hamza122000/3.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~hamza122000/5.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~hamza122000/7.embed"></iframe> 
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~hamza122000/9.embed"></iframe> 
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~hamza122000/11.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~hamza122000/13.embed"></iframe>  
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~hamza122000/15.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~hamza122000/17.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~hamza122000/19.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~hamza122000/21.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~hamza122000/23.embed"></iframe>
    \endhtmlonly

    The distance graphs above indicate to us the amount of distance between the points covered by the different drone paths.
    These distance between the points show us the amount of energy lost by the drone which from the parabolic graph above (for x,y,z axis) we could
    see that the distance between the points are much smaller than the other paths such as Beeline, and Smart. This also showcases that the Parabolic path 
    would cause the drone to travel overall smaller distance to reach its positions within the simulation, which would help the drone conserver more battery,
    while delivering multiple packages to customers.

    \section dronemove Drone movement graphs

    \htmlonly
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~RishiBoy98/18.embed"></iframe>    
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~RishiBoy98/19.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~RishiBoy98/20.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~RishiBoy98/22.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~RishiBoy98/23.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~RishiBoy98/24.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~RishiBoy98/26.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~RishiBoy98/27.embed"></iframe>
    <iframe width="600" height="500" frameborder="0" scrolling="no" src="//plotly.com/~RishiBoy98/28.embed"></iframe>
    \endhtmlonly
   
    \section final_takeaways Conclusion: Takeaways from Data Analysis

    From the data we gathered on the distance and battery drain of the routes, it is clear that the Parabolic Path is the most battery efficient path for the Drone to travel,
    as the drone that travelled through the parabolic path took the least amount of time (135.4 secs). 
    Since battery drain is calculated through distance traveled, the path requiring the shortest distance will yield the most energy-efficient path.
    We gathered Drone distance data by summing the total distance traveled using the distance formula. 

    Here is the total distance and battery drain when the Drone travels the Beeline path.

    \htmlonly
    <embed src="beeline_distance_py.png" width="50%" heigth="50%" href="beeline_distance_py.png"></embed>
    \endhtmlonly

    Here is the total distance and battery drain when the Drone travels the Smart path.

    \htmlonly
    <embed src="smart_distance_py.png" width="50%" heigth="50%" href="smart_distance_py.png"></embed>
    \endhtmlonly

    Here is the total distance and battery drain when the Drone travels the Parabolic path.

    \htmlonly
    <embed src="parabolic_distance_py.png" width="50%" heigth="50%" href="parabolic_distance_py.png"></embed>
    \endhtmlonly

    

    From the graphing data above, we can see that the Parabolic path saves the most amount of battery out of all the paths. 
    In the parabolic path, we can see that the drone picks up the package at 64.41 secs as compared to the other paths 
    such as smart path (74.70 secs) and beeline path (82.09 secs) which shows that the parabolic path is more efficient in 
    allowing the drone to travel to the package faster than the other paths, and also to deliver the package to the customer. 
    The time taken for the drone to deliver to the customer using the parabolic path is 135 secs as compared to the smart path (157.2 secs)
    and beeline path (171 secs). Hence from this analysis we could see that the parabolic path is the best path for the drone followed by
    the Smart path is second in terms of efficiency, and the Beeline path is the least battery-efficient of the three. 

*/  


