#include "Exoskeleton.h"

namespace finalproj
{
    Exoskeleton::Exoskeleton(std::string name, int intensity, int duration)
    {
        name_ = name;
        intensity_ = intensity;
        duration_ = duration;
    }

    Exoskeleton::~Exoskeleton() {}

    const std::string Exoskeleton::getName() const
    {
        return name_;
    }

    void Exoskeleton::display(std::ostream& os) const
    {
        os << "     " << "Type = exoskeleton" << std::endl;
        os << "     " << "Intensity = " << intensity_ << std::endl;
        os << "     " << "Duration = " << duration_ << std::endl;
    }
}
