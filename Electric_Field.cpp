#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream


const double K = 8.987551 * pow(10,9);

class Atom{
  private:
    std::vector<double> position;
    double charge;
  public:
    Atom(){}
    Atom(std::vector<double> position, double charge){
      setPosition(position);
      setCharge(charge);
    }
    std::vector<double> getPosition(){
      return this->position;
    }
    void setPosition(std::vector<double> position){
      this->position = position;
    }
    double getCharge(){
      return this->charge;
    }
    void setCharge(double newCharge){
      this->charge = newCharge;
    }
    void display(){
      for(auto i:position){
        std::cout<<i;
      }
      std::cout<<std::endl<<charge<<std::endl;
    }
};

std::vector<Atom> read_csv(std::string fileName);
std::vector<std::vector<double>> get_field(std::vector<Atom> atoms, std::pair<double,double> start,std::pair<double,double> end,int M);

int main() {
  std::vector<Atom> atoms = read_csv("data.csv");
  std::pair<double,double> start = std::pair<double,double>{0,0};
  std::pair<double,double> end = std::pair<double,double>{10,10};
  int M = 10;
  std::vector<std::vector<double>> field = get_field(atoms,start,end,M);
  for(int i=0; i<M*M; ++i){
    std::cout<<"({"<<field[i][0]<<","<<field[i][1]<<"},{"<<field[i][2]<<field[i][3]<<"})";
    if((i+1)%M==0){
      std::cout<<std::endl;
    }
  }
  return 0;
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
  // for(auto i:result){
  //     for(auto j:i.second){
  //       std::cout<<j;
  //     }
  //     std::cout<<std::endl;
  //   }
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



