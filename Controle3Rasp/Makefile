default: controle_motor

controle_motor:
	gcc -c *.c
	gcc *.o -o teste_timers -lm -lrt

clean:
	rm -f *.o
	rm -f teste_timers

run: 
	./teste_timers
