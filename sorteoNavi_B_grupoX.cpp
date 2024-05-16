//============================================================================
// Name        : sorteoNavi_B_grupoX.cpp
// Author      : Esther del Pico Garcia
// Version     : v1.0
// Copyright   : libre
// Description : Laboratorio C++ informática.
//============================================================================

#include <iostream>								/*Librerias utilizadas durante la ejecucion del programa*/
#include <fstream>
#include <string>
#include <tuple>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
using namespace std;
void lectura(int (&PREMIOS)[1127][2]){			/*Funcion que lee la base de datos con los decimos premiados*/
	int i=0;									/*Declaracion de variables locales*/
	string textoFila;
	ifstream archivo;							/*Flujo de apertura del fichero*/
	archivo.open("R:\\Documents\\Cppws\\sorteoNavi_B_grupoX\\Debug\\sorteoNavidadB.dat",ios::in); /*Apertura del fichero con los premios*/
	if (archivo.fail()){						/*Finalizacion de la ejecucion si no se abre el fichero*/
		cout<<"No se ha podido abrir la base de datos con los premios. Intentelo de nuevo.";
		exit(1);
		}
	while (!archivo.eof()){						/*Lectura del fichero y almacenamiento de los valores en la matriz PREMIOS*/
		getline(archivo,textoFila);
		if (textoFila != ""){
			PREMIOS[i][0] = stoi(textoFila.substr(3, 5));						/*Almacena los numeros premiados en la columna 1*/
			PREMIOS[i][1] = stoi(textoFila.substr(11, textoFila.length()-11));	/*Almacena los premios de cada numero en la columna 2*/
			i++;
		}
	}
}
tuple<int,float> pedirNumero(float &apuesta, int &decimo){	/*Funcion que devuelve a su salida el numero jugado y la apuesta*/
	int i=0,num=0;								/*Declaracion de variables locales*/
	while (num==0){								/*Bucle para solicitar el numero al usuario*/
		cout<<"Por favor, introduzca el numero que desea comprobar"<<endl;
		cin>>decimo;							/*Guarda el numero introducido por el usuario en decimo*/
		if (decimo<0 || decimo>84999){			/*Ejecucion si el numero introducido por el usuario no esta en el rango de los numeros del sorteo*/
				i++;							/*Numero de intentos realizados*/
				cout<<"El numero introducido es erroneo. Numero de intentos restantes: "<<2-i<<endl;	/*Indica por pantalla que el numero es erroneo*/
			}
		else{
			num=1;								/*Si el numero introducido es correcto, modifica el valor de num para que se deje de ejecutar el bucle*/
		}
		if (i>=2){								/*Si se han realizado dos intentos erroneos, se finaliza la ejecucion*/
			cout<<"Se ha superado el numero maximo de intentos"<<endl;
			system("pause");
			exit(1);
		}
	}
	cout<<"Por favor, introduzca el importe jugado"<<endl;	/*Si se ha introducido un numero correcto, se pide al usuario que introduzca la apuesta*/
	cin>>apuesta;											/*Guarda el numero introducido por el usuario en apuesta*/
	return {decimo,apuesta};					/*Al finalizar la funcion, devuelve los valores de decimo y apuesta*/
}
int comprobarPremio(int &decimo,int &dinero, int (&PREMIOS)[1127][2]){	/*Funcvion que comprueba si ha tocado un premio*/
	int i,acierto=0;							/*Declaracion de variables locales*/
	for (i=0;i<1127;i++){						/*Bucle que recorre todas las filas de la matriz donde se han almacenado los premios*/
		if (decimo==PREMIOS[i][0]){				/*Comprueba si el numero del usuario coincide con el de la matriz*/
			dinero=PREMIOS[i][1];				/*Si el numero coincide, guarda el valor de la segunda columna en dicha fila en la variable dinero*/
			acierto=1;							/*Si el numero coincide, asigna a la variable local acierto el valor 1*/
			}
		}
	if (acierto!=1){							/*Si no coincide ningun numero, asigna a la funcion dinero 0*/
		dinero=0;
	}
	return dinero;								/*Al finalizar la ejecucion de la funcion, devuelve el valor de dinero*/
}
int dineroPremio(int &dinero, float &apuesta){	/*Funcion que calcula el premio conseguido*/
	dinero=dinero*apuesta;						/*Asigna a la variable dinero el valor de la apuesta multiplicado por el dinero del premio*/
	return (dinero);							/*Al finalizar la ejecucion de la funcion, devuelve el valor de dinero*/
}
void mostrarPremio(int &decimo, int &dinero){	/*Funcion que muestra por pantalla el premio conseguido*/
	int i;
	if (dinero>0){								/*Si el usuario ha conseguido algun premio, se muestra por pantalla*/
		cout<<"*********************************************************************"<<endl;
		cout<<"**************** SU NUMERO JUGADO: "<<decimo<<" ****************************"<<endl;
		cout<<"****************  HA SIDO PREMIADO CON   ****************************"<<endl;
		cout<<"****************       "<<dinero<<" EUROS        ****************************"<<endl;
		cout<<"*********************************************************************"<<endl;
	}
	else{										/*Si el usuario no ha conseguido algun premio, se muestra por pantalla*/
		cout<<"*********************************************************************"<<endl;
		cout<<"****************  SU NUMERO JUGADO: "<<decimo<<" ****************************"<<endl;
		cout<<"****************    NO HA SIDO PREMIADO   ****************************"<<endl;
		cout<<"****************    QUE TENGA BUEN DIA    ****************************"<<endl;
		cout<<"*********************************************************************"<<endl;
	}
	for (i=0;i<10;i++){							/*Se reproduce un pitido*/
		Beep(1568, 200);
	}
}
int main() {
	int PREMIOS[1127][2],decimo=0,dinero=0;		/*Declaracion de variables*/
	float apuesta=0.0;
	system("color 1F");							/*Modificacion de los colores de la interfaz, fondo azul y letras blancas*/
	lectura(PREMIOS);							/*Llamada a la funcion que lee la BBDD con los premios*/
	tie(decimo,dinero) = pedirNumero(apuesta,decimo); /*Llamada a la funcion que pide el numero al usuario*/
	comprobarPremio(decimo,dinero,PREMIOS);		/*Llamada a la funcion que comprueba el premio*/
	dineroPremio(dinero,apuesta);				/*Llamada a la funcion que calcula el premio*/
	mostrarPremio(decimo,dinero);				/*Llamada a la funcion que muestra por pantalla el resultado*/
	system("pause");							/*Pausa de sistema para la correcta visualizacion*/
	return 0;
}
