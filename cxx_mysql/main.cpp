#include <iostream>

#include<mysql++/mysql++.h>
#include<mysql++/cmdline.h>


using namespace std;
int main(int argc,char * argv[])
{
    char *db_name="student";
    char *db_server="localhost";
    char *db_user="wjh";
    char *db_pass="190528";
    mysqlpp::Connection conn(false);
    if(conn.connect(db_name,db_server,db_user,db_pass)){

        mysqlpp::Query query =conn.query("select * from stduent_information");
        if(mysqlpp::StoreQueryResult res = query.store()){
            cout<<"result"<<endl;
            mysqlpp::StoreQueryResult::iterator it;
            for(it=res.begin();it!=res.end();++it){

                mysqlpp::Row row =*it;
                for(int i=0;i<row.size();i++){
                    cout<<'\t'<<row[i]<<'\t';
                }
                cout<<'\n';


            }
        }else{
            cerr<<"err_num"<<query.errnum()<<endl;
            cerr<<"failed to get item"<<endl;
        }
    }
    return 0;
}
