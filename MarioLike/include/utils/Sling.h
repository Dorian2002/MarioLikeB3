#pragma once
#ifndef SLING_SIGSLOT_H
#define SLING_SIGSLOT_H

#include <functional>
#include <map>


#define DECLARE_DELEGATE(DelegateName, ...) using DelegateName = Event::Signal<__VA_ARGS__>;
#define MAKE_SLOT(Object, Function, ...) Event::Slot<__VA_ARGS__>(Object, Function);

namespace Event
{
    using SlotKey = std::size_t;

    template<typename ...Args>
    class Signal;

    template<typename ...Args>
    class Slot
    {
    private:
        struct Connection
        {
            Signal<Args...>* signal;
            Slot<Args...>* slot;
            SlotKey key;
            bool managed;

            Connection(Signal<Args...>* signal, Slot<Args...>* slot,
                SlotKey key, bool managed) :
                signal(signal), slot(slot), key(key), managed(managed) {
            }

            void releaseSlot() {
                this->slot->connection = nullptr;
                if (this->managed) {
                    delete this->slot;
                }
            }
        };

        std::function<void(Args...)> callback;
        Connection* connection = nullptr;

    public:
        Slot() : callback() {
        }

        Slot(const std::function<void(Args...)>& f) : callback(f) {
        }

        Slot(std::function<void(Args...)>&& f) : callback(f) {
        }

        template <class T>
        Slot(T* target, void (T::* method)(Args...)) {
            setCallback(target, method);
        }

        template <class T>
        Slot(T* target, void (T::* method)(Args...) const) {
            setCallback(target, method);
        }

        Slot(const Slot& slot) : callback(slot.callback) {
        }

        virtual ~Slot() {
            this->disconnect();
        }

        Slot& operator = (const Slot& slot) {
            this->callback = slot.callback;
            return *this;
        }

        Slot& operator = (Slot&& slot) {
            this->disconnect();
            this->move(&slot);
            return *this;
        }

        void disconnect() {
            if (this->connection != nullptr) {
                this->connection->signal->disconnect(this);
            }
        }

        void setCallback(const std::function<void(Args...)>& f) {
            this->callback = f;
        }

        void setCallback(std::function<void(Args...)>&& f) {
            this->callback = f;
        }

        template <class T>
        void setCallback(T* target, void (T::* method)(Args...)) {
            this->callback = [target, method](Args... args) {
                (target->*method)(args...);
            };
        }

        template <class T>
        void setCallback(T* target, void (T::* method)(Args...) const) {
            this->callback = [target, method](Args... args) {
                (target->*method)(args...);
            };
        }

        friend class Signal<Args...>;
    };

    template<typename ...Args>
    class Signal
    {
    private:
        using Connection = typename Slot<Args...>::Connection;

        std::map<std::size_t, Connection> connections;
        SlotKey sequence;

        SlotKey connect(Slot<Args...>* slot, bool managed) {
            if (slot == nullptr) {
                return 0;
            }
            if (slot->connection != nullptr) {
                if (slot->connection->signal == this) {
                    return slot->connection->key;
                }
                slot->disconnect();
            }

            ++this->sequence;
            auto res = this->connections.emplace(
                std::make_pair(
                    this->sequence,
                    Connection(this, slot, this->sequence, managed)
                )
            );

            slot->connection = &res.first->second;
            return this->sequence;
        }

      
    public:
        Signal() : connections(), sequence(0) {
        }

        Signal(const Signal& signal) = delete;

        virtual ~Signal() {
            this->clear();
        }

        Signal& operator = (const Signal& signal) = delete;

        void operator() (Args... args) const {
            this->emit(args...);
        }

        SlotKey connect(Slot<Args...>* slot) {
            return this->connect(slot, false);
        }

        SlotKey connect(Slot<Args...>& slot) {
            return this->connect(&slot, false);
        }

        SlotKey connect(Slot<Args...>&& slot) {
            return this->connect(new Slot<Args...>(std::move(slot)), true);
        }

        void disconnect(SlotKey key) {
            auto it = this->connections.find(key);
            if (it != this->connections.end()) {
                it->second.releaseSlot();
                this->connections.erase(it);
            }
        }

        void disconnect(Slot<Args...>* slot) {
            if (slot != nullptr && slot->connection != nullptr &&
                slot->connection->signal == this) {
                this->disconnect(slot->connection->key);
            }
        }

        void disconnect(Slot<Args...>& slot) {
            this->disconnect(&slot);
        }

        void clear() {
            for (auto& conn : this->connections) {
                conn.second.releaseSlot();
            }
            this->connections.clear();
        }

        void emit(Args... args) const {
            for (const auto& conn : this->connections) {
                if (conn.second.slot->callback) {
                    conn.second.slot->callback(std::forward<Args>(args)...);
                }
            }
        }
    };
}
#endif

/*Event::Slot MySlot = Event::Slot(this, &GameEngine::Update);

Event::Signal MySignal = Event::Signal();
MySignal.connect(MySlot);

MySignal.emit();*/

/*Event::Slot<float> MySlot = Event::Slot<float>(this, &GameEngine::Update);

Event::Signal<float> MySignal = Event::Signal<float>();
MySignal.connect(MySlot);

MySignal.emit(0.0f);*/

/*void GameEngine::Update()
{
    FOnUpdate OnUpdateDelegate;
    OnUpdateDelegate.connect(MAKE_SLOT(this, &GameEngine::Update, float));
    OnUpdateDelegate.emit(0);
}*/
