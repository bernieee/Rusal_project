#include<stdio.h>
#include<stdlib.h>

void save(char *mas, int k_coor, int k_y, char* fname);
void download(char *mas, char* fname);

int main(){
	int k_y;
	int k_coor;
	int year, month, day;
	int years_t=0, month_t=0, day_t=0;
	int ch;
	int smesch;
	double x;
	double y;
	double *pom_d;
	int *pom_i;
	char time[10];
	char *mas;
	int *mas_years;
	int i;
	int j;
	int t;
	char fname1[]="out_in.txt";
	//int dlina;
	int sec; 
	FILE *f;
	FILE*c;
	c=fopen("coor.txt", "r");
	f=fopen("years.txt", "r");
									//заполняем массив с годами
	fscanf(f, "%d", &k_y);
	mas_years=malloc(k_y*sizeof(int));
	for(j=0;j<k_y;j++)
	{
		fscanf(f, "%d", &mas_years[j]);
	}
	//printf("1\n");
									//заполняем большой массив годами 
	
	fscanf(c, "%d", &k_coor);
	mas=malloc((k_coor*(sizeof(int)+2*sizeof(double))+(k_y+1)*sizeof(int)+12*31*k_y*sizeof(int))*sizeof(char));
	pom_i=(int*)(mas);
	*pom_i=k_y;
	for(j=1;j<=k_y;j++)
	{
		//fscanf(c, "%d", &year);
		pom_i=(int*)(mas+j*sizeof(int));
		*pom_i=mas_years[j-1];
	}
	//printf("1\n");
									//заполняем большой массив координатами
	t=0;
	//year=0;
	while(fscanf(c, "%d%d%d%s%lf%lf", &year, &month, &day, time, &x, &y)==6)
	{
		sec=time[0]*10*60*60 + time[1]*60*60 + time[3]*10*60 + time[4]*60 + time[6]*10 + time[7];
		pom_i=(int*)(mas + (k_y+1)*sizeof(int) + k_y*31*12*sizeof(int) + t*sizeof(int) + 2*t*sizeof(double));
		*pom_i=sec;
		//printf("%d  ", *pom_i);
		pom_d=(double*)(mas + (k_y+1)*sizeof(int) + k_y*31*12*sizeof(int) + (t+1)*sizeof(int) + 2*t*sizeof(double));
		*pom_d=x;
		//printf("%lf  ", *pom_d);
		pom_d=(double*)(mas + (k_y+1)*sizeof(int) + k_y*31*12*sizeof(int) + (t+1)*sizeof(int) + 2*t*sizeof(double)+sizeof(double));
		*pom_d=y;
		//printf("%lf\n", *pom_d);
		//printf("%d %d\n %d %d\n %d %d\n", year,years_t,month,month_t,day,day_t);
		if(year!=years_t && month!=month_t && day!=day_t)
		{
		//printf("1\n");
		years_t=year;
		month_t=month;
		day_t=day;
		ch=0;
		while(mas_years[ch]!=year)
		{
			ch++;
		}
		smesch=(k_y+1)*sizeof(int) + k_y*31*12*sizeof(int) + t*(sizeof(int)+2*sizeof(double));
		pom_i=(int*)(mas+(k_y+1)*sizeof(int)+ch*31*12*sizeof(int)+month*31*sizeof(int)+day*sizeof(int));
		*pom_i=smesch;
		}
		t++;
	}
	//save(mas, k_coor, k_y, fname1);
	download(mas, fname1);
	pom_i=(int*)(mas+(k_y+1)*sizeof(int)+0*31*12*sizeof(int)+3*31*sizeof(int)+5*sizeof(int));
	pom_d=(double*)(&mas[*pom_i]+sizeof(int));
	pom_i=(int*)(&mas[*pom_i]);
	printf("%lf\n", *pom_d);
	printf("%d\n", *pom_i);
	return 0;
}

void save(char *mas, int k_coor, int k_y, char* fname)
{
	int all=k_coor*(sizeof(int)+2*sizeof(double))+(k_y+1)*sizeof(int)+12*31*k_y*sizeof(int);
	FILE* out;
	out=fopen(fname, "wb");
	fwrite((void*)&(all), sizeof(int), 1, out);
	fwrite((void*)&(mas[0]), sizeof(char), k_coor*(sizeof(int)+2*sizeof(double))+(k_y+1)*sizeof(int)+12*31*k_y*sizeof(int), out);
	fclose(out);
}

void download(char *mas, char* fname)
{
	int i;
	int k;
	FILE* out;
	out=fopen(fname, "rb");
	//printf("1\n");	
	fread((void*)&(k), sizeof(int), 1, out);
	mas = malloc(k*sizeof(char));
	fread((void*)&(mas[0]), sizeof(char), k, out);
	fclose(out);
}