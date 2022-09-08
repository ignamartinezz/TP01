#include <iostream>
#include <fstream>


using namespace std;

const int clientes{8};
const int tipoprod{5};

/*
Emita un listado donde para cada cliente liste los tipos de producto tal que la cantidad total de
kilos transportados es mayor a 13000.
2. Para el cliente con mayor cantidad tipos de productos que hayan superado 13000 kg en el punto
anterior, emita un listado con nombre de tipo de producto y total de kilómetros recorridos,
ordenado por total de kilómetros en forma ascendente.
Nota: No alterar el vector de nombres.
3. Del listado anterior, tome el tipo de producto con mayor cantidad de kilómetros recorridos e
informe cuantas entregas se hicieron para ese tipo de producto (sin importar para que cliente).
*/
int contar_mayor(int contadorpesados[clientes]){
    int max=0,temp=0;
    for (int i = 0; i < clientes; i++){
        if (contadorpesados[i]>max){
            max=contadorpesados[i];
            temp=i;
        }
    }
    return temp;
}

int contar_mayor_float(float vector[tipoprod]){
    float max=0;
    int temp=0;
    for (int i = 0; i < tipoprod; i++){
        if (vector[i]>max){
            max=vector[i];
            temp=i;
        }
    }
    return temp;
}

void bubblesort_print(float v[], int dim, string productos[tipoprod]){
    int temp, i, j;
    string temp2;
    for ( i = 0; i < dim-1; i++){
        for ( j = 0; j < dim-i-1; j++){
            if (v[j]>v[j+1]){
                temp=v[j];
                temp2=productos[j];
                productos[j]=productos[j+1];
                productos[j+1]=temp2;        
                v[j]=v[j+1];
                v[j+1]=temp;
            
            }
        }
    }
    //los printeo
    for (int i = 0; i < dim; i++){
        cout<<"Producto: "<<productos[i]<<" = " <<v[i]<<", "<<endl;
    }
    

}


int main(void){
	float pesotot[clientes][tipoprod] {}; //matriz para la sumatoria de pesos
	float kmtotal[clientes][tipoprod] {}; //matriz para la sumatoria de kilometros
    int viajes[clientes][tipoprod] {}; //matriz para el conteo de viajes
	int contadorpesados[clientes]{}; //mayores a 13000kg
    int contadorkilometros[tipoprod]{}; //kilometros por producto

    int debug=1;

    string nombres[clientes]{};
    string productos[tipoprod]{};
    
	ifstream arch;
	arch.open("Datos.txt");
	if (!arch) {
		cout << "No se puedo abrir el archivo de datos" << endl;
		return 1;
	}
    int uclient, uprod;
	float peso, dist;
	while (arch >> uclient >> uprod >> peso >> dist) {
		pesotot[uclient][uprod] += peso;
		kmtotal[uclient][uprod]+=dist;
		viajes[uclient][uprod] ++;
        contadorkilometros[uprod]+= dist;
    }
    arch.close();
    arch.open("Nombres.txt");
    if (!arch){
        cout << "Error al tratar de abrir" << endl;
    }
    for (int i = 0; i < clientes && arch >> nombres[i]; ++i);
	for (int i = 0; i < tipoprod && arch >> productos[i]; ++i);
	
    arch.close();
    for (int i = 0; i < clientes; ++i)
		cout << nombres[i] << endl;

    //Punto 1
    cout << "Listado de productos por cliente con transporte mayor a 13000kg: \n" << endl;
    for (int i = 0; i < clientes; i++){
        cout << "Cliente: " << nombres[i] << "\n" << endl;
        for (int j = 0; j < tipoprod; j++){
            if (pesotot[i][j] > 13000){
                cout << "Producto: " << productos[j] << "\n" << endl;
                contadorpesados[i]++;
            }
        }
    }
    //Punto 2
    int mayorcliente=contar_mayor(contadorpesados);
    cout<<"\nEl cliente con mayor cantidad de productos arriba de 13000kg es: "<< nombres[mayorcliente]<<endl;
    bubblesort_print(kmtotal[mayorcliente], tipoprod, productos);// hay que pasarle la lista de kilometros del mayorcliente

    //punto 3
    int mayorkm=contar_mayor_float(kmtotal[mayorcliente]);
    int contadormax=0;

    for (int i = 0; i < clientes; i++){
        contadormax+=viajes[i][mayorkm];
    }
    cout << "\nPunto 3\nProducto con mayorkm recorridos: " << productos[mayorkm] << " Entregas: " << contadormax<< endl;
                
    


    return 0;
}