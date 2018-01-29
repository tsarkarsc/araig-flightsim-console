#include "Profile.h"

namespace finalproj
{
    Profile::Profile(const char* fileName, std::ofstream& os, ARAIG_Sensors& as)
    {
        std::ifstream ifs(fileName);
        if(!ifs)
        {
            throw "Couldn't open Profile file";
        }

        bool isStuDataProcessed = false;
        int count = 0;
        while(ifs.good())
        {
            std::string line;
            std::getline(ifs, line);

            if(!line.empty())
            {
                if (count < 3)
                {       
                    std::istringstream ss(line);
                    std::vector<std::string> fields;
                    std::string field;
                    while(std::getline(ss, field, ','))
                    {
                        fields.push_back(field);
                    }

                    if(fields.size() == 3)
                    {
                        if(!isStuDataProcessed)
                        {
                            stuFirstName_ = fields[0];
                            stuLastName_ = fields[1];
                            stuNum_ = fields[2];
                            isStuDataProcessed = true;
                        }
                        else
                        {
                            flyInstFirstName_ = fields[0];
                            flyInstLastName_ = fields[1];
                            flyInstNum_ = fields[2];
                        }
                    }
                    else if (fields.size() == 2)
                    {
                        calIntensity.max = atoi(fields[0].c_str());
                        calIntensity.min = atoi(fields[1].c_str());
                    }
                }
                else
                {

                    // The reason for this string manipulation is due to getline giving me a line that was 1 character
                    // larger than the actual expected string (except for the very last one in the file)
                    // eg. Task1 expected string length is 5, but line.length() would be 6
                    // it wasn't a whitespace issue, since trimming didn't help, this code is a work around
                    // Cut out "Task", convert num, like "17" from str to int, back to str, put "Task" and "num" back together
                    std::string searchStr = line.substr(0,4) + std::to_string(atoi(line.substr(4).c_str()));
                    if(as.getTask(searchStr) != nullptr)
                    {
                        ToRun.push_back((as.getTask(searchStr))->clone());
                    }
                }
            }
            
            if(count < 3)
                count++;
            
        }
        ifs.close();

        // ******************************************
        // This code is just used to create an output file that looks similar to the sample output file
        // Shows the execution of all the tasks
        // ******************************************

        os << "Student: " << stuFirstName_ << " " << stuLastName_ << " - " << stuNum_ << std::endl;
        os << "Instructor: " << flyInstFirstName_ << " " << flyInstLastName_ << " - " << flyInstNum_ << std::endl;
        os << "Student Calibration:" << std::endl << "MAX = " << calIntensity.max << std::endl << "MIN = " << calIntensity.min << std::endl;
        for(std::vector<Task*>::iterator it = ToRun.begin(); it != ToRun.end(); ++it)
        {
            os << (*it)->getName() << std::endl;
            (*it)->execute(os);
        }
        os.close();
    }

    Profile::~Profile()
    {
        ToRun.clear();
        Completed.clear();
    }

    void Profile::displayToRun()
    {
        std::cout << "Display To Run Tasks" << std::endl;
        for(std::vector<Task*>::iterator it = ToRun.begin(); it != ToRun.end(); ++it)
        {
            (*it)->dump(std::cout);
        }
    }

    void Profile::displayCompleted()
    {
        std::cout << "Display Completed Tasks" << std::endl;
        for(std::vector<Task*>::iterator it = Completed.begin(); it != Completed.end(); ++it)
        {
            (*it)->dump(std::cout);
        }
    }

    void Profile::displayNextTask()
    {
        std::cout << "Display Next Task" << std::endl;
        if(!ToRun.empty())
        {
            ToRun.front()->dump(std::cout);
        }
    }

    void Profile::displayLastCompTask()
    {
        std::cout << "Display Last Task" << std::endl;
        if(!Completed.empty())
        {
            Completed.back()->dump(std::cout);
        }
        
    }

    void Profile::run()
    {
        std::string input = "";

        std::cout << "Student: " << stuFirstName_ << " " << stuLastName_ << " - " << stuNum_ << std::endl;
        std::cout << "Instructor: " << flyInstFirstName_ << " " << flyInstLastName_ << " - " << flyInstNum_ << std::endl;
        std::cout << "Student Calibration:" << std::endl << "MAX = " << calIntensity.max << std::endl << "MIN = " << calIntensity.min << std::endl;

        // Execute tasks based on user input
        do
        {
            std::cout << std::endl;
            std::cout << "Enter r to run a task, or q to quit" << std::endl;
            std::cin >> input;
            std::cout << std::endl;

            if(input.compare("r") == 0)
            {
                std::cout << ToRun.front()->getName() << std::endl;
                ToRun.front()->execute(std::cout);
                Completed.push_back(std::move(ToRun.front()));
                ToRun.erase(ToRun.begin());
            }
            else if (!(input.compare("q") == 0))
            {
                std::cout << "Wrong key. Press r or q" << std::endl;
            }
        } while(!(input.compare("q") == 0 ));
    }

    const int Profile::getToRunSize()
    {
        return ToRun.size();
    }

    const int Profile::getCompletedSize()
    {
        return Completed.size();
    }
}
