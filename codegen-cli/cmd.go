package main

import (
	"codegen-cli/internal"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"os"
)

var projectFiles []string

func init() {
	files, err := ioutil.ReadDir("C:\\imgui.tech\\")
	if err != nil {
		log.Fatal(err)
	}

	for _, file := range files {
		if file.IsDir() == false {
			projectFiles = append(projectFiles, file.Name())
		}
	}
}

func main() {
	fmt.Println("imgui.tech - code generation application.")
	fmt.Printf("Select file (%d) to generate code for:\n", len(projectFiles))
	for i, file := range projectFiles {
		fmt.Printf("[%d] %s\n", i, file)
	}

	fmt.Println("\nType file number to generate code for it:")
	var selectedFile int
	fmt.Scan(&selectedFile)

	fmt.Println("Selected file:", "C:\\imgui.tech\\"+projectFiles[selectedFile])

	byteValue, err := os.ReadFile("C:\\imgui.tech\\" + projectFiles[selectedFile])
	if err != nil {
		log.Fatal(err)
	}

	var projectData internal.Styles
	json.Unmarshal(byteValue, &projectData)

	err = os.WriteFile("generated.hpp", []byte(internal.GenerateFile(projectData)), 0777)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("Done. Created \"generated.hpp\" file. Press any key to exit.")
	fmt.Scanln()
}
