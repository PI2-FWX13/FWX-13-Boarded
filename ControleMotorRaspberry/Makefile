default: controle_motor

controle_motor:
	gcc -c *.c
	gcc *.o -o raspControle -lm -lwiringPi

clean:
	rm -f *.o
	rm -f raspControle

run: motor_controll
	./raspControle
