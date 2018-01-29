#ifndef _TASK_H_
#define _TASK_H_

#include <list>
#include <vector>
#include "Stims.h"
#include "Exoskeleton.h"

namespace finalproj
{
    class Task
    {
    private:
        std::string name_;
        std::list<Stimulation*> stimList_;

    public:
        Task();
        ~Task();
        Task(std::string, const std::list<Stimulation*>& sl);
        Task(const Task&);
        Task(Task&&);
        Task& operator=(const Task&);
        Task&& operator=(Task&&);
        void operator+=(Stimulation* stim);
        Stimulation& operator[](size_t i);
        void removeStim(const std::string stimName);
        void dump(std::ostream& os);
        void execute(std::ostream& os);
        const std::string getName();
        Task* clone() const;
        const int getStimListSize();
    };
}

#endif
