#include <algorithm>
#include <any>
#include <array>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include "pprint.hpp"
#include "cxxopts.hpp"

using namespace std;

struct AppConfig {
  bool help = false;
  bool verbose = false;
} appCfg;

std::ostream& operator<<(std::ostream& os, const AppConfig& c) {
  os << "AppConfig(help:" << c.help << ',' << " verbose:" << c.verbose << ")";
  return os;
}
std::optional<AppConfig> parse(int argc, const char *argv[])
{
    AppConfig cfg;
    try
    {
        cxxopts::Options options(argv[0], " - example command line options");
        options
            .positional_help("[optional args]")
            .show_positional_help();

        options
            .allow_unrecognised_options()
            .add_options()("h,help", "Print help", cxxopts::value<bool>(cfg.help))("v,verbose", "Print debug output", cxxopts::value<bool>(cfg.verbose));

        auto result = options.parse(argc, argv);
        std::cout << "Arguments remain = " << argc << std::endl;
        auto arguments = result.arguments();
        std::cout << "arguments.size: " << arguments.size() << std::endl;
    }
    catch (const cxxopts::OptionException &e)
    {
        std::cout << "error parsing options: " << e.what() << std::endl;
        return std::nullopt;
    }
    return cfg;
}

int main(int argc, const char* argv[]) {
    
    cout << "Starting main() on " << std::thread::hardware_concurrency() << " cores" << std::endl;
    auto appCfgOpt = parse(argc, argv); 
    if (!appCfgOpt) {
      cout << "Argument parsing failed. Exit main() with EXIT_FAILURE" << std::endl;
      exit(EXIT_FAILURE);
    }
    auto appCfg = appCfgOpt.value();
    cout << appCfg << std::endl;
    if( appCfg.verbose ) cout << "Exit main() with EXIT_SUCCESS" << std::endl;
    exit(EXIT_SUCCESS);
}
