import csv
import math
def main():
    sum_x_sq, sum_y_sq, sum_z_sq = 0, 0, 0
    distance_x, distance_y, distance_z, individual_distance, Total_distance = 0, 0, 0, 0, 0

    with open(r"3081_s21/repo-iter3-01-06/project/Data_analysis/Paths/beeline_drone.csv") as csvDatafile:
        # open a csv file to write into
        file = open(r"3081_s21/repo-iter3-01-06/project/Data_analysis/Distances/beeline_distance.csv","w") 
        headers = "distance_x, distance_y, distance_z, distance_between_points, time\n"
        # Write the distance between the points
        file.write(headers)
        data = list(csv.reader(csvDatafile))
        for i in range(1,len(data)-1):
            #compute the absolute value for the difference in the first and second values
            sum_x_sq = pow(abs(float(data[i][0]) - float(data[i+1][0])),2) 
            sum_y_sq = pow(abs(float(data[i][1]) - float(data[i+1][1])),2) 
            sum_z_sq = pow(abs(float(data[i][2]) - float(data[i+1][2])),2)
            distance_x = abs(float(data[i][0]) - float(data[i+1][0]))
            distance_y = abs(float(data[i][1]) - float(data[i+1][1]))
            distance_z = abs(float(data[i][2]) - float(data[i+1][2]))
            individual_distance =  math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            # write to the csv file distance_x, distance_y, distance_z, distance_between_points, time 
            file.write(str(distance_x) + ", " + str(distance_y) + ", " + str(distance_z) + ", " \
                + str(individual_distance) + ", " + data[i][3] +  '\n')
            Total_distance += math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
        print ("| Initial Battery: " + data[1][4] + \
            "\n| Final battery: " + data[len(data)-1][4] +  \
            "\n| Total Battery charge Lost: {0:0.3f}".format(float(data[1][4])-float(data[len(data)-1][4])))
    print("Total Distance travelled: {0:0.3f}".format(float(Total_distance)))
# main() 

def main_2():
    sum_x_sq, sum_y_sq, sum_z_sq = 0, 0, 0
    distance_x, distance_y, distance_z, individual_distance, Total_distance = 0, 0, 0, 0, 0

    with open(r"3081_s21/repo-iter3-01-06/project/Data_analysis/Paths/smart_drone.csv") as csvDatafile:
        # open a csv file to write into
        file = open(r"3081_s21/repo-iter3-01-06/project/Data_analysis/Distances/smart_distance.csv","w")  
        headers = "distance_x, distance_y, distance_z, distance_between_points, time\n"
        file.write(headers)
        data = list(csv.reader(csvDatafile))
        for i in range(1,len(data)-1):
            #compute the absolute value for the difference in the first and second values
            sum_x_sq = pow(abs(float(data[i][0]) - float(data[i+1][0])),2) 
            sum_y_sq = pow(abs(float(data[i][1]) - float(data[i+1][1])),2) 
            sum_z_sq = pow(abs(float(data[i][2]) - float(data[i+1][2])),2)
            distance_x = abs(float(data[i][0]) - float(data[i+1][0]))
            distance_y = abs(float(data[i][1]) - float(data[i+1][1]))
            distance_z = abs(float(data[i][2]) - float(data[i+1][2]))
            individual_distance =  math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            # write to the csv file distance_x, distance_y, distance_z, distance_between_points, time 
            file.write(str(distance_x) + ", " + str(distance_y) + ", " + str(distance_z) + ", " \
                + str(individual_distance) + ", " + data[i][3] + '\n')
            Total_distance += math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq) 

        print ("| Initial Battery: " + data[1][4] + \
            "\n| Final battery: " + data[len(data)-1][4] +  \
            "\n| Total Battery charge Lost: {0:0.3f}".format(float(data[1][4])-float(data[len(data)-1][4])))
    print("Total Distance travelled: {0:0.3f}".format(float(Total_distance)))

# main_2() 

def main_3():
    sum_x_sq, sum_y_sq, sum_z_sq = 0, 0, 0
    distance_x, distance_y, distance_z, individual_distance, Total_distance = 0, 0, 0, 0, 0

    with open(r"3081_s21/repo-iter3-01-06/project/Data_analysis/Paths/parabolic_drone.csv") as csvDatafile:
        # open a csv file to write into
        file = open(r"3081_s21/repo-iter3-01-06/project/Data_analysis/Distances/parabolic_distance.csv","w")
        headers = "distance_x, distance_y, distance_z, distance_between_points, time\n"
        file.write(headers)
        data = list(csv.reader(csvDatafile))
        for i in range(1,len(data)-1):
            #compute the absolute value for the difference in the first and second values
            sum_x_sq = pow(abs(float(data[i][0]) - float(data[i+1][0])),2) 
            sum_y_sq = pow(abs(float(data[i][1]) - float(data[i+1][1])),2) 
            sum_z_sq = pow(abs(float(data[i][2]) - float(data[i+1][2])),2)
            distance_x = abs(float(data[i][0]) - float(data[i+1][0]))
            distance_y = abs(float(data[i][1]) - float(data[i+1][1]))
            distance_z = abs(float(data[i][2]) - float(data[i+1][2]))
            individual_distance =  math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            # write to the csv file distance_x, distance_y, distance_z, distance_between_points, time 
            file.write(str(distance_x) + ", " + str(distance_y) + ", " + str(distance_z) + ", " + str(individual_distance) + ", " + data[i][3] + '\n')
            Total_distance += math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
 
        print ("| Initial Battery: " + data[1][4] + \
            "\n| Final battery: " + data[len(data)-1][4] +  \
            "\n| Total Battery charge Lost: {0:0.3f}".format(float(data[1][4])-float(data[len(data)-1][4])))
    print("Total Distance travelled: {0:0.3f}".format(float(Total_distance)))

main_3()