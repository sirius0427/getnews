#include <stdio.h>
#include <stdlib.h>

#include "LOGS.h"
#include <mysql.h>
#include <dlfcn.h>
#include "NewsInfo.h"

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

void collectmethod(struct c_rule *arg)
{ 
	BEGINLOG();
	char command[33];

	INFOLOGSG( "线程启动成功[%s][%s],频率[%d]", arg->library, arg->method, arg->frequency);
	sleep( 10 );
	if( arg->frequency == 0 )
	{
		ERRORLOGSG( "频率不能为空[%d]", arg->frequency );
	}
	if( strcmp( arg->id, "" ) == 0 )
	{
		return;
	}
	sprintf( command, "%s %s", "./gethtml", arg->id ); 
	DEBUGLOGSG( command );
	while(1)
	{
		system( command );

		DEBUGLOGSG( "frequency[%d]", arg->frequency );
		if( arg->frequency == 0 )
		{
			sleep(60);
		}
		sleep(arg->frequency);

		/*handle = dlopen (arg1->library, RTLD_NOW);     //打开数据库中指定的动态库
		  if (!handle)
		  {
		  ERRORLOGSG ( "%s\n", dlerror());
		  exit(1);
		  }
		  dlerror();
		  pf_t pf=(pf_t)dlsym(handle, arg1->method );    //指针pf指向数据库中函数在当前内存中的地址
		  if ((error = dlerror()) != NULL) 
		  {
		  ERRORLOGSG( "%s\n", error);
		  exit(1);
		  }
		  int ret = pf( &arg1 );        //通过指针pf的调用来调用动态库中的test函数
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
		 */

	}

}

int getNewsInfo( void )
{
	MYSQL *conn_ptr;
	MYSQL_RES *mysqlresult;
	MYSQL_ROW mysqlrow;
	int x,y,numrow,numcol,result;
	char sql_select_data[300]="SELECT * FROM c_collectionrule where state='1'";
	conn_ptr = mysql_init(NULL);
	/*void *handle;
	  char *error;
	  typedef int (*pf_t)();   //声明函数指针类型
	 */

	if(!conn_ptr)
	{
		ERRORLOGSG( "mysql_init failed" );
		return -1;
	}

	conn_ptr = mysql_real_connect(conn_ptr,"localhost","cst","q1w2e3r4t5Y^U&I*O(P)","zyg",0,NULL,0);
	if(conn_ptr)
	{
		INFOLOGSG("Connection success");
		mysql_query(conn_ptr,"set names utf8");
		result = mysql_query(conn_ptr,sql_select_data); //查询数据
		if(result)
		{
			ERRORLOGSG( "mysql_query select data error %u: %s", mysql_errno(conn_ptr), mysql_error(conn_ptr));
			return -1;
		}
		else
		{
			INFOLOGSG("select data success");
			mysqlresult = mysql_store_result(conn_ptr);
			if(mysqlresult){
				numrow = mysql_num_rows(mysqlresult);
				numcol = mysql_num_fields(mysqlresult);
				pthread_t collectthread[numrow];
				void *thread_return[numrow];
				struct c_rule arg[numrow];
				DEBUGLOGSG( "numrow[%d]numcol[%d]", numrow, numcol );
				for(x=0; x<numrow; x++)
				{
					mysqlrow = mysql_fetch_row(mysqlresult);
					for(y=0; y<numcol; y++)
					{
						//DEBUGLOGSG("[mysqlrow[%d]:%-8s", y, mysqlrow[y]);
					}
					strcpy( arg[x].id, mysqlrow[0] );
					strcpy( arg[x].rulename, mysqlrow[1] );
					strcpy( arg[x].url, mysqlrow[2] );
					strcpy( arg[x].encoding, mysqlrow[3] );
					strcpy( arg[x].state, mysqlrow[4] );
					strcpy( arg[x].library, mysqlrow[6] );
					strcpy( arg[x].method, mysqlrow[7] );
					if( strcmp( mysqlrow[8], "" ) == 0)
					{
						ERRORLOGSG( "[%s]的频率不能为空", arg[x].rulename );
						arg[x].frequency=60;
					}
					else
						arg[x].frequency= atoi(mysqlrow[8]);
					INFOLOGSG( "取数据库[%d][%s]", x , arg[x].rulename );
				}
				mysql_close(conn_ptr);
				for(x=0; x<numrow; x++)
				{
					int ret=0;
					ret = pthread_create(&collectthread[x],NULL,(void *) collectmethod,(void *)&arg[x] );
					if(ret!=0){
						ERRORLOGSG("Create pthread error!\n");
						return -1;
					}

					/*
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
					   int ret = pf( mysqlrow[2], mysqlrow[3], mysqlrow[8]);        //通过指针pf的调用来调用动态库中的test函数
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
					 */
					INFOLOGSG( "create pthread [%d] end", x );
				}
				for( x=0; x<numrow; x++)
				{
					INFOLOGSG( "wait pthread [%d] ", x );
					pthread_join(collectthread[x],&thread_return[x]);
					INFOLOGSG( "wait pthread [%d] end", x );
				}
			}

		}
	}
	else
	{
		ERRORLOGSG("Connection failed");
		return -1;
	}


	return 0;
}

int main()
{
	BEGINLOG();

	int ret = getNewsInfo( );
	if( ret != 0 )
	{
		ERRORLOGSG( "取新闻程序执行失败" );
	}

	ENDLOG();
	return 0;
}
