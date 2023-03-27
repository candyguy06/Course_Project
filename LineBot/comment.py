import pymysql

import pandas as pd

def comment(linebotID):
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
    # 學生所有討論 # ownerID為班級編號 posterId為學生編號 resType = 1為老師直接張貼的主題，非課程影片等其他的討論區
    sql = """
          SELECT id, parentId, posterId, postTime, CHAR_LENGTH(title) as length, title
          FROM mod_comment
          WHERE ownerID = {} AND posterId = {} AND resType = 1
          """.format(classID, userID)
    cursor.execute(sql)

    results = cursor.fetchall()
    student_comment = pd.DataFrame(results)

    col_names = [row[0] for row in cursor.description] # 取得欄位
    if len(results) > 0:
        student_comment.columns = col_names
    """
    print(f"table length : {len(student_comment)}")
    print(student_comment)
    """
    # 課程所有討論主題
    sql = """
          SELECT id, parentId, posterId, postTime, CHAR_LENGTH(title) as length, title
          FROM mod_comment
          WHERE ownerID = {} AND resType = 1 AND parentId = 0
          """.format(classID)
    cursor.execute(sql)

    results = cursor.fetchall()
    comment_topic = pd.DataFrame(results)

    col_names = [row[0] for row in cursor.description] # 取得欄位
    if len(results) > 0:
        comment_topic.columns = col_names
    """
    print(f"table length : {len(comment_topic)}")
    print(comment_topic)
    """
    # 關閉游標物件
    cursor.close()
    # 關閉資料庫連線
    connection.close()

    comment_topic['done'] = False

    for i in range(len(comment_topic)): # 紀錄是否討論
        for j in range(len(student_comment)):
            if comment_topic.loc[i,'id'] == student_comment.loc[j,'parentId']:
                comment_topic.loc[i,'done'] = True
            
    return True, comment_topic[comment_topic['done'] == False].reset_index(drop=True)
