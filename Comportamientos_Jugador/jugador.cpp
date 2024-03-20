#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

Action ComportamientoJugador::think(Sensores sensores)
{

	Action accion = actIDLE;

	int a;

	casillas_avanzadas = 15;

	if(mapaResultado.size() <= 30){
		casillas_avanzadas = 5;
	}
	else if(mapaResultado.size() > 30 && mapaResultado.size() <= 50){
		casillas_avanzadas = 15;
	}
	else if(mapaResultado.size() > 50 && mapaResultado.size() <= 75){
		casillas_avanzadas = 20;
	}
	else if(mapaResultado.size() > 75 && mapaResultado.size() <= 100){
		casillas_avanzadas = 25;
	}
	// Mostrar el valor de los sensores
	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC;
	switch (sensores.sentido)
	{
		case norte:	  cout << " Norte\n";	break;
		case noreste: cout << " Noreste\n";	break;
		case este:    cout << " Este\n";	break;
		case sureste: cout << " Sureste\n";	break;
		case sur:     cout << " Sur\n";	break;
		case suroeste:cout << " Suroeste\n";	break;
		case oeste:   cout << " Oeste\n";	break;
		case noroeste:cout << " Noroeste\n";	break;
	}
	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];

	cout << "  Agentes: ";
	for (int i=0; i<sensores.agentes.size(); i++)
		cout << sensores.agentes[i];

	cout << "\nColision: " << sensores.colision;
	cout << "  Reset: " << sensores.reset;
	cout << "  Vida: " << sensores.vida << endl<< endl;

	switch(last_action){
		case actWALK:
			
			switch(current_state.brujula){
				case norte:
					current_state.fil--;
					break;
				case noreste:
					current_state.fil--;
					current_state.col++;
					break;
				case este:
					current_state.col++;
					break;
				case sureste:
					current_state.fil++;
					current_state.col++;
					break;
				case sur:
					current_state.fil++;
					break;
				case suroeste:
					current_state.fil++;
					current_state.col--;
					break;
				case oeste:
					current_state.col--;
					break;
				case noroeste:
					current_state.fil--;
					current_state.col--;
					break;
			}
			break;

		case actRUN:
			
			break;

		case actTURN_SR:
			a = current_state.brujula;
			a = (a + 1) % 8;
			current_state.brujula = static_cast<Orientacion>(a);
			girar_derecha = (rand()%2==0);
			break;
		case actTURN_L:
			a = current_state.brujula;
			a = (a + 6) % 8;
			current_state.brujula = static_cast<Orientacion>(a);
			girar_derecha = (rand()%2==0);
			break;
	}

	if(sensores.terreno[0]=='G' and !bien_situado){
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;
	}

	if(sensores.reset) {
        bien_situado = false;
        bikini = false;
        zapatillas = false;
    }

    if(sensores.colision)
        bien_situado = false;

	if(bien_situado){
		PonerTerrenoEnMatriz(sensores.terreno, current_state, mapaResultado);
	}

	if(sensores.terreno[0]=='K' && !bikini){
		bikini = true;
	}

	if(sensores.terreno[0]=='D' && !zapatillas){
		zapatillas = true;
	}

	if((sensores.bateria >= cant_bateria && sensores.vida >= 900) || (sensores.vida <= 900 && sensores.bateria >= 1500 ))
        cargado = true;
	else
		cargado = false;
	
	if((sensores.terreno[2] == 'X' || sensores.terreno[6]=='X' || sensores.terreno[12] =='X' || sensores.terreno[0] == 'X') && !cargado){
        if(sensores.terreno[0] != 'X' && sensores.terreno[2] != 'M')
            accion = actWALK;
        else
            accion = actIDLE;
	}
	else if(((sensores.terreno[2] == 'G' || sensores.terreno[6] == 'G' || sensores.terreno[12] == 'G' && !bien_situado) ||
            (sensores.terreno[2] == 'K' || sensores.terreno[6] == 'K' || sensores.terreno[12] == 'K' && !bikini) ||
            (sensores.terreno[2] == 'D' || sensores.terreno[6] == 'D' || sensores.terreno[12] == 'D' && !zapatillas))) {
        if(sensores.terreno[2] != 'M')
            accion = actWALK;
        else
            accion = actTURN_L;
	}
 	else if((((sensores.terreno[1] == 'G' && !bien_situado) || sensores.terreno[1] == 'X' || (sensores.terreno[1] == 'K' && !bikini) ||
            (sensores.terreno[1] == 'D' && !zapatillas))) ||
            (((sensores.terreno[5] == 'G' && !bien_situado) || sensores.terreno[5] == 'X' || (sensores.terreno[5] == 'K' && !bikini) ||
            (sensores.terreno[5] == 'D' && !zapatillas)))||
            (((sensores.terreno[11] == 'G' && !bien_situado) || sensores.terreno[11] == 'X' || (sensores.terreno[11] == 'K' && !bikini) ||
            (sensores.terreno[11] == 'D' && !zapatillas)))|| contador > 0) {
        if (contador == 0) {
            accion = actTURN_L;
            contador++;
        } 
		else if (contador == 1) {
            if(sensores.terreno[2] != 'M'){
                accion = actWALK;
                contador++;
            }
			else{
                contador = 0;
            }
        } 
		else if (contador > 1) {
            accion = actTURN_SR;
            if(contador == 3){
				contador = 0;
			}else{
				contador++;
			}
    	}
	}
	else if((((sensores.terreno[3] == 'G' && !bien_situado) || sensores.terreno[3] == 'X' || (sensores.terreno[3] == 'K' && !bikini) ||
               (sensores.terreno[3] == 'D' && !zapatillas))) ||
             (((sensores.terreno[7] == 'G' && !bien_situado) || sensores.terreno[7] == 'X' || (sensores.terreno[7] == 'K' && !bikini) ||
               (sensores.terreno[7] == 'D' && !zapatillas)))||
             (((sensores.terreno[13] == 'G' && !bien_situado) || sensores.terreno[13] == 'X' || (sensores.terreno[13] == 'K' && !bikini) ||
               (sensores.terreno[13] == 'D' && !zapatillas)))|| contador3 > 0){
        if(contador3 >=0 && contador3 < 2){
            accion = actTURN_SR;
            contador3++;
        }else if(contador3 == 2){
            if(sensores.terreno[2] != 'M') {
                accion = actWALK;
                contador3++;
            }else{
                contador8 = 0;
            }
        }else if(contador3 == 3){
            accion = actTURN_L;
            contador3 = 0;
        }
	}
	else if((((sensores.terreno[8] == 'G' && !bien_situado) || sensores.terreno[8] == 'X' || (sensores.terreno[8] == 'K' && !bikini) ||
             (sensores.terreno[8] == 'D' && !zapatillas))) ||
             (((sensores.terreno[14] == 'G' && !bien_situado) || sensores.terreno[14] == 'X' || (sensores.terreno[14] == 'K' && !bikini) ||
             (sensores.terreno[14] == 'D' && !zapatillas)))|| contador8 > 0) {
        if(contador8 >= 0 && contador8 < 2){
            accion = actTURN_SR;
            contador8++;
        }else if (contador8 <= 2){
            if(sensores.terreno[2] != 'M') {
                accion = actWALK;
                contador8++;
            }else{
                contador8 = 0;
            }
        }else{
            accion = actTURN_L;
            contador8 = 0;
        }
    }
	else if((((sensores.terreno[4] == 'G' && !bien_situado) || sensores.terreno[4] == 'X' || (sensores.terreno[4] == 'K' && !bikini) ||
               (sensores.terreno[4] == 'D' && !zapatillas))) ||
             (((sensores.terreno[10] == 'G' && !bien_situado) || sensores.terreno[10] == 'X' || (sensores.terreno[10] == 'K' && !bikini) ||
               (sensores.terreno[10] == 'D' && !zapatillas)))|| contador4 > 0) {
        if(contador4 == 0){
            accion = actTURN_L;
            contador4++;
        }
		else if (contador4 <= 2){
            if(sensores.terreno[2] != 'M') {
                accion = actWALK;
                contador4++;
            }
			else{
                contador4 = 0;
            }
        }
		else if (contador4 > 2){
            accion = actTURN_SR;
			if(contador4 == 4){
				contador4 = 0;
			}
			else{
				contador4++;
			}
        }
    }
	else if((((sensores.terreno[15] == 'G' && !bien_situado) || sensores.terreno[15] == 'X' || (sensores.terreno[15] == 'K' && !bikini) ||
               (sensores.terreno[15] == 'D' && !zapatillas))) || contador15 > 0){
        if(contador15 >= 0 && contador15 < 2){
            accion = actTURN_SR;
            contador15++;
        }else if (contador15 <= 4){
            if(sensores.terreno[2] != 'M') {
                accion = actWALK;
                contador15++;
            }else{
                contador15 = 0;
            }
        }else{
            accion = actTURN_L;
            contador15 = 0;
        }
    }
	else if((((sensores.terreno[9] == 'G' && !bien_situado) || sensores.terreno[9] == 'X' || (sensores.terreno[9] == 'K' && !bikini) ||
               (sensores.terreno[9] == 'D' && !zapatillas))) || contador15 > 0){
        if(contador9 == 0){
            accion = actTURN_L;
            contador9++;
        }else if (contador9 <= 3){
            if(sensores.terreno[2] != 'M') {
                accion = actWALK;
                contador9++;
            }else{
                contador9 = 0;
            }
        }else if(contador9 > 3){
            accion = actTURN_SR;
			if(contador9 == 5){
				contador9 = 0;
			}
			else{
				contador9++;
			}
		}
	
	}  
	else if(avanzadas_actual >= casillas_avanzadas || sensores.terreno[2] == 'P' || sensores.terreno[2] == 'M' || (sensores.terreno[2] == 'A' && !bikini) || (sensores.terreno[2] == 'B' && !zapatillas)){
        avanzadas_actual = 0;
        if(girar_derecha)
            accion = actTURN_SR;
        else
            accion = actTURN_L;
	}
	else if(((sensores.terreno[2] == 'T' || sensores.terreno[2] == 'S' || sensores.terreno[2] == 'G' || sensores.terreno[2] == 'D' || sensores.terreno[2] == 'K' || sensores.terreno[2] == 'X' || (sensores.terreno[2] == 'B' && zapatillas) || (sensores.terreno[2] == 'A' && bikini)))){
		accion = actWALK;
        avanzadas_actual++;
	}

	last_action = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}

