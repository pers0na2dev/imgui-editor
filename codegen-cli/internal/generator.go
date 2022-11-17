package internal

import (
	"fmt"
	"path/filepath"
	"strconv"
	"strings"
)

func GenerateFile(style Styles) (result string) {
	result += fmt.Sprintf("#pragma once\n\n")
	result += fmt.Sprintf("/*\n")
	result += fmt.Sprintf("* Design created and exported using imgui.tech\n")
	result += fmt.Sprintf("* https://imgui.tech | https://t.me/imguitech\n")
	result += fmt.Sprintf("*/\n\n")
	result += fmt.Sprintf("#define IMGUI_DEFINE_MATH_OPERATORS\n\n")
	result += fmt.Sprintf("#include <imgui.h>\n")
	result += fmt.Sprintf("#include <imgui_internal.h>\n\n")
	result += fmt.Sprintf("namespace ImGuiTech {\n")
	result += GenerateFontsList(style)
	result += GenerateImageList(style)
	result += CreateStyles(style)
	result += fmt.Sprintf("\t__forceinline void Render() {\n")
	result += fmt.Sprintf("\t\tImGui::Begin(\"Window\");\n")
	result += fmt.Sprintf("\t\t{\n")
	result += fmt.Sprintf("\t\t\tImGui::SetWindowSize({%0.2ff, %0.2ff});\n\n", style.Data.Window.WindowSize[0], style.Data.Window.WindowSize[1])
	result += fmt.Sprintf("\t\t\tauto pos = ImGui::GetWindowPos();\n")
	result += fmt.Sprintf("\t\t\tauto draw = ImGui::GetWindowDrawList();\n\n")
	for _, a := range style.Data.WindowLayers {
		result += GenerateLayer("\t\t\tdraw", a, 0, "pos")
	}
	result += fmt.Sprintf("\t\t}\n")
	result += fmt.Sprintf("\t\tImGui::End();\n")
	result += fmt.Sprintf("\t}\n")
	result += fmt.Sprintf("}\n")

	return
}

func CreateStyles(style Styles) (result string) {
	result += fmt.Sprintf("\t__forceinline void InitStyles(LPDIRECT3DDEVICE9 device) {\n")
	result += fmt.Sprintf("\t\tImGui::GetStyle().Alpha = %0.2ff;\n", style.Data.Window.Alpha)
	result += fmt.Sprintf("\t\tImGui::GetStyle().DisabledAlpha = %0.2ff;\n", style.Data.Window.DisabledAlpha)
	result += fmt.Sprintf("\t\tImGui::GetStyle().ChildBorderSize = %0.2ff;\n", style.Data.Window.ChildBorderSize)
	result += fmt.Sprintf("\t\tImGui::GetStyle().ChildRounding = %0.2ff;\n", style.Data.Window.ChildRounding)
	result += fmt.Sprintf("\t\tImGui::GetStyle().FrameBorderSize = %0.2ff;\n", style.Data.Window.FrameBorderSize)
	result += fmt.Sprintf("\t\tImGui::GetStyle().FrameRounding = %0.2ff;\n", style.Data.Window.FrameRounding)
	result += fmt.Sprintf("\t\tImGui::GetStyle().IndentSpacing = %0.2ff;\n", style.Data.Window.IndentSpacing)
	result += fmt.Sprintf("\t\tImGui::GetStyle().PopupBorderSize = %0.2ff;\n", style.Data.Window.PopupBorderSize)
	result += fmt.Sprintf("\t\tImGui::GetStyle().Data.WindowBorderSize = %0.2ff;\n", style.Data.Window.WindowBorderSize)
	result += fmt.Sprintf("\t\tImGui::GetStyle().PopupRounding = %0.2ff;\n", style.Data.Window.PopupRounding)
	result += fmt.Sprintf("\t\tImGui::GetStyle().Data.WindowRounding = %0.2ff;\n", style.Data.Window.WindowRounding)
	result += fmt.Sprintf("\t\tImGui::GetStyle().FramePadding = {%0.2ff, %0.2ff};\n", style.Data.Window.FramePadding[0], style.Data.Window.FramePadding[1])
	result += fmt.Sprintf("\t\tImGui::GetStyle().ItemInnerSpacing = {%0.2ff, %0.2ff};\n", style.Data.Window.ItemInnerSpacing[0], style.Data.Window.ItemInnerSpacing[1])
	result += fmt.Sprintf("\t\tImGui::GetStyle().ItemSpacing = {%0.2ff, %0.2ff};\n", style.Data.Window.ItemSpacing[0], style.Data.Window.ItemSpacing[1])
	result += fmt.Sprintf("\t\tImGui::GetStyle().Data.WindowMinSize = {%0.2ff, %0.2ff};\n", style.Data.Window.WindowMinSize[0], style.Data.Window.WindowMinSize[1])
	result += fmt.Sprintf("\t\tImGui::GetStyle().WindowPadding = {%0.2ff, %0.2ff};\n", style.Data.Window.WindowPadding[0], style.Data.Window.WindowPadding[1])
	result += fmt.Sprintf("\t\tImGui::GetStyle().WindowTitleAlign = {%0.2ff, %0.2ff};\n\n", style.Data.Window.WindowTitleAlign[0], style.Data.Window.WindowTitleAlign[1])
	result += GenerateFontsInit(style)
	result += fmt.Sprintf("\n\n")
	result += GenerateImages(style)
	result += fmt.Sprintf("\t}\n\n")

	return
}

