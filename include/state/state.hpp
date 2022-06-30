#pragma once

#include "util.hpp"

/**
 * @brief Reactive state. Listeners will be registered as callbacks to state
 * changes on T
 *
 * @tparam T state type (inherit on T, crtp model)
 */
template <class T>
class State {
public:
    /**
     * @brief Listen to state changes triggered by State<T>
     *
     * @tparam T state type
     */
    class Listener {
        State<T>* state;

    public:
        Listener(State<T>* state) : state(state) {
            state->listeners.push_back(this);
        }

        virtual ~Listener() {
            erase_where(state->listeners,
                [this](auto* instance) { return this == instance; });
        }

        T* getState() { return reinterpret_cast<T*>(state); }

        virtual void onStateUpdate(T* state) = 0;
    };

protected:
    void dispatchUpdate() {
        for (auto* listener : this->listeners)
            listener->onStateUpdate(static_cast<T*>(this));
    }

private:
    std::vector<State<T>::Listener*> listeners;
    friend State<T>::Listener;
};