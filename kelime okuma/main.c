#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

typedef struct list
{
    char *kelime;
    int toplam;
    struct list *sonraki;
} liste;

liste *ilk = NULL, *son = NULL;
liste *yeni,*gecici, *gecici2;

liste *iter, *temp;
liste *son, *q;

int sayac=1;
int say=1;
int k=0;

void ekle(char *veri)
{

    yeni = (liste *) malloc(sizeof (liste));
    yeni->kelime = veri;
    yeni->sonraki = NULL;

    if (ilk == NULL)   //ilk dugumde eleman var mi
    {
        ilk = yeni;
        son = ilk;
        son->sonraki;

    }
    else
    {
        son->sonraki = yeni;
        son = son->sonraki;

    }

}
/*
void listele()
{

    if (ilk == NULL)
    {
        printf("Liste Bos\n");
    }


    else
    {
        int i=0;
        gecici = ilk; //ilk degeri kaybetmemek icin gecici kullanildi
        while (gecici != NULL)
        {
            printf("%d. kelime: %s\n",i+1, gecici->kelime);
            gecici = gecici->sonraki;
            i++;

        }
    }

} */

void listele2(liste * ana)
{
    if (ana == NULL)
    {
        printf("Liste Bos\n");
    }
    else
    {
        int i=0;
        gecici2 = ana; //ilk degeri kaybetmemek icin gecici kullanildi

        while (gecici2 != NULL)
        {


            printf("%d. kelime: %s - adet: %d\n",i+1, gecici2->kelime, gecici2->toplam);
            gecici2 = gecici2->sonraki;
            i++;

        }
    }
    printf("\n");

}

void degerara_ekle()
{
    printf("-------------------------------------------------------------------------\n");
    char *aranan;
    aranan=malloc(sizeof(char)*500);

    char *key;
    key=malloc(sizeof(char)*500);

    char *tutucu;
    tutucu=malloc(sizeof(char)*500);

    son=NULL;

    int control;
    iter=ilk;
    int s=0;
    int adet_tut=0;

    while(iter!=NULL || s==-1) //s==-1 durumu, son kelimenin istisnai durumunda gerceklesir, istisnada iter=null durumdadir
    {
        //iter null oldugundan, iter->kelime tanimi da null olacaktir
        //son kez sayac=0 olmadan once son kelimeyi ve degerini tutmustuk bu yuzden o degerler kullanilir
        if(s==-1) //istisna durum
        {
            aranan=tutucu;

        }
        else
        {
            aranan=iter->kelime;
        }

        temp=ilk;
        while(temp!=NULL || s==-1) //i=-1 istisna durum
        {
            key=temp->kelime;
            control=strcmp(key,aranan);
            if(control==0)
            {
                if(sayac==0) //yeni kelimeye gecildiyse bu if'e gir ama önceki kelimeyi ekle
                {
                    liste_hazirla(tutucu,adet_tut);
                    adet_tut=0;
                    sayac++;

                    if(s==-1)
                    {
                        s=2;
                    }
                }

                else if(adet_tut!=0)
                {
                    liste * once=NULL;
                    liste * sonra=NULL;
                    q=iter;
                    while(q->sonraki->kelime!=key)  //aradaysa kelimeedden onceki dugumu bul
                    {

                        q=q->sonraki; //silinecek dugumden onceki dugum
                    }
                    once=q;
                    sonra=q->sonraki->sonraki;
                    //printf("Silinen deger: %s\n",q->sonraki->kelime);
                    free(q->sonraki);
                    once->sonraki=sonra;

                }
                tutucu=key; //yeni kelimeye geçmeden onceki kelimeyi tut
                adet_tut++; //yeni kelimeden önceki kelimenin adedini tut
                sayac++; //yeni kelimeye gecilip gecilmedigini kontrol etmeye yarar
            }
            temp=temp->sonraki; //aranan kelimeyi tum metinle karsilastirmak icin siradaki karsilastirma kelimesine gec

        }
        sayac=0;
        iter=iter->sonraki;
        //aranan son kelimede bir istisna oldu, aranan kelime yazdýrýlýyor ancak üst satirda tanýmlanan iter=null oluyor
        //bu istisnayi gidermek için döngünün +1 defa (son kelime icin) calismasý gerekiyor

        if(iter==NULL)
        {
            s=-1;
        }
    }
}

