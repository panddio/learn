objects = mytest testlib #定义一个变量,名为:objects，值为：mytest testlib
.PHONY:all #标记 all 为“伪目标”，这里 all 是第一个目标，也是这个Makefile终极目标
all:$(objects) #展开，相当于：all:mytest testlib

mytest:mytest.c mylib.c #目标：依赖
#这里省略了目标生成的规则，由make程序自动推导
testlib:mytest.c libtestlib.a  #目标：依赖
    #创建目标的规则，必须以Tab键开始
	gcc -o testlib mytest.c libtestlib.a

.PHONY:lib
lib:libtestlib.a libtestlib.so # 执行“make lib”命令将生成静态库和动态库

libtestlib.a:mylib.o
	ar rc -o libtestlib.a mylib.o

    #去掉注释，在编译完成时把静态库复制到/usr/lib目录
	#sudo cp libtestlib.a /usr/lib
libtestlib.so:mylib.c
	gcc -shared mylib.c -o libtestlib.so
	#sudo cp libtestlib.so /usr/lib
mylib.o:mylib.c
	gcc -o mylib.o -c mylib.c

.PHONY:clean #clean 为“伪目标” 用于清除make过程生成的文件
clean:
#rm 命令前面加 '-' ，表示忽视这么命令执行过程的错误
	-rm *.o *.a *.so $(objects)

