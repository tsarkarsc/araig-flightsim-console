#ifndef _STIMULATION_H_
#define _STIMULATION_H_

#include <string>
#include <iostream>

namespace finalproj
{
    class Stimulation
    {
    protected:
        std::string name_;

    public:
        virtual void display(std::ostream&) const = 0;
        virtual const std::string getName() const = 0;
    };

}

#endif