func GenerateLayer(draw string, layer Layer, target int, pos string) (result string) {
	if layer.Target == target {
		if layer.Type == 0 {
			result += fmt.Sprintf("%s->AddLine(%s + ImVec2{%0.f.f, %0.f.f}, %s + ImVec2{%0.f.f, %0.f.f}, ImColor(%0.2ff, %0.2ff, %0.2ff, %0.2ff), %0.f.f);\n",
				draw, pos, layer.Pos[0], layer.Pos[1], pos, layer.Pos[0]+layer.Size[0], layer.Pos[1]+layer.Size[1],
				layer.Color[0], layer.Color[1], layer.Color[2], layer.Color[3], layer.Thickness)
		}
		if layer.Type == 1 {
			result += fmt.Sprintf("%s->AddRect(%s + ImVec2{%0.f.f, %0.f.f}, %s + ImVec2{%0.f.f, %0.f.f}, ImColor(%0.2ff, %0.2ff, %0.2ff, %0.2ff), %0.f.f, %d, %0.f.f);\n",
				draw, pos, layer.Pos[0], layer.Pos[1], pos, layer.Pos[0]+layer.Size[0], layer.Pos[1]+layer.Size[1],
				layer.Color[0], layer.Color[1], layer.Color[2], layer.Color[3], layer.Rounding, layer.RoundFlags, layer.Thickness)
		}
		if layer.Type == 2 {
			result += fmt.Sprintf("%s->AddRectFilled(%s + ImVec2{%0.f.f, %0.f.f}, %s + ImVec2{%0.f.f, %0.f.f}, ImColor(%0.2ff, %0.2ff, %0.2ff, %0.2ff), %0.f.f, %d);\n",
				draw, pos, layer.Pos[0], layer.Pos[1], pos, layer.Pos[0]+layer.Size[0], layer.Pos[1]+layer.Size[1],
				layer.Color[0], layer.Color[1], layer.Color[2], layer.Color[3], layer.Rounding, layer.RoundFlags)
		}
		if layer.Type == 3 {
			result += fmt.Sprintf("%s->AddImage(Images::%s, %s + ImVec2{%0.f.f, %0.f.f}, %s + ImVec2{%0.f.f, %0.f.f});\n",
				draw, removeExtension(layer.ImageName), pos, layer.Pos[0], layer.Pos[1], pos, layer.Pos[0]+layer.Size[0], layer.Pos[1]+layer.Size[1])
		}
		if layer.Type == 4 {
			xAppend := 0.0
			yAppend := 0.0

			if layer.TextAlignX == 0 {
				xAppend = 0
			} else if layer.TextAlignX == 1 {
				xAppend = layer.Size[0]/2 - layer.TextSize[0]/2
			} else if layer.TextAlignX == 2 {
				xAppend = layer.Size[0] - layer.TextSize[0]
			}

			if layer.TextAlignY == 0 {
				yAppend = 0
			} else if layer.TextAlignY == 1 {
				yAppend = layer.Size[1]/2 - layer.TextSize[1]/2
			} else if layer.TextAlignY == 2 {
				yAppend = layer.Size[1] - layer.TextSize[1]
			}

			fontName := removeExtension(layer.FontFile) + strconv.Itoa(int(layer.FontSize))
			result += fmt.Sprintf("%s->AddText(Fonts::%s, %0.f, %s + ImVec2{%0.f.f, %0.f.f}, ImColor(%0.2ff, %0.2ff, %0.2ff, %0.2ff), \"%s\");\n",
				draw, fontName, layer.FontSize, pos, layer.Pos[0]+xAppend, layer.Pos[1]+yAppend,
				layer.Color[0], layer.Color[1], layer.Color[2], layer.Color[3],
				layer.TextValue)
		}
		if layer.Type == 5 {
			result += fmt.Sprintf("%s->AddCircle(%s + ImVec2{%0.f.f, %0.f.f}, %0.f, ImColor(%0.2ff, %0.2ff, %0.2ff, %0.2ff), 32.f);\n",
				draw, pos, layer.Pos[0]+(layer.Size[0]/2), layer.Pos[1]+(layer.Size[1]/2), layer.Radius,
				layer.Color[0], layer.Color[1], layer.Color[2], layer.Color[3])
		}
		if layer.Type == 6 {
			result += fmt.Sprintf("%s->AddCircleFilled(%s + ImVec2{%0.f.f, %0.f.f}, %0.f, ImColor(%0.2ff, %0.2ff, %0.2ff, %0.2ff), 32.f);\n",
				draw, pos, layer.Pos[0]+(layer.Size[0]/2), layer.Pos[1]+(layer.Size[1]/2), layer.Radius,
				layer.Color[0], layer.Color[1], layer.Color[2], layer.Color[3])
		}
	}

	return
}

