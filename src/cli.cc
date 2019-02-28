/**
 * User command parser
 */
#include "cli.h"
#include "version.h"
#include <iostream>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/options_description.hpp>

using std::cout;
using std::endl;

namespace po = boost::program_options;

po::variables_map cli::parse(int argc, char** argv)
{
    // general arguments
    po::options_description general("General arguments");
    general.add_options()
        ("help", "show this help page")
        ("version", "show program's version number")
        ("video", "input video");
    po::positional_options_description p;
    p.add("video", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(general).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        general.print(cout);
    }

    if (vm.count("version")) {
        cout << "gameinmotion version " << __GAMEINMOTION_VERSION__ << endl;
    }

    return vm;
}