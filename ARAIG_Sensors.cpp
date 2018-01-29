#include "ARAIG_Sensors.h"

namespace finalproj
{
    ARAIG_Sensors::ARAIG_Sensors(const char* fileStim, const char* fileTask)
    {
        // Stimulation File
        std::ifstream ifsStim(fileStim);
        if(!ifsStim)
        {
            throw "Couldn't open Stimulation file";
        }
        while(ifsStim.good())
        {
            std::string line;
            std::getline(ifsStim, line);
            std::istringstream ss(line);

            if (!line.empty())
            {       
                std::vector<std::string> fields;
                std::string field;
                while(std::getline(ss, field, ','))
                {
                    fields.push_back(field);
                }

                // check if the line is for stims or exoskeleton
                if (fields[0].compare("stim") == 0 && fields.size() == 6)
                {
                    int locInt = 0;
                    if (fields[2].compare("abs") == 0)
                    {
                        locInt = 0;
                    }
                    else if (fields[2].compare("front") == 0)
                    {
                        locInt = 1;
                    }
                    else if (fields[2].compare("back") == 0)
                    {
                        locInt = 2;
                    }
                    else if (fields[2].compare("traps") == 0)
                    {
                        locInt = 3;
                    }
                    
                    // Dynamically allocate memory for a new Stim 
                    stimVec_.push_back(new Stims(fields[1], static_cast<finalproj::Stims::Location>(locInt), atoi(fields[3].c_str()), atoi(fields[4].c_str()), atoi(fields[5].c_str())));
                }
                else
                {
                    // Dynamically allocate memory for a new Exoskeleton
                    stimVec_.push_back(new Exoskeleton(fields[1], atoi(fields[2].c_str()), atoi(fields[3].c_str())));
                }
            }
        }
        ifsStim.close();

        // Task File
        std::ifstream ifsTask(fileTask);
        if(!ifsTask)
        {
            throw "Couldn't open Task file";
        }
        while(ifsTask.good())
        {
            std::string line;
            std::vector<std::string> strs;
            while(std::getline(ifsTask, line))
            {
                strs.push_back(line);
            }

            int vecIndex = 0;
            std::string curTask;
            std::list<Stimulation*> stimsForCurTask;
            
            while (vecIndex < (int) strs.size())
            {
                // If the line has the keyword TASK, set the name of the current task to the name in the line
                // Otherwise, the line has a stim name, search for it in the stim vector and add it to a temp list
                if((int) strs[vecIndex].find("TASK") != -1)
                {
                    curTask = strs[vecIndex].substr(strs[vecIndex].find(",")+1);
                    curTask = curTask.substr(0,4) + std::to_string(atoi(curTask.substr(4).c_str()));
                }
                else
                {
                    std::string searchStr = strs[vecIndex].substr(0,3) + std::to_string(atoi(strs[vecIndex].substr(3).c_str()));

                    if(getStim(searchStr) != nullptr)
                    {
                        stimsForCurTask.push_back(getStim(searchStr));
                    }            
                }

                // Dynamically allocate memory for a new Task If:
                // the next index in the vector will get you a string with the TASK keyword (start of a new task)
                // OR, if the index counter is on the last index in the vector (no more tasks or stims after this)
                if((vecIndex+1 < ((int) strs.size()) && ((int) strs[vecIndex+1].find("TASK")) != -1) || vecIndex == (((int)strs.size())-1)) 
                {
                    // create task
                    taskVec_.push_back(new Task(curTask, stimsForCurTask));   
                    // clear the temp list to start building it for the next task
                    stimsForCurTask.clear();
                }

                vecIndex++;
            }

        }
        ifsTask.close();        
    }

    ARAIG_Sensors::~ARAIG_Sensors()
    {
        stimVec_.clear();
        taskVec_.clear();
    }

    void ARAIG_Sensors::dump(std::ostream& os)
    {
        for(auto& s : stimVec_)
        {
            os << s->getName() << std::endl;
            s->display(os);
        }
    }

    Stimulation* ARAIG_Sensors::getStim(std::string stimName)
    {
        for(std::vector<Stimulation*>::iterator it = stimVec_.begin(); it != stimVec_.end(); ++it)
        {
            if( ((*it)->getName()).compare(stimName) == 0 )
            {
                return *it;
            }
        }
        return nullptr;
    }

    Task* ARAIG_Sensors::getTask(std::string taskName)
    {
        for(std::vector<Task*>::iterator it = taskVec_.begin(); it != taskVec_.end(); ++it)
        {
            if( ((*it)->getName()).compare(taskName) == 0 )
            {
                return *it;
            }
        }
        return nullptr;
    }
}
