#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LOGS.h"
#include "NewsInfo.h"

#define HTML_BUFFER_SIZE 1024*800

//http://qc.wa.news.cn/nodeart/list?nid=1111750&pgnum=1&cnt=10&tp=1&orderby=1?callback=jQuery171044856620818019954_1482590214385&_=1482590225312
//http://www.news.cn/fortune/zjlist.htm 新华网证券新闻
int zjlist( char *input_html, struct NewsInfo *s )
{
	char tmpstr[1024],strDate[9];
	char change[13],rate[13],secuFullcode[10],secuName[13];
	int iStart=0,iEnd;
	int n=0;

	memset( s, 0x00, sizeof( s ));
	char tmp_html[HTML_BUFFER_SIZE]={0};

	for( n=0;n<50; n++) //网页上一页有50条数据
	{
		replace( input_html, "\\\"", "''" );
		memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
		iStart=indexOf(input_html,"\"Title\"");
		input_html = input_html + iStart;
		if( iStart != -1)
		{
			memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
			iStart=indexOf(input_html,"Title");
			input_html = input_html + iStart + 8;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd);
			replace( tmpstr, "''", "\"" );
			sprintf( s[n].title, "%s", tmpstr );

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, "LinkUrl") + 10; 
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd );
			sprintf( s[n].sourceaddr, "%s", tmpstr );  //sourceaddr

			strcpy( s[n].content, "");  //get content 
			strcpy( s[n].newsreleasetime, "");  //get content 

			strcpy( s[n].articleauthor, "新华网证券新闻" );
			strcpy( s[n].sourcename, "新华网证券新闻" );

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

//http://qc.wa.news.cn/nodeart/list?nid=1111751&pgnum=1&cnt=10&tp=1&orderby=1?callback=jQuery17105625017059472348_1482590774961&_=1482590775072
//http://www.news.cn/fortune/gslist.htm 新华网公司新闻
int gslist( char *input_html, struct NewsInfo *s )
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
		iStart=indexOf(input_html,"\"Title\"");
		input_html = input_html + iStart;
		replace( input_html, "\\\"", "''" );
		if( iStart != -1)
		{
			memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
			iStart=indexOf(input_html,"Title");
			input_html = input_html + iStart + 8;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd);
			replace( tmpstr, "''", "\"" );
			sprintf( s[n].title, "%s", tmpstr );

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, "LinkUrl") + 10; 
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd );
			sprintf( s[n].sourceaddr, "%s", tmpstr );  //sourceaddr

			strcpy( s[n].content, "");  //get content 
			strcpy( s[n].newsreleasetime, "");  //get content 

			strcpy( s[n].articleauthor, "新华网公司新闻" );
			strcpy( s[n].sourcename, "新华网公司新闻" );

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

//http://qc.wa.news.cn/nodeart/list?nid=11142781&pgnum=1&cnt=10&tp=1&orderby=1?callback=jQuery17100945115964859724_1495538614660&_=1495538615683
//新华网独家
int djlist( char *input_html, struct NewsInfo *s )
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
		iStart=indexOf(input_html,"\"Title\"");
		input_html = input_html + iStart;
		replace( input_html, "\\\"", "''" );
		if( iStart != -1)
		{
			memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
			iStart=indexOf(input_html,"Title");
			input_html = input_html + iStart + 8;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd);
			replace( tmpstr, "''", "\"" );
			sprintf( s[n].title, "%s", tmpstr );

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, "LinkUrl") + 10; 
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd );
			sprintf( s[n].sourceaddr, "%s", tmpstr );  //sourceaddr

			strcpy( s[n].content, "");  //get content 
			strcpy( s[n].newsreleasetime, "");  //get content 

			strcpy( s[n].articleauthor, "新华网独家" );
			strcpy( s[n].sourcename, "新华网独家" );

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
