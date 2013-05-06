
TARGET := rt
PDF := Bhardwa_Mantovani-Retiming.pdf
SRCS := $(TARGET).tex

.SUFFIXES: .aux .bbl .blg .dvi .log
$(TARGET):
	latex $(SRCS)
	bibtex $(TARGET)
	latex $(SRCS)
	latex $(SRCS)
	dvipdf $(TARGET).dvi
	mv $(TARGET).pdf $(PDF)
	rm -f *.bbl *.blg *.dvi *.log *.aux

.PHONY: clean

clean:
	rm -f $(PDF)
