#include <stdio.h>
#include <printf.h>
#include <stdlib.h>


 typedef unsigned int uint;
uint borrar_bits(uint x, uint pat, int len) {
    uint aux=x; //varibale para ir haciendo las comparasiones sin perder el valor de x
    uint mask = (uint) ~((-1) << len);//mascara que contiene 1's en las cifras menos sognificativas
    int contador=0; //variable que va contando los saltos para poder tener bien la mascara a la hora de eliminar bits
    for (int iter = 0; iter < 32 - len; iter++) {
        if ((aux & mask)==pat) {
            uint maxaux= (uint) ~((-1) << len);//mascara auxiliar para operar
            maxaux = (maxaux<< contador);
            maxaux = ~ maxaux; //de esta forma donde este el patron habran puros 0's, de tal forma que al aplicar el and esos bits se pierdan
            x = maxaux & x;
            aux >>= len;
            contador+=len;


        }else{
            aux >>= 1;
            contador+=1;
        }
    }

    return x;
}

   //implementacion de parte a)

char *reemplazo(char *s, char c, char *pal){
        char *string= s; //variable para calcular largo de s
        char *recorrido=s; // variable para recorrer s
        char *vpal= pal; //variable para obtener el largo de pal
        int largopal=0;
        int largo=0; // largo total para usar malloc
        while(*vpal != '\0'){//obtencion de largo de vpal
            vpal++;
            largopal++;
        }
        while(*string != '\0') {//obtencion de largo total para pedir memoria
            if(*string == c){
                largo+= largopal;
                string++;

            }else{
                largo++;
                string++;
            }
        }
        char *respuesta = (char*) malloc(largo);
        char *prespuesta = respuesta;
        //int countMalloc=0;

        while (*recorrido!='\0'){
            if(*recorrido==c){
                char *aux= pal;
                while(*aux!= '\0') {
                    *prespuesta=*aux;
                    prespuesta++;
                    aux++;
                }
                recorrido++;
            }
            else{
                *prespuesta=*recorrido;
                prespuesta++;
                recorrido++;
            }
        }
    return respuesta;


} //implementacion de reemplazo


void reemplazar(char *s, char c, char *pal){
	
    char *recstringC= s;//variable para recorrer string original y poder contar
    char *recstring= s;//variable para recorrer string original
    char *recresultado= s; // variable que apunta al string final
    int largototal=0; 
    int largoString=0;
    char *ppal=pal; //puntero que apunta hacia el patron que se desea reemplazar
    int largopal=0;
    while (*ppal!='\0'){//esto calcula el largo de la varible que se desea reemplazar
        largopal++;
        ppal++;
    }
    while(*recstringC!= '\0'){
        if(*recstringC==c){
            largototal+=largopal;
            recstringC++;
            largoString++;

        }else {
            largototal++;
            recstringC++;
            largoString++;
        }
    }
    if (largopal>0) {
    	if(largopal==1){
        int i=0;
        while(i<largoString){
            if(*recstring==c){
                *recresultado=*pal;
                recstring++;
                recresultado++;
                i++;
            }else{
                *recresultado=*recstring;
                recstring++;
                recresultado++;
                i++;
            }
        }           
        }else{
        recresultado+=largototal-1;
        recstring+=largoString-1;
        for (int i = 0; i < largoString-1; ++i){
            if(*recstring==c){
                char *pointerPal= pal;//puntero hacia pal
                pointerPal+=largopal-1;
                int contadorSaltosPal=0;
                while(contadorSaltosPal<largopal){
                   *recresultado= *pointerPal;
                    contadorSaltosPal++;
                    recresultado--;
                    pointerPal--;
                }
                recstring--;
            }else{
            	//char *temp=recstring;
            	if(&recresultado!=&recstring){
            		*recresultado=*recstring;
            		recresultado--;
            		recstring--;
            	}else{
            		recresultado--;
            		recstring--;

            	}
                        
            }
        }
        recresultado+=largototal;
        *recresultado='\0';
             } 
    } else{
    	while(*recstring!='\0'){
    	if (c==*recstring){
    		recstring++;
    	}else{
    		*recresultado=*recstring;
    		recstring++;
    		recresultado++;
    	}
        }
        *recresultado='\0';
    }

}


