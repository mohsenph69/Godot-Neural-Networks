
CC=g++
cflags=

export CPLUS_INCLUDE_PATH=./include:.



NNdir= ./core
NNsrc=$(wildcard $(NNdir)/*.cpp)
NNobj=$(patsubst $(NNdir)/%.cpp, $(NNdir)/%.o , $(NNsrc) )

GDdir= ./GD
GDsrc=$(wildcard $(GDdir)/*.cpp)
GDobj=$(patsubst $(GDdir)/%.cpp, $(GDdir)/%.o , $(GDsrc) )

GAdir= ./GA
GAsrc=$(wildcard $(GAdir)/*.cpp)
GAobj=$(patsubst $(GAdir)/%.cpp, $(GAdir)/%.o , $(GAsrc) )


allObj:=$(NNobj) main.o $(GDobj) $(GAsrc)
allsrc:=$(NNsrc) main.cpp $(GDsrc) $(GAsrc)


neural: $(allObj)
	$(CC) -g $(allObj) -o neural

$(NNdir)/%o: $(NNdir)/%cpp
	$(CC) -g -c -o $@ $<


$(GDdir)/%o: $(GDdir)/%cpp
	$(CC) -g -c -o $@ $<

$(GAdir)/%o: $(GAdir)/%cpp
	$(CC) -g -c -o $@ $<

main.o: main.cpp
	$(CC) -g -c -o $@ $<


xor_GD: $(NNobj) $(GDobj) example/xor_GD.o
	$(CC) -g $(NNobj) $(GDobj) example/xor_GD.o -o example/xor_GD 

example/xor_GD.o: example/xor_GD.cpp
	$(CC) -g -c -o $@ $<


xor_GA: $(NNobj) $(GAobj) example/xor_GA.o
	$(CC) -g $(NNobj) $(GAobj) example/xor_GA.o -o example/xor_GA

example/xor_GA.o: example/xor_GA.cpp
	$(CC) -g -c -o $@ $<

line_GA: $(NNobj) $(GAobj) example/line_GA.o
	$(CC) -g $(NNobj) $(GAobj) example/line_GA.o -o example/line_GA

example/line_GA.o: example/line_GA.cpp
	$(CC) -g -c -o $@ $<

run: xor_GA
	@./example/xor_GA

clean:
	rm -f ./core/*.o
	rm -f main.o
	rm -f example/*.o
	rm -f GA/*.o
	rm -f GD/*.o
	rm neural