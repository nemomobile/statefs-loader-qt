#include <statefs/loader.hpp>
#include <statefs/util.h>
#include <cor/so.hpp>
#include "wrapqt.hpp"

static const char *sym_name = statefs_provider_accessor();

#if QT_VERSION < 0x050000
static const char *loader_name = "qt4";
#else
static const char *loader_name = "qt5";
#endif

class QtLoader : public statefs::Loader
{
public:
    virtual ~QtLoader() {}

    std::shared_ptr<statefs_provider> load(std::string const& path)
    {
        if (!app)
            app.reset(new cor::qt::CoreAppContainer());

        std::shared_ptr<cor::SharedLib> lib
            (new cor::SharedLib(path, RTLD_LAZY));
        if (!lib->is_loaded())
            return nullptr;
        auto fn = lib->sym<statefs_provider_fn>(sym_name);
        if (!fn)
            return nullptr;

        statefs_provider *prov = nullptr;
        auto load_ = [fn, &prov]() {
            prov = fn();
        };
        app->execute(load_);
        if (!prov)
            return nullptr;

        auto deleter = [lib](statefs_provider* p) {
            if (p)
                statefs_provider_release(p);
            if (lib)
                lib->close();
        };
        statefs::provider_ptr res(prov, deleter);
        return res;
    }

    virtual std::string name() const { return loader_name; }

private:

    std::unique_ptr<cor::qt::CoreAppContainer> app;
};

EXTERN_C statefs::Loader * create_cpp_provider_loader()
{
    return new QtLoader();
}
