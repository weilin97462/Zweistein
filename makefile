all:
	gcc main.c src/build_pdf_cdf.c src/zweistein.c -O2 -o Zweistein