.SUFFIXES: .c .o
CC=gcc -shared -fPIC -g 
GCC=gcc

all:lib100ppi.so libdzh.so libccstock.so libcs.so libbjnews.so libsohu.so \
	libstcn.so libliegu.so libjrj.so libcaixin.so libchinatimes.so libjjckb.so libnbd.so libp5w.so \
	libgovcn.so libcnstock.so lib163.so libofweek.so libeastmoney.so libdatianxia.so libfeedtrade.so \
	libtaogutong.so libyicai.so libsina.so libcas.so libchinanews.so libwallstreetcn.so libfarmer.so \
	libsdpc.so libpeople.so libnewscn.so libcnenergy.so libtaoguba.so libjiemian.so libeeo.so libmiit.so \
	libcnr.so libchina.so libynet.so libcecn.so libhuanqiu.so libeastday.so libtzxm.so \
	lib10jqka.so libthepaper.so libbbtnews.so libaastocks.so lib21so.so libcankaoxiaoxi.so libguochengxin.so \
	libtttcai.so libcnbeta.so libithome.so libsmm.so libesmchina.so libcailian.so libdfcfzhibo.so \
	libthszhibo.so libstdaily.so libccgp.so libgglb.so \
	libsimilarity.so libsimilarityc.so \
	gethtml getnews clean

OBJ_gglb=gglb.o mystr.o
OBJ_ccgp=ccgp.o mystr.o
OBJ_stdaily=stdaily.o mystr.o
OBJ_thszhibo=thszhibo.o mystr.o
OBJ_dfcfzhibo=dfcfzhibo.o mystr.o
OBJ_cailian=cailian.o mystr.o
OBJ_esmchina=esmchina.o mystr.o
OBJ_smm=smm.o mystr.o
OBJ_ithome=ithome.o mystr.o
OBJ_cnbeta=cnbeta.o mystr.o
OBJ_tttcai=tttcai.o mystr.o
OBJ_guochengxin=guochengxin.o mystr.o
OBJ_cankaoxiaoxi=cankaoxiaoxi.o mystr.o
OBJ_21so=21so.o mystr.o
OBJ_aastocks=aastocks.o mystr.o
OBJ_bbtnews=bbtnews.o mystr.o
OBJ_thepaper=thepaper.o mystr.o
OBJ_10jqka=10jqka.o mystr.o
OBJ_tzxm=tzxm.o mystr.o
OBJ_eastday=eastday.o mystr.o
OBJ_huanqiu=huanqiu.o mystr.o
OBJ_cecn=cecn.o mystr.o
OBJ_ynet=ynet.o mystr.o
OBJ_china=china.o mystr.o
OBJ_cnr=cnr.o mystr.o
OBJ_miit=miit.o mystr.o
OBJ_eeo=eeo.o mystr.o
OBJ_jiemian=jiemian.o mystr.o
OBJ_taoguba=taoguba.o mystr.o
OBJ_cnenergy=cnenergy.o mystr.o
OBJ_newscn=newscn.o mystr.o
OBJ_people=people.o mystr.o
OBJ_sdpc=sdpc.o mystr.o
OBJ_farmer=farmer.o mystr.o
OBJ_wallstreetcn=wallstreetcn.o mystr.o
OBJ_chinanews=chinanews.o mystr.o
OBJ_cas=cas.o mystr.o
OBJ_ofweek_ee=ofweek_ee.o
OBJ_ofweek=ofweek.o
OBJ_eastmneyreport=eastmoneyreport.o
OBJ_eastmneyreporthyyb=eastmoneyreporthyyb.o
OBJ_datianxia=datianxia.o
OBJ_feedtrade=feedtrade.o
OBJ_taogutong=taogutong.o
OBJ_163=163.o mystr.o
OBJ_sina=sina.o mystr.o
OBJ_yicai=yicai.o
OBJ_cnstock=cnstock.o mystr.o
OBJ_govcn=govcn.o mystr.o
OBJ_p5w=p5w.o mystr.o
OBJ_nbd=nbd.o mystr.o
OBJ_jjckb=jjckb.o mystr.o
OBJ_chinatimes=chinatimes.o mystr.o
OBJ_caixin=caixin.o mystr.o
OBJ_jrj=jrj.o mystr.o
OBJ_liegu=liegu.o mystr.o
OBJ_stcn=stcn.o mystr.o
OBJ_sohu=sohu.o mystr.o
OBJ_bjnews=bjnews.o mystr.o
OBJ_cs=cs.o mystr.o
OBJ_dzh=dzh.o mystr.o
OBJ_ccstock=ccstock.o mystr.o
OBJ_100ppi=100ppi.o mystr.o
OBJ_md5=md5.o
OBJ_main=main.o 
OBJ_log=log.o
OBJ_getnews=getnews.o
OBJ_gethtml=gethtml.o
OBJ_dboperate=dboperate.o mystr.o

