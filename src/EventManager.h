#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <functional>
#include <map>
#include <vector>
#include <memory>
#include <exception>

enum Event {
    LOG_DEBUG_INFO,
    PLACE_TILE,
    PLACE_OBJECT,
    SELECT_TILE
};

template <typename Data>
struct EventListener {
    int id;
    void* caller;
    std::function<void(const Data&)> callback;
};

class EventManager {
    private:
        int lastID;
        std::map<Event, std::vector<std::shared_ptr<void>>> events;

        EventManager() : lastID(-1) {}

        ~EventManager() {}

    public:
        static EventManager& get() {
            static EventManager instance;
            return instance;
        }

        template <typename Caller, typename Data>
        int addListener(const Event event, Caller* caller, const std::function<void(const Data&)>& callback) {
            if (caller == nullptr) return -1;
            auto listener = std::make_shared<EventListener<Data>>(EventListener<Data> { ++lastID, caller, callback });
            events[event].emplace_back(listener);
            return lastID;
        }

        template <typename Data>
        void emitEvent(const Event event, const Data& data) {
            if (events.find(event) != events.end()) {
                for (const auto& listener : events[event]) {
                    auto typedListener = std::static_pointer_cast<EventListener<Data>>(listener);

                    try {
                        typedListener->callback(data);
                    } catch (const std::exception& e) {
                        continue;
                    }
                }
            }
        }

        template <typename Caller, typename Data>
        void removeListener(const Event event, Caller* caller) {
            if (caller == nullptr) return;
            if (events.find(event) != events.end()) {
                std::vector<std::shared_ptr<void>>& listeners = events[event];
                
                listeners.erase(
                    std::remove_if(
                        listeners.begin(),
                        listeners.end(),
                        [caller](const std::shared_ptr<void>& listener) {
                                auto typedListener = std::static_pointer_cast<EventListener<Data>>(listener);

                                try {
                                    bool include = typedListener->caller == static_cast<void*>(caller);
                                    return include;
                                } catch (const std::exception& e) {
                                    return true;
                                }
                            }
                    ),
                    listeners.end()
                );

                if (listeners.empty()) {
                    events.erase(event);
                }

            }
        }

        template <typename Caller, typename Data>
        void removeListeners(Caller* caller) {
            if (caller == nullptr) return;
            for (auto& pair : events) {
                std::vector<std::shared_ptr<void>>& listeners = pair.second;
                
                listeners.erase(
                    std::remove_if(
                        listeners.begin(),
                        listeners.end(),
                        [caller](const std::shared_ptr<void>& listener) {
                                auto typedListener = std::static_pointer_cast<EventListener<Data>>(listener);

                                try {
                                    bool include = typedListener->caller == static_cast<void*>(caller);
                                    return include;
                                } catch (const std::exception& e) {
                                    return true;
                                }
                            }
                    ),
                    listeners.end()
                );

                if (listeners.empty()) {
                    events.erase(pair.first);
                }
            }
        }
};

#endif // ifndef EVENT_MANAGER_H
