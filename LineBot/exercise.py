import pymysql

import pandas as pd
from datetime import datetime, timezone, timedelta

def exercise(linebotID):
    ### 資料庫參數設定
    # 開啟資料庫連線
    connection = pymysql.connect(host=host, user=username, password=password, database=database)
    # 使用 cursor() 方法建立一個遊標物件 cursor
    cursor = connection.cursor()

    print("Database 連線成功。")

    sql = """
        SELECT *
        FROM linebot_userid
        WHERE linebotID = {}
        """.format('\''+linebotID+'\'')
    cursor.execute(sql) # id userID courseID account name linebotID

    results = cursor.fetchall()

    student = pd.DataFrame(results)
    col_names = [row[0] for row in cursor.description] # 取得欄位

    if len(student) > 0: # 有 userID
        student.columns = col_names
    
    else:
        # 關閉游標物件
        cursor.close()
        # 關閉資料庫連線
        connection.close()

        return False, student

    userID = student.loc[0,'userID']
    classID = student.loc[0,'courseID']
    
    # 關閉游標物件
    cursor.close()
    # 關閉資料庫連線
    connection.close()

    database = "moocweb_2"  # 資料庫名稱

    # 開啟資料庫連線
    connection = pymysql.connect(host=host, user=username, password=password, database=database)
    # 使用 cursor() 方法建立一個遊標物件 cursor
    cursor = connection.cursor()

    print("Database 連線成功。")

    # 使用 execute() 方法執行 SQL 查詢 
    # 作業目前紀錄 # posterId為班級編號
    sql = """
          SELECT t1.id, t1.contentID, t1.stat_passIDs, t1.stat_passCnt, t1.submitCnt, t2.allowDelay, t1.dueDate, t1.title
          FROM learning_item AS t1
          JOIN exercise AS t2 ON t1.contentID = t2.id
          WHERE t1.posterId = {} AND t1.relType = 'folder' AND t2.draft = 0
          """.format(classID)
    cursor.execute(sql)

    results = cursor.fetchall()
    finish_list = pd.DataFrame(results)

    col_names = [row[0] for row in cursor.description] # 取得欄位
    if len(results) > 0:
        finish_list.columns = col_names
    """
    print(f"table length : {len(finish_list)}")
    print(finish_list)
    """
    # 關閉游標物件
    cursor.close()
    # 關閉資料庫連線
    connection.close()

    finish_list['done'] = False
    finish_list['visible'] = False

    for i in range(len(finish_list)):
        userid_list = finish_list.loc[i,'stat_passIDs'].split(",")
        for j in range(len(userid_list)):
            if str(userID) == userid_list[j]:
                finish_list.loc[i,'done'] = True
                break
        
        if not finish_list.loc[i,'done']:
            if finish_list.loc[i,'allowDelay'] == 1:
                finish_list.loc[i,'visible'] = True

            else:
                if finish_list.loc[i,'dueDate'].to_pydatetime() > datetime.strptime(datetime.now(timezone(timedelta(hours=+8))).strftime("%Y-%m-%d %H:%M:%S"), "%Y-%m-%d %H:%M:%S"):
                    finish_list.loc[i,'visible'] = True


    return True, finish_list[finish_list['visible'] == True].reset_index(drop=True)