libgglb.so:$(OBJ_gglb) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libccgp.so:$(OBJ_ccgp) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libstdaily.so:$(OBJ_stdaily) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libthszhibo.so:$(OBJ_thszhibo) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libdfcfzhibo.so:$(OBJ_dfcfzhibo) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libcailian.so:$(OBJ_cailian) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libesmchina.so:$(OBJ_esmchina) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libsmm.so:$(OBJ_smm) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libithome.so:$(OBJ_ithome) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libcnbeta.so:$(OBJ_cnbeta) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libtttcai.so:$(OBJ_tttcai) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libguochengxin.so:$(OBJ_guochengxin) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libcankaoxiaoxi.so:$(OBJ_cankaoxiaoxi) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

lib21so.so:$(OBJ_21so) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libaastocks.so:$(OBJ_aastocks) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libbbtnews.so:$(OBJ_bbtnews) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libthepaper.so:$(OBJ_thepaper) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

lib10jqka.so:$(OBJ_10jqka) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libtzxm.so:$(OBJ_tzxm) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libeastday.so:$(OBJ_eastday) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libhuanqiu.so:$(OBJ_huanqiu) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libcecn.so:$(OBJ_cecn) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libynet.so:$(OBJ_ynet) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libchina.so:$(OBJ_china) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libcnr.so:$(OBJ_cnr) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libmiit.so:$(OBJ_miit) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libeeo.so:$(OBJ_eeo) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libjiemian.so:$(OBJ_jiemian) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libtaoguba.so:$(OBJ_taoguba) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libcnenergy.so:$(OBJ_cnenergy) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libnewscn.so:$(OBJ_newscn) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libpeople.so:$(OBJ_people) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libsdpc.so:$(OBJ_sdpc) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libfarmer.so:$(OBJ_farmer) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libwallstreetcn.so:$(OBJ_wallstreetcn) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libchinanews.so:$(OBJ_chinanews) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libcas.so:$(OBJ_cas) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

lib100ppi.so:$(OBJ_100ppi) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libdzh.so:$(OBJ_dzh) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libccstock.so:$(OBJ_ccstock) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libcs.so:$(OBJ_cs) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libbjnews.so:$(OBJ_bjnews) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libsohu.so:$(OBJ_sohu) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libjrj.so:$(OBJ_jrj) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libcaixin.so:$(OBJ_caixin) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libofweek.so:$(OBJ_ofweek_ee) $(OBJ_ofweek) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libeastmoney.so:$(OBJ_eastmneyreport) $(OBJ_eastmneyreporthyyb) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libdatianxia.so:$(OBJ_datianxia) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libfeedtrade.so:$(OBJ_feedtrade) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libtaogutong.so:$(OBJ_taogutong) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libyicai.so:$(OBJ_yicai) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

lib163.so:$(OBJ_163) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libsina.so:$(OBJ_sina) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libcnstock.so:$(OBJ_cnstock) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libgovcn.so:$(OBJ_govcn) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libp5w.so:$(OBJ_p5w) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libnbd.so:$(OBJ_nbd) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libjjckb.so:$(OBJ_jjckb) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libchinatimes.so:$(OBJ_chinatimes) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libliegu.so:$(OBJ_liegu) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

libstcn.so:$(OBJ_stcn) $(OBJ_md5) $(OBJ_log)
	$(CC) -o $@ $?
	cp $@ /usr/lib

getnews:$(OBJ_getnews) $(OBJ_log)
	$(GCC) -o $@ $? -ldl -lmysqlclient -liLOG3 -lpthread 

gethtml:$(OBJ_gethtml) $(OBJ_dboperate) $(OBJ_md5) $(OBJ_log) $(OBJ_main)
	$(GCC) -o $@ $? -ldl -lmysqlclient -liLOG3 -lcurl -liconv -I/usr/local/include/iLOG3/ -I/usr/local/libiconv/include/ -L/usr/local/libiconv/lib/ -lsimilarityc

libsimilarity.so:
	g++ similarity.cpp -fpic -shared -o libsimilarity.so -I/usr/include/mysql -lmysqlclient
	cp libsimilarity.so /usr/lib

libsimilarityc.so:
	g++ -fpic -shared -o libsimilarityc.so similarity_c.cpp -lsimilarity
	cp libsimilarityc.so /usr/lib

.c.o:
	$(CC) -c $*.c -std=c99 -I/usr/local/include/iLOG3/ -I/usr/include/mysql -liLOG3 -lmysqlclient -L/usr/local/libiconv/lib/ -liconv -I/usr/local/libiconv/include/

clean:
	rm -f *.o *.so
