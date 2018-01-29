#ifndef _ARAIG_SENSORS_H_
#define _ARAIG_SENSORS_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Task.h"

namespace finalproj
{
    class ARAIG_Sensors
    {
    private:
        std::vector<Stimulation*> stimVec_;
        std::vector<Task*> taskVec_;
        Stimulation* getStim(std::string);
        
    public:
        ARAIG_Sensors(const char*, const char*);
        ~ARAIG_Sensors();
        void dump(std::ostream& os);
        Task* getTask(std::string);

    };
}

#endif