func removeExtension(fpath string) string {
	ext := filepath.Ext(fpath)
	return strings.TrimSuffix(fpath, ext)
}

func GenerateFontsList(styles Styles) (result string) {
	var Fonts = make(map[string]Font)

	for _, a := range styles.Data.WindowLayers {
		if a.Type == 4 {
			fontName := removeExtension(a.FontFile) + strconv.Itoa(int(a.FontSize))
			Fonts[fontName] = Font{a.FontFile, int(a.FontSize)}
		}
	}

	result += fmt.Sprintf("\tnamespace Fonts {\n")
	for key, a := range Fonts {
		result += fmt.Sprintf("\t\tinline ImFont* %s = nullptr; // %s\n", key, a.Name)
	}
	result += fmt.Sprintf("\t}\n\n")
	return
}

func GenerateFontsInit(styles Styles) (result string) {
	var Fonts = make(map[string]Font)

	for _, a := range styles.Data.WindowLayers {
		if a.Type == 4 {
			fontName := removeExtension(a.FontFile) + strconv.Itoa(int(a.FontSize))
			Fonts[fontName] = Font{a.FontFile, int(a.FontSize)}
		}
	}

	for key, a := range Fonts {
		result += fmt.Sprintf("\t\tFonts::%s = ImGui::GetIO().Fonts->AddFontFromFileTTF(\"C:\\\\Windows\\\\Fonts\\\\%s\", %d.f);\n", key, a.Name, a.Size)
	}

	return
}

func GenerateImageList(styles Styles) (result string) {
	var Images = make(map[string]Image)

	for _, a := range styles.Data.WindowLayers {
		if a.Type == 3 {
			fontName := removeExtension(a.ImageName)
			Images[fontName] = Image{a.ImagePath, a.ImageName}
		}
	}

	result += fmt.Sprintf("\tnamespace Images {\n")
	for key, a := range Images {
		result += fmt.Sprintf("\t\tinline IDirect3DTexture9* %s = nullptr; // %s\n", key, a.Path)
	}
	result += fmt.Sprintf("\t}\n\n")
	return
}

func GenerateImages(styles Styles) (result string) {
	var Images = make(map[string]Image)

	for _, a := range styles.Data.WindowLayers {
		if a.Type == 3 {
			fontName := removeExtension(a.ImageName)
			Images[fontName] = Image{a.ImagePath, a.ImageName}
		}
	}

	for key, a := range Images {
		result += fmt.Sprintf("\t\tD3DXCreateTextureFromFileA(device, \"%s\", &Images::%s);\n", strings.Replace(a.Path, "\\", "\\\\", -1), key)
	}

	return
}
