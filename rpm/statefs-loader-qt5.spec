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
BuildRequires: pkgconfig(statefs) >= 0.3.1
BuildRequires: pkgconfig(cor) >= 0.1.4
Requires: statefs

%description
%{summary}

%prep
%setup -q

%build
%cmake -DUSEQT=5
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
make install DESTDIR=%{buildroot}

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_libdir}/statefs/libloader-qt5.so

%post
statefs register %{_libdir}/statefs/libloader-qt5.so || :
