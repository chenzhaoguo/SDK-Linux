#include <iostream>
#include <map>
#include <fstream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>

Eigen::Matrix3d euler2Rotation(Eigen::Vector3d eulerAngles) {  // ZYX
  double roll = eulerAngles(0);
  double pitch = eulerAngles(1);
  double yaw = eulerAngles(2);
  double cr = cos(roll); double sr = sin(roll);
  double cp = cos(pitch); double sp = sin(pitch);
  double cy = cos(yaw); double sy = sin(yaw);
  Eigen::Matrix3d R;
  R << cy*cp,  cy*sp*sr - sy*cr,  sy*sr + cy*cr*sp,
       sy*cp,  cy*cr + sy*sr*sp,  sp*sy*cr - cy*sr,
       -sp,    cp*sr,             cp*cr;
  return R;
}

/// InputFile: slam timestamp px py pz roll pitch yaw.  OutputFile: timestamp px py pz qx qy qz qw
void TumQuat2Euler(std::string filename, std::map<double, std::pair<Eigen::Vector3d, Eigen::Quaterniond>> &line_tum) {
  std::ifstream read_data;
  read_data.open(filename.c_str());
  if (!read_data.is_open()) {
    std::cerr << "Fail to open read_file: " << filename << std::endl;
    return;
  }

  std::string tmp;
  double time_stamp = 0.0;
  Eigen::Vector3d pose;
  Eigen::Vector3d euler;
  Eigen::Matrix3d R;
  Eigen::Quaterniond q;

  std::string data_line;
  while (std::getline(read_data, data_line) && !data_line.empty()) {
    std::istringstream ss(data_line);
    ss >> tmp >> time_stamp >> pose.x() >> pose.y() >> pose.z() >> euler.x() >> euler.y() >> euler.z();

    R = Eigen::AngleAxisd(euler[2], Eigen::Vector3d::UnitZ()) *
        Eigen::AngleAxisd(euler[1], Eigen::Vector3d::UnitY()) *
        Eigen::AngleAxisd(euler[0], Eigen::Vector3d::UnitX());
    q = R;

    line_tum.insert(std::make_pair(time_stamp, std::make_pair(pose, q)));
  }
	read_data.close();
}

void SaveData(std::string filename, std::map<double, std::pair<Eigen::Vector3d, Eigen::Quaterniond>> &line_tum) {
  std::ofstream save_data;
  save_data.open(filename.c_str());

  for (auto iter = line_tum.begin(); iter != line_tum.end(); ++iter) {
    double time = iter->first;
    Eigen::Vector3d pose = iter->second.first;
    Eigen::Quaterniond q = iter->second.second;

    save_data << time << " "
              << pose.x() << " "
              << pose.y() << " "
              << pose.z() << " "
              << q.x() << " "
              << q.y() << " "
              << q.z() << " "
              << q.w() << std::endl;
  }
}

int main() {
  std::string positon_file = "./result23/result23.txt";
  std::map<double, std::pair<Eigen::Vector3d, Eigen::Quaterniond>> line_tum;
  TumQuat2Euler(positon_file, line_tum);

  std::string save_file = "./result23/result23_tum.txt";
  SaveData(save_file, line_tum);

  return 0;
}
