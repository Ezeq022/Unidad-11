#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//ESTRUCTURAS/////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {
				int codTour;
				char nomTour[51];
				int cantVta;
				float precio;
				}T_Tour;

typedef struct {
				char agencia[26];
				int codTour;
				int trimestre;
				int cantVta;
				}T_Ventas;

typedef struct {
                char Agencia[26];
				int cantVta;
				float imptotal;
				float prom;
				}T_Agencia;
//FUNCIONES///////////////////////////////////////////////////////////////////////////////////////////////////////
int CargaArch(T_Tour[], int);
void ProcesarArch(T_Tour[], int);
void GrabarArch(T_Tour[], int);
int Busqueda(T_Tour[], int, int);
//MAIN////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	T_Tour VTour[150];
    int cant;
	cant=CargaArch(VTour, 200);
	ProcesarArch(VTour, cant);
	GrabarArch(VTour, cant);
    printf("\n\n\n");

	return 0;
}
//FUNCIONES////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CargaArch(T_Tour V[], int ce)
{
    FILE *pf;
	T_Tour aux;
	int i=0;
	pf= fopen("TOURS.dat", "rb");
	if(pf==NULL)
	{
		printf("\nNo se pudo abrir el archivo");
		exit(1);
	}
	fread(&aux, sizeof(T_Tour), 1, pf);
    while(!feof (pf) && i<ce)
    {
        V[i]=aux; // PASAR A MEMORIA
        i++; //CONTADOR DE PRODUCTOS
        fread(&aux, sizeof(T_Tour), 1, pf);
    }
    fclose(pf);
    return i;
}
void ProcesarArch(T_Tour V[], int ce)
{
	FILE *pf, *sf;
	T_Ventas aux, error;
	T_Agencia auxag;
	char;
	int pos, band=0;
	float;
	//Apertura archivos
	pf=fopen("VENTAS2.dat", "rb"); //LECTURA
	if(pf==NULL)
	{
		printf("\nNo se pudo abrir el archivo");
		exit(1);
	}
	sf=fopen("ERROR.dat", "wb"); //ESCRITURA
	if(sf==NULL)
	{
		printf("\nNo se pudo abrir el archivo");
		exit(1);
	}
	sf=fopen("ERROR.dat", "wb"); //ESCRITURA
	if(sf==NULL)
	{
		printf("\nNo se pudo abrir el archivo");
		exit(1);
	}
	//Proceso
	fread(&aux, sizeof(T_Vta), 1, pf);
	while(!feof(pf)) //WHILE MAYOR
	{
        totVtaSuc=0;
        cantProd=0;
        strcpy(sucAnt, aux.suc);
        while(strcmpi(sucAnt, aux.suc)==0 && !feof(pf)) //CORTE DE CONTROL
        {
            pos=Busqueda(V, ce, aux.codProd); //BUSQUEDA PRODUCTO
            if(pos!=1)
            {
                if(V[pos].stock>V[pos].puntoPedido)
                {
                    totVtaSuc+=aux.cant*V[pos].precio;
                    cantProd+=aux.cant;
                    V[pos].stock-=aux.cant;
                }
                else
                {
                    faltantes.cantidadPedido+=aux.cant;
                    faltantes.codProd=aux.codProd;
                    fwrite(&faltantes, sizeof(T_Faltantes), 1, sf); //ESCRIBIR PEDIDOS.DAT
                }
            }
            fread(&aux, sizeof(T_Vta), 1, pf);
        }
		recauT+=totVtaSuc; //ACUMULADOR DE RECAUDACION TOTAL DE LA EMPRESA
		if(band==0||cantProd>maxCantProd) //SUCURSAL QUE VENDIO MAS PRODUCTOS
        {
            band=1;
            maxCantProd=cantProd;
            strcpy(maxSuc, sucAnt);
        }
        printf("\nEl importe total vendido en la sucursal %s fue de %.2f", sucAnt, totVtaSuc);
	}
	printf("\nRecaudacion total de la empresa en el mes es %.2f", recauT);
	printf("\nLa sucursal que vendio la mayor cantidad de productos fue: %s", maxSuc);
	fclose(pf);
    fclose(sf);
}
void GrabarArch(T_Prod V[], int ce)
{
    int i;
    FILE *pf;
    pf=fopen("PRODUCTOS.dat", "wb");
    if(pf==NULL)
    {
        printf("\nNo abrio el archivo...");
        exit(1);
    }
    for(i=0; i<ce; i++)
        fwrite(&V[i], sizeof(T_Prod), 1, pf);
    fclose(pf);
}
//BUSQUEDA//////////////////////////////////////////////////////////////////////////////////////////////////////
int Busqueda(T_Prod V[], int ce, int x)
{
	int i=0;
	while(V[i].codProd!=x && i<ce)
        i++;
    if(i==ce)
        return -1;
    else
        return i;
}