void ComportamientoJugador::PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st, vector<vector<unsigned char>> &matriz){
	rellenarPrecipicios(matriz);
	matriz[st.fil][st.col] = terreno[0];
	if(st.brujula == 0){
		matriz[st.fil-1][st.col-1] = terreno[1];
		matriz[st.fil-1][st.col] = terreno[2];
		matriz[st.fil-1][st.col+1] = terreno[3];
		matriz[st.fil-2][st.col-2] = terreno[4];
		matriz[st.fil-2][st.col-1] = terreno[5];
		matriz[st.fil-2][st.col] = terreno[6];
		matriz[st.fil-2][st.col+1] = terreno[7];
		matriz[st.fil-2][st.col+2] = terreno[8];
		matriz[st.fil-3][st.col-3] = terreno[9];
		matriz[st.fil-3][st.col-2] = terreno[10];
		matriz[st.fil-3][st.col-1] = terreno[11];
		matriz[st.fil-3][st.col] = terreno[12];
		matriz[st.fil-3][st.col+1] = terreno[13];
		matriz[st.fil-3][st.col+2] = terreno[14];
		matriz[st.fil-3][st.col+3] = terreno[15];
	}
	else if(st.brujula == 2){
		matriz[st.fil-1][st.col+1] = terreno[1];
		matriz[st.fil][st.col+1] = terreno[2];
		matriz[st.fil+1][st.col+1] = terreno[3];
		matriz[st.fil-2][st.col+2] = terreno[4];
		matriz[st.fil-1][st.col+2] = terreno[5];
		matriz[st.fil][st.col+2] = terreno[6];
		matriz[st.fil+1][st.col+2] = terreno[7];
		matriz[st.fil+2][st.col+2] = terreno[8];
		matriz[st.fil-3][st.col+3] = terreno[9];
		matriz[st.fil-2][st.col+3] = terreno[10];
		matriz[st.fil-1][st.col+3] = terreno[11];
		matriz[st.fil][st.col+3] = terreno[12];
		matriz[st.fil+1][st.col+3] = terreno[13];
		matriz[st.fil+2][st.col+3] = terreno[14];
		matriz[st.fil+3][st.col+3] = terreno[15];
	}
	else if(st.brujula == 4){
		matriz[st.fil+1][st.col+1] = terreno[1];
		matriz[st.fil+1][st.col] = terreno[2];
		matriz[st.fil+1][st.col-1] = terreno[3];
		matriz[st.fil+2][st.col+2] = terreno[4];
		matriz[st.fil+2][st.col+1] = terreno[5];
		matriz[st.fil+2][st.col] = terreno[6];
		matriz[st.fil+2][st.col-1] = terreno[7];
		matriz[st.fil+2][st.col-2] = terreno[8];
		matriz[st.fil+3][st.col+3] = terreno[9];
		matriz[st.fil+3][st.col+2] = terreno[10];
		matriz[st.fil+3][st.col+1] = terreno[11];
		matriz[st.fil+3][st.col] = terreno[12];
		matriz[st.fil+3][st.col-1] = terreno[13];
		matriz[st.fil+3][st.col-2] = terreno[14];
		matriz[st.fil+3][st.col-3] = terreno[15];
	}
	else if(st.brujula == 6){
		matriz[st.fil-1][st.col-1] = terreno[3];
		matriz[st.fil][st.col-1] = terreno[2];
		matriz[st.fil+1][st.col-1] = terreno[1];
		matriz[st.fil-2][st.col-2] = terreno[8];
		matriz[st.fil-1][st.col-2] = terreno[7];
		matriz[st.fil][st.col-2] = terreno[6];
		matriz[st.fil+1][st.col-2] = terreno[5];
		matriz[st.fil+2][st.col-2] = terreno[4];
		matriz[st.fil-3][st.col-3] = terreno[15];
		matriz[st.fil-2][st.col-3] = terreno[14];
		matriz[st.fil-1][st.col-3] = terreno[13];
		matriz[st.fil][st.col-3] = terreno[12];
		matriz[st.fil+1][st.col-3] = terreno[11];
		matriz[st.fil+2][st.col-3] = terreno[10];
		matriz[st.fil+3][st.col-3] = terreno[9];
	}
	else if(st.brujula == 1){
		matriz[st.fil-1][st.col] = terreno[1];
		matriz[st.fil-1][st.col+1] = terreno[2];
		matriz[st.fil][st.col+1] = terreno[3];
		matriz[st.fil-2][st.col] = terreno[4];
		matriz[st.fil-2][st.col+1] = terreno[5];
		matriz[st.fil-2][st.col+2] = terreno[6];
		matriz[st.fil-1][st.col+2] = terreno[7];
		matriz[st.fil][st.col+2] = terreno[8];
		matriz[st.fil-3][st.col] = terreno[9];
		matriz[st.fil-3][st.col+1] = terreno[10];
		matriz[st.fil-3][st.col+2] = terreno[11];
		matriz[st.fil-3][st.col+3] = terreno[12];
		matriz[st.fil-2][st.col+3] = terreno[13];
		matriz[st.fil-1][st.col+3] = terreno[14];
		matriz[st.fil][st.col+3] = terreno[15];
	}
	else if(st.brujula == 3){
		matriz[st.fil][st.col+1] = terreno[1];
		matriz[st.fil+1][st.col+1] = terreno[2];
		matriz[st.fil+1][st.col] = terreno[3];
		matriz[st.fil][st.col+2] = terreno[4];
		matriz[st.fil+1][st.col+2] = terreno[5];
		matriz[st.fil+2][st.col+2] = terreno[6];
		matriz[st.fil+2][st.col+1] = terreno[7];
		matriz[st.fil+2][st.col] = terreno[8];
		matriz[st.fil][st.col+3] = terreno[9];
		matriz[st.fil+1][st.col+3] = terreno[10];
		matriz[st.fil+2][st.col+3] = terreno[11];
		matriz[st.fil+3][st.col+3] = terreno[12];
		matriz[st.fil+3][st.col+2] = terreno[13];
		matriz[st.fil+3][st.col+1] = terreno[14];
		matriz[st.fil+3][st.col] = terreno[15];
	}
	else if(st.brujula == 5){
		matriz[st.fil+1][st.col] = terreno[1];
		matriz[st.fil+1][st.col-1] = terreno[2];
		matriz[st.fil][st.col-1] = terreno[3];
		matriz[st.fil+2][st.col] = terreno[4];
		matriz[st.fil+2][st.col-1] = terreno[5];
		matriz[st.fil+2][st.col-2] = terreno[6];
		matriz[st.fil+1][st.col-2] = terreno[7];
		matriz[st.fil][st.col-2] = terreno[8];
		matriz[st.fil+3][st.col] = terreno[9];
		matriz[st.fil+3][st.col-1] = terreno[10];
		matriz[st.fil+3][st.col-2] = terreno[11];
		matriz[st.fil+3][st.col-3] = terreno[12];
		matriz[st.fil+2][st.col-3] = terreno[13];
		matriz[st.fil+1][st.col-3] = terreno[14];
		matriz[st.fil][st.col-3] = terreno[15];
	}
	else if(st.brujula == 7){
		matriz[st.fil][st.col-1] = terreno[1];
		matriz[st.fil-1][st.col-1] = terreno[2];
		matriz[st.fil-1][st.col] = terreno[3];
		matriz[st.fil][st.col-2] = terreno[4];
		matriz[st.fil-1][st.col-2] = terreno[5];
		matriz[st.fil-2][st.col-2] = terreno[6];
		matriz[st.fil-2][st.col-1] = terreno[7];
		matriz[st.fil-2][st.col] = terreno[8];
		matriz[st.fil][st.col-3] = terreno[9];
		matriz[st.fil-1][st.col-3] = terreno[10];
		matriz[st.fil-2][st.col-3] = terreno[11];
		matriz[st.fil-3][st.col-3] = terreno[12];
		matriz[st.fil-3][st.col-2] = terreno[13];
		matriz[st.fil-3][st.col-1] = terreno[14];
		matriz[st.fil-3][st.col] = terreno[15];
	}
}

void ComportamientoJugador::rellenarPrecipicios(vector<vector<unsigned char>> &matriz){
	int filas = matriz.size();
	int columnas = matriz[0].size();

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < columnas; j++){
			matriz[i][j] = 'P';
		}
	}

	for(int i = filas-3; i < filas; i++){
		for(int j = 0; j < columnas; j++){
			matriz[i][j] = 'P';
		}
	}

	for(int i = 0; i < filas; i++){
		for(int j = 0; j < 3; j++){
			matriz[i][j] = 'P';
		}
	}

	for(int i = 0; i < filas; i++){
		for(int j = columnas-3; j < columnas; j++){
			matriz[i][j] = 'P';
		}
	}
}