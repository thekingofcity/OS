cc = gcc
promEarth = earth
promMars = mars
deps = sbuf.h
obj = earth.o mars.o sbuf.o
objEarth = earth.o sbuf.o
objMars = mars.o sbuf.o

prom: $(obj)
	$(cc) -o $(promEarth) $(objEarth) -lpthread
	$(cc) -o $(promMars) $(objMars) -lpthread
	rm -rf $(obj)

%.o: %.c $(deps)
	$(cc) -c $< -o $@

clean:
	rm -rf $(objEarth) $(promEarth)
	rm -rf $(objMars) $(promMars)
