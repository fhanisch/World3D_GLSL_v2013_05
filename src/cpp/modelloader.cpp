#include "modelloader.h"

FILE *file;



int loadModel(MODELDATA *md, char *filename)
{
	char str[256];
		
	if (fopen_s(&file,filename,"rb") != 0) return 1;
	fseek(file,0,SEEK_SET);

	readString(str);
	readInteger((int*)&md->verticesLength,NULL);
	md->vertices = new float[md->verticesLength];
	for(unsigned int i=0;i<md->verticesLength;i++) readGleitkommazahl(&md->vertices[i], 32);

	readString(str);
	readInteger((int*)&md->indicesLength,NULL);
	md->indices = new unsigned int[md->indicesLength];
	for(unsigned int i=0;i<md->indicesLength;i++) 
	{
		readInteger((int*)md->indices+i,NULL);
		md->indices[i]--;
	}
	fclose(file);
	
	return 0;
}

int readString(char *str)
{	
	char b=0;
	int i=0;

	while(b!=0x0a && i<256)
	{
		fread(&b,1,1,file);
		str[i]=b;
		i++;
	}
	str[i-1]=0;
	return i-1;
}

int readInteger(int *z, char *sign)
{
	char c[10];
	unsigned char b=0xff;
	int i=0;
	char vz=1;
	
	*z=0;
	if (sign!=0) *sign=0;
	while(b>0x2e)
	{	
		fread(&b,1,1,file);
		if (b!='-')
		{			
			c[i]=b&0x0f;
			i++;			
		}
		else
		{
			b=0xff;
			vz=-1;
			if (sign!=0) *sign=1;
		}
	}

	for(int j=0;j<i-1;j++) *z=*z+c[j]*(int)pow(10.0,i-j-2);
	*z=*z*vz;
	return i-1;
}

int readGleitkommazahl(void *g, unsigned char precession)
{		
	int vz=0;
	int nz=0;
	int exp=0;	 	
	DWORD64 b64=0;
	double nachKommaTeilDez=0;
	DWORD64 nachKommaTeilBin=0;
	unsigned char bitsExp;
	if (precession==64) bitsExp = 11; else bitsExp=8;
	unsigned char bitsExpPlusVZ = bitsExp+1;
	unsigned short bias = (unsigned short)pow(2.0,bitsExp-1)-1;
	char vorzeichen=0;

	readInteger(&vz,&vorzeichen);
	if (vorzeichen) vz=vz*(-1);

	int test=vz;	
	if (vz>0)
	{
		while(test!=1) 
		{
			test=test>>1;
			exp++;
		}
	}

	memcpy(&b64,&vz,precession/8);
	b64=b64&0xffffffff;
	b64=b64<<(precession-bitsExpPlusVZ-exp);

	int nachKommaStellen = readInteger(&nz,NULL);
	nachKommaTeilDez=(double)nz*pow(10.0,-nachKommaStellen);

	double tmp=nachKommaTeilDez;
	if(vz>0)
	{
		for(int i=0;i<precession-exp-bitsExpPlusVZ;i++)
		{
			nachKommaTeilBin=nachKommaTeilBin<<1;
			if(2.0*tmp<1.0)
			{
				tmp=2.0*tmp;
				nachKommaTeilBin=nachKommaTeilBin|0;		
			}
			else
			{
				tmp=2.0*tmp-1.0;
				nachKommaTeilBin=nachKommaTeilBin|1;		
			}				
		}
	}
	else if (vz<1 && nz!=0)
	{
		int i=0;
		while(!(nachKommaTeilBin&((DWORD64)1<<(precession-bitsExpPlusVZ))))
		{
			nachKommaTeilBin=nachKommaTeilBin<<1;
			if(2.0*tmp<1.0)
			{
				tmp=2.0*tmp;
				nachKommaTeilBin=nachKommaTeilBin|0;		
			}
			else
			{
				tmp=2.0*tmp-1.0;
				nachKommaTeilBin=nachKommaTeilBin|1;		
			}				
			i--;
		}
		exp=i+(precession-bitsExpPlusVZ);
	}	
	else exp = -127;
	
	b64=b64|nachKommaTeilBin; // Mantisse
	
	if(precession==32) b64=b64&0x7FFFFF; else b64=b64&0xFFFFFFFFFFFFF;

	b64=b64|((DWORD64)(exp+bias)<<(precession-bitsExpPlusVZ));
	
	b64=b64|((DWORD64)vorzeichen<<(precession-1));

	//if (precession==32) b64=b64+1; //Aufrunden

	memcpy(g,&b64,precession/8);
	
	return 0;
}