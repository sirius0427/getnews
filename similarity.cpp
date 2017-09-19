/****************************************************************************
*  					 			NiuParser SDK   					
*					
* 				Copyright (c) 2014-2015 NiuParser All rights reserved.
*
*							niuparser@zjyatuo.com
*  				
****************************************************************************/





#include "stringlib.h"
#include "hashlib.h"
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include <mysql.h>
#include <math.h>
#include <cstring>

using namespace std;

double similarity( char *input)
{

	MYSQL *conn_ptr;
	MYSQL_RES *mysqlresult;
	MYSQL_ROW mysqlrow;
	clock_t start_time;

	int x,y,numrow,numcol,result;
	double sim,simmax=0.00; 
	char sql_select_data[300];
	memset( sql_select_data, 0x00, sizeof( sql_select_data ));
	strcpy( sql_select_data, "SELECT content FROM `newsinfo` where collectiontime > UNIX_TIMESTAMP(ADDDATE(NOW(),INTERVAL -1 DAY))*1000 and articletype='1' and content<>'' order by collectiontime desc limit 1000" );

	string str1;
	string str2,strmax;

	str1.assign(input);

	conn_ptr = mysql_init(NULL);
	if(!conn_ptr)
	{
		cerr<<"mysql_init failed"<<endl;
		exit(-1);
	} 

	conn_ptr = mysql_real_connect(conn_ptr,"localhost","cst","q1w2e3r4t5Y^U&I*O(P)","zyg",3306,NULL,0);
	if(conn_ptr)
	{
		//cerr<<"mysql connection success"<<endl;
		mysql_query(conn_ptr,"set names utf8");
		result = mysql_query(conn_ptr,sql_select_data);
		if(result)
		{
			cerr<<"mysql_query select data error"<<endl;
			return -1;
		}
		else
		{
			start_time = clock();
			mysqlresult = mysql_store_result(conn_ptr);
			numrow = mysql_num_rows(mysqlresult);
			for(x=0; x<numrow; x++)
			{
				mysqlrow = mysql_fetch_row(mysqlresult);
				str2.assign(mysqlrow[0]);
				if( str2 == "" ) 
					continue;

				sim = fnCalculateSimilarity(str1, str2);

				if( sim > simmax )
				{
					simmax=sim;
					strmax=str2;
				}

			}
			mysql_close(conn_ptr);
		}
	}
	//cerr<<"NiuParser Successfully ! Total: "<<numrow<<" Similarity:"<<simmax<<" Use "<<((double)(clock()-start_time)) / CLOCKS_PER_SEC<<" s "<<endl;
	cerr<<"[simmax:]"<< simmax <<endl;
	cerr<<"title:"<< str1 <<endl;
	cerr<<"max Similar title:"<< strmax <<endl;

	return simmax;
}
