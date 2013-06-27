#ifndef _STATEFS_PRIVATE_EVENTS_HPP_
#define _STATEFS_PRIVATE_EVENTS_HPP_

#include <QEvent>
#include <functional>

namespace cor { namespace qt {

class Event : public QEvent
{
public:
    enum Type {
        Execute = QEvent::User
    };

    virtual ~Event() {}

protected:
    Event(Type t) : QEvent(static_cast<QEvent::Type>(t)) {}
private:
    Event();
};

class EventExecute : public Event
{
public:
    EventExecute(std::function<void()> const& fn)
        : Event(Event::Execute), fn_(fn) {}

    void execute() const { fn_(); }
private:
    std::function<void()> fn_;
};

}}

#endif // _STATEFS_PRIVATE_EVENTS_HPP_
