# WilliamsCRC <!-- omit in toc -->

Thin port/wrapper of Ross Williams' CRC library.


![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=c%2B%2B&logoColor=white)
[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![GitHub release](https://img.shields.io/github/v/release/synesissoftware/WilliamsCRC.svg)](https://github.com/synesissoftware/WilliamsCRC/releases/latest)
[![Last Commit](https://img.shields.io/github/last-commit/synesissoftware/WilliamsCRC)](https://github.com/synesissoftware/WilliamsCRC/commits/master)
[![CI](https://github.com/synesissoftware/WilliamsCRC/actions/workflows/ci.yml/badge.svg)](https://github.com/synesissoftware/WilliamsCRC/actions/workflows/ci.yml)


## Table of Contents <!-- omit in toc -->

- [Introduction](#introduction)
  - [Dependencies](#dependencies)
- [Installation](#installation)
- [Components](#components)
- [Examples](#examples)
- [Project Information](#project-information)
  - [Where to get help](#where-to-get-help)
  - [Contribution guidelines](#contribution-guidelines)
  - [Dependencies](#dependencies-1)
  - [Related projects](#related-projects)
  - [License](#license)


## Introduction

**WilliamsCRC** is a small C/C++ library that wraps Ross Williams' classic CRC model, providing a simple API for creating CRC contexts, adding data blocks, and calculating CRCs over memory regions or files.


### Dependencies

| Component    | Implemented in | Use in                              | Dependencies                                                 |
| ------------ | -------------- | ----------------------------------- | ------------------------------------------------------------ |
| Core library | C++            | C, C++ — via **WilliamsCRC/WilliamsCRC.h** | [**STLSoft**](https://github.com/synesissoftware/STLSoft) |
| Examples     | C / C++        | -                                   | **STLSoft**                                                  |
| Unit tests   | C              | -                                   | **STLSoft**, [**xTests**](https://github.com/synesissoftware/xTests) |
| Scratch tests | C / C++       | -                                   | **STLSoft**                                                  |


## Installation

Detailed instructions — via **CMake** or bundling — are provided in [**INSTALL.md**](./INSTALL.md).


## Components

The public API is declared in [`WilliamsCRC/WilliamsCRC.h`](./include/WilliamsCRC/WilliamsCRC.h):

| API | Purpose |
| --- | ------- |
| `WilliamsCRC_Init()` / `WilliamsCRC_Uninit()` | Library initialise / uninitialise |
| `WilliamsCRC_Create()` / `WilliamsCRC_Destroy()` | Create / destroy a CRC context |
| `WilliamsCRC_Add()` / `WilliamsCRC_GetCRC()` | Feed data into a context; read the current CRC |
| `WilliamsCRC_CalculateBlockCrc()` | One-shot CRC over a memory block |
| `WilliamsCRC_CalculateFileCrc()` | One-shot CRC over a file |
| `WilliamsCRC_CalculateFileCrcMax()` | One-shot CRC over a file, up to a byte limit |

Supported CRC widths include 4, 5, 6, 7, 8, 10, 11, 12, 14, 15, 16, 24, 30, and 32 bits. A well-known default polynomial is used when `0` is passed.


## Examples

| Example | Language | Purpose |
| ------- | -------- | ------- |
| [**file_checksum**](./examples/cpp/file_checksum/) | C++ | Calculate a CRC over a file (optional byte limit); with no arguments, checksums itself |

Build with **BUILD_EXAMPLES** enabled (the default), then run via **run_all_examples.sh** or the built binary under the CMake build tree.


## Project Information


### Where to get help

[GitHub Issues](https://github.com/synesissoftware/WilliamsCRC/issues)


### Contribution guidelines

Defect reports, feature requests, and pull requests are welcome on https://github.com/synesissoftware/WilliamsCRC.


### Dependencies

**WilliamsCRC** depends on [**STLSoft**](https://github.com/synesissoftware/STLSoft) (≥ 1.11).

The unit-tests additionally depend on [**xTests**](https://github.com/synesissoftware/xTests) (≥ 0.26), and optionally [**shwild**](https://github.com/synesissoftware/shwild).


### Related projects

* [**STLSoft**](https://github.com/synesissoftware/STLSoft) — SoftSteel library dependencies used by the implementation;


### License

**WilliamsCRC** is released under the [BSD 3-Clause license](./LICENSE). Portions derive from Ross Williams' CRC model (see copyright notices in the sources).


<!-- ########################### end of file ########################### -->
