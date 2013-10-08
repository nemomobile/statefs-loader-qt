Summary: Statefs loader to load providers using Qt5
Name: statefs-loader-qt5
Version: x.x.x
Release: 1
License: LGPLv2
Group: System Environment/Libraries
URL: http://github.com/nemomobile/statefs-loader-qt
Source0: %{name}-%{version}.tar.bz2
BuildRequires: cmake >= 2.8
BuildRequires: pkgconfig(Qt5Core)
BuildRequires: pkgconfig(statefs) >= 0.3.14
BuildRequires: pkgconfig(cor) >= 0.1.4
Requires: statefs >= 0.3.14

%description
%{summary}

%prep
%setup -q

%build
%cmake -DUSEQT=5 %{?_with_multiarch:-DENABLE_MULTIARCH=ON}
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
make install DESTDIR=%{buildroot}

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_statefs_libdir}/libloader-qt5.so

%pre
%statefs_pre || :

%posttrans
%statefs_loader_register %{_statefs_libdir}/libloader-qt5.so system
%statefs_loader_register %{_statefs_libdir}/libloader-qt5.so
%statefs_posttrans || :

%preun
%statefs_preun || :

%postun
%statefs_loader_unregister %{_statefs_libdir}/libloader-qt5.so
%statefs_loader_unregister %{_statefs_libdir}/libloader-qt5.so system
%statefs_cleanup
%statefs_postun || :
