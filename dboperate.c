#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include "LOGS.h"
#include "NewsInfo.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>

#define BUFFER_SIZE 2000
double c_similarity( char * );

int insertSql(struct NewsInfo *s, int num)
{
	MYSQL *conn_ptr;
	MYSQL_RES *mysqlresult;
	MYSQL_ROW mysqlrow;

	int x,y,numrow,numcol,result;
	char sql_select_data[300]={0};
	char sql_insert_data[1024*8]={0};
	int ret=0,succnum=0,dupnum=0;
	double simmax=0.00;
	char tmp_msg[2000],output_msg[2000];
	char tmpstr[1024];

	char buf[BUFFER_SIZE];
	int client_sockfd,len;
	struct sockaddr_in *address=(struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));// 服务器端网络地址结构体

	client_sockfd = socket(AF_INET, SOCK_STREAM, 0);// 建立客户端socket                                 
	address->sin_family = AF_INET;
	address->sin_addr.s_addr = inet_addr("127.0.0.1");
	address->sin_port = htons(8080);
	len = sizeof(struct sockaddr_in);

	int on=1;
	if((setsockopt(client_sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)
	{
		perror("setsockopt failed");
		exit(EXIT_FAILURE);
	}


	conn_ptr = mysql_init(NULL);

	if(!conn_ptr)
	{
		ERRORLOGSG("mysql_init failed");
		return EXIT_FAILURE;
	}
	DEBUGLOGSG( "mysql_init success" );

	conn_ptr = mysql_real_connect(conn_ptr,"localhost","cst","q1w2e3r4t5Y^U&I*O(P)","zyg",3306,NULL,0);

	if(conn_ptr)
	{
		DEBUGLOGSG("mysql connection success" );
		mysql_query(conn_ptr,"set names utf8");
		for( int n=0; n<num; n++){
			sprintf( sql_select_data, "SELECT * FROM newsinfo where id = '%s' union all select * from newsinfo_dup where id = '%s'", s[n].id, s[n].id );
			DEBUGLOGSG("%s", sql_select_data);
			result = mysql_query(conn_ptr,sql_select_data);	

			if(result)
			{
				ERRORLOGSG( "mysql_query select data error %u: %s", mysql_errno(conn_ptr), mysql_error(conn_ptr));
				return -1;
			}
			else
			{
				//LOG_TRACE("select data success");
				mysqlresult = mysql_store_result(conn_ptr);
				if(mysqlresult){
					numrow = mysql_num_rows(mysqlresult);
					DEBUGLOGSG( "select row number[%d][%s]",  numrow, s[n].id );
					if(numrow == 0)	//if not have collect before then insert
					{
						replace( s[n].title, "'", "\"\"" );
						replace( s[n].title, "\"\"", "''" );

						// 与远程服务器建立连接  
						//result = connect(client_sockfd, (struct sockaddr *)&address, len);
						if( succnum != 0 )	//如果不是第一次，则把老的连接先关掉，再重新开新连接
						{
							close(client_sockfd);
							address->sin_addr.s_addr = inet_addr("127.0.0.1");
							address->sin_port = htons(8080);
						}

						client_sockfd = socket(AF_INET, SOCK_STREAM, 0);// 建立客户端socket                                 
						result = connect(client_sockfd, (struct sockaddr *)address, len);
						if(result<0)
						{
							perror("connect failed");
							exit(EXIT_FAILURE);
						}

						if( strlen(s[n].title)>=801 ) 
						{
							strncpy( tmpstr, s[n].title, 801 );
							send(client_sockfd,tmpstr,sizeof(tmpstr),0);
						}
						else
							send(client_sockfd,s[n].title,sizeof(s[n].title),0);
						recv(client_sockfd,s[n].content,BUFFER_SIZE,0);
						INFOLOGSG( "socket recv:%s", s[n].content );

						if( s[n].countpage != 1 )
						{
							simmax = c_similarity( s[n].content );
							INFOLOGSG( "max similarity:%f", simmax );

							if( simmax > 0.5 )
							{
								sprintf( sql_insert_data, "insert into newsinfo_dup values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%d','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%d','%s','%s','%s','%s','%s')",
										s[n].id,s[n].title,s[n].stat,s[n].content,s[n].collectiontime,s[n].sourceaddr,
										s[n].sourcename,s[n].newsreleasetime,s[n].articleauthor,s[n].releasetime,s[n].inforscreenperson,
										s[n].informationpublisher,s[n].countpage,s[n].digest,s[n].collectionruleid,s[n].timegeneplace,
										s[n].authorgeneplace,s[n].publishpersonid,s[n].publishperson,s[n].checkreleaseid,s[n].checkrelease,
										s[n].sectiontype,s[n].collectionstatus,s[n].chosetimestamp,s[n].checktimestamp,s[n].dispatchtimestamp,
										s[n].articletype,s[n].releasesourcename,s[n].releasetitle,s[n].stocksinfo,s[n].releaseadd,s[n].encoding);
							}
							else
							{
								sprintf( sql_insert_data, "insert into newsinfo values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%d','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%d','%s','%s','%s','%s','%s')",
										s[n].id,s[n].title,s[n].stat,s[n].content,s[n].collectiontime,s[n].sourceaddr,
										s[n].sourcename,s[n].newsreleasetime,s[n].articleauthor,s[n].releasetime,s[n].inforscreenperson,
										s[n].informationpublisher,s[n].countpage,s[n].digest,s[n].collectionruleid,s[n].timegeneplace,
										s[n].authorgeneplace,s[n].publishpersonid,s[n].publishperson,s[n].checkreleaseid,s[n].checkrelease,
										s[n].sectiontype,s[n].collectionstatus,s[n].chosetimestamp,s[n].checktimestamp,s[n].dispatchtimestamp,
										s[n].articletype,s[n].releasesourcename,s[n].releasetitle,s[n].stocksinfo,s[n].releaseadd,s[n].encoding);
							}
						}
						else {
							sprintf( sql_insert_data, "insert into newsinfo values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%d','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%d','%s','%s','%s','%s','%s')",
									s[n].id,s[n].title,s[n].stat,s[n].content,s[n].collectiontime,s[n].sourceaddr,
									s[n].sourcename,s[n].newsreleasetime,s[n].articleauthor,s[n].releasetime,s[n].inforscreenperson,
									s[n].informationpublisher,s[n].countpage,s[n].digest,s[n].collectionruleid,s[n].timegeneplace,
									s[n].authorgeneplace,s[n].publishpersonid,s[n].publishperson,s[n].checkreleaseid,s[n].checkrelease,
									s[n].sectiontype,s[n].collectionstatus,s[n].chosetimestamp,s[n].checktimestamp,s[n].dispatchtimestamp,
									s[n].articletype,s[n].releasesourcename,s[n].releasetitle,s[n].stocksinfo,s[n].releaseadd,s[n].encoding);
						}
						if( strlen(sql_insert_data)<=400 )
						{
							INFOLOGSG(sql_insert_data);
						}
						else if( strlen(sql_insert_data) > 400 )
						{
							INFOLOGSG("SQL TOO LONG:%s %s", s[n].id, s[n].title );
						}
						result = mysql_query(conn_ptr,sql_insert_data);	//insert data
						if(result)
						{
							ERRORLOGSG( "mysql_query insert data error %u: %s", mysql_errno(conn_ptr), mysql_error(conn_ptr));
							return -1;
						}
						else
						{
							DEBUGLOGSG( "insert successful");
							succnum++;
						}

						if( s[n].stat[0] == '5' && simmax <= 0.5)
						{
							/* 发送QQ，已封
							address->sin_addr.s_addr = inet_addr("192.168.199.209");
							address->sin_port = htons(5700);
							client_sockfd = socket(AF_INET, SOCK_STREAM, 0);// 建立客户端socket                                 
							result = connect(client_sockfd, (struct sockaddr *)address, len);
							if(result<0)
							{
								perror("connect failed");
								exit(EXIT_FAILURE);
							}
							memset( tmp_msg, 0x00, sizeof( tmp_msg ));
							time_t now; //实例化time_t结构    
							struct tm *timenow; //实例化tm结构指针    
							time(&now);   //time函数读取现在的时间(国际标准时间非北京时间)，然后传值给now    
							timenow = localtime(&now);   //  //localtime函数把从time取得的时间now换算成你电脑中的时间(就是你设置的地区)    

							sprintf( tmp_msg, "%s %s %s %s", asctime(timenow), s[n].title, s[n].sourcename, s[n].sourceaddr ); 
							INFOLOGSG( "SEND QQ:%s", s[n].title );
							convmsg(tmp_msg, output_msg, BUFFER_SIZE, BUFFER_SIZE, "utf-8", "gbk");
							send(client_sockfd,output_msg,sizeof(output_msg),0);
							recv(client_sockfd,tmp_msg,BUFFER_SIZE,0);
							close(client_sockfd);
							*/
						}
					}
					else
					{
						dupnum ++ ;
					}
				}
			}
		}

	}
	else
	{
		ERRORLOGSG( "mysql connect failed %s", mysql_error(conn_ptr));
	}

	DEBUGLOGSG( "insert end" );
	close(client_sockfd);
	free(address);
	mysql_close(conn_ptr);
	if( succnum > 0 )
	{
		return succnum;
	}
	else
	{
		return dupnum;
	}
}
