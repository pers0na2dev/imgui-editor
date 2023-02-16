# 🔩 editor compilation
Use the latest version of Visual Studio.

Install [DirectX SDK](www.microsoft.com/en-us/download/details.aspx?id=6812)

Run the project build in x86 Release with the C++20 version. 


# 📦 codegen-cli compilation
    To generate c++ imgui code, you need to use the codegen-cli in this repository. 

    To compile the application, install the latest version of the Golang compiler, 
    open the "codegen-cli" folder in the terminal and write:

        $ go run main.go ## to run without compiling.
        $ go build -o codegen.exe ## to build an .exe file.
