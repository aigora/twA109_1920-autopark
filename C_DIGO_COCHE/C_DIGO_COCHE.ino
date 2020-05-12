// definición de los motres
#include<AFMotor.h> 
AF_DCMotor Motor_del_izq(4); 
AF_DCMotor Motor_del_der(3); 
AF_DCMotor Motor_tras_izq(1); 
AF_DCMotor Motor_tras_der(2); 
#include<Ultrasonic.h> 
Ultrasonic ultrasonic_tras(40,41),ultrasonic_tras_izq(38,39),ultrasonic_del_izq(36,37),ultrasonic_del(34,35); 
//  definicion sensores ultrasonido 
#define izquierda 0 //comando direccion izquierda
#define derecha 1 //comando direccion derecha 
#define avanzar 2 //comoando hacia delante 
#define retroceder 3 //comando marcha atras 
#define limite_minimo 15 //ancho del coche (cm) 
#define limite_minimo1 28 //largo del coche (cm) 
byte estado_aparcamiento  = 0; //estado de aparcamiento  
int signal_pin = 21; //señal de velocidad 
volatile int val; 
int contador = 0; 
int situacion_actual = 0; 
int situacion_anterior = 0; 
void say(int saydir) 
{ 
for (int i = 0 ;i<= saydir; i+1) 
{ 
val = digitalRead(signal_pin); 
if (val == LOW) { 
  
situacion_actual = 0; 
}
else {  
situacion_actual = 1; 
}  
if(situacion_actual != situacion_anterior) 
{ 
if(situacion_actual == 1) 
{ 
contador = contador + 1; 
Serial.println(contador); 
i = i+1; 
} 
else 
{ 
i = i ; 
} 
situacion_anterior = situacion_actual;  
} 
if (i == saydir) 
{ 
Motor_del_izq.run(RELEASE); 
Motor_del_der.run(RELEASE); 
Motor_tras_izq.run(RELEASE); 
Motor_tras_der.run(RELEASE); 
} 
} 
} 
void motor_pinSetup() 
{ 
Motor_del_izq.run(RELEASE); 
Motor_del_der.run(RELEASE); 
Motor_tras_izq.run(RELEASE); 
Motor_tras_der.run(RELEASE);
} 
// Funciones Movimiento 
void Movimiento_Robot(byte motor, byte spd) 
{ 
if (motor == avanzar) 
{ 
Motor_del_izq.setSpeed(spd); 
Motor_del_der.setSpeed(spd); 
Motor_tras_izq.setSpeed(spd); 
Motor_tras_der.setSpeed(spd); 
Motor_del_izq.run(FORWARD); 
Motor_del_der.run(FORWARD); 
Motor_tras_izq.run(FORWARD); 
Motor_tras_der.run(FORWARD); 
} 
if (motor == retroceder) 
{ 
Motor_del_izq.setSpeed(spd); 
Motor_del_der.setSpeed(spd); 
Motor_tras_izq.setSpeed(spd); 
Motor_tras_der.setSpeed(spd); 
Motor_del_izq.run(BACKWARD); 
Motor_del_der.run(BACKWARD); 
Motor_tras_izq.run(BACKWARD); 
Motor_tras_der.run(BACKWARD); 
} 
if (motor == izquierda) 
{ 
Motor_del_izq.setSpeed(spd); 
Motor_del_der.setSpeed(spd); 
Motor_tras_izq.setSpeed(spd); 
Motor_tras_der.setSpeed(spd); 
Motor_del_izq.run(BACKWARD); 
Motor_del_der.run(FORWARD); 
Motor_tras_izq.run(BACKWARD); 
Motor_tras_der.run(FORWARD); 
} 
if (motor == derecha) 
{ 
Motor_del_izq.setSpeed(spd); 
Motor_del_der.setSpeed(spd); 
Motor_tras_izq.setSpeed(spd); 
Motor_tras_der.setSpeed(spd);  
Motor_del_izq.run(FORWARD); 
Motor_del_der.run(BACKWARD); 
Motor_tras_izq.run(FORWARD); 
Motor_tras_der.run(BACKWARD);  
} 
} 
void Parar_Robot() 
{ 
Motor_del_izq.run(RELEASE); 
Motor_del_der.run(RELEASE); 
Motor_tras_izq.run(RELEASE); 
Motor_tras_der.run(RELEASE);
} 
// Busqueda de aparcamiento 
bool Control_Aparcamiento() 
{ 
long Sensor_del = ultrasonic_del.Ranging(CM); 
long Sensor_der = ultrasonic_del_izq.Ranging(CM); 
long Sensor_tras_der =ultrasonic_tras_izq.Ranging(CM); 
if( (Sensor_der <= limite_minimo)&&(Sensor_tras_der <= limite_minimo)&&(estado_aparcamiento  == 0)) 
{ 
Movimiento_Robot(avanzar, 100); 
estado_aparcamiento  = 1; Serial.println(estado_aparcamiento ); 
} 
if((Sensor_der > limite_minimo)&&(Sensor_der < limite_minimo1)&&(Sensor_tras_der > limite_minimo)&&(Sensor_tras_der < limite_minimo1)&&(estado_aparcamiento  == 1)) 
{ 
Movimiento_Robot(avanzar, 100); 
estado_aparcamiento  = 2;Serial.println(estado_aparcamiento ); 
} 
if((Sensor_der >= limite_minimo1)&&(Sensor_tras_der >= limite_minimo1)&&(estado_aparcamiento  == 1)) 
{ 
/*Decision Aparcamiento En Verical*/  
Parar_Robot() ; 
delay(500); 
estado_aparcamiento  = 10;Serial.println(estado_aparcamiento ); 
}  
if((Sensor_der <= limite_minimo)&&(Sensor_tras_der <= limite_minimo)&&(estado_aparcamiento  == 2)) 
{ 
/* Decision Aparcamiento En Paralelo */
estado_aparcamiento  = 3; Serial.println(estado_aparcamiento ); 
} 
return estado_aparcamiento ; 
} 
void Park_bul() 
{ 
Control_Aparcamiento(); 
if(estado_aparcamiento  == 3 ) 
{ 
Parar_Robot();Serial.println(estado_aparcamiento ); 
delay(400); 
estado_aparcamiento  = 4; 
} 
if(estado_aparcamiento  == 4 ) 
{  
Movimiento_Robot(retroceder,120); 
say(18); 
Parar_Robot();Serial.println(estado_aparcamiento ); 
delay(500); 
Movimiento_Robot(derecha,150); 
say(9); 
Parar_Robot(); 
delay(500); 
estado_aparcamiento  = 5; 
} 
if(estado_aparcamiento  == 5) 
{ 
Movimiento_Robot(retroceder,120); 
long Sensor_tras = ultrasonic_tras.Ranging(CM);Serial.println(Sensor_tras); 
if(Sensor_tras>0 &&Sensor_tras<= 13) 
{ 
Parar_Robot(); 
delay(400); 
estado_aparcamiento  = 6; 
} 
return Sensor_tras; 
} 
if(estado_aparcamiento  == 6) 
{ 
Movimiento_Robot(izquierda,150); 
long Sensor_der = ultrasonic_del_izq.Ranging(CM); Serial.println(Sensor_der); 
long Sensor_tras_der = ultrasonic_tras_izq.Ranging(CM); Serial.println(Sensor_tras_der);  
if(Sensor_der == Sensor_tras_der) 
{ 
Parar_Robot(); 
estado_aparcamiento  = 7; 
} 
return Sensor_der,Sensor_tras_der; 
} 
if(estado_aparcamiento  == 7) 
{ 
long Sensor_del = ultrasonic_del.Ranging(CM); 
if(Sensor_del<=6) 
{ 
Parar_Robot(); 
estado_aparcamiento  = 8; 
} 
else 
{ 
Movimiento_Robot(avanzar,100); 
} 
return Sensor_del; 
} 
if (estado_aparcamiento  ==10) 
{ 
Movimiento_Robot(izquierda,180); 
say(14); 
Parar_Robot(); 
delay(500); 
estado_aparcamiento  = 7; 
} 
} 
void setup() 
{ 
Serial.begin(9600); 
attachInterrupt(5, say, CHANGE); 
pinMode (signal_pin, INPUT) ;  
motor_pinSetup(); 
} 
void loop() 
{ 
Park_bul(); 
} 
