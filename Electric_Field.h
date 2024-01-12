#ifndef ELECTRIC_FIELD_H
#define ELECTRIC_FIELD_H
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream

class Atom{
  private:
    std::vector<double> position;
    double charge;
  public:
    Atom(std::vector<double> position, double charge);
    std::vector<double> getPosition();
    void setPosition(std::vector<double> position);
    void setCharge(double newCharge);
    double getCharge();
    void display();
};

std::vector<Atom> read_csv(std::string fileName);
std::vector<std::vector<double>> get_field(std::vector<Atom> atoms, std::pair<double,double> start,std::pair<double,double> end,int M);

#endif