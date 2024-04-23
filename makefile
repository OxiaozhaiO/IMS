target=main.o 
object=ims
CC=g++
$(object):$(target)
	$(CC) -o $(object) $(target)
%.o:%.cpp
	$(CC) -c $^ 

.PHONY clean:
	rm $(target) $(object)
