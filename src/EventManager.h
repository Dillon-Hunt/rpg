#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <functional>
#include <map>
#include <vector>
#include <memory>
#include <exception>

/**
 * Available events
 */
enum Event {
    LOG_DEBUG_INFO,
    PLACE_TILE,
    PLACE_OBJECT,
    PLACE_TILED_OBJECT,
    SELECT_TILE,
    MOUSE_CLICK,
    ESCAPE
};

/**
 * Base structure for a listener
 */
struct BaseEventListener {
    virtual ~BaseEventListener() = default;
    virtual bool matchesCaller(void* caller) const = 0;
};

/**
 * Structure for a listener with a callback with data
 */
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

/**
 * Structure for a listener with a callback without data
 */
template <>
struct EventListener<void> : BaseEventListener {
    int id;
    void* caller;
    std::function<void()> callback;

    EventListener(int id, void* caller, std::function<void()> callback)
        : id(id), caller(caller), callback(callback) {}

    bool matchesCaller(void* c) const override {
        return caller == c;
    }
};

/**
 * Manages events throughout application
 */
class EventManager {
    private:
        int lastID;
        std::map<Event, std::vector<std::shared_ptr<BaseEventListener>>> events;

        /**
         * Constructs a new EventManager object
         */
        EventManager() : lastID(-1) {}

        /**
         * Deconstructor for EventManager
         */
        ~EventManager() {}

    public:
        /**
         * Retrives the EventManager object
         *
         * @returns a static EventManager object
         */
        static EventManager& get() {
            static EventManager instance;
            return instance;
        }

        /**
         * Creates a new event listener without any data
         *
         * @param event the name of the event
         * @param caller the object that is listening
         * @param callback the function to call when the event occurs
         * @returns the id of the event listener
         */
        template <typename Caller>
        int addListener(const Event event, Caller* caller, const std::function<void()>& callback) {
            auto listener = std::make_shared<EventListener<void>>(EventListener<void> { ++lastID, caller, callback });
            events[event].emplace_back(listener);
            return lastID;
        }

        /**
         * Creates a new event listener
         *
         * @param event the name of the event
         * @param caller the object that is listening
         * @param callback the function to call when the event occurs
         * @returns the id of the event listener
         */
        template <typename Caller, typename Data>
        int addListener(const Event event, Caller* caller, const std::function<void(const Data&)>& callback) {
            auto listener = std::make_shared<EventListener<Data>>(EventListener<Data> { ++lastID, caller, callback });
            events[event].emplace_back(listener);
            return lastID;
        }
        
        /**
         * Emits an event without data
         *
         * @param event the name of the event
         */
        void emitEvent(const Event event) {
            if (events.find(event) != events.end()) {
                for (const auto& listener : events[event]) {
                    auto typedListener = std::static_pointer_cast<EventListener<void>>(listener);

                    try {
                        typedListener->callback();
                    } catch (const std::exception& e) {
                        continue;
                    }
                }
            }
        }

        /**
         * Emits an event with data
         *
         * @param event the name of the event
         * @param data the event's data
         */
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

        /**
         * Removes a specific listener for a specific caller
         *
         * @param event the name of the event to remove
         * @param caller the caller to remove the listeners for
         */
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

        /**
         * Removes all listeners for a specific caller
         *
         * @param caller the caller to remove the listeners for
         */
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

#endif // EVENT_MANAGER_H
