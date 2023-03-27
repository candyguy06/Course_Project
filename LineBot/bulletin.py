import pymysql

import pandas as pd
from datetime import datetime, timezone, timedelta

def bulletin(linebotID):
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

        return False, 0, student

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
    # 課程公告 # id, SUBSTR(pageId, 8) AS ownerID, userID, publishFrom, publishTo, topMost, viewCnt, title
    sql = """
          SELECT id, SUBSTR(pageId, 8) AS ownerID, userID, publishFrom, publishTo, topMost, viewCnt, title
          FROM bulletin
          WHERE SUBSTR(pageID, 8) = {} AND uploadComplete = 1
          ORDER BY publishFrom DESC
          """.format(classID)
    cursor.execute(sql)

    results = cursor.fetchall()
    bulletin_list = pd.DataFrame(results)

    col_names = [row[0] for row in cursor.description] # 取得欄位
    if len(results) > 0:
        bulletin_list.columns = col_names
    """
    print(f"table length : {len(bulletin_list)}")
    print(bulletin_list)
    """
    # 關閉游標物件
    cursor.close()
    # 關閉資料庫連線
    connection.close()

    bulletin_list['visible'] = False

    for i in range(len(bulletin_list)):
        if bulletin_list.loc[i,'publishTo'] == "0000-00-00 00:00:00" or \
           bulletin_list.loc[i,'publishTo'] > datetime.strptime(datetime.now(timezone(timedelta(hours=+8))).strftime("%Y-%m-%d %H:%M:%S"), "%Y-%m-%d %H:%M:%S"):
            bulletin_list.loc[i,'visible'] = True


    return True, classID, bulletin_list[bulletin_list['visible'] == True].reset_index(drop=True)
    