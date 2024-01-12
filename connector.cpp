#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

#include "Electric_Field.h"

using namespace Rcpp;
using namespace arma;

// [[Rcpp::export]]
arma::mat start() {
  std::vector<Atom> atoms = read_csv("data.csv");
  std::pair<double,double> start = std::pair<double,double>{2.5,2.5};
  std::pair<double,double> end = std::pair<double,double>{7.5,7.5};
  int M = 40;
  std::vector<std::vector<double>> field = get_field(atoms,start,end,M);
  int ncol = field[0].size();
  int nrow = field.size();
  arma::mat field_mat(nrow,ncol,arma::fill::zeros);
  for(int i=0; i<M*M; ++i){
    field_mat(i,0) = field[i][0];
    field_mat(i,1) = field[i][1];
    field_mat(i,2) = field[i][2];
    field_mat(i,3) = field[i][3];
  }
  return field_mat;
}

// [[Rcpp::export]]
arma::mat get_charges(){
  std::vector<Atom> atoms = read_csv("data.csv");
  int nrows = atoms.size();
  int ncols = 3;
  arma::mat charges_mat(nrows,ncols,arma::fill::zeros);
  for(int i=0; i<nrows;++i){
    Atom atom = atoms[i];
    std::vector<double> position = atom.getPosition();
    double charge = atom.getCharge();
    charges_mat(i,0) = position[0];
    charges_mat(i,1) = position[1]; 
    charges_mat(i,2) = charge;
  }
  return charges_mat;
}