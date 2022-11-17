# imgui.tech
No-code UI creating software for ImGui. Create an interface for your application with the convenience of Figma and the functionality of Photoshop.

The project is developing quite slowly due to my busy schedule in real life, so I decided it was worth opening it up to opsorsors.


# 🔩 editor compilation
    Use the latest version of Visual Studio.
    Run the project build in x86 Release with the C++20 version. 


# 📦 codegen-cli compilation
    To generate c++ imgui code, you need to use the codegen-cli in this repository. 

    To compile the application, install the latest version of the Golang compiler, 
    open the "codegen-cli" folder in the terminal and write:

        $ go run main.go ## to run without compiling.
        $ go build -o codegen.exe ## to build an .exe file.

# ✏️ pull request rules
    Please specify what exactly you have changed and what the point of the change is.
    Pull requests without this information are likely to be automatically rejected.