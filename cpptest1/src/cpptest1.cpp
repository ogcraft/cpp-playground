#include <algorithm>
#include <any>
#include <array>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include "cxxopts.hpp"

using namespace std;

void parse(int argc, const char* argv[])
{
  try
  {
    cxxopts::Options options(argv[0], " - example command line options");
    options
      .positional_help("[optional args]")
      .show_positional_help();

    bool help = false;
    bool verbose = false;

    options
      .allow_unrecognised_options()
      .add_options()
      ("h,help", "Print help", cxxopts::value<bool>(help))
      ("v,verbose", "Print debug output", cxxopts::value<bool>(verbose))
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
      std::cout << options.help({"", "Group"}) << std::endl;
      exit(0);
    }

    std::cout << "Arguments remain = " << argc << std::endl;

    auto arguments = result.arguments();
    std::cout << "Saw " << arguments.size() << " arguments" << std::endl;
  }
  catch (const cxxopts::OptionException& e)
  {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }
}

int main(int argc, const char* argv[]) {
    cout << "Starting main() on " << std::thread::hardware_concurrency() << " cores" << "\n";

    parse(argc, argv);

    return EXIT_SUCCESS;
}
