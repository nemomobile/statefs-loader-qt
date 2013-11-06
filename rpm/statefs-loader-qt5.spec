%define statefs_ver 0.3.24

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
BuildRequires: pkgconfig(statefs) >= %{statefs_ver}
BuildRequires: pkgconfig(cor) >= 0.1.4
Requires: statefs >= %{statefs_ver}

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
%statefs_loader_install qt5 %{_statefs_libdir}/libloader-qt5.so

%clean
rm -rf %{buildroot}

%files -f qt5.files
%defattr(-,root,root,-)
%{_statefs_libdir}/libloader-qt5.so

%pre
%statefs_pre

%post
/sbin/ldconfig
%statefs_loader_register qt5
%statefs_post

%preun
%statefs_preun
%statefs_loader_unregister qt5

%postun
/sbin/ldconfig
%statefs_postun
