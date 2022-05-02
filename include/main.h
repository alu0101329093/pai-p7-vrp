#ifndef P7VRP_MAIN_H_
#define P7VRP_MAIN_H_

#include <fstream>
#include <iostream>
#include <string>

#include "vrp/vrp_grasp_options.h"
#include "vrp/vrp_intra_route_exchange.h"
#include "vrp/vrp_inter_route_exchange.h"
#include "vrp/vrp_problem.h"
#include "vrp/vrp_solution.h"
#include "vrp/vrp_solver.h"

namespace daa {

VrpProblem ReadInfoFromFile(const std::string& file_name);

}  // namespace daa

int main(int argc, char* argv[]);

#endif  // P7VRP_MAIN_H_
