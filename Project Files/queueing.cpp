#include "queueing.h"
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

// ─────────────────────────────
// HELPER — 4-decimal formatter
// ─────────────────────────────
string fmt(double v) {
    ostringstream ss;
    ss << fixed << setprecision(4) << v;
    return ss.str();
}

// ─────────────────────────────
// FACTORIAL
// ─────────────────────────────
double factorial(int n) {
    double f = 1;
    for (int i = 2; i <= n; i++) f *= i;
    return f;
}

// ─────────────────────────────
// Erlang-C  P_wait
// ─────────────────────────────
double erlangC(double a, int s, double rho, double& P0out) {
    double sum = 0;
    for (int n = 0; n < s; n++)
        sum += pow(a, n) / factorial(n);
    P0out = 1.0 / (sum + pow(a, s) / (factorial(s) * (1.0 - rho)));
    return (pow(a, s) / (factorial(s) * (1.0 - rho))) * P0out;
}

// ─────────────────────────────
// RATE CONVERSION BLOCK
// ─────────────────────────────
string rateBlock(double lambda, double mu, bool hr) {
    string out = "\r\nRATE CONVERSIONS\r\n"
                 "--------------------------------\r\n";
    if (hr) {
        out += "  Arrival Rate  (lambda)  =  " + fmt(lambda)        + " /hr   =  " + fmt(lambda / 60.0)       + " /min\r\n";
        out += "  Service Rate  (mu)      =  " + fmt(mu)            + " /hr   =  " + fmt(mu    / 60.0)        + " /min\r\n";
        out += "  Mean Interarrival Time  =  " + fmt(60.0 / lambda) + " min   =  " + fmt(1.0   / lambda)      + " hr\r\n";
        out += "  Mean Service Time       =  " + fmt(60.0 / mu)     + " min   =  " + fmt(1.0   / mu)          + " hr\r\n";
    } else {
        out += "  Arrival Rate  (lambda)  =  " + fmt(lambda)        + " /min  =  " + fmt(lambda * 60.0)       + " /hr\r\n";
        out += "  Service Rate  (mu)      =  " + fmt(mu)            + " /min  =  " + fmt(mu    * 60.0)        + " /hr\r\n";
        out += "  Mean Interarrival Time  =  " + fmt(1.0 / lambda)  + " min   =  " + fmt(1.0 / (lambda*60.0)) + " hr\r\n";
        out += "  Mean Service Time       =  " + fmt(1.0 / mu)      + " min   =  " + fmt(1.0 / (mu*60.0))    + " hr\r\n";
    }
    return out;
}

// ─────────────────────────────
// TIME CONVERSION BLOCK
// ─────────────────────────────
string timeBlock(double Wq, double Ws, bool hr) {
    string out = "\r\nTIME CONVERSIONS\r\n"
                 "--------------------------------\r\n";
    if (hr) {
        out += "  Queue Wait Time   (Wq)  =  " + fmt(Wq) + " hr   =  " + fmt(Wq * 60.0) + " min\r\n";
        out += "  System Wait Time  (Ws)  =  " + fmt(Ws) + " hr   =  " + fmt(Ws * 60.0) + " min\r\n";
    } else {
        out += "  Queue Wait Time   (Wq)  =  " + fmt(Wq) + " min  =  " + fmt(Wq / 60.0) + " hr\r\n";
        out += "  System Wait Time  (Ws)  =  " + fmt(Ws) + " min  =  " + fmt(Ws / 60.0) + " hr\r\n";
    }
    return out;
}

// ─────────────────────────────
// M/M/1
// ─────────────────────────────
string solveMM1(double lambda, double mu, bool hr) {
    if (lambda >= mu) return "  ERROR: System Unstable  (lambda >= mu)\r\n";
    double rho = lambda / mu;
    double P0  = 1.0 - rho;
    double Lq  = (lambda * lambda) / (mu * (mu - lambda));
    double Wq  = Lq / lambda;
    double Ws  = Wq + 1.0 / mu;
    double Ls  = lambda * Ws;
    string u   = hr ? " hr" : " min";
    string out =
        "========================================\r\n"
        "   M/M/1  RESULTS\r\n"
        "========================================\r\n"
        "  Traffic Intensity    (rho)  =  " + fmt(rho) + "\r\n"
        "  Idle Probability     (P0)   =  " + fmt(P0)  + "\r\n"
        "  Avg Customers Queue  (Lq)   =  " + fmt(Lq)  + "\r\n"
        "  Avg Customers System (Ls)   =  " + fmt(Ls)  + "\r\n"
        "  Avg Queue Wait Time  (Wq)   =  " + fmt(Wq)  + u + "\r\n"
        "  Avg System Wait Time (Ws)   =  " + fmt(Ws)  + u + "\r\n";
    out += rateBlock(lambda, mu, hr);
    out += timeBlock(Wq, Ws, hr);
    out += "========================================\r\n";
    return out;
}

