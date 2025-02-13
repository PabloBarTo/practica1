#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

struct state{
  int fil; 
  int col;
  Orientacion brujula;
};

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
      current_state.fil = 99;
      current_state.col = 99;
      current_state.brujula = norte;
      last_action = actIDLE;
      girar_derecha = false;
      bien_situado = false;
      bikini = false;
      zapatillas = false;
      contador = 0;
      contador3 = 0;
      contador8 = 0;
      contador4 = 0;
      contador15 = 0;
      contador9 = 0;
      cant_bateria = 5000;
      cargado = false;
      casillas_avanzadas = 0;
      avanzadas_actual = 0;
      salir_zona_izquierda = 0;
      salir_zona_derecha = 0;
      contador_dig10 = 0;
      contador_dig9 = 0;
      contador_dig11 = 0;
      contador_dig12 = 0;

    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st, vector<vector<unsigned char>> &matriz);
    void rellenarPrecipicios(vector<vector<unsigned char>> &matriz);

  private:
  // Declarar aquí las variables de estado
    state current_state;
    Action last_action;
    bool girar_derecha;
    bool bien_situado;
    bool bikini;
    bool zapatillas;
    int contador;
    int contador3;
    int contador8;
    int contador4;
    int contador15;
    int contador9;
    int cant_bateria;
    bool cargado;
    int casillas_avanzadas;
    int avanzadas_actual;
    int salir_zona_izquierda;
    int salir_zona_derecha;
    int contador_dig10;
    int contador_dig9;
    int contador_dig11;
    int contador_dig12;
};
#endif