void liste_hazirla(char * ekle, int tane)
{
    int adet_cmp;
    liste *iter2;
    int ilkiTut, sonuTut;
    liste * sonDugum;


    if(son==NULL) //ilk elemani ekle
    {
        son=(liste *)malloc(sizeof(liste));
        son->kelime=ekle;
        son->toplam=tane;
        son->sonraki=NULL;

    }

    else
    {
        ilkiTut=son->toplam;
        k++;
        iter2=son;
        printf("Eklenecek kelimenin tane: %d , eklenecek: %s , ilk kelimenin adedi: %d \n",tane,ekle,ilkiTut);

        if(tane>ilkiTut || tane==ilkiTut)
        {

            printf("Basa ekle calisacak.\n");
            basa_ekle(ekle,tane); //en bastaki kelime degerine gore
            k++;
        }

        else  //tane<ilkiTut iken
        {
            if(k<2)
            {
                //printf("Sona ekle calisti.\n");
                sona_ekle(ekle,tane);
            }

            else
            {
                while (iter2->sonraki->sonraki!=NULL)  //iter2->sonraki->sonraki== NULL ise, x1 x2 x3 x4 x5, x4u tutar //x4'un sonrasý= x5, sonrasý= null //bana x5 lazim // bu da iter2->sonraki eder
                {
                    iter2=iter2->sonraki; //x4'e esit

                }

                sonDugum=iter2->sonraki; //x5'e esit
                sonuTut=sonDugum->toplam;
                if(tane<sonuTut || tane==sonuTut)   //gelen deger en sondakinden de kucukse en sona ekleriz
                {

                    sona_ekle(ekle,tane);
                    //printf("sona ekle calisacak\n");
                    k++;
                }
                else
                {
                    //printf("Araya ekle calisacak\n");
                    araya_ekle(ekle,tane);
                    k++;

                }

            }


        }

    }
    listele2(son);
}
void sona_ekle(char * eklenecek, int adet)
{
    liste * temp2=(liste*)malloc(sizeof(liste)); //eklenecek kutu icin gecici yer
    temp2->kelime=eklenecek;
    temp2->toplam=adet;
    temp2->sonraki=NULL;

    q=son;
    while(q->sonraki!=NULL)
    {
        q=q->sonraki; //son dugumu bulur
    }

    q->sonraki=temp2;

}

void araya_ekle(char * eklenecek,int adet)
{
    liste * temp2=(liste *)malloc(sizeof(liste)); //eklenecek kutu icin gecici yer
    temp2->kelime=eklenecek;
    temp2->toplam=adet;

    liste * iter3;
    iter3=son;

    while(iter3->sonraki->toplam > adet && iter3->sonraki!=NULL)
    {
        iter3=iter3->sonraki;

    }

    temp2->sonraki=iter3->sonraki;
    iter3->sonraki= temp2;

}

void basa_ekle(char * eklenecek, int adet)
{
    liste * temp2=(liste *) malloc(sizeof(liste));
    temp2->kelime=eklenecek;
    temp2->toplam=adet;
    temp2->sonraki=son;
    son=temp2;
}

void kelimeAyir(char *metin)
{
    char *kelime = NULL;
    kelime = strtok (metin," ");
    while (kelime != NULL)
    {
        ekle(kelime);
        kelime = strtok (NULL, " ");
    }
}

int main()
{
    setlocale(LC_ALL,"Turkish");
    FILE *fp = fopen("Deneme2.txt","r");
    char metin[1000];
    while (fgets( metin, sizeof(metin), fp ))
        kelimeAyir(metin);

    //listele();
    fclose(fp);
    degerara_ekle();


    return 0;
}
