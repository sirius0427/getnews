#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LOGS.h"
#include "NewsInfo.h"

#define HTML_BUFFER_SIZE 1024*800

int yicai( char *input_html, struct NewsInfo *s )
{
	    char tmpstr[1024],strDate[9];
		//char str2[20]="post-4895";
		char change[13],rate[13],secuFullcode[10],secuName[13];
		int iStart,iEnd;
		int n=0;

		memset( s, 0x00, sizeof( s ));
		int i=indexOf( input_html, "news_List");
		input_html = input_html + i;
		i=indexOf( input_html, "</div>");
		char tmp_html[HTML_BUFFER_SIZE]={0};
		input_html[i] = '\0';


		for( n=0;n<50; n++) //网页上一页有50条数据
		{
			memset(tmpstr,0x00,sizeof(tmpstr)); //初始化

			iStart=indexOf(input_html,"href=");
			input_html = input_html + iStart ;
			if( iStart != -1)
			{
				iStart=indexOf(input_html,"f-fs22");
				input_html = input_html + iStart + 6;
				iStart=indexOf(input_html,"href=\"");
				input_html = input_html + iStart + 6;
				iEnd=indexOf( input_html, "\"");
				strncpy( tmpstr, input_html, iEnd);
				sprintf( s[n].sourceaddr, "%s", tmpstr );

				memset( tmpstr, 0x00, sizeof( tmpstr ));
				iStart = indexOf( input_html, "blank\">") + 7;
				input_html = input_html + iStart;
				iEnd=indexOf( input_html, "</a>");
				strncpy( tmpstr, input_html, iEnd );
				strcpy( s[n].title, tmpstr );  //get title 

				memset( tmpstr, 0x00, sizeof( tmpstr ));
				iStart = indexOf( input_html, "<span>") + 6;
				input_html = input_html + iStart; 
				iEnd=indexOf( input_html, "</span>");
				strncpy( tmpstr, input_html, iEnd );
				strcpy( s[n].newsreleasetime, tmpstr );  //get title 

				/*memset( tmpstr, 0x00, sizeof( tmpstr ));
				iStart = indexOf( input_html, "f-ff1 f-fs14") + 14;
				input_html = input_html + iStart; 
				iEnd=indexOf( input_html, "</p>");
				if( iEnd < 300)
				{   
					    strncpy( tmpstr, input_html, iEnd );
				}
				else 
					    strncpy( tmpstr, input_html, 300 );
				strcat( s[n].content, tmpstr );
*/
				strcpy( s[n].content, "" );

				strcpy( s[n].articleauthor, "第一财经新闻" );
				strcpy( s[n].sourcename, "第一财经新闻" );

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
