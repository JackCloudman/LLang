Gram=Objects/y.tab.c Objetcs/y.tab.h

all: $(Gram) Objects/lex.yy.c Objects/Object.c Objects/stringObject.c Objects/listObject.c Objects/intObject.c Objects/init.c Objects/abstract.c
	@gcc -I include -o Lala Objects/y.tab.c Objects/lex.yy.c Objects/Object.c Objects/stringObject.c Objects/listObject.c Objects/intObject.c Objects/init.c Objects/abstract.c
	@echo Compiled

$(Gram): Objects/LLang.y
	@yacc -d Objects/LLang.y
	@mv *.tab.* Objects/

Objects/lex.yy.c: Objects/LLang.l
	@flex Objects/LLang.l
	@mv lex.yy.c Objects/

clean:
	@rm -f Objects/lex.yy.c Objects/*.tab.* Lala
	@echo Clean
