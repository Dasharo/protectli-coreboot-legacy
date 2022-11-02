# Protectli legacy coreboot firmware

## Prerequsites

1. Access to the following repositories:
  - [protectli-coreboot-legacy](https://github.com/Dasharo/protectli-coreboot-legacy)
  - [protectli-blobs](https://github.com/Dasharo/protectli-blobs)

## Build

* Clone repository:

```bash
git clone  git@github.com:Dasharo/protectli-coreboot-legacy.git
```

* Checkout to the desired revision (e.g. `v4.12.0.8`):

```bash
cd protectli-coreboot-legacy
git checkout v4.12.0.8
```

* Build:

```bash
DISTCLEAN=true ./build.sh fw4b
```
