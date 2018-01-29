#ifndef _EXOSKELETON_H_
#define _EXOSKELETON_H_

#include "Stimulation.h"

namespace finalproj
{
    class Exoskeleton : public Stimulation
    {
    private:
        int intensity_;
        int duration_;

    public:
        Exoskeleton(std::string, int, int);
        ~Exoskeleton();
        void display(std::ostream&) const;
        const std::string getName() const;
    };
}

#endif
