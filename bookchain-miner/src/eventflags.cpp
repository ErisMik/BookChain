#pragma once

#include "queue.hpp"
#include <string>
#include <vector>

namespace bookchain::eventflags {

enum class EventKey {
    NEW_BLOCK,
};

class Event {
public:
    Event(EventKey eventKey, std::string data);
    data();
    eventKey();

private:
    EventKey _eventKey;
    std::string _data;
};

class EventEntry {
};

class EventTable {
public:
    static addEvent

        private : ::ThreadsafeQueue<EventEntry>
};

class EventWriter {
};

class EventReader {
};

}  // namespace bookchain::eventflags
