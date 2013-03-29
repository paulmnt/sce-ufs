
TARGET := ufs
PDF := Bhardwa_Mantovani-Function_similarity.pdf
SRCS := ufs.tex

.SUFFIXES: .aux .bbl .blg .dvi .log
$(TARGET):
	latex $(SRCS)
	latex $(SRCS)
	dvipdf $(TARGET).dvi
	mv $(TARGET).pdf $(PDF)
	rm -f *.bbl *.blg *.dvi *.log *.aux

.PHONY: clean

clean:
	rm -f $(PDF)
