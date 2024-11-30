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
    PLACE_TILED_OBJECT,
    SELECT_TILE
};

struct BaseEventListener {
    virtual ~BaseEventListener() = default;
    virtual bool matchesCaller(void* caller) const = 0;
};

template <typename Data>
struct EventListener : BaseEventListener {
    int id;
    void* caller;
    std::function<void(const Data&)> callback;

    EventListener(int id, void* caller, std::function<void(const Data&)> callback) : id(id), caller(caller), callback(callback) {}

    bool matchesCaller(void* c) const override {
        return caller == c;
    }
};

class EventManager {
    private:
        int lastID;
        std::map<Event, std::vector<std::shared_ptr<BaseEventListener>>> events;

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

        template <typename Caller>
        void removeListener(const Event event, Caller* caller) {
            if (caller == nullptr) return;

            if (events.find(event) != events.end()) {
                std::vector<std::shared_ptr<BaseEventListener>>& listeners = events[event];
                
                listeners.erase(
                    std::remove_if(
                        listeners.begin(),
                        listeners.end(),
                        [caller](const std::shared_ptr<void>& listener) {
                            auto baseListener = std::static_pointer_cast<BaseEventListener>(listener);

                            if (baseListener) {
                                return baseListener->matchesCaller(static_cast<void*>(caller));
                            }

                            return true;
                        }
                    ),
                    listeners.end()
                );

                if (listeners.empty()) {
                    events.erase(event);
                }

            }
        }

        template <typename Caller>
        void removeListeners(Caller* caller) {
            if (caller == nullptr) return;

            for (auto it = events.begin(); it != events.end();) {
                std::vector<std::shared_ptr<BaseEventListener>>& listeners = it->second;
                
                listeners.erase(
                    std::remove_if(
                        listeners.begin(),
                        listeners.end(),
                        [caller](const std::shared_ptr<void>& listener) {
                            auto baseListener = std::static_pointer_cast<BaseEventListener>(listener);

                            if (baseListener) {
                                return baseListener->matchesCaller(static_cast<void*>(caller));
                            }

                            return true;
                        }
                    ),
                    listeners.end()
                );

                if (listeners.empty()) {
                    it = events.erase(it);
                } else {
                    it++;
                }
            }
        }
};

#endif // ifndef EVENT_MANAGER_H
