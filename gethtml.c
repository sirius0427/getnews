#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "iconv.h"
#include "LOGS.h"
#define HTML_BUFFER_SIZE 1024*800
#define MIN(a,b) ((a)>(b)?(b):(a))

/*将str1字符串中第一次出现的str2字符串替换成str3*/  
void replaceFirst1(char *str1,char *str2,char *str3)  
{  
	char str4[strlen(str1)+1];  
	char *p;  
	strcpy(str4,str1);  
	if((p=strstr(str1,str2))!=NULL)/*p指向str2在str1中第一次出现的位置*/  
	{   
		while(str1!=p&&str1!=NULL)/*将str1指针移动到p的位置*/  
		{   
			str1++;  
		}   
		str1[0]='\0';/*将str1指针指向的值变成/0,以此来截断str1,舍弃str2及以后的内容，只保留str2以前的内容*/  
		strcat(str1,str3);/*在str1后拼接上str3,组成新str1*/  
		strcat(str1,strstr(str4,str2)+strlen(str2));/*strstr(str4,str2)是指向str2及以后的内容(包括str2),strstr(str4,str2)+strlen(str2)就是将指针向前移动strlen(str2)位，跳过str2*/  
	}   
}  
/*将str1出现的所有的str2都替换为str3*/  
void replace1(char *str1,char *str2,char *str3)  
{  
	while(strstr(str1,str2)!=NULL)  
	{   
		replaceFirst1(str1,str2,str3);  
	}   
}
struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(s->len+1);
    if (s->ptr == NULL) {
        ERRORLOGSG( "malloc() failed");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

int convmsg(char * src, char * des, int srclen, int deslen, const char *srctype, const char *destype)
{
    if (strcmp(srctype, destype) == 0)
    {
        memcpy(des, src, MIN(srclen, deslen));
        return 0;
    }
    iconv_t conv = iconv_open (destype, srctype);
    if(conv == (iconv_t)-1)
    {
        ERRORLOGSG("iconvopen err[%s][%s]", destype, srctype);
        return -1;
    }
    char *in = src;
    char *out = des;
    size_t  avail = deslen;
    size_t insize = srclen;
    char *wrptr = des;
    char *inptr = src;
    while (avail > 0)
    {
        size_t nread = avail;
        size_t nconv;
        //LOG_DEBUG("avail:%d", avail);
        /* Do the conversion.  */
        nconv = iconv (conv, &inptr, &insize, &wrptr, &avail);
        if (nconv == (size_t)-1)
        {
            //INFOLOGSG("iconv end");
            break;
        }
		if( nread == avail )
		{
			wrptr[insize] = inptr[insize];
			inptr += (size_t)1;
			avail --;
		}
    }
    iconv_close (conv);
    return 0;
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
    size_t new_len = s->len + size*nmemb;
    s->ptr = realloc(s->ptr, new_len+1);
    if (s->ptr == NULL) {
        ERRORLOGSG( "realloc() failed");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr+s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size*nmemb;
}

int getHtml( char *strUrl, char *charCode,  char *output_html )
{
    CURL *curl;
    CURLcode res;
    int inlen,outlen;
    struct string s;
    struct curl_slist *chunk = NULL;

    curl = curl_easy_init();
    if(curl) {
        init_string(&s);
        char tmp_html[HTML_BUFFER_SIZE]={0};

        chunk = curl_slist_append(chunk, "Accept-Encoding: gzip, deflate"); 
        //chunk = curl_slist_append(chunk, "User-Agent: Mozilla/6.0 (compatible; MSIE 11.0; Windows NT 5.1; CIBA)");
        //chunk = curl_slist_append(chunk, "User-Agent:Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36" );
        chunk = curl_slist_append(chunk, "User-Agent:Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36" );
        //chunk = curl_slist_append(chunk, "Connection: Keep-Alive");

        curl_easy_setopt(curl, CURLOPT_URL, strUrl);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk );
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
		curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
        res = curl_easy_perform(curl);
        curl_slist_free_all(chunk);
        if( res == CURLE_OK )
        {
            DEBUGLOGSG( "下载网页成功 %s", strUrl );
        }   
        else
        {
            ERRORLOGSG( "下载网页失败 %s", strUrl );
            free(s.ptr);
            return -1;
        }

        strcpy( tmp_html, s.ptr );
        inlen=strlen(tmp_html);
        outlen=strlen(tmp_html);

		//printf( "%s\n", tmp_html );
        int ret = convmsg(tmp_html, output_html, HTML_BUFFER_SIZE, HTML_BUFFER_SIZE, charCode, "utf-8");
		DEBUGLOGSG( "转换网页成功%s", charCode );

		//printf( "%s\n", output_html );

		replace1( output_html, "\\\"", "'" );

        free(s.ptr);

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    return 0;
}

/*int GetCharset(char *src_html,char *charCode) {  
    char tmp_html[HTML_BUFFER_SIZE]={0};  
    int pos = indexOf(src_html, "text/html; charset=");  
    if (pos > 0) {  
        strncpy(tmp_html, src_html + pos + strlen("text/html; charset="), strlen(src_html) - pos);  
        pos = indexOf(tmp_html, "\"");  
        if (pos > 0) {  
            strncpy(charCode, tmp_html, pos);  
        }  
    }  
    return 0;
}
*/ 

