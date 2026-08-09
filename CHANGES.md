# WilliamsCRC - CHANGES <!-- omit in toc -->


## 2.0.6 - 9th August 2026

2.0.6


## 2.0.6-alpha1 - 7th August 2026

* Added modular GitHub Actions CI (**ci.yml** / **ci-cell.yml**) with install-smoke coverage;
* Added unit-tests **test.unit.api**, **test.unit.block_crc**, and **test.unit.file_crc** (via **xTests**);
* Expanded **README.md** (incl. CI badges and Components table);
* Added **AUTHORS.md**, **CHANGES.md**, and **NEWS.md**;
* Standardised library version macros (**SYNSOFT_WILLIAMSCRC_VER_***) to the computed composite form (**VER_PATCH**, **VER_ALPHABETA**, **VER_REVISION** alias);
* Fixed **WilliamsCRC_CalculateFileHandleCrc()** NULL dereference when no byte-count out-parameter is supplied;
* Fixed stale **b64** copy-paste in **CMakeLists.txt** / **test/CMakeLists.txt** (implicit-link suppress define; dependency comments);
* Fixed MSVC C4996 (`fopen`) in **test.unit.file_crc** via safe-open helper;
* **test.scratch.file_checksum** now smokes with no arguments (checksums self);
* CMake helper-script enhancements (**ProjectName** from **.sis/project_name.txt**; MinGW `MakeCmd` consistency; modernised **run_all_unit_tests.sh** / **run_all_unit_tests.cmd** with `--unit-only` / `--component-only`);
* Project boilerplate canonicalisation (**INSTALL.md** **STLSoft** clone URL; **FAQ.md** / **TODO.md** tidy);


## 2.0.5 - 27th February 2025

* GCC / CMake compatibility improvements;


## 2.0.4 - 23rd October 2024

* CMake scripts improvements;


## 2.0.3 - 17th October 2024

* CMake packaging finalisation;


## 2.0.2 - 10th July 2024

* CMake finalisation;


## 2.0.1 - 30th June 2024

* Maintenance release;


## 2.0.0 - 9th January 2024

* CMake-based build and packaging;


## 1.2.4-beta1 - 31st December 2023

* FOSS modernisation begun;


## 1.2.3 - 7th January 2021

* GCC compatibility;


<!-- ########################### end of file ########################### -->