// ─────────────────────────────
// M/M/c
// ─────────────────────────────
string solveMMc(double lambda, double mu, int c, bool hr) {
    if (lambda >= c * mu) return "  ERROR: System Unstable  (lambda >= c*mu)\r\n";
    double a = lambda / mu, rho = lambda / (c * mu);
    double P0, Pc = erlangC(a, c, rho, P0);
    double Lq = (Pc * a * rho) / (1.0 - rho);
    double Wq = Lq / lambda;
    double Ws = Wq + 1.0 / mu;
    double Ls = lambda * Ws;
    string u  = hr ? " hr" : " min";
    string out =
        "========================================\r\n"
        "   M/M/c  RESULTS\r\n"
        "========================================\r\n"
        "  Traffic Intensity    (rho)  =  " + fmt(rho) + "\r\n"
        "  Idle Probability     (P0)   =  " + fmt(P0)  + "\r\n"
        "  Prob. All Servers Busy (Pc) =  " + fmt(Pc)  + "\r\n"
        "  Avg Customers Queue  (Lq)   =  " + fmt(Lq)  + "\r\n"
        "  Avg Customers System (Ls)   =  " + fmt(Ls)  + "\r\n"
        "  Avg Queue Wait Time  (Wq)   =  " + fmt(Wq)  + u + "\r\n"
        "  Avg System Wait Time (Ws)   =  " + fmt(Ws)  + u + "\r\n";
    out += rateBlock(lambda, mu, hr);
    out += timeBlock(Wq, Ws, hr);
    out += "========================================\r\n";
    return out;
}

// ─────────────────────────────
// M/G/1  (Pollaczek-Khinchine)
// ─────────────────────────────
string solveMG1(double lambda, double mu, double sigmaS, bool hr) {
    if (lambda >= mu) return "  ERROR: System Unstable  (lambda >= mu)\r\n";
    double rho = lambda / mu;
    double ES  = 1.0 / mu;
    double ES2 = sigmaS * sigmaS + ES * ES;
    double Cs  = sigmaS / ES;
    double P0  = 1.0 - rho;
    double Lq  = (lambda * lambda * ES2) / (2.0 * (1.0 - rho));
    double Wq  = (lambda * ES2)          / (2.0 * (1.0 - rho));
    double Ws  = Wq + ES;
    double Ls  = lambda * Ws;
    string u   = hr ? " hr" : " min";
    string out =
        "========================================\r\n"
        "   M/G/1  RESULTS  (P-K Formula)\r\n"
        "========================================\r\n"
        "  Utilization          (rho)  =  " + fmt(rho) + "\r\n"
        "  Idle Probability     (P0)   =  " + fmt(P0)  + "\r\n"
        "  Mean Service Time    E[S]   =  " + fmt(ES)  + u + "\r\n"
        "  2nd Moment of Svc    E[S2]  =  " + fmt(ES2) + "\r\n"
        "  Service CV           (Cs)   =  " + fmt(Cs)  + "\r\n"
        "  Avg Customers Queue  (Lq)   =  " + fmt(Lq)  + "\r\n"
        "  Avg Customers System (Ls)   =  " + fmt(Ls)  + "\r\n"
        "  Avg Queue Wait Time  (Wq)   =  " + fmt(Wq)  + u + "\r\n"
        "  Avg System Wait Time (Ws)   =  " + fmt(Ws)  + u + "\r\n";
    out += rateBlock(lambda, mu, hr);
    out += timeBlock(Wq, Ws, hr);
    out += "========================================\r\n";
    return out;
}

// ─────────────────────────────
// M/G/s  (Allen-Cunneen)
// ─────────────────────────────
string solveMGS(double lambda, double mu, int s, double sigmaS, bool hr) {
    if (lambda >= s * mu) return "  ERROR: System Unstable  (lambda >= s*mu)\r\n";
    double a   = lambda / mu;
    double rho = lambda / (s * mu);
    double ES  = 1.0 / mu;
    double Cs  = sigmaS / ES;
    double P0, Pw = erlangC(a, s, rho, P0);
    double Wq  = ((1.0 + Cs * Cs) / 2.0) * (Pw / (s * mu - lambda));
    double Ws  = Wq + ES;
    double Lq  = lambda * Wq;
    double Ls  = lambda * Ws;
    string u   = hr ? " hr" : " min";
    string out =
        "========================================\r\n"
        "   M/G/s  RESULTS  (Allen-Cunneen)\r\n"
        "========================================\r\n"
        "  Utilization          (rho)   =  " + fmt(rho) + "\r\n"
        "  Idle Probability     (P0)    =  " + fmt(P0)  + "\r\n"
        "  Prob. of Waiting     (Pwait) =  " + fmt(Pw)  + "\r\n"
        "  Service CV           (Cs)    =  " + fmt(Cs)  + "\r\n"
        "  Avg Customers Queue  (Lq)    =  " + fmt(Lq)  + "\r\n"
        "  Avg Customers System (Ls)    =  " + fmt(Ls)  + "\r\n"
        "  Avg Queue Wait Time  (Wq)    =  " + fmt(Wq)  + u + "\r\n"
        "  Avg System Wait Time (Ws)    =  " + fmt(Ws)  + u + "\r\n";
    out += rateBlock(lambda, mu, hr);
    out += timeBlock(Wq, Ws, hr);
    out += "========================================\r\n";
    return out;
}

