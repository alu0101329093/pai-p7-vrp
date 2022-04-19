#ifndef P7VRP_MAIN_H_
#define P7VRP_MAIN_H_

#include <fstream>
#include <iostream>
#include <string>

#include "vrp/vrp_greedy.h"
#include "vrp/vrp_problem.h"
#include "vrp/vrp_solution.h"

namespace daa {

VrpProblem ReadInfoFromFile(const std::string& file_name);

}  // namespace daa

int main(int argc, char* argv[]);

#endif  // P7VRP_MAIN_H_
