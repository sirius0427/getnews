#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LOGS.h"
#include "NewsInfo.h"

#define HTML_BUFFER_SIZE 1024*800

//http://newsapi.eastmoney.com/kuaixun/v2/api/list?limit=20&column=zhibo 东方财富直播
int dfcfzhibo( char *input_html, struct NewsInfo *s )
{
	char sectionstr[HTML_BUFFER_SIZE];
	char *pp;
	char tmpstr[1024],strDate[9];
	char url_w[1024],url_pdf[1024],title[2048],digest[2048];
	char change[13],rate[13],secuFullcode[10],secuName[13];
	int iStart=0,iEnd;
	int n=0;

	memset( s, 0x00, sizeof( s ));
	char tmp_html[HTML_BUFFER_SIZE]={0};

	iStart=indexOf(input_html,"\"id\"");
	input_html = input_html + iStart;
	iEnd=indexOf(input_html,"\"PageCount\"");
	input_html[iEnd] = '\0';

	for( n=0;n<20; n++) //网页上一页有20条数据
	{
		memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
		iStart=indexOf(input_html,"\"id\"");
		input_html = input_html + iStart;
		iEnd=indexOf(input_html,"}");
		memset( sectionstr, 0x00, sizeof( sectionstr ));
		strncpy( sectionstr, input_html, iEnd );;
		pp = sectionstr;
		input_html = input_html + iEnd + 1;
		if( iStart != -1)
		{
			memset( url_w, 0x00, sizeof( url_w ));
			iStart=indexOf(pp,"\"url_w\"");
			if( iStart != -1 )
			{
				iEnd=indexOf( pp+iStart+9, "\"");
				strncpy( url_w, pp+iStart+9, iEnd);
			}

			memset( url_pdf, 0x00, sizeof( url_pdf ));
			iStart=indexOf(pp,"\"url_pdf\"");
			if( iStart != -1 )
			{
				iEnd=indexOf( pp+iStart+11, "\"");
				strncpy( url_pdf, pp+iStart+11, iEnd);
			}

			memset( title, 0x00, sizeof( title ));
			iStart=indexOf(pp,"\"title\"");
			if( iStart != -1 )
			{
				iEnd=indexOf( pp+iStart+9, "\"");
				strncpy( title, pp+iStart+9, iEnd);
			}

			memset( digest, 0x00, sizeof( digest ));
			iStart=indexOf(pp,"\"digest\"");
			if( iStart != -1 )
			{
				iEnd=indexOf( pp+iStart+10, "\"");
				strncpy( digest, pp+iStart+10, iEnd);
			}

			if( strlen( digest ) > 0 )
			{
				strcpy( s[n].title, digest );
			}
			else
				strcpy( s[n].title, title );

			if( strlen( url_pdf ) > 0 )
			{
				strcpy( s[n].sourceaddr, url_pdf );
			}
			else
				strcpy( s[n].sourceaddr, url_w );

			strcpy( s[n].content, "");  //get content 
			strcpy( s[n].newsreleasetime, "");  //get content 

			strcpy( s[n].articleauthor, "东方财富直播" );
			strcpy( s[n].sourcename, "东方财富直播" );
			//s[n].countpage=1;   //不加过滤
			strcpy( s[n].stat, "5");

			time_t now;
			time(&now);
			sprintf( s[n].collectiontime, "%ld000", now );
			sprintf( s[n].releasetime, "%ld000", now );
			sprintf( s[n].sectiontype, "1" );
			sprintf( s[n].collectionstatus, "1" );
			sprintf( s[n].checktimestamp, "%ld000", now );
			Compute_string_md5( s[n].title, s[n].id );
			s[n].articletype=1;

			//DEBUGLOGSG( "%s\t%-100s\t%s\t%s\t%-24s\t%s\t", s[n].id, s[n].title, s[n].newsreleasetime, s[n].sourcename, s[n].articleauthor, s[n].sourceaddr);

		}
		else break;
	}
	return n;
}

