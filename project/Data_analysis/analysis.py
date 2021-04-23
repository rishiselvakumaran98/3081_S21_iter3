import csv
import math
def main():
    sum_x_sq = 0
    sum_y_sq = 0
    sum_z_sq = 0
    # distance = 0
    Total_distance = 0
    with open(r'3081_s21/Data_analysis/smart_drone.csv') as csvDatafile:
        # open a csv file 
        data = list(csv.reader(csvDatafile))
        for i in range(1,len(data)-1):
            #compute the absolute value for the difference in the first and second values
            sum_x_sq = pow(abs(float(data[i][0]) - float(data[i+1][0])),2) 
            sum_y_sq = pow(abs(float(data[i][1]) - float(data[i+1][1])),2) 
            sum_z_sq = pow(abs(float(data[i][2]) - float(data[i+1][2])),2)
            # distance = math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            Total_distance += math.sqrt(sum_x_sq + sum_y_sq + sum_z_sq)
            # write to the csv file x_distance, y_distance, z_distance, distance_between_points(distance), 
        print ("| Initial Battery: " + data[1][4] + \
            "\n| Final battery: " + data[len(data)-1][4] +  \
            "\n| Total Battery charge Lost: {0:0.3f}".format(float(data[1][4])-float(data[len(data)-1][4])))
    print("Total Distance travelled: {0:0.3f}".format(float(Total_distance)))












    # print("Area under the x-axis: {0:0.3f}".format(sum_area_x))
    # print("Area under the y-axis: {0:0.3f}".format(sum_area_y))
    # print("Area under the z-axis: {0:0.3f}".format(sum_area_z))
    # print("Total area under the graph: {0:0.3f}".format(sum_area_x + sum_area_y + sum_area_z))
    

main()

