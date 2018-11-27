 #include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#define SEED_URL "https://www.chitkara.edu.in"
#define Url_Length 1000
#define HASH_size 100
#define MAX_URL_PER_PAGE 1000
static int k=0;
struct node *head=NULL;
struct url
{
char str[Url_Length];
int depth;
};
struct node
{
struct url u;
int visited;
struct node *next;
int key;
};
struct hash
{
struct node *head1;
struct node *tail1;
int countlinks;
};
int hash(char str[500])
{
    int i=0,num;
	//printf("String in hash function is %s ", str);
    int sum=0;
    char ch;
    while(str[i]!='\0')
    {
        ch=str[i];
        num=ch;
        sum=sum+num;
        i++;
    }
    //printf(" :  value is %d\n",sum%100);
    return (sum%100);
}
struct node * createnode(char *urljodaalna,int depthjodaalni,int key)
{
	struct node *temp=(struct node *)malloc(sizeof(struct node)*1);
	
	//printf("urljodaalna is %s\n",urljodaalna);
	strcpy(temp->u.str,urljodaalna);
	
	temp->u.depth=depthjodaalni;
	temp->key=key;
	temp->visited=1;
	temp->next=NULL;
	
	//printf("url=%s::depth=%d::visited=%d\n",temp->u.str,temp->u.depth,temp->visited);
	
	return temp;
}
struct node * insertnode(char *urljodaalna,int depthjodaalni,int key)
{
	struct node *temp=createnode(urljodaalna,depthjodaalni,key);
	
	//printf("url=%s::depth=%d::visited=%d\n",temp->u.str,temp->u.depth,temp->visited);
	
	if(head==NULL)
	{
	head=temp;
	}
	else
	{
	struct node *t;
	t=head;
		while(t->next!=NULL)
		{
		t=t->next;
		}
		t->next=temp;
	}
return temp;
}
void inserthash(struct hash *h,int key,char *urljodaalna,int depthjodaalni,int *totallinks)
{
	//printf("total no of links are %d\n",*totallinks);
	//printf("url jo daalna is %s\n", urljodaalna);
	//printf("hash is %s\n",h[key].head1->u.str);
	struct node *t=(struct node *)malloc(sizeof(struct node));
	t=h[key].head1;
	
	int count=h[key].countlinks;
	if(t==NULL&&count==0)
	{
		h[key].head1=insertnode(urljodaalna,depthjodaalni,key);
		(h[key].countlinks)++;	
		*totallinks=*totallinks+1;
	}
	else
	{
		//printf("xxxxxxx\n");
		while(t->next != NULL && count > 1)
		{
		//printf("****** \t");
		//printf("%s #### %s %d \n",t->u.str,urljodaalna,strcmp(t->u.str,urljodaalna));
			if(strcmp(t->u.str,urljodaalna)==0)
			{
			//printf("****url already exists in linked list****\n");
			return;
			}
			t=t->next;
			count--;
		}
			//printf("%s #### %s %d \n",t->u.str,urljodaalna,strcmp(t->u.str,urljodaalna));
		if(strcmp(t->u.str,urljodaalna)==0)
			{
			//printf("****url already exists in linked list*****\n");
			return;
			}
		//printf(" t is %d\n",t->key);
        char s[100];
		struct node *temp=createnode(urljodaalna,depthjodaalni,key);
		struct node *temp1;
		temp1=t->next;
		t->next=temp;
		temp->next=temp1;
		//printf(" t next is %s\n",t->next->u.str);
		(h[key].countlinks)++;
		*totallinks=*totallinks+1;
	}
}
void printlist()
{
struct node *t;
t=head;
	while(t!=NULL)
	{
	printf("%s\n",t->u.str);
	t=t->next;
	}
}
int validateurl(char *str)
{
	if(strcmp(SEED_URL,str)==0)
	{
	return 1;
	}
	else
	{
	return 0;
	}
}
void validatedepth(char *str)
{
	if((str[0]-'0')==1)
	{
	printf("valid depth\n");
	return;
	}
	else
	{
	printf("invalid depth\n");
	exit(1);
	}
}
void testDir(char *dir)
{
  struct stat statbuf;
  if ( stat(dir, &statbuf) == -1 ) 
  {
    fprintf(stderr, "-----------------\n");
    fprintf(stderr, "Invalid directory\n");
    fprintf(stderr, "-----------------\n");
    exit(1);
  }

  //Both check if there's a directory and if it's writable
  if ( !S_ISDIR(statbuf.st_mode) ) 
  {
    fprintf(stderr, "-----------------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
    fprintf(stderr, "-----------------------------------------------------\n");
    exit(1);
  }

  if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR ) 
  {
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. It isn't writable\n");
    fprintf(stderr, "------------------------------------------\n");
    exit(1);
  }
}

