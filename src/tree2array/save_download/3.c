#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int NYears;
int *Years;

int NDays;
int *Days;

int NCoords;
char * Coords;

unsigned int MemSize;
char * Mem;

int main(){
	char buf[512];

	FILE * out;
	FILE * in;
	FILE * indata;
	char fdata[]="coordinates.txt";
	int year,mounth,day,time;
	double x,y;
	int i;
	
	indata = fopen(fdata,"r");
	if(indata==NULL){
		printf("FopenErr:<%s>\n",fdata);
		exit(0);
	}

		fscanf(indata,"%s", buf);
		fscanf(indata,"%d",&NYears);
			NDays = NYears*12*31;
		
		fscanf(indata,"%s", buf);
		fscanf(indata,"%d",&NCoords);
			MemSize = sizeof(NYears) + sizeof(NCoords) + NYears*sizeof(int) + 
				NDays*sizeof(int) + NCoords*(sizeof(int)+2*sizeof(double));
		
	Mem = (char*)malloc(MemSize*sizeof(char));

	Years= (int*)Mem + 2;
	Days = Years + NYears;
	Coords = (char*)(Days+NDays);
	
	i=0;
	while(fscanf(indata,"%d %d %d %d %lf %lf", &year, &mounth, &day, &time, &x, &y) == 6){
			*(int*)(Coords+(sizeof(int)+sizeof(double)+sizeof(double))*i)=time;
			*(double*)(Coords+(sizeof(int)+sizeof(double)+sizeof(double))*i+sizeof(int))=x;
			*(double*)(Coords+(sizeof(int)+sizeof(double)+sizeof(double))*i+sizeof(int)+sizeof(double))=y;
	printf("i=%d\n",i);
	i++;
	}
	
	for(i=0;i<NCoords;i++){
		time  = *(int*)(Coords+(sizeof(int)+sizeof(double)+sizeof(double))*i);
			x=*(double*)(Coords+(sizeof(int)+sizeof(double)+sizeof(double))*i+sizeof(int));
			y=*(double*)(Coords+(sizeof(int)+sizeof(double)+sizeof(double))*i+sizeof(int)+sizeof(double));
		printf("%d %lf %lf\n", time,x,y);
	}

	out = fopen("tmp","wb");
	fwrite((void*) Mem,1,MemSize, out);
	fclose(out);

	in = fopen("tmp", "rb");
	fread((void*)Mem, 1, MemSize, in);
	fclose(in);
	
	for(i=0;i<NCoords;i++){
		time  = *(int*)(Coords+(sizeof(int)+sizeof(double)+sizeof(double))*i);
			x=*(double*)(Coords+(sizeof(int)+sizeof(double)+sizeof(double))*i+sizeof(int));
			y=*(double*)(Coords+(sizeof(int)+sizeof(double)+sizeof(double))*i+sizeof(int)+sizeof(double));
		printf("%d %lf %lf\n", time,x,y);
	}
	
	
return 0;
}	


/*	
	
	
	
	
	
	
	
	
	
	
		NMem = 134782;


	
	
	

	Mem =(char *)malloc(NMem*sizeof(char));

	memcpy((void*)Mem, (void*)&NMem, sizeof(int));
	
	
	printf("<%u> \n",NMem);
	
	return 0;
}
*/