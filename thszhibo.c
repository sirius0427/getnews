#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LOGS.h"
#include "NewsInfo.h"

#define HTML_BUFFER_SIZE 1024*800

//http://news.10jqka.com.cn/gundong_mlist/1_0_1_1/ 同花顺直播
int thszhibo( char *input_html, struct NewsInfo *s )
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

	for( n=0;n<20; n++) //网页上一页有20条数据
	{
		memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
		iStart=indexOf(input_html,"<item>");
		input_html = input_html + iStart;
		iEnd=indexOf(input_html,"</item>");
		memset( sectionstr, 0x00, sizeof( sectionstr ));
		strncpy( sectionstr, input_html, iEnd );;
		pp = sectionstr;
		input_html = input_html + iEnd + 7;
		if( iStart != -1)
		{
			memset( url_w, 0x00, sizeof( url_w ));
			iStart=indexOf(pp,"<url><![CDATA[");
			if( iStart != -1 )
			{
				iEnd=indexOf( pp+iStart+14, "]]></url>");
				strncpy( url_w, pp+iStart+14, iEnd);
			}

			memset( title, 0x00, sizeof( title ));
			iStart=indexOf(pp,"<title><![CDATA[");
			if( iStart != -1 )
			{
				iEnd=indexOf( pp+iStart+16, "]]></title>");
				strncpy( title, pp+iStart+16, iEnd);
			}

			memset( digest, 0x00, sizeof( digest ));
			iStart=indexOf(pp,"<digest><![CDATA[");
			if( iStart != -1 )
			{
				iEnd=indexOf( pp+iStart+17, "]]></digest>");
				strncpy( digest, pp+iStart+17, iEnd);
			}

			sprintf( s[n].title, "[%s]%s", title, digest );
			strcpy( s[n].sourceaddr, url_w );

			strcpy( s[n].content, "");  //get content 
			strcpy( s[n].newsreleasetime, "");  //get content 

			strcpy( s[n].articleauthor, "同花顺直播" );
			strcpy( s[n].sourcename, "同花顺直播" );
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

