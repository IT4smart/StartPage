#gcc andi.c $(pkg-config --cflags --libs gtk+-3.0) -o andi.out -Wall -Wextra
#this works gcc  andi.c layout.c -o configuration `(pkg-config --cflags --libs gtk+-3.0)` -lX11
CC      	= 	gcc 
#CFLAGS  	= 	`(shell pkg-config --cflags --libs gtk+-3.0)` -lX11
GTK3	  	= 	`(pkg-config --cflags --libs gtk+-3.0)` -lX11
#OFLAGS  	=  	-O2 # O3 ist nicht viel schneller und prod. Compilerwarnungen # ohne Optimierungen: -O0
WFLAGS  	= 	-Wall -Wextra 

#LDFLAGS 	=  	-lm -lstdc++ ${HOME}/trng-4.15/src/.libs/libtrng4.a

TARGETDIR 	= RUN

TARGET		= startpage

OBJ 		=	\
			main.o			\
			layout.o		\
			init.o			\


config:  $(OBJ)
	$(CC) $(WFLAGS) $(OBJ) -o $(TARGET) $(GTK3)

%.o: %.c
	$(CC) $(WFLAGS) -c $<	-o	$@ 		$(GTK3)

clean:
	rm $(OBJ) $(TARGET) -rf
	
