#pragma once
#include <string>

// ─────────────────────────────
// Formatting / math helpers
// ─────────────────────────────
std::string fmt(double v);
double factorial(int n);
double erlangC(double a, int s, double rho, double& P0out);

// ─────────────────────────────
// Output block builders
// ─────────────────────────────
std::string rateBlock(double lambda, double mu, bool hr);
std::string timeBlock(double Wq, double Ws, bool hr);

// ─────────────────────────────
// Queueing model solvers
// ─────────────────────────────
std::string solveMM1(double lambda, double mu, bool hr);
std::string solveMMc(double lambda, double mu, int c, bool hr);
std::string solveMG1(double lambda, double mu, double sigmaS, bool hr);
std::string solveMGS(double lambda, double mu, int s, double sigmaS, bool hr);
std::string solveGG1(double lambda, double mu, double Ca, double sigmaS, bool hr);
std::string solveGGS(double lambda, double mu, int s, double Ca, double sigmaS, bool hr);
