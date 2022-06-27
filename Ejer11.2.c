/*Se dispone de un archivo con las ventas del mes de cada una de las sucursales de una empresa (VENTAS.DAT El archivo se
encuentra ordenado por sucursal y contiene la siguiente estructura:

 •  Sucursal (15 caracteres máximo)     //ORDENADO
 •  Código de producto (entero)
 •  Cantidad (entero)

Por otro lado se dispone de un archivo de los productos (PRODUCTOS.dat que vende la empresa y el estado del stock al mes
pasado con la siguiente estructura:

 •  Código de producto (entero)
 •  Descripción (20 caracteres máximo)
 •  Precio (float)
 •  Stock (entero)
 •  Punto de pedido (entero)
 •  Cantidad para pedido (entero)

No se sabe la cantidad exacta de productos pero sí se sabe que no hay más de 200. Se desea:

 a.  Mostrar el total vendido en cada sucursal.
 b.  Mostrar la recaudación total de la empresa en el mes.
 c.  Determinar la sucursal que vendió mayor cantidad de productos.
 d.  Actualizar el archivo de productos con el nuevo stock.
 e.  Realizar un archivo llamado pedidos.dat que incluya aquellos productos que deben solicitarse (código y cantidad) de
aquellos productos que al finalizar de procesar las ventas del mes queden con stock menor al punto de pedido.*/
//INCLUDE////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
//ESTRUCTURAS////////////////////
typedef struct {
				char suc[16];
				int codProd;
				int cant;
				}T_Vta;

typedef struct {
				int codProd;
				char descrip[21];
				float precio;
				int stock;
				int puntoPedido;
				int cantPedido;
				}T_Prod;

typedef struct {
				int codProd;
				int cantidadPedido;
				}T_Faltantes;
//FUNCtion
int CargaArch(T_Prod, int);
void ProcesarYGrabarArch(T_Prod, int);
int Busqueda(T_Prod, int, int);
//MAIN
int main()
{
	T_Prod VProd[200];
    int cant;
	cant=CargaArch(VProd, 200);
	ProcesarYGrabarArch(VProd, cant);
    printf("\n\n\n");

	return 0;
}
//FUNCIONES//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CargaArch(T_Prod V[], int ce)
{
    FILE *pf;
	T_Prod aux;
	int i=0;
	pf= fopen("PRODUCTOS.dat", "rb");
	if(pf==NULL)
	{
		printf("\nNo se pudo abrir el archivo");
		exit(1);
	}
	fread(&aux, sizeof(T_Prod), 1, pf);
    while(!feof (pf) && i<ce)
    {
        V[i]=aux;
        i++;
        fread(&aux, sizeof(T_Prod), 1, pf);
    }
    fclose(pf);
    return i;
}
void ProcesarYGrabarArch(T_Prod V[], int ce)
{
	FILE *sf, *tf;
	T_Vta aux;
	T_Faltantes faltantes;
	char sucAnt[16];
	int pos, reacT, totvtaS;
	sf=fopen("VENTAS.dat", "rb");
	if(sf==NULL)
	{
		printf("\nNo se pudo abrir el archivo");
		exit(1);
	}
	tf=fopen("PEDIDOS.dat", "wb");
	if(tf==NULL)
	{
		printf("\nNo se pudo abrir el archivo");
		exit(1);
	}
	fread(&aux, sizeof(T_Vta), 1, sf);
	while(!feof(sf))
	{
		reacT=0;
		pos=Busqueda(V[], ce, aux.codProd);
		if(pos!=-1)
		{
			totvtaS=0;
			strcpy(sucAnt, aux.suc);

		}
		fread(&aux, sizeof(T_Vta), 1, sf);
	}
	fclose(sf);
    fclose(tf);
}
//BUSQUEDA
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
