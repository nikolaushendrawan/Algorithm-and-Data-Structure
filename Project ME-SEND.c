#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>
#include<string.h>
#include<windows.h>
#include<ctype.h>
#include<time.h>
#include <unistd.h>

#define V 6
#define INT_MAX 99999

typedef struct data
{
	char nama[10];
	int jarak;
	struct data *next, *prev;
}data;
data *head, *curr, *tail;

typedef struct driver
{
	char orang[50];
	char telp[50];
	char plat[50];
}driver;
driver pengantar[100];

char* arrHari[7] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
//====================
/*
	V (caps)  = jumlah vertex / titik
	v (kecil) = counter
	i 		  = counter
	count	  = counter
	graph 	  = sebagai bagan / gambaran yang dibentuk kedalam matriks
	src		  = source
	dist[]    = menampung jarak dari titik 1 ke titik lain
	sptset[]  = visited array
	INT_MAX	  = nilai 999999 (MAX)

	SPT = shortest path

*/
//====================

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void LoadingScreen()
{
    int i, j;
    char ch;

    gotoxy(50, 20);
    printf("Loading...");
    gotoxy(30, 22);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    for(i = 0; i < 55; i++)
	{
        Sleep(100);
        if(i == 10)
		{
            gotoxy(50, 24);
            system("COLOR F2");
            printf("Initializing...");
            gotoxy(40, 22);
        }
        else if(i == 20)
		{
            gotoxy(50, 24);
            system("COLOR F2");
            printf("Setting up...");
            gotoxy(50, 22);
        }
        else if(i == 30)
		{
            gotoxy(50, 24);
            system("COLOR F2");
            printf("Finishing touches...");
            gotoxy(60, 22);
        }
        else if(i == 40)
		{
            gotoxy(50, 24);
            system("COLOR F2");
            printf("Welcome to Me-Send");
            gotoxy(70, 22);
        }
        printf("%c", 219);
    }
    SetConsoleTextAttribute(hConsole, saved_attributes);
    printf("\n");
    gotoxy(35, 24);
    printf("Loading success!");
    system("pause");
}

void header()
{
    system("cls");
    system("COLOR F2");
    printf("========================================================================\n\n");
    printf("\t\t\t pengiriman Me - Send");
    printf("\n\n========================================================================\n");
}

void mainheader()
{
	system("cls");
	system("COLOR F2");
	printf("#####################################################################################################\n");
	printf("###    ############  ######           #####          ####           ###    #####  ####          #####\n");
	printf("###  #  #########    ######  ##############  ############  ############     ####  ####  ######   ####\n");
	printf("###  ##  #######  #  ######  ##############  ############  ############  #   ###  ####  #######  ####\n");
	printf("###  ###  #####  ##  ######           #####          ####           ###  ##   ##  ####  #######  ####\n");
	printf("###  ####  ###  ###  ######  ######################  ####  ############  ###   #  ####  #######  ####\n");
	printf("###  #####  #  ####  ######  ######################  ####  ############  ####     ####  ######   ####\n");
	printf("###  ##############  ######           #####          ####           ###  #####    ####          #####\n");
	printf("#####################################################################################################\n");
}

float hitung(int tjarak, float tberat)
{
	float tbiaya;
	tbiaya = ((tjarak/10) * 5000) + ((tberat/2) * 5000);
	return tbiaya;
}

void hapus_depan()
{
    if(head == tail)
	{
        curr = head;
        free(curr);
        head = tail = NULL;
    }
    else
	{
        curr = head;
        head = head -> next;
        free(curr);
        head ->prev = NULL;
    }
}

int minDistance(int dist[], int sptSet[])
{
	int min = INT_MAX, min_index1;
	int v;

	for(v = 0; v < V; v++)
	{
		//jika sptset[v] adalah 0 dan dist[v] lebih kecil atau sama dengan min
		//(dimana min = INT_MAX = 999999) maka lakukan:
		if(sptSet[v] == 0 && dist[v] <= min)
		{
			//min diubah nilainya mengikuti dist[v] dan
			//min_index1 menjadi nilai v
			min = dist[v];
			min_index1 = v;
		}
	}
	//nilai min_index1 dikembalikan kefungsi utama (void dijkstra)
	//dalam bentuk variabel u
	return min_index1;
}

