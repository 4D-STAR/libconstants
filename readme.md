# libconstants

libconstants is the authoritative source for physical constants for the SERiF project.

This has been broken out of the main serif project to allow for more modularity

## Building
In order to build libconstants you need `meson>=1.5.0`. This can be installed with `pip`

```bash
pip install "meson>=1.5.0"
```

Then from the root libconstants directory it is as simple as

```bash
meson setup build --buildtype=release
meson compile -C build
meson test -C build
```

this will auto generate a pkg-config file for you so that linking other libraries to libconstants is easy.

