#pragma once

class AbstractSubject;
class SubjectEvent;

class IObserver
{
public:
    virtual ~IObserver() = default;

    virtual void updateObserver(
            const AbstractSubject& subject,
            const SubjectEvent& event) = 0;
};
