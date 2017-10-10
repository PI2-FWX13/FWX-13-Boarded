default: motor_controll

controle_motor:
	gcc motor_controll.c read_gcode.h -o motor_controll -lm

clean:
	rm -f *.o
	rm -f motor_controll

run: motor_controll
	./motor_controll
