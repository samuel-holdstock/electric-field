#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include "Electric_Field.h"

const double K = 8.987551 * pow(10,9);

Atom::Atom(std::vector<double> position, double charge){
  setPosition(position);
  setCharge(charge);
}
std::vector<double> Atom::getPosition(){
  return this->position;
}
void Atom::setPosition(std::vector<double> position){
  this->position = position;
}
double Atom::getCharge(){
  return this->charge;
}
void Atom::setCharge(double newCharge){
  this->charge = newCharge;
}
void Atom::display(){
  for(auto i:position){
    std::cout<<i;
  }
  std::cout<<std::endl<<charge<<std::endl;
}



std::vector<Atom> read_csv(std::string fileName){
  int numberOfAtoms=0;
  std::vector<std::pair<std::string, std::vector<double>>> result;
  std::ifstream myFile(fileName);
  if(!myFile.is_open()) throw std::runtime_error("Could not open file.");
  std::string line, colname;
  int val;
  if(myFile.good()){
    std::getline(myFile,line);
    std::stringstream ss(line);
    while(std::getline(ss,colname,',')){
      result.push_back({colname, std::vector<double> {}});
    }
    while(std::getline(myFile, line))
    {
      numberOfAtoms++;
        std::stringstream ss(line);
        int colIdx = 0;
        while(ss >> val){
            result.at(colIdx).second.push_back(val);
            if(ss.peek() == ',') ss.ignore();
            colIdx++;
        }
    }
    myFile.close();
  }
  std::vector<Atom> atoms;
  for(int i=0;i<numberOfAtoms;i++){
    double xpos = result[0].second[i];
    double ypos = result[1].second[i];
    double charge = result[2].second[i];
    std::vector<double> position{xpos,ypos};
    Atom testAtom(position,charge);
    atoms.push_back(testAtom);
  }
  return atoms;
}

std::vector<std::vector<double>> get_field(std::vector<Atom> atoms, std::pair<double,double> start,std::pair<double,double> end,int M){
  double dx = (end.first-start.first)/M;
  double dy = (end.second-start.second)/M;
  std::vector<std::vector<double>> field; 
  for(int i=0; i<M; ++i){
    for(int j=0; j<M; ++j){
      double force[2] = {0,0};
      double position[2] {start.first + i*dx,start.second + j*dy};
      for(auto atom:atoms){
        double displacement [2] = {atom.getPosition()[0] - position[0], atom.getPosition()[1] - position[1]};
        double distance2 = pow(displacement[0],2)+pow(displacement[1],2);
        double distance = sqrt(distance2);
        force[0] = K*atom.getCharge()/distance2 * displacement[0]/distance;
        force[1] = K*atom.getCharge()/distance2 * displacement[1]/distance;
      }
      field.push_back(std::vector<double>{position[0],position[1],force[0],force[1]});
    }
  }
  return field;
}



