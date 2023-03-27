import pymysql

import pandas as pd
from datetime import datetime, timezone, timedelta

def exam(linebotID):
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
    # 課程測驗
    sql = """
          SELECT t1.id, SUBSTR(t1.pageId, 7) AS examID, t1.userID, t1.start_date, t1.end_date, t2.title
          FROM mod_exam AS t1
          JOIN content AS t2 ON SUBSTR(t1.pageId, 7) = t2.id
          WHERE t1.uploadComplete = 1 AND t2.ownerID = {}
          """.format(classID)
    cursor.execute(sql)

    results = cursor.fetchall()
    exam_list = pd.DataFrame(results)

    col_names = [row[0] for row in cursor.description] # 取得欄位
    if len(results) > 0:
        exam_list.columns = col_names
    """
    print(f"table length : {len(exam_list)}")
    print(exam_list)
    """
    # 學生測驗紀錄
    sql = """
          SELECT id, examID, userID, score, lastUpdate
          FROM mod_exam_record
          WHERE examID IN (
              SELECT t1.id
              FROM mod_exam AS t1
              JOIN content AS t2 ON SUBSTR(t1.pageId, 7) = t2.id
              WHERE t1.uploadComplete = 1 AND t2.ownerID = {}
              )
          AND userID = {}
          """.format(classID, userID)
    cursor.execute(sql)

    results = cursor.fetchall()
    done_list = pd.DataFrame(results)

    col_names = [row[0] for row in cursor.description] # 取得欄位
    if len(results) > 0:
        done_list.columns = col_names
    """
    print(f"table length : {len(done_list)}")
    print(done_list)
    """
    # 關閉游標物件
    cursor.close()
    # 關閉資料庫連線
    connection.close()

    exam_list['done'] = False
    exam_list['visible'] = False

    for i in range(len(exam_list)):
        for j in range(len(done_list)):
            if exam_list.loc[i,'id'] == done_list.loc[j,'examID']:
                exam_list.loc[i,'done'] = True
            if exam_list.loc[i,'end_date'].to_pydatetime() > datetime.strptime(datetime.now(timezone(timedelta(hours=+8))).strftime("%Y-%m-%d %H:%M:%S"), "%Y-%m-%d %H:%M:%S"):
                exam_list.loc[i,'visible'] = True
                

    return True, exam_list[(exam_list['done'] == False) & (exam_list['visible'] == True)].reset_index(drop=True)
