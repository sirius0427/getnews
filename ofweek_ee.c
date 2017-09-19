//#include "ofweek_ee.h"
#include "LOGS.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "NewsInfo.h"

#define HTML_BUFFER_SIZE 1024*800

int ofweek_ee( char *input_html, struct NewsInfo *s )
{
    char tmpstr[1024],strDate[9];
    char change[10],rate[10],secuFullcode[10],secuName[10];
    int iStart,iEnd;
    char indexstr[30]="list_model";
	int n=0;

    int i=indexOf( input_html, indexstr );
    input_html = input_html + i;    //得到采集字符串的开始
    strcpy( indexstr, "<div class=\"page\">" );
    i=indexOf( input_html, indexstr );
    input_html[i] = '\0';   //得到采集字符串的结束

	//printf( "%s\n", input_html );

    for( n=0;n<50; n++) //网页上一页有50条数据
    {
        memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
        iStart=indexOf(input_html,"<h3><a href=\"");
        input_html = input_html + iStart + 13;
        if( iStart != -1)
        {
            iEnd=indexOf( input_html, "\"");
            strncpy( tmpstr, input_html, iEnd);
            sprintf( s[n].sourceaddr, "%s", tmpstr );

            iStart=indexOf(input_html,">")+1;
            input_html = input_html + iStart;

            if( strncmp( input_html, "<img", 4 ) == 0 )
            {
                DEBUGLOGSG( "这条带img" );
                iStart=indexOf(input_html,">")+1;
                input_html = input_html + iStart;
            }

            memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
            iEnd=indexOf( input_html, "<");
            strncpy( tmpstr, input_html, iEnd);
            sprintf( s[n].title, "%s", tmpstr );
	    Compute_string_md5( s[n].title, s[n].id );

	    memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
            iStart=indexOf(input_html,"<span>")+6;
            input_html = input_html + iStart;
			iEnd=indexOf( input_html, "</span>");
            strncpy( tmpstr, input_html, iEnd);
            sprintf( s[n].content, "%s", tmpstr );

			memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
            iStart=indexOf(input_html,"class=\"date\"");
            input_html = input_html + iStart;
            iStart=indexOf(input_html,"</a>|");
            input_html = input_html + iStart;
            iStart=indexOf(input_html,"20");
            input_html = input_html + iStart;
			iEnd = indexOf( input_html, "</span>" );
			strncpy( s[n].newsreleasetime, input_html, iEnd );

			strcpy( s[n].articleauthor, "OFweek电子工程网" );
			strcpy( s[n].sourcename, "OFweek电子工程网" );

			time_t now;
			time(&now);
			sprintf( s[n].collectiontime, "%ld000", now );
			sprintf( s[n].releasetime, "%ld000", now );
			sprintf( s[n].sectiontype, "1" );
			sprintf( s[n].collectionstatus, "1" );
			sprintf( s[n].checktimestamp, "%ld000", now );
			s[n].articletype=1;
			strcpy( s[n].stat, "1");

			DEBUGLOGSG( "%s\t%-100s\t%s\t%s\t%-24s\t%s\t", s[n].id, s[n].title, s[n].newsreleasetime, s[n].sourcename, s[n].articleauthor, s[n].sourceaddr);

        }
		else break;
    }
    return n;
}
