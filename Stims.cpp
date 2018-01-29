#include "Stims.h"

namespace finalproj
{
    Stims::Stims(std::string name, Location loc, int intensity, int frequency, int duration)
    {
        name_ = name;
        loc_ = loc;
        intensity_ = intensity;
        frequency_ = frequency;
        duration_ = duration;
    }

    Stims::~Stims() {}

    const std::string Stims::getName() const
    {
        return name_;
    }

    void Stims::display(std::ostream& os) const
    {
        std::string locStr;
        switch (loc_)
        {
            case abs: 
                locStr = "abs";
                break;
            case front:
                locStr = "front";
                break;
            case back:
                locStr = "back";
                break;
            case traps:
                locStr = "traps";
                break;
        }
        os << "     " << "Type = stim" << std::endl;
        os << "     " << "Location = " << locStr << std::endl;
        os << "     " << "Intensity = " << intensity_ << std::endl;
        os << "     " << "Frequency = " << frequency_ << std::endl;
        os << "     " << "Duration = " << duration_ << std::endl;
    }
}