//masuk ke linked list
void linked(int tdist[])
{
	system("COLOR F2");
	//untuk nama titik tiap tempat
    char tempat[V][10] = {"UMN","Newton","Pascal","Allicante","Darwin","Dalton"};

	//struct data *curr, *head, *tail;
	int i;

	head = NULL;

	for(i=0; i<V; i++)
	{
		//menyiapkan tempat untuk curr
		curr = (struct data*)malloc(sizeof(struct data));

		curr->jarak = tdist[i];
		strcpy(curr->nama, tempat[i]);

		if(head == NULL)
		{
			head = tail = curr;
		}
		else
		{
			//curr = curr->next;
			tail->next = curr; //memindahkan curr ke kotak berikutnya
			curr->prev = tail; //mengarahkan (arrow) prev menuju tail
			tail = curr;	   //memindahkan tail menuju ke kotak curr
		}
	}
	curr = head;
}

// main process
void dijkstra(int graph[V][V], int src)
{
	// 1. masukkan variabel yang dibutuhkan XD
	int i, v, u, count, dist[V];
	int sptSet[V]; //visited array


	for(i=0; i<V; i++)
	{
		dist[i] = INT_MAX; //jarak dibuat jadi 999999 / infinite
		sptSet [i] = 0; //sptset dibuat 0 pada setiap titik
	}

	dist[src] = 0;

	//3. mencari shortest path dengan memanggil fungsi lain
	for (count = 0; count < V-1; count++)
	{
		//nilai u didapat dari nilai min_index1 dari fungsi minDistance
		u = minDistance(dist, sptSet);
		sptSet[u] = 1;

        for(v = 0; v < V; v++)
        {
        	//jika graph di titik sekarang + cost jarak dari u ke v nilainya dibawah nilai titik v (titik selanjutnya)
        	//maka niai titik v menjadi titik awal dist[u] + cost jarak dari u ke v menjadi nilai d[v]
            if(!sptSet[v] && graph[u][v] && dist [u] != INT_MAX && dist[u] + graph [u][v] < dist[v])
            {
                dist[v] = dist[u]+graph[u][v];
            }
        }
	}
	linked(dist);
}

//search
void search()
{
//	system("cls");
//	header();
system("COLOR F2");
	char key[10];
	char orang[50], telp[50], plat[50];
	float berat;
	float biaya;
	int i;
	int counter;
	int resi;
	int layanan;
	int cmp; //compare
	bool stop;

	int randomNumber;
	SYSTEMTIME st;
    GetLocalTime(&st);
	printf("\nsilahkan pilih tempat yang ingin dituju");
	printf("\nsearch: ");
	scanf("%s",&key);
	printf("\nmasukkan berat barang yang akan anda kirim: ");
	scanf("%f",&berat);
	printf("\nPilih Layanan yang anda inginkan: ");
	printf("1. reguler\t2.express\n");
	printf("pilihan: ");
	scanf("%d",&layanan);

	srand(time(NULL));
    	stop = false;
        randomNumber = rand();
        randomNumber = randomNumber % 100000;
        while(stop == false)
		{
            for(i = 0; i <= 1; i++)
			{
                stop = true;
            }
        }
        resi = randomNumber;
	//=====================================================================

	FILE *fo;
	fo = fopen("Data.txt","a+");
	while(!feof(fo))
	{
		fscanf(fo,"%[^#]#%[^#]#%[^\n]\n", &orang, &telp, &plat);fflush(stdin);
		strcpy(pengantar[counter].orang, orang);
		strcpy(pengantar[counter].telp, telp);
		strcpy(pengantar[counter].plat, plat);
		counter++;
	}
	fclose(fo);


	for(counter = 0; counter <10; counter++)
	{
		printf("%s\n",pengantar[counter].orang);
	}
	system("pause");
	srand(time(NULL));
    	stop = false;
        randomNumber = rand();
        randomNumber = randomNumber % 10;
        while(stop == false)
		{
            for(i = 0; i <= 1; i++)
			{
                stop = true;
            }
        }
    counter = randomNumber;

	curr = head;
    while(curr->next != NULL)
   	{
   		//jika cmp bernilai 0 berarti character curr dan keyword yang dimasukkan sama
   		for(i=0; i<V; i++)
   		{
   			cmp = strcmpi(key, curr->nama);
   			if(curr->next != NULL)
   			{
   				if(cmp == 0)
   				{
   					break;
				}
				else
				{
					curr = curr->next;
				}
			}
			else
			{
				break;
			}
		}
	//==========================================================================================================
   		if(cmp == 0)
	    {
	    	biaya = hitung(curr->jarak, berat);
	    	system("cls");
	    	header();

	    	printf("\n\tE-recipient\n");
	    	if(layanan == 1)
	    	{
	    		printf("\nLayanan\t\t\t: reguler\n");
			}
			else if(layanan == 2)
			{
				printf("\nLayanan\t\t\t: express\n");
			}
			else
			{
				printf("pilihan tidak valid!");
				break;
			}

			if(layanan == 2)
			{
				biaya = biaya + 5000;
			}
		//=============================================================================================================
			printf("Hari/Tanggal\t\t: %s, %d/%d/%d \n", arrHari[st.wDayOfWeek], st.wDay, st.wMonth, st.wYear);
    		printf("Waktu       \t\t: %d:%d:%d \n", st.wHour, st.wMinute, st.wSecond);
    		printf("nama pengantar\t\t: %s\n",pengantar[counter].orang);
    		printf("nomor telepon\t\t: %s\n",pengantar[counter].telp);
    		printf("plat kendaraan\t\t: %s",pengantar[counter].plat);
	   		printf("\nnama tujuan\t\t: %s",curr->nama);
	   		printf("\njarak dari UMN ke %s: %dKm",curr->nama, curr->jarak);
	   		printf("\nnomor resi\t\t: %d",resi);
	   		printf("\nberat\t\t\t: %.2fKg\nbiaya\t\t\t: Rp %.2f\n\n", berat, biaya);
	   		break;
		}
		else
		{
			printf("data tidak ditemukan \n");
			break;
		}
		curr = curr->next;
	}
}