/*To calculate file size & creating path of new file
-------------------------------------------------------------
struct stat st; //variable which will count length of file.
stat("temp.txt",&st); // temp.txt is the file where wget fetch the html
int file_size=st.st_size;

sprintf(itostring,"%d",file_no); //converts integer into string
char file[]="/temp"; //name of file.
char f[]=".txt";
strcat(p,path); //creating path using strcat in p.
strcat(p,file);
strcat(p,itostring);
strcat(p,f);
printf("PATH has been created\n");*/

//Function to fetch the web page
void createpathforfile(char *p,int fileno)
{
char ch[50];
sprintf(ch,"%d",fileno);
char file[]="/home/prince/study/crawler/files/temp";
char f[]=".txt";
strcat(p,file);
strcat(p,ch);
strcat(p,f);
//printf("path is %s",p);
}
void getpage(char *url)
{
char urlbuffer[Url_Length+300]={0}; 

strcat(urlbuffer, "wget ");

strcat(urlbuffer, url);

strcat(urlbuffer," -O /home/prince/study/crawler/files/temp.txt");

printf("string is %s\n\n",urlbuffer);

system(urlbuffer);
}
//to check whetehet the extracted url has base address correct or not
int checkwithbase(char *dupvalistr)
{
	char str[50];
	strcpy(str, SEED_URL);
	//printf("str is %s\n",str);
	int k=0;
	while(str[k]==*(dupvalistr+k)&&str[k]!='\0')
	{
	//printf("str[k] is %c::dupvalis str is %c\n",str[k],*(dupvalistr+k));
	k++;
	}
	//printf("str[k] is %c::dupvalis str is %c\n",str[k],*(dupvalistr+k));
	//printf("******%c*******\n",*(dupvalistr+k+1));
	if(str[k]=='\0'&&*(dupvalistr+k+1)!=34)
	return 1;
	else
	return 0;
}

int finalurlcheck(char *checklengthstr, char **finalstorestr, int *currsize)
{

	//printf(" check is %s\n",checklengthstr);
	
	if(!validateurl(checklengthstr))
	{
		for(int i=0; i<(*currsize); i++)
		{
		//printf(" finalstorestr is %s\n",finalstorestr[i]);
			if(strcmp(checklengthstr,finalstorestr[i])==0)
			{
				//printf("in finalcheck URl already in finalstorestr\n");
				return 0;
			}
		}
		return 1;
	}
	else
	{
	//printf("in final check URl match with seed url\n");
	return 0;
	}
	
}
//to check href
char** extracturls(char *filevalistr,int *currsize)
{
int total=0;
(*currsize)=0;
char* dupfilevalistr = filevalistr;
char checklengthstr[Url_Length];
char **finalstorestr = (char**)malloc(MAX_URL_PER_PAGE * sizeof(char *)); // Allocate row pointers

for(int i = 0; i < MAX_URL_PER_PAGE; i++)
  finalstorestr[i] = malloc(Url_Length * sizeof(char));  // Allocate each row separately

//for(int i=0;i<MAX_URL_PER_PAGE;i++)
//finalstorestr[i]="NULL";

//char finalstorestr[MAX_URL_PER_PAGE][Url_Length];
while ( (dupfilevalistr=strstr(dupfilevalistr,"href")) != NULL )
 {
 //printf(" hi you are in extract url\n");
 	int i=0;
	if(*(dupfilevalistr-2)=='a')
	{
	if(*(dupfilevalistr+4)=='=')
		{
				dupfilevalistr += 5;
				//printf("character : %c\n", *dupfilevalistr);
				if(*(dupfilevalistr)==34)
				{
					dupfilevalistr++;
					if(*(dupfilevalistr)!=35)
					{
						if(checkwithbase(dupfilevalistr)==1)
						{
						while(*(dupfilevalistr)!=34)
						{
						
						checklengthstr[i++]=*(dupfilevalistr);
						dupfilevalistr++;
						}
						if (checklengthstr[i - 1] == '/')
						checklengthstr[i - 1] = '\0';
						else
						 checklengthstr[i]='\0';
						//printf("checklength string is %s\n",checklengthstr);
						if(finalurlcheck(checklengthstr, finalstorestr, currsize)!=0)
						{
						//printf("checklength string is %s\n",checklengthstr);
						strcpy(finalstorestr[(*currsize)],checklengthstr);
						//printf("finalstore  string is %s\n",finalstorestr[(*currsize)]);
						(*currsize)++;
						total++;
						}
						
					
						}
					}
				}
		}
	}	
	dupfilevalistr++;
 }
printf("total no of valid links are %d\n", (*currsize)); // prints 3 as it should
return finalstorestr;
}

