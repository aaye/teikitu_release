
<h1 align="center">Teikitu: Real-Time Interactive Engine</h1>
<p align="center">
  A low-level real-time interactive engine written in C, and a game platform written in C++.<br>
  <a href="https://aaye.github.io/projects/teikitu/documentation"><strong>Explore Teikitu documentation »</strong></a><br><br>
  <a href="https://github.com/aaye/teikitu_release/issues/new?template=bug_report.md">Report bug</a> · <a href="https://github.com/aaye/teikitu_release/issues/new?template=feature_request.md">Request feature</a>
</p>

## Personal Project by Andrew Aye
Contact: [`GitHub`][rep-url], [`LinkedIn`][linkedin-url], [`Mail`][mail], [`Personal Page`][personal-page-url], [`Blog`][blog-url]

## Table of Contents

- [Project Status](#project-status)
- [Project History](#quick-start)
- [Author History](#quick-start)
- [Quick Start](#quick-start)
- [Repo Structure](#repo-structure)
- [Prerequisites and Dependencies](#prerequisites-and-dependencies)
- [Known Issues and Workflow Improvements](#known-issues-and-workflow-improvements)
- [Copyright and license](#copyright-and-license)

## Project Status

[![CodeFactor Grade][codefactor-badge]][codefactor-url]
[![Documentation][documentation-badge]][documentation-url]
[![License: CC BY-NC-SA 4.0][license-badge]][license-url]
![GitHub Sponsors](https://img.shields.io/github/sponsors/aaye)

### Internal Development Build Status

<sub>
    
| Build |   Host   |  GPU  |  Audio  |  SIMD  |  Thread  |    OS    | CPU | Debug | Release | Final | Tools |
|:--------:|:--------:|:-----:|:-------:|:------:|:--------:|:--------:|:---:|:-----:|:-------:|:-----:|:-----:|
| Ninja | Windows  | None  | None    | C17    | Windows  | Windows  | Intel  | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_none_none_debug&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_none_none_release&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_none_none_final&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_none_none_tools&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) |
| Ninja | Windows  | REF   | None    | C17    | Windows  | Windows  | Intel  | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_ref_none_debug&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_ref_none_release&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_ref_none_final&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_ref_none_tools&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) |
| Ninja | Windows  | DX12  | None    | C17    | Windows  | Windows  | Intel  | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_dx12_none_debug&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_dx12_none_release&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_dx12_none_final&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_dx12_none_tools&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) |
| Ninja | Windows  | VLKN  | None    | C17    | Windows  | Windows  | Intel  | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=ninja_debug_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=ninja_release_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=ninja_final_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=ninja_tools_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) |
| Xcode | Mac OS   | None  | None    | C17    | POSIX    | POSIX    | ARM    | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) |
| Xcode | Mac OS   | Metal | None    | C17    | POSIX    | POSIX    | ARM    | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) |
| Make  | Linux    | None  | None    | C17    | POSIX    | POSIX    | ARM    | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) | ![CircleCI](https://circleci.com/gh/aaye/teikitu.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none&circle-token=de43df1f4dfd9a6428a778c0bcd118f6b57ea7fd) |

</sub>

### Public Release Build Status

<sub>
    
| Build |   Host   |  GPU  |  Audio  |  SIMD  |  Thread  |    OS    | CPU | Debug | Release | Final | Tools |
|:--------:|:--------:|:-----:|:-------:|:------:|:--------:|:--------:|:---:|:-----:|:-------:|:-----:|:-----:|
| Ninja | Windows  | None  | None    | C17    | Windows  | Windows  | Intel  | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_none_none_debug) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_none_none_release) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_none_none_final) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_none_none_tools) |
| Ninja | Windows  | REF   | None    | C17    | Windows  | Windows  | Intel  | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_ref_none_debug) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_ref_none_release) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_ref_none_final) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_ref_none_tools) |
| Ninja | Windows  | DX12  | None    | C17    | Windows  | Windows  | Intel  | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_dx12_none_debug) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_dx12_none_release) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_dx12_none_final) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_ninja_clang_c17_x64_win_win_desktop_dx12_none_tools) |
| Ninja | Windows  | VLKN  | None    | C17    | Windows  | Windows  | Intel  | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=ninja_debug_clang_c17_x64_win_win_desktop_dx12_none) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=ninja_release_clang_c17_x64_win_win_desktop_dx12_none) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=ninja_final_clang_c17_x64_win_win_desktop_dx12_none) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=ninja_tools_clang_c17_x64_win_win_desktop_dx12_none) |
| MSVC | Windows  | DX12  | None    | C17    | Windows  | Windows  | Intel  | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_msvc_17_msvc_c17_x64_win_win_wc_desktop_dx12_none) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_msvc_17_msvc_c17_x64_win_win_wc_desktop_dx12_none) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_msvc_17_msvc_c17_x64_win_win_wc_desktop_dx12_none) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___win_msvc_17_msvc_c17_x64_win_win_wc_desktop_dx12_none) |
| Xcode | Mac OS   | None  | None    | C17    | POSIX    | Mac      | ARM    | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none) | ![CircleCI](https://circleci.com/gh/aaye/teikitu_release.svg?style=svg&branch=build___mac_xcode_clang_c17_x64_win_win_desktop_dx12_none) |

</sub>

## Project History

I started this code base at the University of Waterloo (1993-2000). Since then, it has seen over eight significant refactors. The original implementation was object-oriented and Windows com-compliant. The current version is written in a functional style using C17. I am aware that there are many advantages to modern C++. However, when using C++, authors tend to adopt object-orientated paradigms, which, in my opinion, are not a good match for an engine. I have also found that the coding flexibility I adopt in coding this engine has crushed C++ compilers and optimizers. I once had a  revision of the code base with the entire math and geometry library implemented as templates to facilitate an easy way to test 32bit and 64bit floats (for simulation issues and inconsistencies). The release build failed to finish after running for 24 hours. The current implementation, which uses the C pre-processor language for code generation to replace the use of templates, compiles in seconds (under a minute).

## Author History

**Andrew Aye** has worked in the game industry since March 2001. His responsibilities were first to create significant game engine features (for example, a modern simulation on the PS2) and then to create and modify all aspects of a game engine (real-time interactive). Along the way, he became responsible for growing other engineers and organizations. The highlight (to date) of this career was owning the responsibility for leading and managing two Call of Duty projects (Modern Warfare 3, and Ghosts). In 2017, he transitioned into a traditional tech company (Amazon) and helped to bootstrap the Amazon Pharmacy project. In his role on the leadership team of North America Consumables, he helped navigate the pandemic for the engineering teams (remote work) and collaborated on creative solutions for the excessive demand placed on the amazon.com site. He then spent a brief period in an SMS Ad startup (Attentive) as their first Senior Director to support their hyper-scale growth. He later transitioned to Meta in the Instagram Ads organization and, most recently, into the Developer Relations organization for Reality Labs.

## Quick Start

Several quick start options are available:
- Tested (supported) generators are Visual Studio 2022, Xcode, Unix Makefiles, Ninja (Windows)
- Teikitu currently uses the superbuild process using CMake
  - The root CMakeLists.txt file contains only a list of external projects (including Teikitu)
  - Most of the projects are Teikitu dependencies
  - Once all the projects have been successfully built and installed, you can iterate only on Teikitu (or your personal project) without running cmake on the root.
- On a Windows host computer, clone the repo: `git clone https://github.com/aaye/teikitu_release.git`
  - Create a Visual Studio solution using the MSVC compiler and a project using LLVM and Clang
    - Iterating is faster with the Visual Studio solution/project. However, it is not an approved build format since we are forced to use the C++ compiler.
    - `cd build_scripts` (or equivalent)
    - `.\make_windows.ps1 -GPU:DX12`
    - Visual Studio solution file will be in ***//build/msvc17_msvc_c17_x64_win_win_wc_desktop_dx12_none***
    - Ninja Clang project will be in ***//build/msvc17_msvc_c17_x64_win_win_wc_desktop_dx12_none***
  - Compile the matrix of supported configurations
    - `cd build_scripts` (or equivalent)
    - `.\test_windows.ps1`
    - Build results will be in ***//build/ninja_xxx***
- On a Mac host computer (preferably Apple hardware / ARM), clone the repo: `git clone https://github.com/aaye/teikitu_release.git`
  - Work in Progress [Tested - Issue for script to automate the process](https://github.com/aaye/teikitu/issues/22)
- On a Linux host computer, clone the repo: `git clone https://github.com/aaye/teikitu_release.git`
  - Work in Progress [Tested on WSL (Windows Linux Environment) - Issue for script to automate the process](https://github.com/aaye/teikitu/issues/23)

## Repo Structure

```text
teikitu
├──build_scripts/ - START HERE - contains scripts for creating IDE project files or building the project.
├──cmake/ - the core cmake files.
├──teikitu_assets/ - location is created during the build process to store reference data assets.
│  ├──images/ - contains reference images used in the unit tests.
├──teikitu_external/ - location for external dependencies, including git submodules (please read quick start).
├──teikitu_ide/ - contains files needed when generating ide specific project files.
├──teikitu_private/ - contains the source code for the project, including the unit tests.
│  ├──src/ - contains the source code of the project.
│  └──tests/ - contains the unit tests for validating the project.
├──teikitu_samples/ - contains some basic games and applications using Teikitu.
├──teikitu_sdk/ - contains the public include and inline files for using Teikitu.
└──teikitu_tools/ - contains some basic tools created to work with Teikitu.
```
      
## Prerequisites and Dependencies

- [cmake][cmake-url] – Open-Source, cross-platform build tool

## Known Issues and Workflow Improvements

**1. Microsoft Visual Studio Compiler (only) will compile all files as CXX**
<details><summary>2. Standard atomic header for the Microsoft Visual Studio Compiler</summary>
The header file has an error in its 16-byte template overrides. I fixed the defect and validated the change by both the removal of a deadlock that the locking version created and by a size comparison of the atomic 16-byte data structures. If it is not using the 16-byte CAS instructions, the structure will pad to 32 bytes instead of 16. The corrected file was placed into the Teikitu external directory and is used instead of the standard (included) file.
</details>
<details><summary>3. Microsoft Visual Studio Clang-CL (no longer supported)</summary>
    
***C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Microsoft\VC\v170\Microsoft.Cpp.ClangCl.Common.targets*** updated to prevent a Clang warning-as-error issue. If EnableFiberSafeOptimizations is enabled (/GT on the command line) it causes Clang-CL to issue a warning about an unused command-line argument. I suggest adding the following after a similar block that is used to clear out Multiprocessor Compilation (/MP)
```
<!-- copy EnableFiberSafeOptimizations to _EnableFiberSafeOptimizations.
     EnableFiberSafeOptimizations is cleared to avoid passing /GT to clang-cl, which generates a warning -->

<ItemGroup>
  <ClCompile Condition="'%(ClCompile.EnableFiberSafeOptimizations)' == 'true'">
    <_EnableFiberSafeOptimizations>true</_EnableFiberSafeOptimizations>
    <EnableFiberSafeOptimizations>false</EnableFiberSafeOptimizations>
  </ClCompile>`<br>
</ItemGroup>`
```

***C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Microsoft\VC\v170\Microsoft.Cpp.ClangCl.Common.targets*** updated to prevent a critical issue where Clang-CL is not passing through the C-standard flag to Clang. The result caused PCH and compilation mis-matches (the PCH was not compiled using the same C-standard flags as the C source files).

Object created near line 132 (<!-- Precompiled headers - need to build them first -->)
Missing an assignment for

```
LanguageStandard_C =“%(ClCompile.LanguageStandard_C)”
```

</details>
<details><summary>4. CMake Improvements when generating Visual Studio project files. (Personal preference change, not necessary by others)</summary>
Modified to allow me to set the intermediate directory.
</details>




## Copyright and License

Teikitu is subject to the [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/) unless otherwise stated.


[bug-report-url]: https://github.com/twbs/bootstrap/issues/new?template=bug_report.md
[feature-request-url]: https://github.com/twbs/bootstrap/issues/new?template=feature_request.md

[rep-url]: https://github.com/aaye
[linkedin-url]: https://www.linkedin.com/in/andrew-aye/
[mail]: andrew.aye@gmail.com
[personal-page-url]: https://andrew.aye.page
[blog-url]: https://aaye.github.io/professional/blog/

[codefactor-badge]: https://img.shields.io/codefactor/grade/github/aaye/teikitu_release
[codefactor-url]: https://www.codefactor.io/repository/github/aaye/teikitu_release
[documentation-badge]: https://github.com/aaye/teikitu/actions/workflows/documentation.yml/badge.svg
[documentation-url]: https://aaye.github.io/projects/
[license-badge]: https://img.shields.io/badge/License-CC_BY--NC--SA_4.0-lightgrey.svg
[license-url]: http://creativecommons.org/licenses/by-nc-sa/4.0/

[cmake-url]: https://cmake.org/
