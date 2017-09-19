#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LOGS.h"
#include "NewsInfo.h"

#define HTML_BUFFER_SIZE 1024*800

int NeteaseTechTodayHot( char *input_html, struct NewsInfo *s )
{
	char tmpstr[1024],strDate[9];
	char change[13],rate[13],secuFullcode[10],secuName[13];
	int iStart=0,iEnd;
	int n=0;

	memset( s, 0x00, sizeof( s ));
	char tmp_html[HTML_BUFFER_SIZE]={0};

	for( n=0;n<50; n++) //网页上一页有50条数据
	{
		memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
		iStart=indexOf(input_html,"title");
		if( iStart != -1)
		{
			iStart=indexOf(input_html,"title");
			input_html = input_html + iStart + 8;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd);
			strcpy( s[n].title, tmpstr );  //get title 

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, "docurl") + 9; 
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd );
			sprintf( s[n].sourceaddr, "%s", tmpstr );

			strcpy( s[n].content, "");  //get content 

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, "time") + 7;
			input_html = input_html + iStart; 
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd );
			strcpy( s[n].newsreleasetime, tmpstr );  //get content 

			strcpy( s[n].articleauthor, "网易科技今日热点" );
			strcpy( s[n].sourcename, "网易科技今日热点" );

			time_t now;
			time(&now);
			sprintf( s[n].collectiontime, "%ld000", now );
			sprintf( s[n].releasetime, "%ld000", now );
			sprintf( s[n].sectiontype, "1" );
			sprintf( s[n].collectionstatus, "1" );
			sprintf( s[n].checktimestamp, "%ld000", now );
			Compute_string_md5( s[n].title, s[n].id );
			s[n].articletype=1;
			strcpy( s[n].stat, "1");

			DEBUGLOGSG( "%s\t%-100s\t%s\t%s\t%-24s\t%s\t", s[n].id, s[n].title, s[n].newsreleasetime, s[n].sourcename, s[n].articleauthor, s[n].sourceaddr);

		}
		else break;
	}
	return n;
}

int NeteaseNewestLists( char *input_html, struct NewsInfo *s )
{
	char tmpstr[1024],strDate[9];
	char change[13],rate[13],secuFullcode[10],secuName[13];
	int iStart=0,iEnd;
	int n=0;

	memset( s, 0x00, sizeof( s ));
	char tmp_html[HTML_BUFFER_SIZE]={0};

	iStart=indexOf(input_html,"newest-lists");
	input_html = input_html + iStart;
	iEnd = indexOf(input_html,"newest_bottom");
	input_html[iEnd] = '\0' ;

	for( n=0;n<50; n++) //网页上一页有50条数据
	{
		memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
		iStart=indexOf(input_html,"href=");
		if( iStart != -1)
		{
			iStart=indexOf(input_html,"href=");
			input_html = input_html + iStart + 6;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd);
			sprintf( s[n].sourceaddr, "%s", tmpstr );
			//strcpy( s[n].title, tmpstr );  //get title 

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, "nl-title") + 10; 
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "<");
			strncpy( tmpstr, input_html, iEnd );
			replace( tmpstr, "\n", "" );
			trim( tmpstr );
			sprintf( s[n].title, "%s", tmpstr );

			strcpy( s[n].content, "");  //get content 

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, "nl-time") + 9;
			input_html = input_html + iStart; 
			iEnd=indexOf( input_html, "<");
			strncpy( tmpstr, input_html, iEnd );
			strcpy( s[n].newsreleasetime, tmpstr );  //get content 

			strcpy( s[n].articleauthor, "网易科技最新快讯" );
			strcpy( s[n].sourcename, "网易科技最新快讯" );

			time_t now;
			time(&now);
			sprintf( s[n].collectiontime, "%ld000", now );
			sprintf( s[n].releasetime, "%ld000", now );
			sprintf( s[n].sectiontype, "1" );
			sprintf( s[n].collectionstatus, "1" );
			sprintf( s[n].checktimestamp, "%ld000", now );
			Compute_string_md5( s[n].title, s[n].id );
			s[n].articletype=1;
			strcpy( s[n].stat, "1");

			DEBUGLOGSG( "%s\t%-100s\t%s\t%s\t%-24s\t%s\t", s[n].id, s[n].title, s[n].newsreleasetime, s[n].sourcename, s[n].articleauthor, s[n].sourceaddr);

		}
		else break;
	}
	return n;

}

//http://money.163.com/special/00252G50/macro.html 宏观财经
int macro( char *input_html, struct NewsInfo *s )
{
	char tmpstr[1024],strDate[9];
	char change[13],rate[13],secuFullcode[10],secuName[13];
	int iStart=0,iEnd;
	int n=0;

	memset( s, 0x00, sizeof( s ));
	char tmp_html[HTML_BUFFER_SIZE]={0};

	iStart=indexOf(input_html,"area_list");
	input_html = input_html + iStart;
	iEnd = indexOf(input_html,"list_page");
	input_html[iEnd] = '\0' ;

	for( n=0;n<50; n++) //网页上一页有50条数据
	{
		memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
		iStart=indexOf(input_html,"\"item_top\"");
		if( iStart != -1)
		{
			iStart=indexOf(input_html,"href=");
			input_html = input_html + iStart + 6;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd);
			sprintf( s[n].sourceaddr, "%s", tmpstr );
			//strcpy( s[n].title, tmpstr );  //get title 

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, ">") + 1; 
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "<");
			strncpy( tmpstr, input_html, iEnd );
			sprintf( s[n].title, "%s", tmpstr );

			strcpy( s[n].content, "");  //get content 

			strcpy( s[n].newsreleasetime, "" );  //get content 

			strcpy( s[n].articleauthor, "网易宏观新闻" );
			strcpy( s[n].sourcename, "网易宏观新闻" );

			time_t now;
			time(&now);
			sprintf( s[n].collectiontime, "%ld000", now );
			sprintf( s[n].releasetime, "%ld000", now );
			sprintf( s[n].sectiontype, "1" );
			sprintf( s[n].collectionstatus, "1" );
			sprintf( s[n].checktimestamp, "%ld000", now );
			Compute_string_md5( s[n].title, s[n].id );
			s[n].articletype=1;
			strcpy( s[n].stat, "1");

			DEBUGLOGSG( "%s\t%-100s\t%s\t%s\t%-24s\t%s\t", s[n].id, s[n].title, s[n].newsreleasetime, s[n].sourcename, s[n].articleauthor, s[n].sourceaddr);

		}
		else break;
	}
	return n;

}

