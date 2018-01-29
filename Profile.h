#ifndef _PROFILE_H_
#define _PROFILE_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "ARAIG_Sensors.h"

namespace finalproj
{
    class Profile
    {
    private:
        std::string stuFirstName_;
        std::string stuLastName_;
        std::string stuNum_;
        std::string flyInstFirstName_;
        std::string flyInstLastName_;
        std::string flyInstNum_;
        struct CalIntensity
        {
            int max;
            int min;
        };
        CalIntensity calIntensity;
        std::vector<Task*> ToRun;
        std::vector<Task*> Completed;

    public:
        Profile(const char*, std::ofstream&, ARAIG_Sensors&);
        ~Profile();
        void displayToRun();
        void displayCompleted();
        void displayNextTask();
        void displayLastCompTask();
        void run();
        const int getToRunSize();
        const int getCompletedSize();
    };

}

#endif
