//#include "ofweek_ee.h"
#include "LOGS.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "NewsInfo.h"

#define HTML_BUFFER_SIZE 1024*800

int ofweek( char *input_html, struct NewsInfo *s )
{
    char tmpstr[1024],strDate[9];
    char change[10],rate[10],secuFullcode[10],secuName[10];
    int iStart,iEnd;
    char indexstr[30]="tuwen";
	int n=0;

    int i=indexOf( input_html, indexstr );
    input_html = input_html + i;    //得到采集字符串的开始
    strcpy( indexstr, "<form action" );
    i=indexOf( input_html, indexstr );
    input_html[i] = '\0';   //得到采集字符串的结束

    for( n=0;n<50; n++) //网页上一页有50条数据
    {
        memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
        iStart=indexOf(input_html,"<h3><a href=");
        input_html = input_html + iStart + 12;
        if( iStart != -1)
        {
            iEnd=indexOf( input_html, " target");
            strncpy( tmpstr, input_html, iEnd);
            sprintf( s[n].sourceaddr, "%s", tmpstr );

            /*iStart=indexOf(input_html,">")+1;
            input_html = input_html + iStart;

            if( strncmp( input_html, "<img", 4 ) == 0 )
            {
                DEBUGLOGSG( "这条带img" );
                iStart=indexOf(input_html,">")+1;
                input_html = input_html + iStart;
            }
			*/

            iStart=indexOf(input_html,"title=")+6;
            input_html = input_html + iStart;

            memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
            iEnd=indexOf( input_html, ">");
            strncpy( tmpstr, input_html, iEnd);
            sprintf( s[n].title, "%s", tmpstr );
			Compute_string_md5( s[n].title, s[n].id );

			memset(tmpstr,0x00,sizeof(tmpstr)); //初始化
            iStart=indexOf(input_html,"<span>")+6;
            input_html = input_html + iStart;
			iEnd=indexOf( input_html, "</span>");
            strncpy( tmpstr, input_html, iEnd);
            sprintf( s[n].content, "%s", tmpstr );

			strcpy( s[n].newsreleasetime, "" );

			strcpy( s[n].articleauthor, "OFweek高科技行业门户" );
			strcpy( s[n].sourcename, "OFweek高科技行业门户" );

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

