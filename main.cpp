// BTP 305 Final Project
// Tanvir Sarkar

#include <iostream>
#include "Profile.h"

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cerr << argv[0] <<": incorrect number of arguments\n";
        std::cerr << "Usage: " << argv[0] << " profile_file stim_file task_file output_file\n";
        return 1;
    }

    // finalproj::ARAIG_Sensors as("StimulationConfig.csv", "TaskConfiguration.csv");
    // std::ofstream os("fpm4_output.txt");
    finalproj::ARAIG_Sensors as(argv[2], argv[3]);
    std::ofstream os(argv[4]);
    // finalproj::Profile pf("SampleProfileConfiguration.csv", os, as);
    finalproj::Profile pf(argv[1], os, as);
    pf.run();

    return 0;
}

