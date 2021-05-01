#include "Parabolic.h"

namespace csci3081 {

	std::vector<std::vector<float>> Parabolic::GetPath(std::vector<float> source, std::vector<float> destination) {
		Vector3D vo (source);
		Vector3D ve (destination);
		Vector3D vm = ((vo+ve)*0.5);
		double t = 30.0; // we take t as 30 steps for a smooth parabolic movement to the final destination of the drone
		// We use the equations provided in lab 14 for the parabolic path movement lab as a reference to form the following computations:
		Vector3D vt = ((ve-vo)*(1.0/t));
		Vector3D v;
		std::vector<std::vector<float>> path;
		double offset = 20.0;
		for (int i = 0; i < t; i++) {
			v = vo+vt*i;
			double y = 1-pow( (v.DistanceBetween(vm)), 2)/pow( vo.DistanceBetween(vm), 2);
			double j = 150.0; 
			y = y*j;
			Vector3D temp (v[0], v[1]+y+offset, v[2]);
			path.push_back(Vector3D::ConvertToVector(temp));
		} //close for loop
	
		std::vector<float> vert = {float(ve[0]), float(ve[1]+offset), float(ve[2])};
		path.push_back(vert);
		path.push_back(destination);
		return path;
	} //close method 

}//end of namespace 