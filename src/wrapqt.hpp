#ifndef _QCOREAPWRAPPER_HPP_
#define _QCOREAPWRAPPER_HPP_

#include "events.hpp"

#include <QObject>
#include <QCoreApplication>

#include <memory>
#include <chrono>
#include <thread>

namespace cor { namespace qt {

class CoreAppImpl : public QCoreApplication
{
    Q_OBJECT;
public:
    CoreAppImpl(int &argc, char *argv[])
        : QCoreApplication(argc, argv)
    {}

    virtual ~CoreAppImpl() { }
    virtual bool event(QEvent*);
};

class CoreAppCondNotify : public QObject
{
    Q_OBJECT;
public:
    CoreAppCondNotify(std::unique_lock<std::mutex> &lock
                      , std::condition_variable &cond);
private slots:
    void notify();
private:
    std::unique_lock<std::mutex> &lock_;
    std::condition_variable &cond_;
};


class CoreAppContainer
{
public:
    CoreAppContainer();
    virtual ~CoreAppContainer();

    void execute(std::function<void()> const&);
private:
    static int argc_;
    static char* argv_[];

    std::mutex mutex_;
    std::condition_variable started_;
    std::thread thread_;
    std::unique_ptr<CoreAppImpl> app_;
};

}}
 
#endif // _QCOREAPWRAPPER_HPP_
