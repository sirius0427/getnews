#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LOGS.h"
#include "NewsInfo.h"

#define HTML_BUFFER_SIZE 1024*800

//https://www.tzxm.gov.cn:8081/tzxmspweb/tzxmspweb/portalopenPublicInformation.do?method=queryExamineAll 投资项目在线审批监控平台
int spweb( char *input_html, struct NewsInfo *s )
{
	char tmpstr[1024],strDate[9];
	char tmpxmdm[200];	//项目代码
	char change[13],rate[13],secuFullcode[10],secuName[13];
	int iStart=0,iEnd;
	int n=0;

	memset( s, 0x00, sizeof( s ));
	char tmp_html[HTML_BUFFER_SIZE]={0};

	iStart=indexOf(input_html,"<table");
	input_html = input_html + iStart;
	iStart=indexOf(input_html,"<tr>");
	input_html = input_html + iStart + 4;
	iEnd=indexOf(input_html,"</table>");
	input_html[iEnd] = '\0';

	for( n=0;n<50; n++) //网页上一页有50条数据
	{
		memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
		memset(tmpxmdm,0x00,sizeof(tmpxmdm)); //初始化
		iStart=indexOf(input_html,"<tr>");
		if( iStart != -1)
		{
			input_html = input_html + iStart + 4;

			memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
			iStart=indexOf(input_html,"title=\"");
			input_html = input_html + iStart + 7;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd);
			sprintf( s[n].title, "%s", tmpstr );

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, "window.open('") + 13; 
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "'");
			strncpy( tmpstr, input_html, iEnd );
			sprintf( s[n].sourceaddr, "https://www.tzxm.gov.cn:8081%s", tmpstr );  //sourceaddr

			/*memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, ">") + 1 ; 
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "<");
			strncpy( tmpxmdm, input_html, iEnd );
			replace( tmpxmdm, "&nbsp;", "" );
			strcpy( tmpstr, s[n].title );
			sprintf( s[n].title, "%s%s", tmpxmdm, tmpstr );
			*/


			strcpy( s[n].content, "");  //get content 
			strcpy( s[n].newsreleasetime, "");  //get content 

			strcpy( s[n].articleauthor, "投资项目审批平台" );
			strcpy( s[n].sourcename, "投资项目审批平台" );

			time_t now;
			time(&now);
			sprintf( s[n].collectiontime, "%ld000", now );
			sprintf( s[n].releasetime, "%ld000", now );
			sprintf( s[n].sectiontype, "1" );
			sprintf( s[n].collectionstatus, "1" );
			s[n].countpage=1;   //不加过滤
			sprintf( s[n].checktimestamp, "%ld000", now );
			Compute_string_md5( s[n].title, s[n].id );
			s[n].articletype=1;
			strcpy( s[n].stat, "5");

			DEBUGLOGSG( "%s\t%-100s\t%s\t%s\t%-24s\t%s\t", s[n].id, s[n].title, s[n].newsreleasetime, s[n].sourcename, s[n].articleauthor, s[n].sourceaddr);

		}
		else break;
	}
	return n;
}
