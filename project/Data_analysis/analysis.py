import csv
import math
def main():
    sum_x_sq = 0
    sum_y_sq = 0
    sum_z_sq = 0
    distance_x = 0
    distance_y = 0
    distance_z = 0 
    individua_distance = 0
    # distance = 0
    Total_distance = 0
    with open(r"/home/linux_en/desktop/repo-iter3-01-06/project/smart_drone.csv") as csvDatafile:
        # open a csv file
        file = open("smart_distance.csv","w") 
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
            individua_distance =  math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            file.write(str(distance_x) + ", " + str(distance_y) + ", " + str(distance_z) + ", " + str(individua_distance) + ", " + data[i][3] +  '\n')
            # distance = math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            Total_distance += math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            # write to the csv file x_distance, y_distance, z_distance, distance_between_points(distance), 
        print ("| Initial Battery: " + data[1][4] + \
            "\n| Final battery: " + data[len(data)-1][4] +  \
            "\n| Total Battery charge Lost: {0:0.3f}".format(float(data[1][4])-float(data[len(data)-1][4])))
    print("Total Distance travelled: {0:0.3f}".format(float(Total_distance)))


def main_2():
    sum_x_sq = 0
    sum_y_sq = 0
    sum_z_sq = 0
    distance_x = 0
    distance_y = 0
    distance_z = 0 
    individua_distance = 0
    # distance = 0
    Total_distance = 0
    with open(r"/home/linux_en/desktop/repo-iter3-01-06/project/beeline_drone.csv") as csvDatafile:
        # open a csv file
        file = open("beeline_distance.csv","w") 
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
            individua_distance =  math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            file.write(str(distance_x) + ", " + str(distance_y) + ", " + str(distance_z) + ", " + str(individua_distance) + ", " + data[i][3] + '\n')
            # distance = math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            Total_distance += math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            # write to the csv file x_distance, y_distance, z_distance, distance_between_points(distance), 
        print ("| Initial Battery: " + data[1][4] + \
            "\n| Final battery: " + data[len(data)-1][4] +  \
            "\n| Total Battery charge Lost: {0:0.3f}".format(float(data[1][4])-float(data[len(data)-1][4])))
    print("Total Distance travelled: {0:0.3f}".format(float(Total_distance)))

def main_3():
    sum_x_sq = 0
    sum_y_sq = 0
    sum_z_sq = 0
    distance_x = 0
    distance_y = 0
    distance_z = 0 
    individua_distance = 0
    # distance = 0
    Total_distance = 0
    with open(r"/home/linux_en/desktop/repo-iter3-01-06/project/parabolic_drone.csv") as csvDatafile:
        # open a csv file
        file = open("parabolic_distance.csv","w") 
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
            individua_distance =  math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            file.write(str(distance_x) + ", " + str(distance_y) + ", " + str(distance_z) + ", " + str(individua_distance) + ", " + data[i][3] + '\n')
            # distance = math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            Total_distance += math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            # write to the csv file x_distance, y_distance, z_distance, distance_between_points(distance), 
        print ("| Initial Battery: " + data[1][4] + \
            "\n| Final battery: " + data[len(data)-1][4] +  \
            "\n| Total Battery charge Lost: {0:0.3f}".format(float(data[1][4])-float(data[len(data)-1][4])))
    print("Total Distance travelled: {0:0.3f}".format(float(Total_distance)))

main() 
main_2() 
main_3()