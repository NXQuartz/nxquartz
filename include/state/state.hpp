#pragma once

#include "util.hpp"

// Forward declare because templates
template <class T> class StateListener;

/**
 * @brief Reactive state. StateHandlers will be registered as callbacks to state changes on T
 * 
 * @tparam T state type (inherit on T, crtp model)
 */
template <class T>
class State {
protected:
    void dispatchUpdate() {
        for (auto* listener : this->listeners)
            listener->onStateUpdate(reinterpret_cast<T*>(this));
    }
private:
    std::vector<StateListener<T>*> listeners;
    friend StateListener<T>;
};

/**
 * @brief Listen to state changes triggered by State<T>
 * 
 * @tparam T state type
 */
template <class T>
class StateListener {
    State<T>* state;
public:
    StateListener(State<T>* state) : state(state) {
        state->listeners.push_back(this);
    }

    ~StateListener() {
        erase_where(state->listeners, [this](auto* instance) {
            return this == instance;
        });
    }

    T* getState() {
        return reinterpret_cast<T*>(state);
    }

    virtual void onStateUpdate(T* state) = 0;
};