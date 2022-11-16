/*
Se dispone de un archivo con las ventas del mes de cada una de las sucursales de una empresa. El archivo
se encuentra ordenado por sucursal y contiene la siguiente estructura:
• Sucursal (15 caracteres máximo)
• Código de producto (entero)
• Cantidad (entero)
Por otro lado, se dispone de un archivo de los productos que vende la empresa y el estado del stock al mes
pasado con la siguiente estructura:
• Código de producto (entero)
• Descripción (20 caracteres máximo)
• Precio (float)
• Stock (entero)
• Punto de pedido (entero)
• Cantidad para pedido (entero)
No se sabe la cantidad exacta de productos, pero sí se sabe que no hay más de 200. Se desea:
a. Mostrar el importe total vendido en cada sucursal.
b. Mostrar la recaudación total de la empresa en el mes.
c. Determinar la sucursal que vendió mayor cantidad de productos.
d. Actualizar el archivo de productos con el nuevo stock.
e. Realizar un archivo llamado pedidos.dat que incluya aquellos productos que deben solicitarse
(código y cantidad) de aquellos productos que al finalizar de procesar las ventas del mesa queden
con stock menor al punto de pedido.
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{char sucu[16];
               int cod;
               int cant;
               }Tventa;

typedef struct{int cod;
               char des[21];
               float precio;
               int stock;
               int pedido;
               int cantpedi;
               }Tprod;

typedef struct{int cod;
               int cant;
               }Tfaltante;


int LeerArch(Tventa[],int);
void ProcesarArch(Tventa[],int);
int Busqueda(Tventa[],int,int);
void Actualizar(Tventa[],int);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Tventa venta[200]={0};
    Tprod aux;
    int cant;

    cant = LeerArch(venta,200);
    ProcesarArch(venta,cant);
    Actualizar(venta,cant);



return 0;
}
int LeerArch (Tventa v[],int ce)
{
    int i=0;
    Tventa aux;
    FILE *ven;
    ven=fopen("VENTAS.DAT","rb");
    if(ven==NULL)
    {
        printf("Error al leer ventas");
        exit(1);
    }
    fread(&aux,sizeof(Tventa),1,ven);
    while(!feof(ven) && i<ce)
    {
        v[i]=aux;
        i++;
        fread(&aux,sizeof(Tventa),1,ven);
    }
    fclose(ven);
    return i;
}
void ProcesarArch(Tventa v[],int ce)
{
    Tventa aux;
    Tprod prod;
    Tfaltante aux2;
    char sucAnt[16],sucMax[16];
    int pos,recauT,totalM,max,band=0;
    FILE *produc,*pedidos;
    produc=fopen("PRODUCTOS.DAT","rb");
    if(produc==NULL)
    {
        printf("Error al leer productos");
        exit(1);
    }
    pedidos=fopen("FALTANTES.DAT","wb");
    if(pedidos==NULL)
    {
        printf("Error al grabar faltantes");
        exit(1);
    }
    fread(&aux,sizeof(Tprod),1,produc);
    while(!feof(produc))
    {
        recauT=0;
        pos=Busqueda(v,ce,aux.cod);
        if(pos!=-1)
        {
            totalM=0;
            strcpy(sucAnt,aux.sucu);
            while(strcmpi(sucAnt,aux.sucu)!=0 && !feof(produc))
            {
                totalM+=aux.cant;
                recauT+=aux.cant;
                prod.stock-=aux.cant;

            }
            printf("\nLa sucursal %s vendio %d productos",sucAnt,totalM); ////PUNTO A)///
        }
        if(band==0 || max<totalM)
        {
            band=1;
            max=totalM;
            strcpy(sucMax,sucAnt);
        }
        fread(&aux,sizeof(Tprod),1,produc);
        printf("\nEl total vendido por la empresa en el mes es %d",recauT);////PUNTO B)///
        printf("\nLa sucursal %s fue la que vendio la mayor cantidad de productos, siendo %d",sucMax,max);////PUNTO C)///
        if(prod.stock<prod.pedido)
        {
            aux2.cod==aux.cod;
            aux2.cant+=aux.cant;
            fwrite(&aux2,sizeof(Tfaltante),1,pedidos);
        }
    }
    fclose(produc);
    fclose(pedidos);


}
int Busqueda(Tventa v[],int ce,int x)
{
    int i=0;
    while(v[i].cod!=x && i<ce)
    {
        i++;
    }
    if(i==ce)
    {
        return -1;
    }
    else
    {
        return i;
    }
}
void Actualizar(Tventa v[],int ce)
{
    int i;
    FILE *venta;
    venta=fopen("VENTAS.DAT","wb");
    if(venta==NULL)
    {
        printf("Error al actualizar");
        exit(1);
    }
    for(i=0;i<ce;i++)
    {
        fwrite(&v[i],sizeof(Tventa),1,venta);
    }
    fclose(venta);
}
