Protectli coreboot port release notes
=====================================

## [v4.12.0.12]

Release date: 23.02.2023

### Binaries

- [FW4C v4.12.0.12](https://cloud.3mdeb.com/index.php/s/MjkZ8m69iAFTnGt)
- [FW4C v4.12.0.12 SHA256 sum](https://cloud.3mdeb.com/index.php/s/CmGtrst5JQMFZCE)

Checking shasums:

```shell
# assuming all 2 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw4c_v4.12.0.12.rom.SHA256
```

Flashing instructions (assuming Linux with flashrom v1.0 or newer and
`iomem=relaxed` in kernel command line):

```shell
flashrom -p internal -w protectli_fw4c_v4.12.0.12.rom --ifd -i bios
```

### Components

* coreboot based on 4.12 revision c82e0e111a98
* [TianoCore UEFIPayload revision 139c157403 based on upstream revision dd7523b5b1](https://github.com/Dasharo/edk2/compare/dd7523b5b1...139c157403)
* Custom FSP to support FW4C platform based on public Intel Braswell FSP,
  SHA256: eb03161df80a9d108c8e1608532f9206aa211bb79be99daabba71bfc68f8fa52
* Management Engine: TXE 2.0.5.1137 extracted from FW4C-221026 AMI BIOS,
  SHA256: 0de2f65efa380cd1f8c104b84f108780c595b0da957098b2b4a44f626c00266c
* Flash descriptor extracted from FW4C-221026 AMI BIOS,
  SHA256: 089baf9562dcb5d7b0719bffdaac247d4fc3d92cac557303d8cde0cdc755a253

### Added

- iPXE network boot support with Intel i225 NIC
- UEFI compatible interface
- Persistent boot options and boot order

### Changed

- Switched from SeaBIOS to UEFI Payload
- Switched from FSP Cache as RAM setup to open-source Cache as RAM (CAR) setup
  eliminating power cycles
- USB calibration settings for better USB detection rate

### Fixed

- Occasional power cycles after power off
- USB detection issues
- USB 2.0 port hang-ups
- Display not working on inner HDMI port

### Limitations

- Firmware display resolution is fixed to 1024x768 due to VGA OptionROM
  limitations. VGA OptionROM is required for inner HDMI port to work in the
  firmware. Other display initialization methods (FSP GOP Driver and Intel EFI
  GOP Driver) with high resolution capabilities did not work.

## [v4.12.0.9]

Release date: 8.12.2022

### Binaries

- [FW4C v4.12.0.9](https://cloud.3mdeb.com/index.php/s/F5em8ddcZPWSRSW)
- [FW4C v4.12.0.9 SHA256 sum](https://cloud.3mdeb.com/index.php/s/MzqDiMaayR3PiqN)

Checking shasums:

```shell
# assuming all 2 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw4c_v4.12.0.9.rom.SHA256
```

Flashing instructions (assuming Linux with flashrom v1.0 or newer and
`iomem=relaxed` in kernel command line):

```shell
flashrom -p internal -w protectli_fw4c_v4.12.0.9.rom --ifd -i bios
```

### Components

* coreboot based on 4.12 revision 87f9fc8584c9
* [SeaBIOS v1.0.6 based on rel-1.12.1 revision 171fc897](https://github.com/Dasharo/SeaBIOS/compare/171fc897...v1.0.6)
* Custom built FSP to support FW4C platform based on Intel Braswell FSP MR3,
  SHA256: 7131aa947d2f97d678048b186187474b61d0a292076192bf9efc8234537313ca
* Management Engine: TXE 2.0.5.1137 extracted from FW4C-221026 AMI BIOS,
  SHA256: 0de2f65efa380cd1f8c104b84f108780c595b0da957098b2b4a44f626c00266c
* Flash descriptor extracted from FW4C-221026 AMI BIOS,
  SHA256: 089baf9562dcb5d7b0719bffdaac247d4fc3d92cac557303d8cde0cdc755a253

### Added

- FW4C platform support

## [v4.12.0.8]

Release date: 25.10.2022

### Binaries

- [FW4B v4.12.0.8](https://cloud.3mdeb.com/index.php/s/5jSpmJ4K9ptGBmG)
- [FW4B v4.12.0.8 SHA256 sum](https://cloud.3mdeb.com/index.php/s/nf4JFoiJnJj5sn3)

Checking shasums:

```shell
# assuming all 2 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw4b_v4.12.0.8.rom.sha256
```

Flashing instructions (assuming Linux with flashrom v1.0 or newer and
`iomem=relaxed` in kernel command line):

```shell
flashrom -p internal -w protectli_fw4b_v4.12.0.8.rom --ifd -i bios
```

### Components

* coreboot based on 4.12 revision 87f9fc8584c9
* [SeaBIOS v1.0.6 based on rel-1.12.1 revision 171fc897](https://github.com/Dasharo/SeaBIOS/compare/171fc897...v1.0.6)
* [iPXE 2017.3 stable revision ebf2eaf515e4](https://github.com/ipxe/ipxe/commits/ebf2eaf515e4)

### Fixed

- Fixed high CPU usage in Windows

## [v4.9.0.3]

Release date: 14.20.2022

### Binaries

- [FW2B v4.9.0.3](https://cloud.3mdeb.com/index.php/s/fTqwoHm68rjZYXQ)
- [FW2B v4.9.0.3 SHA256 sum](https://cloud.3mdeb.com/index.php/s/pmEpyX8ZoFzeEne)

Checking shasums:

```shell
# assuming all 2 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw2b_v4.9.0.3.rom.sha256
```

Flashing instructions (assuming Linux with flashrom v1.0 or newer and
`iomem=relaxed` in kernel command line):

```shell
flashrom -p internal -w protectli_fw2b_v4.9.0.3.rom --ifd -i bios
```

### Components

* coreboot based on 4.9 revision a706ad5
* [SeaBIOS v1.0.4 based on rel-1.12.1 revision 171fc897](https://github.com/Dasharo/SeaBIOS/compare/171fc897...v1.0.4)
* [iPXE 2017.3 stable revision fd6d1f4](https://github.com/ipxe/ipxe/commits/fd6d1f4)

### Fixed

- Fixed high CPU usage in Windows

## [v4.9.0.2]

Release date: 01.06.2021

### Binaries

- [FW2B v4.9.0.2](https://3mdeb.com/open-source-firmware/protectli/fw2b/protectli_fw2b_v4.9.0.2.rom)
- [FW2B v4.9.0.2 SHA256 sum](https://3mdeb.com/open-source-firmware/protectli/fw2b/protectli_fw2b_v4.9.0.2.rom.sha256)

Checking shasums:

```shell
# assuming all 2 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw2b_v4.9.0.2.rom.sha256
```

Flashing instructions (assuming Linux with flashrom v1.0 or newer and
`iomem=relaxed` in kernel command line):

```shell
flashrom -p internal -w protectli_fw2b_v4.9.0.2.rom --ifd -i bios
```

### Components

* coreboot based on 4.9 revision a706ad5
* [SeaBIOS v1.0.4 based on rel-1.12.1 revision 171fc897](https://github.com/Dasharo/SeaBIOS/compare/171fc897...v1.0.4)
* [iPXE 2017.3 stable revision fd6d1f4](https://github.com/ipxe/ipxe/commits/fd6d1f4)

### Changed

- Disabled HPET timer causing issues in Linux

## [v4.12.0.7]

Release date: 01.10.2021

### Binaries

- [FW4 v4.12.0.7](https://cloud.3mdeb.com/index.php/s/XN5e2b864Rk4pcj)
- [FW4 v4.12.0.7 SHA256 sum](https://cloud.3mdeb.com/index.php/s/KroToJL4BAbmAcb)
- [coreboot v4.12.0.7 source code](https://cloud.3mdeb.com/index.php/s/JyDiXQiTj3fJaiH)

```shell
# assuming all 2 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw6_v4.12.0.7.rom.SHA256
```

Building images

```shell
wget https://cloud.3mdeb.com/index.php/s/JyDiXQiTj3fJaiH/download -O Protectli_coreboot_v4.12.0.7.zip
unzip Protectli_coreboot_v4.12.0.7.zip
./build.sh fw4
```

> Please remove and unzip the package again when building subsequent binaries.

Flashing instructions (assuming Linux with flashrom v1.0 or newer and
`iomem=relaxed` in kernel command line):

```shell
flashrom -p internal -w protectli_fw4_v4.12.0.7.rom --ifd -i bios
```

### Components

* coreboot based on 4.12 revision 87f9fc8584c9
* [SeaBIOS v1.0.6 based on rel-1.12.1 revision 171fc897](https://github.com/Dasharo/SeaBIOS/compare/171fc897...v1.0.6)
* [iPXE 2017.3 stable revision ebf2eaf515e4](https://github.com/ipxe/ipxe/commits/ebf2eaf515e4)

### Features

* added iPXE support for i210 NICs on FW4

## [v4.12.0.6]

Release date: 27.07.2021

### Binaries

- [FW6 v4.12.0.6](https://cloud.3mdeb.com/index.php/s/zcSpzB3ocSgKnzY)
- [FW6 v4.12.0.6 SHA256 sum](https://cloud.3mdeb.com/index.php/s/qzdXA6N8yrwRzNH)
- [coreboot v4.12.0.6 source code](https://cloud.3mdeb.com/index.php/s/P6wk3Y3SaN9EBMi)

```shell
# assuming all 2 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw6_v4.12.0.6.rom.SHA256
```

Building images

```shell
wget https://cloud.3mdeb.com/index.php/s/P6wk3Y3SaN9EBMi/download -O Protectli_coreboot_v4.12.0.6.zip
unzip Protectli_coreboot_v4.12.0.6.zip
./build.sh fw6
```

> Please remove and unzip the package again when building subsequent binaries.

Flashing instructions (assuming Linux with flashrom v1.0 or newer and
`iomem=relaxed` in kernel command line):

```shell
flashrom -p internal -w protectli_fw6_v4.12.0.6.rom --ifd -i bios
```

### Components

* coreboot based on 4.12 revision 87f9fc8584c9
* [SeaBIOS v1.0.6 based on rel-1.12.1 revision 171fc897](https://github.com/Dasharo/SeaBIOS/compare/171fc897...v1.0.6)
* [iPXE 2017.3 stable revision ebf2eaf515e4](https://github.com/ipxe/ipxe/commits/ebf2eaf515e4)

### Fixed

* disable CLKREQ in mPCIE slot to fix issues with WiFi cards operation

## [v4.12.0.5]

Release date: 19.02.2021

### Binaries

- [FW2B v4.12.0.5](https://cloud.3mdeb.com/index.php/s/M9xnEq35jEoaqPD)
- [FW2B v4.12.0.5 SHA256 sum](https://cloud.3mdeb.com/index.php/s/5sRQpCHYxyxM7ZT)
- [FW4B v4.12.0.5](https://cloud.3mdeb.com/index.php/s/dCRgJbL6Tc65ki2)
- [FW4B v4.12.0.5 SHA256 sum](https://cloud.3mdeb.com/index.php/s/k4WYjXqx5xqNrN4)
- [coreboot v4.12.0.5 source code](https://cloud.3mdeb.com/index.php/s/9TnjBezgiX3kTKQ)

```shell
# assuming all 2 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw2b_v4.12.0.5.rom.SHA256
sha256sum -c protectli_fw4b_v4.12.0.5.rom.SHA256
```

Building images

```shell
wget https://cloud.3mdeb.com/index.php/s/9TnjBezgiX3kTKQ/download -O Protectli_coreboot_v4.12.0.5.zip
unzip Protectli_coreboot_v4.12.0.5.zip
./build.sh fw2b
# or
./build.sh fw4b
```

> Please remove and unzip the package again when building subsequent binaries.

Flashing instructions (assuming Linux with flashrom v1.0 or newer and
`iomem=relaxed` in kernel command line):

```shell
flashrom -p internal -w protectli_fw4b_v4.12.0.5.rom --ifd -i bios
# or
flashrom -p internal -w protectli_fw2b_v4.12.0.5.rom --ifd -i bios
```

### Fixed

* memory initialization issues on FW2B/FW4B with Kingston and Crucial DIMMs

## [v4.12.0.4]

Release date: 26.11.2020

### Binaries

- [FW6 v4.12.0.4](https://cloud.3mdeb.com/index.php/s/BRD7SkqtwZEiw6S)
- [FW6 v4.12.0.4 SHA256 sum](https://cloud.3mdeb.com/index.php/s/fbQn3TMtRSjXs59)
- [FW2B v4.12.0.4](https://cloud.3mdeb.com/index.php/s/r2TCsMsXB6gWjkd)
- [FW2B v4.12.0.4 SHA256 sum](https://cloud.3mdeb.com/index.php/s/DgArCNXib6pn85Y)
- [FW4B v4.12.0.4](https://cloud.3mdeb.com/index.php/s/rjQyHkNe28z3SWS)
- [FW4B v4.12.0.4 SHA256 sum](https://cloud.3mdeb.com/index.php/s/BJcDJb9nbWXYkJs)

```shell
# assuming all 2 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw6_v4.12.0.4.rom.sha256
```

### Features

* added iPXE support for i210 NICs on FW6

## [v4.12.0.3]

Release date: 28.10.2020

### Binaries

- [FW6 v4.12.0.3](https://cloud.3mdeb.com/index.php/s/AdyNkr9f2Lr5rfS)
- [FW6 v4.12.0.3 SHA256 sum](https://cloud.3mdeb.com/index.php/s/2Dtfqw8gMQC74yR)
- [FW2B v4.12.0.3](https://cloud.3mdeb.com/index.php/s/7NdxmDoeSyoySrA)
- [FW2B v4.12.0.3 SHA256 sum](https://cloud.3mdeb.com/index.php/s/ALDKmQ5nf5zGbpT)
- [FW4B v4.12.0.3](https://cloud.3mdeb.com/index.php/s/9yfNcFXqZExZ4Br)
- [FW4B v4.12.0.3 SHA256 sum](https://cloud.3mdeb.com/index.php/s/sTXT7oyoGXFR9pj)

```shell
# assuming all 2 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw6_v4.12.0.3.rom.sha256
```

### Features

* added memtest payload for FW2B and FW4B

## [v4.12.0.1]

Release date: 13.07.2020

### Binaries

- [FW6 v4.12.0.1](https://cloud.3mdeb.com/index.php/s/9JyyaF5WiNHb4sB)
- [FW6 v4.12.0.1 SHA256 sum](https://cloud.3mdeb.com/index.php/s/WXywrSWe3Dmqmre)
- [FW2B v4.12.0.1](https://cloud.3mdeb.com/index.php/s/kLiNDmygjfQPD3k)
- [FW2B v4.12.0.1 SHA256 sum](https://cloud.3mdeb.com/index.php/s/eoMXzMja5iyo9mc)
- [FW4B v4.12.0.1](https://cloud.3mdeb.com/index.php/s/wQrTtLZsb5ArXak)
- [FW4B v4.12.0.1 SHA256 sum](https://cloud.3mdeb.com/index.php/s/xbpm3N7cCBT56Ff)
-
```shell
# assuming all 2 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw6_v4.12.0.1.rom.sha256
```

### Features

* rebased to coreboot 4.12 revision 87f9fc85
* enabled firmware TPM 2.0 on FW6
* updated the microcode to newest revision
* enabled open source graphics initialization on FW6 - libgfxinit
* integrated BMP bootsplash

### Known issues

* The screen output on FW6 does not scale well in SeaBIOS and has color issues
  with JPG bootsplash

## [v4.9.0.1]

Release date: 25.03.2019

### Binaries

- [fw2b coreboot](https://cloud.3mdeb.com/index.php/s/HSmwYaJXGpoYrnp/download)

- [fw2b coreboot SHA256 file](https://cloud.3mdeb.com/index.php/s/zQa2rnQftfj9P4d/download)

- [fw4b coreboot](https://cloud.3mdeb.com/index.php/s/H8CjW4EZ6poFTdW/download)

- [fw4b coreboot SHA256 file](https://cloud.3mdeb.com/index.php/s/QkKZ32N3Ye5Xkzy/download)

Checking shasums:

```shell
# assuming all 4 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw2b_v4.9.0.1.rom.sha256
sha256sum -c protectli_fw4b_v4.9.0.1.rom.sha256
```

### Features

* added a coreboot version string printed on screen and serial in SeaBIOS
* changed the platform naming in SMBIOS tables to upper case

### Known issues

* Boards use slightly older Intel FSP (Intel's proprietary silicon
  initialization code) due to problems with memory initialization with newer
  FSP.
  UPDATE: it is impossible to use the FSP MR2 binary directly from the
  Intel repository. FSP MR2 has a SecureBoot option which breaks the memory
  initialization routine. In the blobs package we have added a patched binary
  with SecureBoot disabled, which works on the Protectli platforms. The binary
  has been patched using Intel's Binary Configuration Tool (BCT).

* Upper USB 3.0 port detects devices with a significant delay in BIOS. In order
  to increase detectability of USB devices, maximum USB polling time has been
  increased to 6 seconds (was 100ms by default). It has a serious impact on boot
  time, but ensure better USB operation in BIOS. The operating system has no
  problems with USB.

Solution/workaround: if one encounters problems with USB mass storage or
keyboard, swap the USB slots. It is advised to use upper USB 3.0 port for
keyboards since full USB3.0 speed is achievable only in the lower slot in BIOS.
If one encounters problems with upper USB 3.0 slot, replugging USB stick right
after `SeaBIOS (version ...)` string appears, causes the stick to be detected
immediately.

## [rc4]

Release date: 20.03.2019

### Binaries

- [fw2b coreboot](https://cloud.3mdeb.com/index.php/s/mD2KCLo3LnkfTfa/download)

- [fw2b coreboot SHA256 file](https://cloud.3mdeb.com/index.php/s/Max6RxseWH5w2Kz/download)

- [fw4b coreboot](https://cloud.3mdeb.com/index.php/s/Hi8z8JNo6ajATzF/download)

- [fw4b coreboot SHA256 file](https://cloud.3mdeb.com/index.php/s/BJJP97G8WdZ8PBo/download)

Checking shasums:

```shell
# assuming all 4 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw2b_rc4.rom.sha256
sha256sum -c protectli_fw4b_rc4.rom.sha256
```

### Features

* fixed boot failure fallback to iPXE instead of USB if present

### Known issues

* Boards use slightly older Intel FSP (Intel's proprietary silicon
  initialization code) due to problems with memory initialization with newer
  FSP.
  UPDATE: it is impossible to use the FSP MR2 binary directly from the
  Intel repository. FSP MR2 has a SecureBoot option which breaks the memory
  initialization routine. In the blobs package we have added a patched binary
  with SecureBoot disabled, which works on the Protectli platforms. The binary
  has been patched using Intel's Binary Configuration Tool (BCT).

* Upper USB 3.0 port detects devices with a significant delay in BIOS. In order
  to increase detectability of USB devices, maximum USB polling time has been
  increased to 6 seconds (was 100ms by default). It has a serious impact on boot
  time, but ensure better USB operation in BIOS. The operating system has no
  problems with USB.

Solution/workaround: if one encounters problems with USB mass storage or
keyboard, swap the USB slots. It is advised to use upper USB 3.0 port for
keyboards since full USB3.0 speed is achievable only in the lower slot in BIOS.
If one encounters problems with upper USB 3.0 slot, replugging USB stick right
after `SeaBIOS (version ...)` string appears, causes the stick to be detected
immediately.

## [rc3]

Release date: 15.03.2019

### Binaries

- [fw2b coreboot](https://cloud.3mdeb.com/index.php/s/DenB99kbzqcx96Z/download)

- [fw2b coreboot SHA256 file](https://cloud.3mdeb.com/index.php/s/ig32xx5WtoFFwSo/download)

- [fw4b coreboot](https://cloud.3mdeb.com/index.php/s/WpQY2aCnHfk3q6Q/download)

- [fw4b coreboot SHA256 file](https://cloud.3mdeb.com/index.php/s/AZ9Gbcxa92sDS7z/download)

Checking shasums:

```shell
# assuming all 4 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw2b_rc3.rom.sha256
sha256sum -c protectli_fw4b_rc3.rom.sha256
```

### Features

* slightly improved USB detection when multiple sticks plugged

* fixed issue with broken serial port when bootsplash is enabled but no display
  attached

* brought back bootsplash image

* enabled debugging info for issue resolving purposes

* display can be attached later after operating system is loaded, no need to
  keep display attached during early boot phase (but in order to get graphical
  output in BIOS, display must be attached from the beggining)

* SeaBIOS seem to does not hang anymore (hardware enumeration may take several
  seconds which may make false impression of hang)

### Known issues

* Boards use slightly older Intel FSP (Intel's proprietary silicon
  initialization code) due to problems with memory initialization with newer
  FSP.
  UPDATE: it is impossible to use the FSP MR2 binary directly from the
  Intel repository. FSP MR2 has a SecureBoot option which breaks the memory
  initialization routine. In the blobs package we have added a patched binary
  with SecureBoot disabled, which works on the Protectli platforms. The binary
  has been patched using Intel's Binary Configuration Tool (BCT).

* Upper USB 3.0 port detects devices with a significant delay in BIOS. In order
  to increase detectability of USB devices, maximum USB polling time has been
  increased to 6 seconds (was 100ms by default). It has a serious impact on boot
  time, but ensure better USB operation in BIOS. The operating system has no
  problems with USB.

Solution/workaround: if one encounters problems with USB mass storage or
keyboard, swap the USB slots. It is advised to use upper USB 3.0 port for
keyboards since full USB3.0 speed is achievable only in the lower slot in BIOS.
If one encounters problems with upper USB 3.0 slot, replugging USB stick right
after `SeaBIOS (version ...)` string appears, causes the stick to be detected.

## [rc2]

Release date: 14.03.2019

### Binaries

- [fw2b coreboot](https://cloud.3mdeb.com/index.php/s/d9zqDRdJ7QaNLL4/download)

- [fw2b coreboot SHA256 file](https://cloud.3mdeb.com/index.php/s/7oXiEmEiEbcSS5P/download)

- [fw4b coreboot](https://cloud.3mdeb.com/index.php/s/N6G5EYqnKSdtkpY/download)

- [fw4b coreboot SHA256 file](https://cloud.3mdeb.com/index.php/s/Qr6aLwZijGBadcD/download)

Checking shasums:

```shell
# assuming all 4 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw2b_rc2.rom.sha256
sha256sum -c protectli_fw4b_rc2.rom.sha256
```

### Features

* iPXE payload is loaded on demand instead of executed at each boot

* boot menu key has been changed to F11 and work on both serial and USB keyboard

* removed bootsplash to fix issue with broken serial port when display not
  attached

* changed to custom SeaBIOS v1.0.1

### Known issues

* Boards use slightly older Intel FSP (Intel's proprietary silicon
  initialization code) due to problems with memory initialization with newer
  FSP.
  UPDATE: it is impossible to use the FSP MR2 binary directly from the
  Intel repository. FSP MR2 has a SecureBoot option which breaks the memory
  initialization routine. In the blobs package we have added a patched binary
  with SecureBoot disabled, which works on the Protectli platforms. The binary
  has been patched using Intel's Binary Configuration Tool (BCT).

* Upper USB 3.0 port detects devices with a significant delay in BIOS. In order
  to increase detectability of USB devices, maximum USB polling time has been
  increased to 5 seconds (was 100ms by default). It has a serious impact on boot
  time, but ensure better USB operation in BIOS. The operating system has no
  problems with USB.

Solution/workaround: if one encounters problems with USB mass storage or
keyboard, swap the USB slots. It is advised to use upper USB 3.0 port for
keyboards since full USB3.0 speed is achievable only in the lower slot in BIOS.

* When the display is not connected Intel proprietary code (called FSP) does
  not initialize graphics. That leads to no graphical output in OS, even if the
  display is attached later in the boot process. The display can be removed
  after booting has been completed, it will not affect the operation of
  graphics anymore.

Solution/workaround: keep display attached during boot process so the graphics
will be initialized.

* SeaBIOS payload sometimes hangs on PCI enumeration (platform specific issue).

Solution/workaround: reset the platform by re-plugging power supply.

## [rc1]

Release date: 06.03.2019

### Binaries

- [fw2b coreboot](https://cloud.3mdeb.com/index.php/s/RWERmDC6ak62SFF/download)

- [fw2b coreboot SHA256 file](https://cloud.3mdeb.com/index.php/s/RBP5iyrwSb6GPER/download)

- [fw4b coreboot](https://cloud.3mdeb.com/index.php/s/RNXrCEnaG8BW7Em/download)

- [fw4b coreboot SHA256 file](https://cloud.3mdeb.com/index.php/s/xCG35Z3zpmcAmqr/download)

Checking shasums:

```shell
# assuming all 4 files have been downloaded to the same directory without changing names
sha256sum -c protectli_fw2b_rc1.rom.sha256
sha256sum -c protectli_fw4b_rc1.rom.sha256
```

### Features

* Full coreboot support for FW2B and FW4B mainboards

* Protectli logo displayed on boot

* Boot menu for boot medium selection entered via F10 key

* PXE network boot support

* Legacy boot support

* SATA and USB boot support

* Serial console support

* Graphics support

### Known issues and troubleshooting

* SeaBIOS payload sometimes hangs on PCI enumeration (platform specific issue).

Solution/workaround: reset the platform by re-plugging power supply.

* Boot menu key in SeaBIOS is F10, not F11. Due to inconsistency in the USB
  keyboard scan codes translation, F11 has a different keycode for the serial
  port and for the keyboard. According to
  [USB HID to PS/2 keycode translation from Microsoft](https://download.microsoft.com/download/1/6/1/161ba512-40e2-4cc9-843a-923143f3456c/translate.pdf)
  there are 2 translation tables, the first one is used by most systems and
  applications (including SeaBIOS), while the second one is used by Microsoft.
  It looks like USB keyboards are designed to work under windows and follow the
  second translation table. That leads to incorrect key code detection. Keys
  from F1 to F10 have consistent key codes, starting from F11, the keycodes
  begin to differ.

Solution: no solution. Boot menu key changed to F10.

* Upper USB 3.0 port detects devices with a significant delay in BIOS. In order
  to increase detectability of USB devices, maximum USB polling time has been
  increased to 5 seconds (was 100ms by default). It has a serious impact on boot
  time, but ensure better USB operation in BIOS. The operating system has no
  problems with USB.

Solution/workaround: if one encounters problems with USB mass storage or
keyboard, swap the USB slots. It is advised to use upper USB 3.0 port for
keyboards since full USB3.0 speed is achievable only in the lower slot in BIOS.

* When the display is not connected Intel proprietary code (called FSP) does
  not initialize graphics. That leads to no graphical output in OS, even if the
  display is attached later in the boot process. The display can be removed
  after booting has been completed, it will not affect the operation of
  graphics anymore.

Solution/workaround: keep display attached during boot process so the graphics
will be initialized.

* When graphics is not initialized, the boot menu options do not show up on
  serial console. The issue is caused by unsuccessful bootsplash showing with
  uninitialized graphics. SeaBIOS cannot return to the correct mode which
  breaks the serial console output of the boot menu.

Solution/workaround: keep display attached during boot process so the graphics
will be initialized. Or remove the bootsplash from coreboot image:

```shell
./build/cbfstool build/coreboot.rom remove -n bootsplash.jpg
```

* Boards use slightly older Intel FSP (Intel's proprietary silicon
  initialization code) due to problems with memory initialization with newer
  FSP.
  UPDATE: it is impossible to use the FSP MR2 binary directly from the
  Intel repository. FSP MR2 has a SecureBoot option which breaks the memory
  initialization routine. In the blobs pakcage we have added a patched bianry
  with SecureBoot disabled, which works on the Protectli platforms. The binary
  has been patched using Intel's Binary Configuration Tool (BCT).