void testagrguments(int argc,char*argv[])
{
 int counter; 
    printf("Program Name Is: %s\n",argv[0]); 
	    if(argc == 1) 
		printf("No Extra Command Line Argument Passed Other Than Program Name\n"); 
	    else if(argc<4) 
	    { 
	        printf("less Number Of Arguments Passed: %d\n", argc); 
	    }
		else
		{
		     printf("Number Of Arguments Passed: %d\n", argc); 
		     printf("----Following Are The Command Line Arguments Passed----\n"); 
			for(counter=0; counter<argc; counter++) 
			    printf("argv[%d]: %s\n",counter, argv[counter]);
		}

   if((validateurl(argv[1]))==1)
   {
   printf("valid match with seed url\n");
   }
   else
   {
   printf("url do not match with seed url\n");
   exit(1);
   }
	validatedepth(argv[2]);
	testDir(argv[3]);
}
void printfinalstore(int finalsize,char **finalstorestr)
{
	for(int i=0;i<finalsize;i++)
	{
		printf("strings in finalstore str are %s\n",finalstorestr[i]);
	}
}

int main(int argc,char* argv[]) 
{ 
   
	//wget() for validating URL --without proxy--
	if(!system("wget --spider argv[1]"))
    printf("Valid URL\n");
    else
    printf("Invalid URL\n");
    
  struct hash h[HASH_size]; 
  
		  for(int i=0;i<HASH_size;i++)
			{
			h[i].head1=NULL;
			h[i].tail1=NULL;
			h[i].countlinks=0;
			}
	
	int links=0;
	int *totallinks=&links;
	
 for(int k=0;k<174;k++)
	{ 
	int counter=k;
	 if(counter==0)
	getpage(argv[1]);
	else
	{
	struct node *t=head;
		while(counter!=1)
		{
		t=t->next;
		counter--;
		}
		getpage(t->u.str);
	}
	//to get the size of file in which wget gets the html code

	struct stat st; //variable which will count length of file.

	printf(" file exits if 0 and do not exists if not equal to 0::%d\n", stat("/home/prince/study/crawler/files/temp.txt",&st));

	long int file_size=st.st_size;

	printf(" size of file is %ld\n",file_size);

	//allocating size to filevalistr
	char *filevalistr=(char *)malloc(sizeof(char)*(file_size+1));

	//copying html file data into filevalistr
	int i=0;

	FILE *fptr=fopen("/home/prince/study/crawler/files/temp.txt","r");

	if(fptr == NULL)
	{
	printf("file not found\n");
	exit(1);
	}

	char ch;
	ch=getc(fptr);

	while(ch != EOF)
	{
		filevalistr[i++]=ch;
		ch=getc(fptr);
	}

	//filevalistr[i++]='\0';
	fclose(fptr);
	
 	char p[50]={0};
   // printf("hey p is%s\n",p);
    int fileno=k;
    createpathforfile(p,fileno);
    fptr=fopen(p,"w");
    fprintf(fptr,"%s",filevalistr);
	//finalsize mein finalstring k andar jitni rows store hai unka size hai
	int finalsize;
	int *ptr=&finalsize;


	//printf("filevali str is \n %s\n",filevalistr);
	char **finalstorestr=extracturls(filevalistr,ptr);

	//printfinalstore(finalsize,finalstorestr);
	
	int key;
	
	for(int i=0;i<finalsize;i++)
	{
	key=hash(finalstorestr[i]);
	inserthash(h,key,finalstorestr[i],3,totallinks);
	}
	
}
printlist();
printf("total no of links are %d\n",*totallinks);

}



