#include <algorithm>
#include <any>
#include <array>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include "cxxopts.hpp"

using namespace std;

struct AppConfig {
  bool help = false;
  bool verbose = false;
} appCfg;

int parse(int argc, const char* argv[], AppConfig& cfg)
{
  try
  {
    cxxopts::Options options(argv[0], " - example command line options");
    options
      .positional_help("[optional args]")
      .show_positional_help();

    options
      .allow_unrecognised_options()
      .add_options()
      ("h,help", "Print help", cxxopts::value<bool>(cfg.help))
      ("v,verbose", "Print debug output", cxxopts::value<bool>(cfg.verbose))
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
      std::cout << options.help({"", "Group"}) << std::endl;
      return EXIT_SUCCESS;
    }

    std::cout << "Arguments remain = " << argc << std::endl;

    auto arguments = result.arguments();
    std::cout << "Saw " << arguments.size() << " arguments" << std::endl;
  }
  catch (const cxxopts::OptionException& e)
  {
    std::cout << "error parsing options: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int main(int argc, const char* argv[]) {
    
    int ret = EXIT_SUCCESS;
    cout << "Starting main() on " << std::thread::hardware_concurrency() << " cores" << "\n";

    if ( (ret = parse(argc, argv, appCfg)) != EXIT_SUCCESS) {
      cout << "Argument parsing failed. Exit main() with " << ret << "\n";
      exit(ret);
    }
    if(appCfg.verbose) cout << "Exit main() with " << ret << "\n";
    exit(ret);
}
