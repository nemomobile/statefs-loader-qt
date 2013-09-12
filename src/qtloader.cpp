#include <statefs/loader.hpp>
#include <statefs/util.h>
#include <cor/so.hpp>
#include "wrapqt.hpp"

#include <iostream>
#include <QDebug>

static const char *sym_name = statefs_provider_accessor();

#if QT_VERSION < 0x050000
static const char *loader_name = "qt4";
#else
static const char *loader_name = "qt5";
#endif

class QtLoader : public statefs::Loader
{
public:
    QtLoader() : is_reloadable_(true) {
        if (QCoreApplication::instance())
            std::cerr << "NB! QCoreApplication is already created!"
                      << std::endl;
    }

    virtual ~QtLoader() {
    }

    std::shared_ptr<statefs_provider> load
    (std::string const& path, statefs_server *server)
    {
        if (!app) {
            is_reloadable_ = false;
            app.reset(new cor::qt::CoreAppContainer());
        }

        auto lib = std::make_shared<cor::SharedLib>(path, RTLD_LAZY);
        if (!lib->is_loaded()) {
            qWarning() << "qt5 loader: Can't load " << path.c_str();
            return nullptr;
        }
        auto fn = lib->sym<statefs_provider_fn>(sym_name);
        if (!fn) {
            qWarning() << "qt5 loader: Can't resolve statefs_provider_fn in "
                       << path.c_str();
            return nullptr;
        }

        statefs_provider *prov = nullptr;
        auto load_ = [fn, &prov, server]() {
            prov = fn(server);
        };
        app->execute(load_);
        if (!prov) {
            qWarning() << "qt5 loader: provider is null";
            return nullptr;
        }

        auto deleter = [lib](statefs_provider* p) mutable {
            if (p)
                statefs_provider_release(p);
            lib.reset();
        };
        statefs::provider_ptr res(prov, deleter);
        return res;
    }

    virtual std::string name() const { return loader_name; }

    virtual bool is_reloadable() const { return is_reloadable_; }

private:

    std::unique_ptr<cor::qt::CoreAppContainer> app;
    bool is_reloadable_;
};

EXTERN_C statefs::Loader * create_cpp_provider_loader()
{
    return new QtLoader();
}
