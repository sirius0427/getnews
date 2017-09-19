#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LOGS.h"
#include "NewsInfo.h"

#define HTML_BUFFER_SIZE 1024*800

int eastmoneyreporthyyb( char *input_html, struct NewsInfo *s )
{
	char tmpstr[1024],strDate[9],title[1024];
	char str2[20]="data\":[";
    char change[13],rate[13],secuFullcode[10],secuName[13];
    char yyyy[5],mm[3],dd[3];
	int iStart,iEnd;
	int n=0;
	
	int i=indexOf( input_html, str2 );
	//LOG_TRACE( "data position start[%d]", i );
	input_html = input_html + i;
	strcpy( str2, "});" );
	i=indexOf( input_html, str2 );
	//LOG_TRACE( "data position end[%d]", i );
	char tmp_html[HTML_BUFFER_SIZE]={0};
	input_html[i] = '\0';
    iStart=indexOf(input_html,"[\"");
    input_html = input_html + iStart + 2;
    for( n=0;n<50; n++)	//网页上一页有50条数据
	{
		memset(tmpstr,0x00,sizeof(tmpstr));	//初始化
		
		if( iStart != -1)
		{
            memset( change, 0x00, sizeof( change ));
			iEnd=indexOf( input_html, ",");
			strncpy( change, input_html, iEnd);    //get change
			//printf( "%s\t", change);

            memset( yyyy,0x00, sizeof( yyyy ));
            memset( mm,0x00, sizeof( mm ));
            memset( dd,0x00, sizeof( dd ));
			iStart = indexOf( input_html, ",") + 1;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, ",");
			strncpy( tmpstr, input_html, iEnd );    //get date 
			strcpy( s[n].newsreleasetime, tmpstr );	//get newsreleasetime

            iEnd=indexOf( tmpstr, "/" );
            strncpy( yyyy, tmpstr, iEnd );
            strcpy(tmpstr ,tmpstr + iEnd + 1);
            iEnd=indexOf( tmpstr, "/" );
            strncpy( mm, tmpstr, iEnd );
            strcpy(tmpstr ,tmpstr + iEnd + 1);
            iEnd=indexOf( tmpstr, " " );
            strncpy( dd, tmpstr, iEnd );
            sprintf( strDate, "%4s%02d%02d", yyyy, atoi(mm), atoi(dd) );
            //printf ("%s\t", strDate );  //get YYYYMMDD
			
            memset( secuName, 0x00, sizeof( secuName));
			iStart = indexOf( input_html, ",") + 1;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, ",");
			strncpy( tmpstr, input_html, iEnd );
			sprintf( s[n].sourceaddr, "%s%s/%s.html", "http://data.eastmoney.com/report/", strDate, tmpstr );
			//printf( "%s\t", s[n].sourceaddr );	//getUrl

			iStart = indexOf( input_html, ",") + 1;
			input_html = input_html + iStart;   //jump one

			iStart = indexOf( input_html, ",") + 1;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, ",");
			strncpy( s[n].sourcename, input_html, iEnd );
			//printf( "%s\t", s[n].sourcename );	//getSourceName

			iStart = indexOf( input_html, ",") + 1;
			input_html = input_html + iStart;
			iStart = indexOf( input_html, ",") + 1;
			input_html = input_html + iStart;   //jump two

            memset( rate,0x00, sizeof( rate ));
			iStart = indexOf( input_html, ",") + 1;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, ",");
			strncpy( rate, input_html, iEnd );
			//printf( "%s\t", rate );	//getrate

			iStart = indexOf( input_html, ",") + 1;
			input_html = input_html + iStart;   //jump one

            memset( title, 0x00, sizeof(title));
			iStart = indexOf( input_html, ",") + 1;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, ",");
			strncpy( title, input_html, iEnd ); //get title

            memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, ",") + 1;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, ",");
			strncpy( tmpstr, input_html, iEnd );    //getsecuName
			sprintf( s[n].title,"%s 变动:%s 类别:%s %s", tmpstr, change, rate, title);
			//printf( "%s\n",s[n].title );

			strcpy( s[n].stat, "1");
			
			time_t now;
			time(&now);
			sprintf( s[n].collectiontime, "%ld000", now );
			
			Compute_string_md5( s[n].title, s[n].id );
			//printf( "%s\t", s[n].id );
			//printf( "\n" );
			DEBUGLOGSG( "%s\t%-100s\t%s\t%s\t%-24s\t%s\t", s[n].id, s[n].title, s[n].newsreleasetime, s[n].sourcename, s[n].articleauthor, s[n].sourceaddr);
			strcpy(s[n].content,"eastmoneyreporter" );
			s[n].articletype=1;
            strcpy(s[n].sectiontype,"1" );
            strcpy(s[n].collectionstatus,"1" );
			//printf( "\n" );
			//printf( "%s\n", tmpstr);
            iStart=indexOf(input_html,",\"");
            input_html = input_html + iStart + 2;
        }
		else break;
    }
	return n;
}
