CFLAGS= -shared -fPIC -std=c++11

INCLUDE=-I. -I /data1/apache2/htdocs/LuaJIT/src/
# static
LDFLAGS=-L../lib -L/data1/apache2/htdocs/LuaJIT/src/ -lluajit -Wl,-rpath,../lib:/data1/apache2/htdocs/LuaJIT/src/

SRC=$(wildcard *.cpp)
OBJS=$(subst .cpp,.o,${SRC})

TARGET=motan.so

CC=g++

${TARGET}: ${OBJS}
	$(CC) -o $@ ${OBJS} ${CFLAGS} ${INCLUDE}  ${LDFLAGS}

${OBJS}:%.o:%.cpp
	$(CC) -o $@ -c $< ${CFLAGS} ${INCLUDE}

.PHONY: clean
clean:
	-rm -rf lib ${OBJS} ${TARGET} *.dSYM a.out
