/**
 * User command parser
 */
#include "cli.h"
#include "avinfo.h"
#include "version.h"
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <boost/program_options/parsers.hpp>
#include "boost/program_options/variables_map.hpp"
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/options_description.hpp>

using std::cout;
using std::endl;
using std::vector;
using std::string;

namespace po = boost::program_options;

int cli::main(int argc, char** argv)
{
    // general arguments
    po::options_description general("General arguments");
    general.add_options()
        ("help", "show this help page")
        ("version", "show program's version number")
        ("video", "input video")
        ("show", "show video information");
    po::positional_options_description p;
    p.add("video", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(general).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        general.print(cout);
        return 0;
    }

    if (vm.count("version")) {
        cout << "gameinmotion version " << __GAMEINMOTION_VERSION__ << endl;
        return 0;
    }

    if (!vm.count("video")) {
        cout << "usage: gameinmotion [options] video" << endl;
        return -EINVAL;
    }

    if (vm.count("show")) {
        avinfo::print_av_info(vm["video"].as<string>());
    }

    return 0;
}