int main()
{
	mainheader();
	LoadingScreen();
	//untuk pemilihan & menu
	int exit = 0;
	int pilihan;
	int pilih;
	int i, j;


	//untuk jalur terpendek
	//int graph[V][V];
	int parent;
	int target;
	int dist;

	//untuk barang
	int berat;

	system("COLOR F2");
//==============================================================================================
	//graph fixed

       int graph[V][V] =  {{0,10,0,30,45,0},    //1
						   {10,0,50,0,40,25},   //2
						   {0,50,0,0,35,15},    //3
						   {30,0,0,0,0,20},     //4
						   {45,40,35,0,0,55},   //5
						   {0,25,15,20,55,0}};  //6

	mainheader();
	//untuk dijkstra
	dijkstra(graph,0);



	//menu
	while(exit == 0)
	{

		header();
		printf("\t1.cari lokasi pengantaran anda\n");
	    printf("\t2.tampilkan tarif\n");
	    printf("\t0.keluar\n");
	    printf("========================================================================\n");
	    printf(" pilihan: ");
		scanf("%d",&pilihan);

		switch(pilihan)
		{
			case 1:
				system("cls");
				header();
				search();

				system("pause");
			break;
			//=======================
			case 2:
				system("cls");
				header();
				system("COLOR F2");
				printf("\n\n");
				printf("biaya per 3Km : Rp 1000\n");
				printf("biaya per 1Kg : Rp 2500\n");
				printf("express = total biaya + Rp 5000\n");
				system("pause");
			break;
			//=======================
			case 0:
				system("COLOR F2");
				system("cls");
				header();
				printf("\nApa anda yakin?\n");
				printf("\n1. ya\t");
				printf("2. tidak\n");
				printf("\npilihan: ");
				scanf("%d",&pilih);
				if(pilih == 1)
				{
					system("cls");
					printf("\n\nSemoga Hari Anda Menyenangkan!\n\n");
					system("pause");
					while(head != NULL)
					{
						hapus_depan();
					}
					exit = 1;
				}
				else if(pilih == 2)
				{
					exit = 0;
				}
				else
				{
					printf("\n\nMaaf inputan tidak valid");
				}

            break;
			//=======================
			default:
				printf("maaf, pilihan yang anda masukkan tidak valid!");
				system("pause");
            break;
		}
	}
return 0;
}
