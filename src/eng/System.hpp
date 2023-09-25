#ifndef SYSTEM_HPP
#define SYSTEM_HPP

class System
{
public:
    System();
    ~System();
    System(System&) = delete;
    System(System&&) = delete;
    System operator=(System) = delete;
    System& operator=(System&&) = delete;
};

#endif
