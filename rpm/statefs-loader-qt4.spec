Summary: Statefs loader to load providers using Qt4
Name: statefs-loader-qt4
Version: x.x.x
Release: 1
License: LGPLv2
Group: System Environment/Libraries
URL: http://github.com/nemomobile/statefs-loader-qt
Source0: %{name}-%{version}.tar.bz2
BuildRequires: cmake >= 2.8
BuildRequires: pkgconfig(QtCore)
BuildRequires: pkgconfig(statefs) >= 0.3.14
BuildRequires: pkgconfig(cor) >= 0.1.4
Requires: statefs >= 0.3.14

%description
%{summary}

%prep
%setup -q

%build
%cmake -DUSEQT=4
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
make install DESTDIR=%{buildroot}

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_statefs_libdir}/libloader-qt4.so

%posttrans
%statefs_loader_register %{_statefs_libdir}/libloader-qt4.so system
%statefs_loader_register %{_statefs_libdir}/libloader-qt4.so || :

%postun
%statefs_loader_unregister %{_statefs_libdir}/libloader-qt4.so
%statefs_loader_unregister %{_statefs_libdir}/libloader-qt4.so system || :
