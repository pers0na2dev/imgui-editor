# 🔥 **kaazedev/imgui-editor**

<div align="center">
<a href="https://github.com/kaazedev/imgui-editor">
    <img width="100%" src=".github/images/logo.svg" alt="@kaazedev/imgui-editor's logo">
</a>

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![Pull Requests][pull-requests-shield]][pull-requests-url]
</div>

---

## 🤔 **About the project**

No-code UI creating software for ImGui. Create an interface for your application with the convenience of Figma and the functionality of Photoshop.
<br /><br />
The project is developing quite slowly due to my busy schedule in real life, so I decided it was worth opening it up to other developers.

---

## ⚡ **Compiling**


### Prerequisites

- IDE (either)
  - [Visual Studio](https://visualstudio.microsoft.com/)
  - [CLion](https://www.jetbrains.com/clion/)
- C++ Compiler (either)
  - [MinGW](https://sourceforge.net/projects/mingw/)
  - [MSVC](https://visualstudio.microsoft.com/downloads/)
- CMake [https://cmake.org/download/](https://cmake.org/download/)

### Installation

This guide assumes you have already installed the prerequisites.

1. Install [DirectX SDK](https://www.microsoft.com/en-us/download/details.aspx?id=6812)
2. Clone the repo
   ```cmd
   git clone https://github.com/kaazedev/imgui-editor.git
    ```

#### Visual Studio

1. Open the project in Visual Studio using File > Open > CMake
2. Select the CMakeLists.txt file
3. Select the build type (Debug or Release)
4. Click "Configure"
5. Click "Generate"
6. Click "Open Project"
7. Build the project

#### CLion

1. Open the project by selecting the CMakeLists.txt file
2. Select the build type (Debug or Release)

### 📦 codegen-cli compilation
To generate c++ imgui code, you need to use the codegen-cli in this repository. 

To compile the application, install the latest version of the Golang compiler, 
open the "codegen-cli" folder in the terminal and write:

To run without compiling:
```cmd
go run main.go
```

To build an .exe file:
```cmd
go build -o codegen.exe
```

## 🎉 Was the Project helpful? Help us raise these numbers up

[![GitHub followers](https://img.shields.io/github/followers/kaazedev.svg?style=social)](https://github.com/kaazedev)
[![GitHub stars](https://img.shields.io/github/stars/kaazedev/imgui-editor.svg?style=social)](https://github.com/kaazedev/imgui-editor/stargazers)
[![GitHub watchers](https://img.shields.io/github/watchers/kaazedev/imgui-editor.svg?style=social)](https://github.com/kaazedev/imgui-editor/watchers)
[![GitHub forks](https://img.shields.io/github/forks/kaazedev/imgui-editor.svg?style=social)](https://github.com/kaazedev/imgui-editor/network/members)

<a href="https://star-history.com/#kaazedev/imgui-editor&Timeline"><img src="https://api.star-history.com/svg?repos=kaazedev/imgui-editor&type=Timeline" alt="Star History Chart" height="386"></a>

Enjoy! 😃

---

## 🙏 **Acknowledgements**

* [omar (ocornut)](https://github.com/ocornut) - For creating ImGui

---

## ⚖️📝 **License and Changelog**

See the license in the '**[LICENSE](LICENSE)**' file.

Watch the changes in the '**[CHANGELOG.md](CHANGELOG.md)**' file.

---

_Made with a lot of ❤️❤️ by **[@kaazedev](https://github.com/kaazedev)**_

[contributors-shield]: https://img.shields.io/github/contributors/kaazedev/imgui-editor.svg?style=for-the-badge
[contributors-url]: https://github.com/kaazedev/imgui-editor/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/kaazedev/imgui-editor.svg?style=for-the-badge
[forks-url]: https://github.com/kaazedev/imgui-editor/network/members
[stars-shield]: https://img.shields.io/github/stars/kaazedev/imgui-editor.svg?style=for-the-badge
[stars-url]: https://github.com/kaazedev/imgui-editor/stargazers
[issues-shield]: https://img.shields.io/github/issues/kaazedev/imgui-editor.svg?style=for-the-badge
[issues-url]: https://github.com/kaazedev/imgui-editor/issues
[license-shield]: https://img.shields.io/github/license/kaazedev/imgui-editor.svg?style=for-the-badge
[license-url]: https://github.com/kaazedev/imgui-editor/blob/master/LICENSE
[pull-requests-shield]: https://img.shields.io/github/issues-pr/kaazedev/imgui-editor.svg?style=for-the-badge
[pull-requests-url]: https://github.com/kaazedev/imgui-editor/pulls
[product-screenshot]: .github/images/preview.png
