#pragma once

#include <algorithm>
#include <vector>
#include <list>
#include <utility>
#include <stdexcept>

#include "Observer.hpp"

class SubjectEvent
{
public:
    virtual ~SubjectEvent() = default;
};

class AbstractSubject
{
public:
    virtual ~AbstractSubject() = default;

    void addObserver(IObserver& observer)
    {
        observers_.emplace_back(observer);
    }

    void removeObserver(const IObserver& observer)
    {
        auto el = std::find_if(observers_.begin(), observers_.end(),
            [&](const IObserver& item)
            {
                return &observer == &item;
            });

        if (el == observers_.end())
            throw std::runtime_error("AbstractSubject::removeObserver(): observer not found");

        observers_.erase(el);
    }

protected:
    void notifyObservers()
    {
        SubjectEvent dummyEvent;
        notifyObservers(dummyEvent);
    }

    void notifyObservers(const SubjectEvent& event)
    {
        for (IObserver& observer : observers_)
            observer.updateObserver(*this, event);
    }

private:
    std::list<std::reference_wrapper<IObserver>> observers_;
};
