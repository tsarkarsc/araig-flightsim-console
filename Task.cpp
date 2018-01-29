#include "Task.h"

namespace finalproj
{
    Task::Task()
    {
        name_ = "";
        stimList_.clear();
    }

    Task::~Task() 
    {
        stimList_.clear();
    }

    Task::Task(std::string str, const std::list<Stimulation*>& sl)
    {
        name_ = str;
        stimList_ = sl;
    }

    Task::Task(const Task& task)
    {
        name_ = task.name_;
        stimList_ = task.stimList_;
    }

    Task::Task(Task&& task)
    {
        name_ = task.name_;
        stimList_ = task.stimList_;
        task.name_ = "";
        task.stimList_.clear();
    }

    Task& Task::operator=(const Task& task)
    {
        if(this != &task)
        {
            name_ = task.name_;
            stimList_.clear();
            stimList_ = task.stimList_;
        }
        return *this;
    }

    Task&& Task::operator=(Task&& task)
    {
        if(this != &task)
        {
            name_ = task.name_;
            task.name_ = "";
            stimList_.clear();
            stimList_ = std::move(task.stimList_);
        }
        return std::move(*this);
    }

    void Task::operator+=(Stimulation* stim)
    {
        stimList_.push_back(stim);
    }

    Stimulation& Task::operator[](size_t i)
    {
        std::list<Stimulation*>::iterator it = stimList_.begin();
        std::advance(it, i);
        return **it; 
    }

    const std::string Task::getName()
    {
        return name_;
    }

    void Task::removeStim(const std::string stimName)
    {
        for(std::list<Stimulation*>::iterator it = stimList_.begin(); it != stimList_.end(); ++it)
        {
            if (stimName.compare((*it)->getName()) == 0)
            {
                stimList_.erase(it++);
            }
        }
    }

    void Task::dump(std::ostream& os)
    {
        os << name_ << std::endl;
        for(std::list<Stimulation*>::iterator it = stimList_.begin(); it != stimList_.end(); ++it)
        {
            os << "     " << (*it)->getName() << std::endl;
        }
    }

    void Task::execute(std::ostream& os)
    {
        for(std::list<Stimulation*>::iterator it = stimList_.begin(); it != stimList_.end(); ++it)
        {
            os << (*it)->getName() << std::endl;
            (*it)->display(os);
        }
    }

    Task* Task::clone() const
    {
        return new Task(*this);
    }

    const int Task::getStimListSize()
    {
        return stimList_.size();
    }
}
