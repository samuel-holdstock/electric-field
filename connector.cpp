#include <Rcpp.h>
#include "Electric_Field.h"

using namespace Rcpp;


// [[Rcpp::export]]
double meanC(NumericVector x) {
  int n = x.size();
  double total = 0;
  for(int i = 0; i < n; ++i) {
    total += x[i];
  }
  return total / n;
}

// [[Rcpp::export]]
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