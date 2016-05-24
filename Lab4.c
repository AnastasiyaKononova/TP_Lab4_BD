//
//  Lab4.c
//  TP_Lab4
//
//  Created by Admin on 15.03.16.
//  Copyright © 2016 Admin. All rights reserved.

#include <sqlite3.h>
#include <stdio.h>

static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main(void) {
    
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    
    const char* data = "Callback function called";
    
    rc = sqlite3_open("data1.db", &db);
    
    if( rc )
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
    }
    
    char operation;
    int stop = 0;
    
    while(stop == 0)
    {
        printf("Choose operation:\n1-operation INSERT\n2-operation SELECT\n3-operation DELETE\n4-parameterized querie\n5-display photo\n6-transaction insert\n7-autocommit\n8-stop\n");
        
        scanf("%s", &operation);
        
        switch(operation)
        {
        
            case '1': //INSERT
            {
                char s[40];
            
                char sql[500] = "INSERT INTO department (id, firstname, secondname, lastname, date_of_birth, town_of_birth, country_of_birth, addres, office, current_position, date_of_admission) values (";
            
                printf("Input values to insert:\n");
                printf("firstname: ");
                scanf("%s", s);
                strcat(sql, s);
                strcat(sql, "', '");
                printf("secondname: ");
                scanf("%s", s);
                strcat(sql, s);
                strcat(sql, "', '");
                printf("lastname: ");
                scanf("%s", s);
                strcat(sql, s);
                strcat(sql, "', '");
                printf("birth: ");
                scanf("%s", s);
                strcat(sql, s);
                strcat(sql, "', '");
                printf("town: ");
                scanf("%s", s);
                strcat(sql, s);
                strcat(sql, "', '");
                printf("country: ");
                scanf("%s", s);
                strcat(sql, s);
                strcat(sql, "', '");
                printf("address: ");
                scanf("%s", s);
                strcat(sql, s);
                strcat(sql, "', '");
                printf("id: ");
                scanf("%s", s);
                strcat(sql, s);
                strcat(sql, "', '");
                printf("department: ");
                scanf("%s", s);
                strcat(sql, s);
                strcat(sql, "', '");
                printf("post: ");
                scanf("%s", s);
                strcat(sql, s);
                strcat(sql, "', '");
                printf("admission: ");
                scanf("%s", s);
                strcat(sql, s);
                strcat(sql, "');");
                printf("\n");
            
                rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
                if( rc != SQLITE_OK )
                {
                    fprintf(stderr, "SQL error: %s\n", zErrMsg);
                    sqlite3_free(zErrMsg);
                }
                else
                {
                    fprintf(stdout, "Records created successfully\n");
                }
            
            }
                break;
                
        case '2'://SELECT
        {
            /* Create SQL statement */
            char sql4[500] = "SELECT * from employees";
    
            /* Execute SQL statement */
            rc = sqlite3_exec(db, sql4, callback, (void*)data, &zErrMsg);
            if( rc != SQLITE_OK )
            {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }
            else
            {
                fprintf(stdout, "Operation done successfully\n");
            }
        }
                break;
                
        case '3'://DELETE
        {
            char id[50];
    
            printf("Input id: ");
            scanf("%s", id);
    
            char sql1[500] = "DELETE from employees where id = ";
    
            strcat(sql1, id);
            strcat(sql1, ";");
    
            rc = sqlite3_exec(db, sql1, callback, (void*)data, &zErrMsg);
    
            if( rc != SQLITE_OK )
            {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }
            else
            {
                fprintf(stdout, "Operation done successfully\n");
            }
        
        }
                break;
    
        case '4'://parameterized querie
        {
            int a = 0;
            printf("Choose parameter:\n1 - id\n2 - firstname\n3 - secondname\n4 - lastname\n");
            scanf("%d", &a);
    
            char param[50];
            printf("Input value of parameter:\n");
            scanf("%s", param);
    
            if(a == 1)
            {
                char sql2[500] = "SELECT * from employees where id = ";
                strcat(sql2, param);
                strcat(sql2, ";");
                rc = sqlite3_exec(db, sql2, callback, (void*)data, &zErrMsg);
            }
            if(a == 2)
            {
                char sql2[500] = "SELECT * from employees where firstname = '";
                strcat(sql2, param);
                strcat(sql2, "';");
                rc = sqlite3_exec(db, sql2, callback, (void*)data, &zErrMsg);
            }
            if(a == 3)
            {
                char sql2[500] = "SELECT * from employees where secondname = '";
                strcat(sql2, param);
                strcat(sql2, "';");
                rc = sqlite3_exec(db, sql2, callback, (void*)data, &zErrMsg);
            }
            if(a == 4)
            {
                char sql2[500] = "SELECT * from employees where lastname = '";
                strcat(sql2, param);
                strcat(sql2, "';");
                rc = sqlite3_exec(db, sql2, callback, (void*)data, &zErrMsg);
            }
            if(a == 5)
            {
                char sql2[500] = "SELECT * from employees where country = '";
                strcat(sql2, param);
                strcat(sql2, "';");
                rc = sqlite3_exec(db, sql2, callback, (void*)data, &zErrMsg);
            }
    
            if( rc != SQLITE_OK )
            {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }
            else
            {
                fprintf(stdout, "Operation done successfully\n");
            }
            
        }
                break;
    
        case '5'://photo
        {
            FILE *fp = fopen("file.jpg", "wb");
    
            char id2[100];
    
            printf("Input id: ");
            scanf("%s", id2);
    
            char sql3[500] = "SELECT photo from employees where id = ";
            strcat(sql3, id2);
            strcat(sql3, ";");
    
            sqlite3_stmt *pStmt;
    
            rc = sqlite3_prepare_v2(db, sql3, -1, &pStmt, 0);
    
            if( rc != SQLITE_OK )
            {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }
            else
            {
                fprintf(stdout, "Operation done successfully\n");
            }
    
            rc = sqlite3_step(pStmt);
    
            int bytes = 0;
    
            if(rc == SQLITE_ROW)
            {
                bytes = sqlite3_column_bytes(pStmt, 0);
            }
    
            fwrite(sqlite3_column_blob(pStmt, 0), bytes, 1, fp);
    
            if(ferror(fp))
            {
                fprintf(stderr, "fwrite () failed\n");
                return 1;
            }
    
            int r = fclose(fp);
    
            if(r == EOF)
            {
                fprintf(stderr, "Cannot close file handler\n");
            }
    
            rc = sqlite3_finalize(pStmt);
        }
                break;
    
        case '6'://transaction
        {
    
    char sql[500] = "BEGIN TRANSACTION; INSERT INTO employees(firstname, secondname, lastname, birth, town, country, address, id, department, post, admission) values (";
    
    char buf[50];
    
    fprintf(stdout, "firstname: ");
    scanf("%s", buf);
    strcat(sql, buf);
    strcat(sql, "', '");
    fprintf(stdout, "secondname: ");
    scanf("%s", buf);
    strcat(sql, buf);
    strcat(sql, "', '");
    fprintf(stdout, "lastname: ");
    scanf("%s", buf);
    strcat(sql, buf);
    strcat(sql, "', '");
    fprintf(stdout, "birth: ");
    scanf("%s", buf);
    strcat(sql, buf);
    strcat(sql, "', '");
    fprintf(stdout, "town: ");
    scanf("%s", buf);
    strcat(sql, buf);
    strcat(sql, "', '");
    fprintf(stdout, "country: ");
    scanf("%s", buf);
    strcat(sql, buf);
    strcat(sql, "', '");
    fprintf(stdout, "address: ");
    scanf("%s", buf);
    strcat(sql, buf);
    strcat(sql, "', '");
    fprintf(stdout, "id: ");
    scanf("%s", buf);
    strcat(sql, buf);
    strcat(sql, ", '");
    fprintf(stdout, "department: ");
    scanf("%s", buf);
    strcat(sql, buf);
    strcat(sql, "', '");
    fprintf(stdout, "post: ");
    scanf("%s", buf);
    strcat(sql, buf);
    strcat(sql, "', '");
    fprintf(stdout, "admission: ");
    scanf("%s", buf);
    strcat(sql, buf);
    strcat(sql, "');COMMIT;");
    
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "End of inserting.\n");
    }
        }
        break;

        case '7'://autocommit
        {
            fprintf(stdout, "By default, sqlite version 3 operates in autocommit mode.\n");
            printf("Autocommit: %d\n", sqlite3_get_autocommit(db));
    
            if(operation == 8)//stop
            {
                stop = 1;
            }
        }
                break;
        }
    }
    sqlite3_close(db);
    
    return 0;
}