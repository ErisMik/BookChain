#pragma once

#include "queue.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace bookchain::eventflags {

enum class EventKey {
    NEW_BLOCK,
};

class Event {
public:
    Event(EventKey eventKey, std::string data);
    std::string data();
    EventKey eventKey();

private:
    EventKey _eventKey;
    std::string _data;
};

class EventDispatcher {
public:
    addEvent

        private : ::ThreadsafeQueue<EventEntry>
};

class EventSubscriber {
public:
private:
};

}  // namespace bookchain::eventflags
