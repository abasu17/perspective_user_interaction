OUTPUT = main
LIBS_OPENCV = `pkg-config --libs opencv`

all : $(OUTPUT)

$(OUTPUT) : main.cpp
	g++ -ggdb -o $@ main.cpp $(LIBS_OPENCV) -lX11 -lXtst -lXext -Wunused-variable

clean :
	rm -v $(OUTPUT)
