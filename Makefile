.PHONY: all clean

all: modbus publish subscribe

clean:
	rm -rf \
		modbus \
		publish \
		subscribe

modbus: modbus.c
	gcc -o $@ modbus.c `pkg-config --libs libmxidaf`

publish: publish.c
	gcc -o $@ publish.c `pkg-config --libs libmxidaf`

subscribe: subscribe.c
	gcc -o $@ subscribe.c `pkg-config --libs libmxidaf`
