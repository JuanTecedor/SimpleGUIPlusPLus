#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "Event.hpp"

#include <vector>

class EventHandler
{
public:
    [[nodiscard]] static std::vector<Event> events();
private:
};

#endif
