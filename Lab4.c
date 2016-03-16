//
//  Lab4.c
//  TP_Lab4
//
//  Created by Admin on 16.03.16.
//  Copyright © 2016 Admin. All rights reserved.

#include <sqlite3.h>
#include <stdio.h>

int main(void) {
    
    sqlite3 *vdb;
    //sqlite3_stmt *res;
    
    int rc = sqlite3_open("data.vdb", &vdb);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(vdb));
        sqlite3_close(vdb);
        
        return 1;
    }
    else printf ("Open");
    /*
    rc = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &res, 0);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    
    rc = sqlite3_step(res);
    
    if (rc == SQLITE_ROW) {
        printf("%s\n", sqlite3_column_text(res, 0));
    }
    
    sqlite3_finalize(res);*/
    sqlite3_close(vdb);
    
    return 0;
}