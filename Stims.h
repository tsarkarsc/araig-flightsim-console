#ifndef _STIMS_H_
#define _STIMS_H_

#include "Stimulation.h"

namespace finalproj
{
    class Stims : public Stimulation
    {
    public:
        enum Location { abs, front, back, traps };
        Stims(std::string, Location, int, int, int);
        ~Stims();
        void display(std::ostream&) const;
        const std::string getName() const;

    private:
        Location loc_;
        int intensity_;
        int frequency_;
        int duration_;
    };
}

#endif
