build: clean
	g++ ./src/camel2snake.cc -o ./bin/camel2snake -O3
	g++ ./src/snake2camel.cc -o ./bin/snake2camel -O3

clean: ./bin
	rm -rf ./bin/*

./bin:
	mkdir ./bin

install: build
	sudo cp ./bin/camel2snake /bin
	sudo cp ./bin/snake2camel /bin
	make clean

uninstall:
	sudo rm -f /bin/camel2snake
	sudo rm -f /bin/snake2camel

