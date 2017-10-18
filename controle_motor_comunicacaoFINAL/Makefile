default: controle_motor

controle_motor:
	gcc -c *.c
	gcc *.o -o motor_controll -lm -lwiringPi

clean:
	rm -f *.o
	rm -f motor_controll

run: motor_controll
	./motor_controll
