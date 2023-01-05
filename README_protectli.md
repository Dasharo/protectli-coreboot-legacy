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

## Flashing new firmware

After flashing new firmware image, do a hard reboot. To do a hard reboot simply
pull the power plug, wait a moment and plug it back in. Powering down the device
by holding the power button, or even using shutdown/reboot commands can corrupt
the flash memory and brick your device. Doing a hard reboot avoids this issue.
