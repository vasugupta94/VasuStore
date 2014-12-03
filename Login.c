#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addLoggedIn(char u[])
{
	FILE* loggedIn = fopen("LoggedIn.csv","a");
	//fseek(loggedIn,-1,SEEK_END);
	fprintf(loggedIn,"%s,",u);
	fclose(loggedIn);
}

int main()
{
	FILE* list = fopen("Members.csv","rt");
	if( list==NULL )
	{
		return 1;
	}

        printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);

	char user[200], pass[200];	
	char *data, *first, *second;
	int len = atoi(getenv("CONTENT_LENGTH")) + 1;
	data = (char*)calloc(len,sizeof(char));
	fgets(data,len,stdin);
	if( data!=NULL )
	{
		first = strtok(data,"&");
		second = strtok(NULL,"");
		sscanf(first,"username=%s",user);
		sscanf(second,"password=%s",pass);
	}

	char line[200];
	int found = 0;
	char *u, *p;

	while( !found )
	{
		fgets(line,200,list);
		if( feof(list) )
		{
			break;
		}
		u = strtok(line,",");
		p = strtok(NULL,"\n");
//		printf("%s-%s\n",u,p);
		if( strcmp(user,u)==0 && strcmp(pass,p)==0 )
		{
			found = 1;
		}
	}

	if( found )
	{
		addLoggedIn(user);
		char url[100] = "http://cs.mcgill.ca/~nkhosh/BannerDone.html";
		printf("<html><head><meta http-equiv=\"refresh\" content=\"0;%s\"\r\n</head></html>",url);
	}
	else
	{
		printf("<html><body><h1>Not found!</h1></body></html>");
		printf("<a href=index.html><br>Home page</br></a>");
		printf("<a href=login.html><br>Login page</br></a>");
	}
	fclose(list);
	return 0;
}
