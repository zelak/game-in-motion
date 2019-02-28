/**
 * User command parser
 */
#include "boost/program_options/variables_map.hpp"


#pragma once

namespace cli {
    boost::program_options::variables_map parse(int argc, char** argv);
};