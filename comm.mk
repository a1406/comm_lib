INCLUDES = -I../thirdlib/log4c-1.2.1/src  -I../thirdlib/libevent-2.0.21-stable/include/  -I../thirdlib/libevent-2.0.21-stable/ -I./include  -I../comm_include  -I../thirdlib/protobuf-c-0.15/ -I../comm_lib/include/ -I../proto/
LIBPATH = -L../thirdlib/libevent-2.0.21-stable/.libs/ -L../thirdlib/log4c-1.2.1/src/log4c/.libs 
MYSQL_CFLAGS = -I/usr/include/mysql -DBIG_JOINS=1  -fno-strict-aliasing -g
