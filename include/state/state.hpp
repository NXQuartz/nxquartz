#pragma once

#include "util.hpp"

/**
 * @brief Reactive state. Listeners will be registered as callbacks to state
 * changes on T
 *
 * @tparam T state type (inherit on T, crtp pattern)
 */
template <class T>
class State {
public:
    State& operator=(State&&) = delete;

    /**
     * @brief Listen to state changes triggered by State<T>
     *
     * @tparam T state type
     */
    class Listener {
        T& state;

    public:
        Listener(T& state) : state(state) {
            state.listeners.push_back(this);
        }

        virtual ~Listener() {
            erase_where(state.listeners,
                [this](auto* instance) { return this == instance; });
        }

        T& getState() { return state; }

        virtual void onStateUpdate(T& state) = 0;
    };

protected:
    void dispatchUpdate() {
        for (auto* listener : this->listeners)
            listener->onStateUpdate(static_cast<T&>(*this));
    }

private:
    std::vector<Listener*> listeners;
    friend Listener;
};