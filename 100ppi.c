#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LOGS.h"
#include "NewsInfo.h"

#define HTML_BUFFER_SIZE 1024*800
int list_chance( char *input_html, struct NewsInfo *s )
{
	char tmpstr[1024],strDate[9];
	char change[13],rate[13],secuFullcode[10],secuName[13];
	int iStart=0,iEnd;
	int n=0;

	memset( s, 0x00, sizeof( s ));
	char tmp_html[HTML_BUFFER_SIZE]={0};

	iStart=indexOf(input_html,"list-c");
	input_html = input_html + iStart;
	iEnd=indexOf(input_html,"</div>");
	input_html[iEnd] = '\0';

	for( n=0;n<50; n++) //网页上一页有50条数据
	{
		memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
		iStart=indexOf(input_html,"detail_chance");
		if( iStart != -1)
		{
			iStart=indexOf(input_html,"detail_chance");
			input_html = input_html + iStart ;
			iEnd=indexOf( input_html, "\"");
			strncpy( tmpstr, input_html, iEnd);
			sprintf( s[n].sourceaddr, "http://stock.100ppi.com/%s", tmpstr );  //sourceaddr

			memset( tmpstr, 0x00, sizeof( tmpstr ));
			iStart = indexOf( input_html, ">") +1; 
			input_html = input_html + iStart;
			iEnd=indexOf( input_html, "<");
			strncpy( tmpstr, input_html, iEnd );
			sprintf( s[n].title, "%s", tmpstr );

			if ( indexOf( tmpstr, "90天" ) != -1 || indexOf( tmpstr, "60天" ) != -1 || indexOf( tmpstr, "30天" ) != -1 || indexOf( tmpstr, "20天" ) != -1)
			{
				n--;
				continue;
			}

			strcpy( s[n].content, "");  //get content 
			strcpy( s[n].newsreleasetime, "");  //get content 

			strcpy( s[n].articleauthor, "生意社买入机会" );
			strcpy( s[n].sourcename, "生意社买入机会" );
			s[n].countpage=1;   //不加过滤

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

