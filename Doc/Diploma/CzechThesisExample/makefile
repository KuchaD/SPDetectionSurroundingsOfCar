ifeq ($(OS),Windows_NT)
	Detected_OS := Windows
else
	Detected_OS := Linux
endif

ifeq ($(Detected_OS),Windows)
	DelCmd = del /s /q
	RmdirCmd = rmdir /s /q
	CopyCmd = copy
else
	DelCmd = rm -rf
	RmdirCmd = rm -rf
	CopyCmd = cp
endif

LaTeX := pdflatex

cz:
	$(LaTeX) main.tex
	$(LaTeX) main.tex
	$(LaTeX) main.tex
