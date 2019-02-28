/**
 *
 */
#include <stdio.h>
#include <errno.h>
#include "cli.h"
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
    auto vm = ::cli::parse(argc, argv);

    if (!vm.count("video")) {
        cout << "usage: gameinmotion [options] video" << endl;
        return -EINVAL;
    }

    return 0;
}