#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "LOGS.h"
#include <mysql.h>
#include <dlfcn.h>
#include "NewsInfo.h"
#define HTML_BUFFER_SIZE 1024*800

struct c_rule
{
	char id[32+1];
	char rulename[255+1];
	char url[1000+1];
	char encoding[20+1];
	char state[20+1];
	char lastupdate[100+1];
	char library[255+1];
	char method[255+1];
	int frequency;
};

int main( int argc, char *argv[])
{
	struct c_rule c_rule1;
	MYSQL *conn_ptr;
	MYSQL_RES *mysqlresult;
	MYSQL_ROW mysqlrow;
	int x,y,numrow,numcol,result,ret;
	char sql_select_data[300];
	char sql_update_data[300];
	//"SELECT * FROM c_collectionrule";
	char output_html[HTML_BUFFER_SIZE]={0};
	struct NewsInfo s[100];

	void *handle;
	char *error;
	typedef int (*pf_t)();   //声明函数指针类型


	sprintf( sql_select_data, "SELECT * FROM c_collectionrule where id='%s'", argv[1] );

	BEGINLOG();
	conn_ptr = mysql_init(NULL);
	if(!conn_ptr)
	{
		ERRORLOGSG( "mysql_init failed" );
		return -1;
	}
	conn_ptr = mysql_real_connect(conn_ptr,"localhost","cst","q1w2e3r4t5Y^U&I*O(P)","zyg",0,NULL,0);
	if(conn_ptr)
	{
		mysql_query(conn_ptr,"set names utf8");
		result = mysql_query(conn_ptr,sql_select_data); //查询数据
		if(result)
		{
			ERRORLOGSG( "mysql_query select data error %u: %s", mysql_errno(conn_ptr), mysql_error(conn_ptr));
			return -1;
		}
		else
		{
			mysqlresult = mysql_store_result(conn_ptr);
			if(mysqlresult){
				numrow = mysql_num_rows(mysqlresult);
				numcol = mysql_num_fields(mysqlresult);
				mysqlrow = mysql_fetch_row(mysqlresult);
				/*strcpy( c_rule1[x]->id, mysqlrow[0] );
				  strcpy( c_rule1[x]->rulename, mysqlrow[1] );
				  strcpy( c_rule1[x]->url, mysqlrow[2] );
				  strcpy( c_rule1[x]->encoding, mysqlrow[3] );
				  strcpy( c_rule1[x]->state, mysqlrow[4] );
				  strcpy( c_rule1[x]->library, mysqlrow[6] );
				  strcpy( c_rule1[x]->method, mysqlrow[7] );
				  c_rule1[x]->frequency= atoi(mysqlrow[8]);
				  */
			}
			else
			{
				ERRORLOGSG( "取mysql数据失败" );
				mysql_close(conn_ptr);
				return -1;
			}
		}
		mysql_close(conn_ptr);
	}
	else
	{
		ERRORLOGSG( "连接数据库错%u: %s", mysql_errno(conn_ptr), mysql_error(conn_ptr));
		return -1;
	}

	INFOLOGSG( "downhtml[%s],encoding[%s]", mysqlrow[2], mysqlrow[3] );
	ret = getHtml( mysqlrow[2], mysqlrow[3], &output_html );
	if( ret != 0 )
	{
		//mysql_close(conn_ptr);
		ENDLOG();
		return 0;
	}

	handle = dlopen (mysqlrow[6], RTLD_NOW);     //打开数据库中指定的动态库
	if (!handle)
	{
		ERRORLOGSG ( "%s\n", dlerror());
		exit(1);
	}
	dlerror();
	pf_t pf=(pf_t)dlsym(handle,mysqlrow[7] );    //指针pf指向数据库中函数在当前内存中的地址
	if ((error = dlerror()) != NULL) 
	{
		ERRORLOGSG( "%s\n", error);
		exit(1);
	}
	ret = pf( &output_html, &s );        //通过指针pf的调用来调用动态库中的test函数
	if( ret == 0 )
	{
		INFOLOGSG( "执行函数[%s]成功，未产生记录", mysqlrow[7] );
	}
	else if( ret > 0 )
	{
		INFOLOGSG( "执行函数[%s]成功，产生[%d]条记录", mysqlrow[7], ret );
	}
	else
	{
		ERRORLOGSG( "执行函数[%s]失败", handle,mysqlrow[7] );
	}
	dlclose(handle);      //关闭调用动态库句柄

	int num = insertSql( &s, ret );
	INFOLOGSG( "插入记录结束，成功[%d]条", num );

	conn_ptr = mysql_init(NULL);
	if(!conn_ptr)
	{
		ERRORLOGSG( "mysql_init failed" );
		return -1;
	}
	conn_ptr = mysql_real_connect(conn_ptr,"localhost","cst","q1w2e3r4t5Y^U&I*O(P)","zyg",0,NULL,0);
	if(conn_ptr)
	{
		if( num >0 )
		{
			sprintf( sql_update_data, "update c_collectionrule set lastupdate=now(),lastexectime=now() where id='%s'", mysqlrow[0] );
			DEBUGLOGSG( "%s", sql_update_data );
			if( mysql_query(conn_ptr,sql_update_data) ) //修改数据
			{
				ERRORLOGSG( "修改c_collectionrule失败%s", mysql_error(conn_ptr));
			}
		}
		else
		{
			sprintf( sql_update_data, "update c_collectionrule set lastexectime=now() where id='%s'", mysqlrow[0] );
			DEBUGLOGSG( "%s", sql_update_data );
			if( mysql_query(conn_ptr,sql_update_data) ) //修改数据
			{
				ERRORLOGSG( "修改c_collectionrule失败%s", mysql_error(conn_ptr));
			}
		}
	}
	else
	{
		ERRORLOGSG( "连接数据库错%u: %s", mysql_errno(conn_ptr), mysql_error(conn_ptr));
		return -1;
	}

	mysql_close(conn_ptr);
	ENDLOG();
	return 0;
}
