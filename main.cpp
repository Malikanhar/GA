#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

struct infotype{
    int x,y;
};

struct Coord{
    infotype info[16];
};

float jarak(int x1, int y1, int x2, int y2)
{
    return sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
}

int main()
{
    Coord C;
    C.info[0].x=82;
    C.info[1].x=96;
    C.info[2].x=50;
    C.info[3].x=49;
    C.info[4].x=13;
    C.info[5].x=29;
    C.info[6].x=58;
    C.info[7].x=84;
    C.info[8].x=14;
    C.info[9].x=2;
    C.info[10].x=3;
    C.info[11].x=5;
    C.info[12].x=98;
    C.info[13].x=84;
    C.info[14].x=61;
    C.info[15].x=1;
    C.info[0].y=76;
    C.info[1].y=44;
    C.info[2].y=5;
    C.info[3].y=8;
    C.info[4].y=7;
    C.info[5].y=89;
    C.info[6].y=30;
    C.info[7].y=39;
    C.info[8].y=24;
    C.info[9].y=39;
    C.info[10].y=82;
    C.info[11].y=10;
    C.info[12].y=52;
    C.info[13].y=25;
    C.info[14].y=59;
    C.info[15].y=65;


    int Node[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    int pCross = 80;
    int pMutasi = 20;

    int nGen = 50;
    int nPop = 100;
    int nKrom = (sizeof(Node)/sizeof(Node[0]))+1;
    int Pop[nPop][nKrom];
    int gab[nPop*2][nKrom];
    float SteadyState[nPop];
    float Cost_min;
    int Generasi;

    // Inisialisasi Populasi
    srand(time(0));
    for (int i=0; i<nPop; i++){
        int N=nKrom-1;
        Pop[i][0]=0;
        for (int j=1; j<nKrom; j++){
            int temp=rand()%N;
            Pop[i][j] = Node[temp];
            for (int k=temp; k<nKrom-2; k++){
                Node[k]=Node[k+1];
                Node[k+1]=Pop[i][j];
            }
            N--;
        }
    }
//    for (int i=0; i<nPop; i++){
//        for (int j=0; j<nKrom-1; j++){
//            cout<<Pop[i][j]<<" - ";
//        }
//        cout<<Pop[i][nKrom-1]<<endl;
//    }
    for (int i=0; i<nGen; i++){
        float fitness[sizeof(gab)/sizeof(gab[0])];
        int anak[nPop][nKrom];

        int y = -1;
        for (int j=0; j<nPop/2; j++){

            // Seleksi Orang Tua
            int parent1 = rand()%nPop;
            int parent2 = rand()%nPop;

            int anak1[nKrom];
            int anak2[nKrom];

            for(int a=0; a<nKrom; a++){
                anak1[a] = Pop[parent1][a];
                anak2[a] = Pop[parent2][a];
            }

            // CrossOver
            int randd;
            randd = rand()%100;
            if (randd <=pCross){
                int titik = 2+rand()%(nKrom-2);
                for (int k=1; k<titik; k++){
                    int temp = anak1[k];
                    anak1[k]=anak2[k];
                    anak2[k]=temp;
                    int l;
                    if(k==1){
                        l=2;
                    }
                    else{
                        l=1;
                    }
                    while (l<nKrom && anak1[l]!=anak1[k]){
                        l++;
                        if(l==k){
                            l++;
                        }
                    }
                    if( anak1[l]==anak1[k]){
                        anak1[l]=temp;
                    }

                    if(k==1){
                        l=2;
                    }
                    else{
                        l=1;
                    }
                    while (l<nKrom && anak2[l]!=anak2[k]){
                        l++;
                        if(l==k){
                            l++;
                        }
                    }
                    if( anak2[l]==anak2[k]){
                        anak2[l]=anak1[k];
                    }
                }
            }

            // Mutasi
            randd = rand()%100;
            if (randd <=pMutasi){
                int titik = 1+rand()%(nKrom-1);
                int newNumber = 1+rand()%(nKrom-1);
                int l=1;
                while (anak1[l]!=newNumber){
                    l++;
                }
                anak1[l]=anak1[titik];
                anak1[titik]=newNumber;
            }
            randd = rand()%100;
            if (randd <=pMutasi){
                int titik = 1+rand()%(nKrom-1);
                int newNumber = 1+rand()%(nKrom-1);
                int l=1;
                while (anak2[l]!=newNumber){
                    l++;
                }
                anak2[l]=anak2[titik];
                anak2[titik]=newNumber;
            }
            y++;
            for (int z=0; z<nKrom; z++){
                anak[y][z] = anak1[z];
            }
            y++;
            for (int z=0; z<nKrom; z++){
                anak[y][z] = anak2[z];
            }
        }
        for(int a=0; a<nPop; a++){
            for(int b=0; b<nKrom; b++){
                gab[a][b]=Pop[a][b];
            }
        }
        for(int a=nPop; a<(nPop+(sizeof(anak)/sizeof(anak[0]))); a++){
            for(int b=0; b<nKrom; b++){
                gab[a][b]=anak[a-nPop][b];
            }
        }


        // Hitung Fitness
        for (int a=0; a<sizeof(gab)/sizeof(gab[0]); a++){
            fitness[a] = 0;
            for (int b=0; b<nKrom-1; b++){
                fitness[a] += jarak(C.info[gab[a][b]].x, C.info[gab[a][b]].y , C.info[gab[a][b+1]].x, C.info[gab[a][b+1]].y);
            }
            fitness[a] += jarak(C.info[gab[a][15]].x, C.info[gab[a][15]].y , C.info[gab[a][0]].x, C.info[gab[a][0]].y);
        }

        // Survivor
        int t;
        float temp;
        int temp2[nKrom];
        for(int a=1; a<sizeof(gab)/sizeof(gab[0]); a++){
            t=a;
            while(t>0 && fitness[t-1]>fitness[t]){
                temp=fitness[t];
                for(int b=0; b<nKrom; b++){
                    temp2[b]=gab[t][b];
                }
                fitness[t]=fitness[t-1];
                for(int b=0; b<nKrom; b++){
                    gab[t][b]=gab[t-1][b];
                }
                fitness[t-1]=temp;
                for(int b=0; b<nKrom; b++){
                    gab[t-1][b]=temp2[b];
                }
                t--;
            }
        }

        for(int i=0; i<nPop; i++){
            for(int j=0; j<nKrom; j++){
                Pop[i][j]=gab[i][j];
            }
            SteadyState[i]=fitness[i];
        }
        if(i==0){
            Generasi=1;
            Cost_min=SteadyState[0];
        }
        else{
            if(SteadyState[0]<Cost_min){
                Cost_min=SteadyState[0];
                Generasi=i+1;
            }
        }
    }
    cout<<"Generasi ke-"<<Generasi<<endl;
    cout<<"Jarak\t: "<<SteadyState[0]<<endl;
    cout<<"Rute\t: ";
    for (int i=0; i<nKrom; i++){
        cout<<Pop[0][i]<<" - ";
    }
    cout<<Pop[0][0];
}
