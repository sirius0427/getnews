#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LOGS.h"
#include "NewsInfo.h"

#define HTML_BUFFER_SIZE 1024*800

int eastmoneyreport( char *input_html, struct NewsInfo *s )
{
	char tmpstr[1024],strDate[9];
	char str2[20]="data\":[{";
    char change[13],rate[13],secuFullcode[10],secuName[13];
	int iStart,iEnd;
	int n=0;
	
	memset( s, 0x00, sizeof( s ));
	int i=indexOf( input_html, str2 );
	//LOG_TRACE( "data position start[%d]", i );
	input_html = input_html + i;
	strcpy( str2, "};" );
	i=indexOf( input_html, str2 );
	//LOG_TRACE( "data position end[%d]", i );
	char tmp_html[HTML_BUFFER_SIZE]={0};
	input_html[i] = '\0';
	for( n=0;n<50; n++)	//网页上一页有50条数据
	{
		memset(tmpstr,0x00,sizeof(tmpstr));	//初始化
		
		iStart=indexOf(input_html,"author");
		input_html = input_html + iStart + 9;
		if( iStart != -1)
		{
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd);
			strcpy( s[n].articleauthor, tmpstr );	//get articleauthor
			//printf( "%s\t", s[n].articleauthor);

            memset( change, 0x00, sizeof( change ));
			iStart = indexOf( input_html, "change") + 9;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "\",\"");
			strncpy( change, input_html, iEnd );    //get change
			
			memset( tmpstr, 0x00, sizeof( tmpstr ));
			memset( strDate, 0x00, sizeof( strDate ));
			iStart = indexOf( input_html, "datetime") + 11;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "\",\"");
			strncpy( tmpstr, input_html, iEnd );
			strcpy( s[n].newsreleasetime, tmpstr );	//get newsreleasetime
			
			strncat( strDate, tmpstr, 4);
			strncat( strDate, tmpstr+5, 2);
			strncat( strDate, tmpstr+8, 2);
			//printf( "%s\t", strDate );	//getDate
			
			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, "infoCode") + 11;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "\",\"");
			strncpy( tmpstr, input_html, iEnd );
			sprintf( s[n].sourceaddr, "%s%s/%s.html", "http://data.eastmoney.com/report/", strDate, tmpstr );
			//printf( "%s\t", s[n].sourceaddr );	//getUrl
			
			
			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, "insName") + 10;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "\",\"");
			strncpy( tmpstr, input_html, iEnd );
			strcpy( s[n].sourcename, tmpstr );	//get sourcename
			//printf( "%s\t", s[n].sourcename );

            memset( rate, 0x00, sizeof( rate ));
			iStart = indexOf( input_html, "rate") + 7;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "\",\"");
			strncpy( rate, input_html, iEnd );  //getrate
            
            memset( secuFullcode, 0x00, sizeof( secuFullcode));
			iStart = indexOf( input_html, "secuFullCode") + 15;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "\",\"");
			strncpy( secuFullcode, input_html, iEnd );  //getsecuFullcode

            memset( secuName, 0x00, sizeof( secuName));
			iStart = indexOf( input_html, "secuName") + 11;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "\"");
			strncpy( secuName, input_html, iEnd );  //get secuName
			
			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, "title") + 8;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "\",\"");
			strncpy( tmpstr, input_html, iEnd );
			sprintf( s[n].title,"%s %s %s %s %s", secuFullcode, secuName, change, rate, tmpstr );
			//printf( "%s\t", s[n].title );
			
			if( indexOf( s[n].title, "首次 买入" ) != -1 )
			{
				strcpy( s[n].stat, "5");
			}
			else
				strcpy( s[n].stat, "1");

			s[n].countpage=1;	//不加过滤
			
			time_t now;
			time(&now);
			sprintf( s[n].collectiontime, "%ld000", now );
			
			Compute_string_md5( s[n].title, s[n].id );
			//printf( "%s\t", s[n].id );
			DEBUGLOGSG( "%s\t%-100s\t%s\t%s\t%-24s\t%s\n", s[n].id, s[n].title, s[n].newsreleasetime, s[n].sourcename, s[n].articleauthor, s[n].sourceaddr);
			strcpy(s[n].content,"eastmoneyreporter" );
			s[n].articletype=1;
            strcpy(s[n].sectiontype,"1" );
            strcpy(s[n].collectionstatus,"1" );
			//printf( "\n" );
			//printf( "%s\n", tmpstr);
		}
		else
		{
			break;
		}
	}
	return n;
}

/*返回str2第一次出现在str1中的位置(下表索引),不存在返回-1*/
int indexOf(char *str1, char *str2) {
	char *p = str1;
	int i = 0;
	p = strstr(str1, str2);
	if (p == NULL)
		return -1;
	else {
		while (str1 != p) {
			str1++;
			i++;
		}
	}
	return i;
}

