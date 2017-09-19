#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LOGS.h"
#include "NewsInfo.h"

#define HTML_BUFFER_SIZE 1024*800

//http://live.sina.com.cn/zt/f/v/finance/globalnews1 新浪7*24小时财经
int live( char *input_html, struct NewsInfo *s )
{
	    char tmpstr[1024],strDate[9];
		char change[13],rate[13],secuFullcode[10],secuName[13];
		int iStart,iEnd;
		int n=0;

		memset( s, 0x00, sizeof( s ));
		char tmp_html[HTML_BUFFER_SIZE]={0};

		iStart=indexOf(input_html,"\"bd_list\"");
		input_html = input_html + iStart;
		iEnd=indexOf(input_html,"\"toolbar-pagination\"");
		input_html[iEnd] = '\0';


		for( n=0;n<50; n++) //网页上一页有50条数据
		{
			memset(tmpstr,0x00,sizeof(tmpstr)); //初始化

			iStart=indexOf(input_html,"bd_i_txt_c");
			input_html = input_html + iStart ;
			if( iStart != -1)
			{
				iStart=indexOf(input_html,">");
				input_html = input_html + iStart + 1;
				iEnd=indexOf( input_html, "<");
				if( iEnd >=2000 )
				{
					strncpy( tmpstr, input_html, 1998);
				}
				else
					strncpy( tmpstr, input_html, iEnd);
				sprintf( s[n].title, "%s", tmpstr );

				strcpy( s[n].sourceaddr, "" );
				strcpy( s[n].newsreleasetime, "" );  //get title 
				strcat( s[n].content, "");

				strcpy( s[n].articleauthor, "新浪7*24小时财经" );
				strcpy( s[n].sourcename, "新浪7*24小时财经" );

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

//http://roll.finance.sina.com.cn/finance/zq1/ssgs/index.shtml 新浪财经上市公司
int ssgs( char *input_html, struct NewsInfo *s )
{
	char tmpstr[1024],strDate[9];
	char change[13],rate[13],secuFullcode[10],secuName[13];
	int iStart=0,iEnd;
	int n=0;

	memset( s, 0x00, sizeof( s ));
	char tmp_html[HTML_BUFFER_SIZE]={0};

	iStart=indexOf(input_html,"\"list_009\"");
	input_html = input_html + iStart;
	iEnd=indexOf(input_html,"\"hs01\"");
	input_html[iEnd] = '\0';

	for( n=0;n<50; n++) //网页上一页有50条数据
	{
		memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
		iStart=indexOf(input_html,"href=\"");
		if( iStart != -1)
		{
			memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
			iStart=indexOf(input_html,"href=\"");
			input_html = input_html + iStart + 6;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd);
			sprintf( s[n].sourceaddr, "%s", tmpstr );  //sourceaddr

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, ">") + 1;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "</a>");
			strncpy( tmpstr, input_html, iEnd );
			sprintf( s[n].title, "%s", tmpstr );

			strcpy( s[n].content, "");  //get content 
			strcpy( s[n].newsreleasetime, "");  //get content 

			strcpy( s[n].articleauthor, "新浪财经上市公司" );
			strcpy( s[n].sourcename, "新浪财经上市公司" );

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

//http://roll.news.sina.com.cn/interface/rollnews_ch_out_interface.php?col=43&spec=&type=&ch=03&k=&offset_page=0&offset_num=0&num=60&asc=&page=1&r=0.27956114133885035
//新浪财经滚动
int roll( char *input_html, struct NewsInfo *s )
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
		iStart=indexOf(input_html,",title : \"");
		if( iStart != -1)
		{
			memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
			iStart=indexOf(input_html,",title : \"");
			input_html = input_html + iStart + 10;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd);
			sprintf( s[n].title, "%s", tmpstr );

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, ",url : \"") + 8;
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd );
			sprintf( s[n].sourceaddr, "%s", tmpstr );  //sourceaddr

			strcpy( s[n].content, "");  //get content 
			strcpy( s[n].newsreleasetime, "");  //get content 

			strcpy( s[n].articleauthor, "新浪财经滚动" );
			strcpy( s[n].sourcename, "新浪财经滚动" );

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

//http://feed.mix.sina.com.cn/api/roll/get?pageid=164&lid=1693&num=10&page=1&callback=feedCardJsonpCallback&_=1482657687545
//新浪产经滚动
int chanjing( char *input_html, struct NewsInfo *s )
{
	char tmpstr[1024],strDate[9];
	char change[13],rate[13],secuFullcode[10],secuName[13];
	int iStart=0,iEnd;
	int n=0,i=0,ret=0;

	memset( s, 0x00, sizeof( s ));
	char tmp_html[HTML_BUFFER_SIZE]={0};
	
	iStart=indexOf(input_html, "\"data\"" );
	input_html = input_html + iStart + 6;
	replace( input_html, "\\", "" ); 

	for( n=0;n<50; n++) //网页上一页有50条数据
	{
		i=0;
		memset( tmp_html, 0x00, sizeof( tmp_html ));
		iStart = indexOf( input_html, "{" );
		input_html = input_html + iStart + 1;
		ret = 1;
		if( iStart != -1 )
		{
			while(1)
			{
				tmp_html[i] = input_html[i];
				if( input_html[i] == '{' )
				{
					ret++;	
				}
				if( input_html[i] == '}' )
				{
					ret--;	
				}
				if( ret == 0 || input_html[i] == '\0' )
				{
					break;
				}
				i++;
			}
			//printf( "%s\n", tmp_html );

			input_html = input_html + i + 1;

			iStart=indexOf(tmp_html,"\"url\":\"");
			if( iStart == -1 )
				break;

			memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
			iStart=indexOf(tmp_html,"\"url\":\"") + 7;
			iEnd=indexOf( tmp_html+iStart, "\"");
			strncpy( tmpstr, tmp_html+iStart, iEnd);
			replace( tmpstr, "\\", "" );
			sprintf( s[n].sourceaddr, "%s", tmpstr );  //sourceaddr

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( tmp_html, "\"title\":\"") + 9;
			iEnd=indexOf( tmp_html+iStart, "\"");
			strncpy( tmpstr, tmp_html+iStart, iEnd );
			sprintf( s[n].title, "%s", tmpstr );

			strcpy( s[n].content, "");  //get content 
			strcpy( s[n].newsreleasetime, "");  //get content 

			strcpy( s[n].articleauthor, "新浪产经滚动" );
			strcpy( s[n].sourcename, "新浪产经滚动" );

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
		else
			break;

	}
	return n;
}

//http://feed.mix.sina.com.cn/api/roll/get?pageid=1&lid=21&num=30&versionNumber=1.2.8&page=1&encode=utf-8&callback=feedCardJsonpCallback&_=1481811167020
//新浪科技
int tech( char *input_html, struct NewsInfo *s )
{
	char tmpstr[1024],strDate[9];
	char change[13],rate[13],secuFullcode[10],secuName[13];
	int iStart=0,iEnd;
	int n=0,i=0,ret=0;

	memset( s, 0x00, sizeof( s ));
	char tmp_html[HTML_BUFFER_SIZE]={0};
	
	iStart=indexOf(input_html, "\"data\"" );
	input_html = input_html + iStart + 6;
	replace( input_html, "\\", "" ); 

	for( n=0;n<50; n++) //网页上一页有50条数据
	{
		i=0;
		memset( tmp_html, 0x00, sizeof( tmp_html ));
		iStart = indexOf( input_html, "{" );
		input_html = input_html + iStart + 1;
		ret = 1;
		if( iStart != -1 )
		{
			while(1)
			{
				tmp_html[i] = input_html[i];
				if( input_html[i] == '{' )
				{
					ret++;	
				}
				if( input_html[i] == '}' )
				{
					ret--;	
				}
				if( ret == 0 || input_html[i] == '\0' )
				{
					break;
				}
				i++;
			}
			//printf( "%s\n", tmp_html );

			input_html = input_html + i + 1;

			iStart=indexOf(tmp_html,"\"url\":\"");
			if( iStart == -1 )
				break;

			memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
			iStart=indexOf(tmp_html,"\"url\":\"") + 7;
			iEnd=indexOf( tmp_html+iStart, "\"");
			strncpy( tmpstr, tmp_html+iStart, iEnd);
			replace( tmpstr, "\\", "" );
			sprintf( s[n].sourceaddr, "%s", tmpstr );  //sourceaddr

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( tmp_html, "\"title\":\"") + 9;
			iEnd=indexOf( tmp_html+iStart, "\"");
			strncpy( tmpstr, tmp_html+iStart, iEnd );
			sprintf( s[n].title, "%s", tmpstr );

			strcpy( s[n].content, "");  //get content 
			strcpy( s[n].newsreleasetime, "");  //get content 

			strcpy( s[n].articleauthor, "新浪科技" );
			strcpy( s[n].sourcename, "新浪科技" );

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
		else
			break;

	}
	return n;
}

