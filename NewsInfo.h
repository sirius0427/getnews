#ifndef _NewsInfo_H_
#define _NewsInfo_H_
struct NewsInfo {
	char id[100+1];
	char title[2000+1];
	char stat[16+1];
	char content[9000+1];
	char collectiontime[32+1];
	char sourceaddr[1000+1];
	char sourcename[200+1];
	char newsreleasetime[200+1];
	char articleauthor[200+1];
	char releasetime[32+1];
	char inforscreenperson[32+1];
	char informationpublisher[32+1];
	int countpage;
	char digest[2000+1];
	char collectionruleid[45+1];
	char timegeneplace[20+1];
	char authorgeneplace[20+1];
	char publishpersonid[45+1];
	char publishperson[45+1];
	char checkreleaseid[45+1];
	char checkrelease [45+1];
	char sectiontype[45+1];
	char collectionstatus[45+1];
	char chosetimestamp[400+1];
	char checktimestamp[400+1];
	char dispatchtimestamp[400+1];
	int articletype;
	char releasesourcename[200+1];
	char releasetitle[2000+1];
	char stocksinfo[2000+1];
	char releaseadd[2000+1];
	char encoding[100+1];
};

void BEGINLOG( void );
void ENDLOG( void );
int indexOf( char *, char * );
int Compute_string_md5( char *, char * );
void replace( char *, char * , char *);
void trim( char * );
int getHtml( char *, char *, char (*)[] );
#endif
