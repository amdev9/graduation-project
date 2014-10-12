#include <iostream>
 #include <postgresql/libpq-fe.h>
 #include <string>
#include <cstdlib>
  
  int     main() {
	    PGconn          *conn;
  		PGresult        *res;
        int             rec_count;
        int             row;
 		int             col;
    //***
    int number = 0;
    bool lab = false;
   // string name;
 
         conn = PQconnectdb("dbname=gaschedule_development host=localhost user=alex password=alex");
 
         if (PQstatus(conn) == CONNECTION_BAD) {
                 puts("We were unable to connect to the database");
          
      }
 
     
 
         res = PQexec(conn,
                 "select * from rooms order by id");
       if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                        puts("We did not get any data!");
                  
        }
         rec_count = PQntuples(res);

        // printf("We received %d records.\n", rec_count);
      //   puts("==========================");

       //for (row=0; row<rec_count; row++) {
                //for (col=0; col<4; col++) {
                   
                      printf("%d\t", atoi(PQgetvalue(res, 0, 3)));
              // }
               

               puts("");
       // }
      //  puts("==========================");
 
         PQclear(res);

     PQfinish(conn);
          return 0;
 }
