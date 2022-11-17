package internal

type Layer struct {
	Color      []float64 `json:"Color"`
	FontFile   string    `json:"FontFile"`
	FontName   string    `json:"FontName"`
	FontSize   float64   `json:"FontSize"`
	ImagePath  string    `json:"ImagePath"`
	ImageName  string    `json:"ImageName"`
	Pos        []float64 `json:"Pos"`
	RoundFlags int       `json:"RoundFlags"`
	Rounding   float64   `json:"Rounding"`
	Size       []float64 `json:"Size"`
	Target     int       `json:"Target"`
	TextAlignX int       `json:"TextAlignX"`
	TextAlignY int       `json:"TextAlignY"`
	TextSize   []float64 `json:"TextSize"`
	TextValue  string    `json:"TextValue"`
	Thickness  float64   `json:"Thickness"`
	Radius     float64   `json:"Radius"`
	Type       int       `json:"Type"`
}

type Checkbox struct {
	TotalSize []float64 `json:"TotalSize"`
	FrameSize []float64 `json:"FrameSize"`
	FramePos  []float64 `json:"FramePos"`
}

type Font struct {
	Name string
	Size int
}

type Image struct {
	Path string
	Name string
}

type Styles struct {
	Data struct {
		Window struct {
			Alpha            float64   `json:"Alpha"`
			ChildBorderSize  float64   `json:"ChildBorderSize"`
			ChildRounding    float64   `json:"ChildRounding"`
			DisabledAlpha    float64   `json:"DisabledAlpha"`
			FrameBorderSize  float64   `json:"FrameBorderSize"`
			FramePadding     []float64 `json:"FramePadding"`
			FrameRounding    float64   `json:"FrameRounding"`
			IndentSpacing    float64   `json:"IndentSpacing"`
			ItemInnerSpacing []float64 `json:"ItemInnerSpacing"`
			ItemSpacing      []float64 `json:"ItemSpacing"`
			PopupBorderSize  float64   `json:"PopupBorderSize"`
			PopupRounding    float64   `json:"PopupRounding"`
			Size             []float64 `json:"Size"`
			WindowBorderSize float64   `json:"WindowBorderSize"`
			WindowSize       []float64 `json:"WindowSize"`
			WindowMinSize    []float64 `json:"WindowMinSize"`
			WindowPadding    []float64 `json:"WindowPadding"`
			WindowRounding   float64   `json:"WindowRounding"`
			WindowTitleAlign []float64 `json:"WindowTitleAlign"`
		} `json:"Window"`

		WindowLayers []Layer `json:"Layers"`
	} `json:"Data"`
}