// ─────────────────────────────
// G/G/1  (Kingman's approximation)
// ─────────────────────────────
string solveGG1(double lambda, double mu, double Ca, double sigmaS, bool hr) {
    if (lambda >= mu) return "  ERROR: System Unstable  (lambda >= mu)\r\n";
    double rho = lambda / mu;
    double ES  = 1.0 / mu;
    double Cs  = sigmaS / ES;
    double P0  = 1.0 - rho;
    double Wq  = (rho / (1.0 - rho)) * ((Ca*Ca + Cs*Cs) / 2.0) * ES;
    double Ws  = Wq + ES;
    double Lq  = lambda * Wq;
    double Ls  = lambda * Ws;
    string u   = hr ? " hr" : " min";
    string out =
        "========================================\r\n"
        "   G/G/1  RESULTS  (Kingman Approx)\r\n"
        "========================================\r\n"
        "  Utilization (approx) (rho)  =  " + fmt(rho) + "\r\n"
        "  Idle Prob.  (approx) (P0)   =  " + fmt(P0)  + "\r\n"
        "  Arrival CV           (Ca)   =  " + fmt(Ca)  + "\r\n"
        "  Service CV           (Cs)   =  " + fmt(Cs)  + "\r\n"
        "  Avg Customers Queue  (Lq)   =  " + fmt(Lq)  + "\r\n"
        "  Avg Customers System (Ls)   =  " + fmt(Ls)  + "\r\n"
        "  Avg Queue Wait Time  (Wq)   =  " + fmt(Wq)  + u + "\r\n"
        "  Avg System Wait Time (Ws)   =  " + fmt(Ws)  + u + "\r\n";
    out += rateBlock(lambda, mu, hr);
    out += timeBlock(Wq, Ws, hr);
    out += "========================================\r\n";
    return out;
}

// ─────────────────────────────
// G/G/s  (Allen-Cunneen)
// ─────────────────────────────
string solveGGS(double lambda, double mu, int s, double Ca, double sigmaS, bool hr) {
    if (lambda >= s * mu) return "  ERROR: System Unstable  (lambda >= s*mu)\r\n";
    double a   = lambda / mu;
    double rho = lambda / (s * mu);
    double ES  = 1.0 / mu;
    double Cs  = sigmaS / ES;
    double P0, Pw = erlangC(a, s, rho, P0);
    double Wq  = ((Ca*Ca + Cs*Cs) / 2.0) * (Pw / (s * mu - lambda));
    double Ws  = Wq + ES;
    double Lq  = lambda * Wq;
    double Ls  = lambda * Ws;
    string u   = hr ? " hr" : " min";
    string out =
        "========================================\r\n"
        "   G/G/s  RESULTS  (Allen-Cunneen)\r\n"
        "========================================\r\n"
        "  Utilization          (rho)   =  " + fmt(rho) + "\r\n"
        "  Idle Probability     (P0)    =  " + fmt(P0)  + "\r\n"
        "  Prob. of Waiting     (Pwait) =  " + fmt(Pw)  + "\r\n"
        "  Arrival CV           (Ca)    =  " + fmt(Ca)  + "\r\n"
        "  Service CV           (Cs)    =  " + fmt(Cs)  + "\r\n"
        "  Avg Customers Queue  (Lq)    =  " + fmt(Lq)  + "\r\n"
        "  Avg Customers System (Ls)    =  " + fmt(Ls)  + "\r\n"
        "  Avg Queue Wait Time  (Wq)    =  " + fmt(Wq)  + u + "\r\n"
        "  Avg System Wait Time (Ws)    =  " + fmt(Ws)  + u + "\r\n";
    out += rateBlock(lambda, mu, hr);
    out += timeBlock(Wq, Ws, hr);
    out += "========================================\r\n";
    return out;
}
