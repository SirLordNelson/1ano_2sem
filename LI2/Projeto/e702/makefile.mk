CFLAGS=-Wall -Wextra -pedantic -O2
OBJS=$(patsubst %c, %o, $(wildcard *.c))

# deck: deck.o main.o
# 	$(CC) $(CFLAGS) -o $@ $^

# Procura funções demasiado complexas 
complexidade:
	@echo Only printing when Modified McCabe Cyclomatic Complexity is above 5
	@echo | pmccabe -v
	@pmccabe *.c| sort -nr | awk '{if($$1>5)print}'

# Procura problemas no código 
check:
	cppcheck --enable=all --suppress=missingIncludeSystem .

# Esta parte foi gerada usando o comando gcc -MM *.c
main.o: main.c deck.h

codigo.zip: $(wildcard *.h) $(wildcard *.c)
	zip -9r $@ $^
  
clean:
	rm $(OBJS) a.out deck