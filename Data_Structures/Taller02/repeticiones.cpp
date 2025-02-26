#include <bits/stdc++.h>
#define ll long long
using namespace std;
/**
 * Creacion de la clase palabra con sus metodos y atributos
 */
class Palabra{
    private:
        string palabra;
        ll n_linea;
    public:
    /**
     * Getters y setters
     */
        void fijarPalabra(string n_palabra){
            palabra = n_palabra;
        }

        void fijarNumLinea(ll n_num){
            n_linea = n_num;
        }

        string obtenerPalabra(){
            return palabra;
        }

        ll obtenerNumLinea(){
            return n_linea;
        }
};
/**
 * Creacion de la clase palabra con sus metodos y atributos
 */
class ArchivoTexto{
    private:

        vector<vector<Palabra>> lineasTexto;

    public:
        /**
         * Getter y setter
         */
        void fijarListaLineas(vector<vector<Palabra>> n_lista){
            lineasTexto = n_lista;
        }

        vector<vector<Palabra>> obtenerListaLineas(){
            return lineasTexto;
        }
        /**
         * Retorna el numero de lineas del archivo de texto
         */
        ll obtenerNumLineas(){
            return lineasTexto.size();
        }
        /**
         * Agrega un vector de palabras que contiene las palabras de una linea en especifico
         */
        void agregarListaPals(vector<Palabra> n_lista){
            lineasTexto.push_back(n_lista);
        }
        /**
         * Algoritmo de busqueda para poder encontrar si la subcadena
         * se encuentra al inicio de una palabra
         */
        void buscarPrincipio(Palabra subcadena){
            string subcadena_extraida = subcadena.obtenerPalabra();
            vector<Palabra> comienzan;
            for(auto l : lineasTexto){
                for(auto p : l){
                    string palabra_extraida = p.obtenerPalabra();
                    if(palabra_extraida.size()<subcadena_extraida.size()) continue;
                    bool flag = true;
                    for(int i = 0; i<subcadena_extraida.size(); i++){
                        if(palabra_extraida[i] != subcadena_extraida[i]) flag = false;
                    }
                    if(flag){
                        comienzan.push_back(p);
                    }
                }
            }
            cout<<"\nHay "<<comienzan.size()<<" palabras que comienzan con: "<<subcadena_extraida<<"\n";
            for(auto p : comienzan){
                cout<<"Linea "<<p.obtenerNumLinea()<<": "<<p.obtenerPalabra()<<"\n";
            }
        }
        /**
         * Algoritmo que busca si la subcadena y la subcadena invertida existen
         * dentro de otra palabra
         */
        void buscarContienen(Palabra subcadena){
            string subcadena_extraida = subcadena.obtenerPalabra();
            string subcadena_reversa = subcadena_extraida;
			reverse(subcadena_reversa.begin(),subcadena_reversa.end());
            vector<Palabra> contienen,contienen_invertida;
            for(auto l : lineasTexto){
                for(auto p : l){
                    string palabra_extraida = p.obtenerPalabra();
                    if(palabra_extraida.find(subcadena_extraida) != string::npos){
                        contienen.push_back(p);
                    }
                    if(palabra_extraida.find(subcadena_reversa) != string::npos){
                        contienen_invertida.push_back(p);
                    }
                }
            }
            cout<<"\nHay "<<contienen.size()<<" palabras que contienen: "<<subcadena_extraida<<"\n";
            for(auto p : contienen){
                cout<<"Linea "<<p.obtenerNumLinea()<<": "<<p.obtenerPalabra()<<"\n";
            }
            cout<<"\nHay "<<contienen_invertida.size()<<" palabras que contienen: "<<subcadena_reversa<<"\n";
            for(auto p : contienen_invertida){
                cout<<"Linea "<<p.obtenerNumLinea()<<": "<<p.obtenerPalabra()<<"\n";
            }
        }

};

int main(int argc, char *argv[]){
    if(argc != 2){
        cout<<"El uso correcto del comando es\nPara linux: ./repeticiones [nombreDelArchivo.txt]\nPara Windows: repeticiones.exe [nombreDelArchivo.txt]\n";
        return -1;
    }else{
        vector<Palabra> lectura_palabra;
        fstream archivo;
        Palabra palabra;
        ArchivoTexto archivoTexto;
        archivo.open(argv[1]);
        string numero_lineas_texto,substring,linea;
        //Obtiene la linea del archivo que contiene el numero de lineas
        getline(archivo,numero_lineas_texto);
        ll numero_lineas = atoll(numero_lineas_texto.c_str());
        //Obtiene el substring a buscar
        getline(archivo,substring);
        ll lin = 0;
        //Mientras hayan lineas sin ser procesadas
        while(getline(archivo,linea)){
            string linea_auxiliar;
            vector<string> linea_desglosada;
            lectura_palabra.resize(0);
            lin++;
            stringstream ss(linea);
            //desglosa una de las lineas en palabras unicas y se añaden a un vector
            while(ss >> linea_auxiliar){
                palabra.fijarNumLinea(lin);
                palabra.fijarPalabra(linea_auxiliar);
                lectura_palabra.push_back(palabra);
            }
            //Se añaden todas las palabras a la clase  archivo de texto
            archivoTexto.agregarListaPals(lectura_palabra);
        }
        //Se cierra el archivo de texto
        archivo.close();
        //Se fija el substring
        palabra.fijarPalabra(substring);
        //Se ejecutan las busquedas
        archivoTexto.buscarPrincipio(palabra);
        archivoTexto.buscarContienen(palabra);
    }
}
