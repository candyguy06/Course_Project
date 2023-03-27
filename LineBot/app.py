from flask import Flask, request, abort
from linebot import LineBotApi, WebhookHandler
from linebot.exceptions import InvalidSignatureError
from linebot.models import FollowEvent, MessageEvent, TextMessage, TextSendMessage, FlexSendMessage

import configparser

# LINE 聊天機器人的基本資料
config = configparser.ConfigParser()
config.read('config.ini')

line_bot_api = LineBotApi(config.get('line-bot', 'channel_access_token'))
handler = WebhookHandler(config.get('line-bot', 'channel_secret'))
app = Flask(__name__)

# 監聽所有來自 /callback 的 Post Request
@app.route("/callback", methods=['POST'])
def callback():
    # get X-Line-Signature header value
    signature = request.headers['X-Line-Signature']
    # get request body as text
    body = request.get_data(as_text=True)
    app.logger.info("Request body: " + body)
    # handle webhook body
    try:
        handler.handle(body, signature)
    except InvalidSignatureError:
        abort(400)
    return 'OK'

# 被新追蹤的歡迎詞
@handler.add(FollowEvent)
def handle_follow(event):
    print(f"新加入userID: {event.source.user_id}")

    Flex_message = FlexSendMessage(
        alt_text="歡迎使用 職場溝通軟功夫 線上學習助理。",
        contents={
            "type": "bubble",
            "body": {
                "type": "box",
                "layout": "vertical",
                "contents": [
                    {
                        "type": "text",
                        "text": "歡迎使用 職場溝通軟功夫 線上學習助理。"
                    },
                    {
                        "type": "text",
                        "text": "點擊'學生登記'完成登記來使用更多功能。"
                    }
                ]
            },
            "footer": {
                "type": "box",
                "layout": "vertical",
                "contents": [
                    {
                        "type": "button",
                        "action": {
                            "type": "message",
                            "label": "學生登記",
                            "text": "學生登記"
                        }
                    }
                ]
            }
        }
    )
    
    line_bot_api.reply_message(event.reply_token, Flex_message)

from userid import userid
from video import video
from comment import comment
from exercise import exercise
from exam import exam
from bulletin import bulletin
from recommend import recommend
from qa import qa
import os
import pandas as pd
from datetime import datetime, timezone, timedelta

# 處理訊息
@handler.add(MessageEvent, message=TextMessage)
def handle_message(event):
    # message to feed back
    print(f"Handle: reply_token: {event.reply_token}, user_id: {event.source.user_id}, message: {event.message.text}")

    # 紀錄所有使用紀錄，以每日作為分隔
    now_date = datetime.now(timezone(timedelta(hours=+8))).strftime("%Y-%m-%d")
    now_time = datetime.now(timezone(timedelta(hours=+8))).strftime("%Y-%m-%d-%H-%M-%S")
    
    if os.path.isfile(f"./response_log/response_{now_date}.txt"):
        with open(f"./response_log/response_{now_date}.txt", "a", encoding='utf-8') as f:
            f.write("{"+f"\"reply_token\": \"{event.reply_token}\", \"user_id\": \"{event.source.user_id}\", \"now_time\": \"{now_time}\", \"message\": \"{event.message.text}\""+"}\n")
    else:
        with open(f"./response_log/response_{now_date}.txt", "w", encoding='utf-8') as f:
            f.write("{"+f"\"reply_token\": \"{event.reply_token}\", \"user_id\": \"{event.source.user_id}\", \"now_time\": \"{now_time}\", \"message\": \"{event.message.text}\""+"}\n")

    text = event.message.text # 輸入內容
    linebotID = event.source.user_id # 學生與bot的聊天室編號
    is_record = False # 正在學生登記
    is_recommend = False # 正在推薦影片
    is_qa = False #正在問答

    function_list = ["學生登記", "未讀影片", "未做討論", "未做作業", "未做測驗", "課程公告", "題庫問答", "推薦影片"] # 所有功能

    if os.path.isfile(f"./record/record_{linebotID}.txt"): # 存在"學生登記"暫存檔案
        if (text in function_list) or text == "小幫手" or text == "小幫手2":
            os.remove(f"./record/record_{linebotID}.txt")
            print(f"record_{linebotID}.txt 已刪除。")
        
        else:
            n_dt = datetime.now(timezone(timedelta(hours=+8))).strftime("%Y-%m-%d %H:%M:%S") # 取得現在時間、設定為 +8 時區

            with open(f"./record/record_{linebotID}.txt", encoding='utf-8') as f:
                record_list = f.read().splitlines()
            
            f_dt = record_list[0]
            a_dt = datetime.strptime(n_dt, "%Y-%m-%d %H:%M:%S")
            b_dt = datetime.strptime(f_dt, "%Y-%m-%d %H:%M:%S")

            sec_range = (a_dt - b_dt).seconds

            if sec_range > 180: # 逾時3分鐘，刪除暫存資料，並退出登記階段
                os.remove(f"./record/record_{linebotID}.txt")
                print(f"record_{linebotID}.txt 已刪除。")

                Flex_message = FlexSendMessage(
                    alt_text="逾時提醒訊息。",
                    contents={
                        "type": "bubble",
                        "body": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": [
                                {
                                    "type": "text",
                                    "text": "\'學生登記\'逾時3分鐘，"
                                },
                                {
                                    "type": "text",
                                    "text": "請點擊\'學生登記\'重新進行登記。"
                                }
                            ]
                        },
                        "footer": {
                            "type": "box",
                            "layout": "horizontal",
                            "contents": [
                                {
                                    "type": "button",
                                    "action": {
                                        "type": "message",
                                        "label": "學生登記",
                                        "text": "學生登記"
                                    }
                                }
                            ]
                        }
                    }
                )
                
                line_bot_api.reply_message(event.reply_token, Flex_message)
            
            else:
                is_record = True
                print(f"{linebotID} 正在登記userID。")

    if os.path.isfile(f"./recommend/recommend_{linebotID}.txt"): # 存在"推薦影片"暫存檔案
        if (text in function_list) or text == "小幫手" or text == "小幫手2":
            with open(f"./recommend/recommend_{linebotID}.txt", encoding='utf-8') as f:
                recommend_list = f.read().splitlines()

            os.remove(f"./recommend/recommend_{linebotID}.txt")
            print(f"recommend_{linebotID}.txt 已刪除。")
        
        else:
            n_dt = datetime.now(timezone(timedelta(hours=+8))).strftime("%Y-%m-%d %H:%M:%S") # 取得現在時間、設定為 +8 時區

            with open(f"./recommend/recommend_{linebotID}.txt", encoding='utf-8') as f:
                recommend_list = f.read().splitlines()
            
            f_dt = recommend_list[0]
            a_dt = datetime.strptime(n_dt, "%Y-%m-%d %H:%M:%S")
            b_dt = datetime.strptime(f_dt, "%Y-%m-%d %H:%M:%S")

            sec_range = (a_dt - b_dt).seconds

            if sec_range > 180: # 逾時3分鐘，刪除暫存資料，並退出推薦階段
                os.remove(f"./recommend/recommend_{linebotID}.txt")
                print(f"chat_{linebotID}.txt 已刪除。")

                Flex_message = FlexSendMessage(
                    alt_text="逾時提醒訊息。",
                    contents={
                        "type": "bubble",
                        "body": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": [
                                {
                                    "type": "text",
                                    "text": "\'問題回饋\'逾時3分鐘，"
                                },
                                {
                                    "type": "text",
                                    "text": "請重新輸入問題或選擇其他功能。"
                                }
                            ]
                        },
                        "footer": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": [
                                {
                                    "type": "button",
                                    "action": {
                                        "type": "message",
                                        "label": "小幫手",
                                        "text": "小幫手"
                                    }
                                }
                            ]
                        }
                    }
                )
                
                line_bot_api.reply_message(event.reply_token, Flex_message)
            
            else:
                is_recommend = True
                print(f"{linebotID} 正在推薦影片。")

    if os.path.isfile(f"./qa/qa_{linebotID}.txt"): # 存在"題庫問答"暫存檔案
        if (text in function_list) or text == "小幫手" or text == "小幫手2":
            with open(f"./qa/qa_{linebotID}.txt", encoding='utf-8') as f:
                qa_list = f.read().splitlines()

            os.remove(f"./qa/qa_{linebotID}.txt")
            print(f"qa_{linebotID}.txt 已刪除。")
        
        else:
            n_dt = datetime.now(timezone(timedelta(hours=+8))).strftime("%Y-%m-%d %H:%M:%S") # 取得現在時間、設定為 +8 時區

            with open(f"./qa/qa_{linebotID}.txt", encoding='utf-8') as f:
                qa_list = f.read().splitlines()
            
            f_dt = qa_list[0]
            a_dt = datetime.strptime(n_dt, "%Y-%m-%d %H:%M:%S")
            b_dt = datetime.strptime(f_dt, "%Y-%m-%d %H:%M:%S")

            sec_range = (a_dt - b_dt).seconds

            if sec_range > 180: # 逾時3分鐘，刪除暫存資料，並退出推薦階段
                os.remove(f"./qa/qa_{linebotID}.txt")
                print(f"chat_{linebotID}.txt 已刪除。")

                Flex_message = FlexSendMessage(
                    alt_text="逾時提醒訊息。",
                    contents={
                        "type": "bubble",
                        "body": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": [
                                {
                                    "type": "text",
                                    "text": "\'問題回饋\'逾時3分鐘，"
                                },
                                {
                                    "type": "text",
                                    "text": "請重新輸入問題或選擇其他功能。"
                                }
                            ]
                        },
                        "footer": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": [
                                {
                                    "type": "button",
                                    "action": {
                                        "type": "message",
                                        "label": "小幫手",
                                        "text": "小幫手"
                                    }
                                }
                            ]
                        }
                    }
                )
                
                line_bot_api.reply_message(event.reply_token, Flex_message)
            
            else:
                is_qa = True
                print(f"{linebotID} 正在問答。")


    if is_record or (not is_record and text == "學生登記"): # 學生登記 userID
        response = userid(text, linebotID) # 前往userid.py連結c-learning資料庫

        response_json = []
        for i in range(len(response)):
            response_json.append(
                {
                    "type": "text",
                    "text": response[i]
                }
            )

        if os.path.isfile(f"./record/record_{linebotID}.txt"): # 正在登記 userID
            # 學生登記時暫存的檔案，包含：紀錄時間、是否退出、階段步驟、學生姓名、學生學號
            with open(f"./record/record_{linebotID}.txt", encoding='utf-8') as f:
                record_list = f.read().splitlines()
            
            step_count = int(record_list[2]) # 正在進行步驟
   
            if step_count == 2 or step_count == 3: # 純文字輸出
                Flex_message = FlexSendMessage(
                    alt_text="文字輸出訊息。",
                    contents={
                        "type": "bubble",
                        "body": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": response_json
                        }
                    }
                )
            
            elif step_count == 4 or step_count == 5: # 包含是否按鈕輸出
                Flex_message = FlexSendMessage(
                    alt_text="資料確認訊息。",
                    contents={
                        "type": "bubble",
                        "body": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": response_json
                        },
                        "footer": {
                            "type": "box",
                            "layout": "horizontal",
                            "contents": [
                                {
                                    "type": "button",
                                    "action": {
                                        "type": "message",
                                        "label": "是(Yes)",
                                        "text": "是"
                                    }
                                },
                                {
                                    "type": "button",
                                    "action": {
                                        "type": "message",
                                        "label": "否(No)",
                                        "text": "否"
                                    }
                                }
                            ]
                        }
                    }
                )
            
        else: # 即將退出登記
            Flex_message = FlexSendMessage(
                alt_text="退出登記訊息。",
                contents={
                    "type": "bubble",
                    "body": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": response_json
                    },
                    "footer": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "button",
                                "action": {
                                    "type": "message",
                                    "label": "小幫手",
                                    "text": "小幫手"
                                }
                            }
                        ]
                    }
                }
            )
            
        line_bot_api.reply_message(event.reply_token, Flex_message)

    elif is_recommend or (not is_recommend and text == "推薦影片"): # 根據問題提供推薦的影片
        response = recommend(text, linebotID)

        response_json = []
        if os.path.isfile(f"./recommend/recommend_{linebotID}.txt"): # 正在推薦影片
            # 學生登記時暫存的檔案，包含：紀錄時間、是否退出、階段步驟、學生問題、bot回覆
            with open(f"./recommend/recommend_{linebotID}.txt", encoding='utf-8') as f:
                recommend_list = f.read().splitlines()
            
            step_count = int(recommend_list[2]) # 正在進行步驟

            if step_count == 2: # 取得提問
                for i in range(len(response)):
                    response_json.append(
                        {
                            "type": "text",
                            "text": response[i]
                        }
                    )
                
                Flex_message = FlexSendMessage(
                    alt_text="取得提問訊息。",
                    contents={
                        "type": "bubble",
                        "body": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": response_json
                        }
                    }
                )
            
            if step_count == 3: # 提供推薦影片
                url_json = []

                response_json.append(
                    {
                        "type": "text",
                        "text": "問題："
                    }
                )
                response_json.append(
                    {
                        "type": "text",
                        "text": text
                    }
                )
                response_json.append(
                    {
                        "type": "text",
                        "text": "回答："
                    }
                )
                response_json.append(
                    {
                        "type": "text",
                        "text": "推薦影片："
                    }
                )

                i = 0
                while i < len(response):
                    response_json.append(
                        {
                            "type": "text",
                            "text": f"日期：{response[i]}"
                        }
                    )
                    response_json.append(
                        {
                            "type": "text",
                            "text": f"影片：{response[i+1]}"
                        }
                    )
                    response_json.append(
                        {
                            "type": "text",
                            "text": f"推薦時間：{response[i+2]}"
                        }
                    )
                    url_json.append(
                        {
                            "type": "button",
                            "action": {
                                "type": "uri",
                                "label": f"{response[i+1]}",
                                "uri": f"https://c-learning.cycu.edu.tw/media/{response[i+3]}/"
                            }
                        }
                    )
                    i = i + 4
                
                Flex_message = FlexSendMessage(
                    alt_text="對話聊天訊息。",
                    contents={
                        "type": "bubble",
                        "body": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": response_json
                        },
                        "footer": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": url_json
                        }
                    }
                )

                line_bot_api.push_message(linebotID, Flex_message)

                Flex_message = FlexSendMessage(
                    alt_text="幫助確認訊息。",
                    contents={
                        "type": "bubble",
                        "body": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": [
                                {
                                    "type": "text",
                                    "text": "請問推薦的影片對你是否幫助嗎？"
                                }
                            ]
                        },
                        "footer": {
                            "type": "box",
                            "layout": "horizontal",
                            "contents": [
                                {
                                    "type": "button",
                                    "action": {
                                        "type": "message",
                                        "label": "是(Yes)",
                                        "text": "是"
                                    }
                                },
                                {
                                    "type": "button",
                                    "action": {
                                        "type": "message",
                                        "label": "否(No)",
                                        "text": "否"
                                    }
                                }
                            ]
                        }
                    }
                )
            
        else: # 退出推薦
            for i in range(len(response)):
                response_json.append(
                    {
                        "type": "text",
                        "text": response[i]
                    }
                )

            Flex_message = FlexSendMessage(
                alt_text="退出推薦訊息。",
                contents={
                    "type": "bubble",
                    "body": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": response_json
                    },
                    "footer": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "button",
                                "action": {
                                    "type": "message",
                                    "label": "小幫手",
                                    "text": "小幫手"
                                }
                            }
                        ]
                    }
                }
            )
            
        line_bot_api.reply_message(event.reply_token, Flex_message)

    elif is_qa or (not is_qa and text == "題庫問答"): # 根據問題提供題庫回答
        Flex_message = FlexSendMessage(
            alt_text="退出推薦訊息。",
            contents={
                "type": "bubble",
                "body": {
                    "type": "box",
                    "layout": "vertical",
                    "contents": [
                        {
                            "type": "text",
                            "text": "問答中 請耐心等候"
                        }
                    ]
                }
            }
        )
        line_bot_api.reply_message(event.reply_token, Flex_message)
        response = qa(text, linebotID)

        response_json = []
        if os.path.isfile(f"./qa/qa_{linebotID}.txt"): # 正在問答
            # 學生登記時暫存的檔案，包含：紀錄時間、是否退出、階段步驟、學生問題、bot回覆
            with open(f"./qa/qa_{linebotID}.txt", encoding='utf-8') as f:
                qa_list = f.read().splitlines()
            
            step_count = int(qa_list[2]) # 正在進行步驟

            if step_count == 2: # 取得提問
                for i in range(len(response)):
                    response_json.append(
                        {
                            "type": "text",
                            "text": response[i]
                        }
                    )
                
                Flex_message = FlexSendMessage(
                    alt_text="取得提問訊息。",
                    contents={
                        "type": "bubble",
                        "body": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": response_json
                        }
                    }
                )


            
            if step_count == 3: # 確認問題題目
                qa_json = []

                response_json.append(
                    {
                        "type": "text",
                        "text": "以下哪個問題是您要問的?"
                    }
                )

                i = 0
                while i < len(response):
                    qa_json.append(
                        {
                            "type": "button",
                            "action": {
                                "type": "message",
                                "label": f"{i}.{response[i]}",
                                "text": f"{i}"
                            }
                        }
                    )

                    response_json.append(
                        {
                            "type": "text",
                            "text": f"{i}."                                
                        }
                    )

                    tail = 0
                    for j in range(15,len(response[i]),15) :
                        response_json.append(
                            {
                                "type": "text",
                                "text": f"{response[i][j-15:j]}"                                
                            }
                        )
                        tail = j

                    response_json.append(
                        {
                            "type": "text",
                            "text": f"{response[i][tail:len(response[i])]}"                                
                        }
                    )

                    i = i + 1

                qa_json.append(
                    {
                        "type": "button",
                        "action": {
                            "type" :"message",
                            "label" : "沒有想問的",
                            "text": f"沒有想問的"
                        }
                    }
                )
                
                Flex_message = FlexSendMessage(
                    alt_text="對話聊天訊息。",
                    contents={
                        "type": "bubble",
                        "body": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": response_json
                        },
                        "footer": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": qa_json
                        }
                    }
                )


            if step_count == 4 :
                for i in range(len(response)):
                    response_json.append(
                        {
                            "type": "text",
                            "text": response[i]
                        }
                    )
                Flex_message = FlexSendMessage(
                    alt_text="回答問題。",
                    contents={
                        "type": "bubble",
                        "body": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": response_json
                        }
                    }
                )

                line_bot_api.push_message(linebotID, Flex_message)

                Flex_message = FlexSendMessage(
                    alt_text="幫助確認訊息。",
                    contents={
                        "type": "bubble",
                        "body": {
                            "type": "box",
                            "layout": "vertical",
                            "contents": [
                                {
                                    "type": "text",
                                    "text": "請問這次的問答對你是否幫助嗎？"
                                }
                            ]
                        },
                        "footer": {
                            "type": "box",
                            "layout": "horizontal",
                            "contents": [
                                {
                                    "type": "button",
                                    "action": {
                                        "type": "message",
                                        "label": "是(Yes)",
                                        "text": "是"
                                    }
                                },
                                {
                                    "type": "button",
                                    "action": {
                                        "type": "message",
                                        "label": "否(No)",
                                        "text": "否"
                                    }
                                }
                            ]
                        }
                    }
                )
            
        else: # 退出提問
            for i in range(len(response)):
                response_json.append(
                    {
                        "type": "text",
                        "text": response[i]
                    }
                )

            Flex_message = FlexSendMessage(
                alt_text="退出問答訊息。",
                contents={
                    "type": "bubble",
                    "body": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": response_json
                    },
                    "footer": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "button",
                                "action": {
                                    "type": "message",
                                    "label": "小幫手",
                                    "text": "小幫手"
                                }
                            }
                        ]
                    }
                }
            )
            
        line_bot_api.push_message(linebotID, Flex_message)

    elif text == "小幫手" or text == "小幫手2": # 功能總表：學生登記 未讀影片 未做討論 未做作業 未做測驗 課程公告 推薦影片
        text_json = []
        function_json = []
        if text == "小幫手":
            text_json.append(
                {
                    "type": "text",
                    "text": f"{text}：還有\'小幫手2\'"
                }
            )

            for i in range(3):
                function_json.append(
                    {
                        "type": "button",
                        "action": {
                            "type": "message",
                            "label": f"{function_list[i]}",
                            "text": f"{function_list[i]}"
                        }
                    }
                )
            
            function_json.append(
                {
                    "type": "button",
                    "action": {
                        "type": "message",
                        "label": "小幫手2",
                        "text": "小幫手2"
                    }
                }
            )
        
        elif text == "小幫手2":
            text_json.append(
                {
                    "type": "text",
                    "text": f"{text}："
                }
            )

            for i in range(3,6):
                function_json.append(
                    {
                        "type": "button",
                        "action": {
                            "type": "message",
                            "label": f"{function_list[i]}",
                            "text": f"{function_list[i]}"
                        }
                    }
                )

        Flex_message = FlexSendMessage(
            alt_text="小幫手訊息。",
            contents={
                "type": "bubble",
                "body": {
                    "type": "box",
                    "layout": "vertical",
                    "contents": text_json
                },
                "footer": {
                    "type": "box",
                    "layout": "vertical",
                    "contents": function_json
                }
            }
        )
        
        line_bot_api.reply_message(event.reply_token, Flex_message)
    
    elif text == "未讀影片": # 學生未讀的必讀影片
        hasLinebotID, past_must_list, current_must_list = video(linebotID, must_video=True) # 必讀 # id contentID contentDate contentType contentTitle finished
        hasLinebotID, past_may_list, current_may_list = video(linebotID, must_video=False) # 非必讀
        must_json = []
        may_json = []

        if hasLinebotID: # 有 linebotID
            must_json.append(
                {
                    "type": "text",
                    "text": "未讀的必讀影片："
                }
            )

            for a in range(len(past_must_list)):
                must_json.append(
                    {
                        "type": "text",
                        "text": f"{past_must_list.loc[a,'contentDate']} : {past_must_list.loc[a,'contentTitle']}"
                    }
                )

            must_json.append(
                {
                    "type": "text",
                    "text": "這週的必讀影片："
                }
            )

            for a in range(len(current_must_list)):
                must_json.append(
                    {
                        "type": "text",
                        "text": f"{current_must_list.loc[a,'contentDate']} : {current_must_list.loc[a,'contentTitle']}"
                    }
                )
            
            may_json.append(
                {
                    "type": "text",
                    "text": "未讀非必讀影片："
                }
            )

            for b in range(len(past_may_list)):
                may_json.append(
                    {
                        "type": "text",
                        "text": f"{past_may_list.loc[b,'contentDate']} : {past_may_list.loc[b,'contentTitle']}"
                    }
                )
            
            may_json.append(
                {
                    "type": "text",
                    "text": "這週非必讀影片："
                }
            )

            for b in range(len(current_may_list)):
                may_json.append(
                    {
                        "type": "text",
                        "text": f"{current_may_list.loc[b,'contentDate']} : {current_may_list.loc[b,'contentTitle']}"
                    }
                )
            
            Flex_message = FlexSendMessage(
                alt_text="未讀影片訊息。",
                contents={
                    "type": "carousel",
                    "contents": [
                        {
                            "type": "bubble",
                            "body": {
                                "type": "box",
                                "layout": "vertical",
                                "contents": must_json
                            },
                            "footer": {
                                "type": "box",
                                "layout": "vertical",
                                "contents": [
                                    {
                                        "type": "button",
                                        "action": {
                                            "type": "message",
                                            "label": "小幫手",
                                            "text": "小幫手"
                                        }
                                    }
                                ]
                            }
                        },
                        {
                            "type": "bubble",
                            "body": {
                                "type": "box",
                                "layout": "vertical",
                                "contents": may_json
                            }
                        }
                    ]
                }
            )
            
            line_bot_api.reply_message(event.reply_token, Flex_message)

        else:
            Flex_message = FlexSendMessage(
                alt_text="尚未登記訊息。",
                contents={
                    "type": "bubble",
                    "body": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "text",
                                "text": "請先進行'學生登記'，來啟動這項功能。"
                            }
                        ]
                    },
                    "footer": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "button",
                                "action": {
                                    "type": "message",
                                    "label": "學生登記",
                                    "text": "學生登記"
                                }
                            }
                        ]
                    }
                }
            )
            
            line_bot_api.reply_message(event.reply_token, Flex_message)

    elif text == "未做討論": # 學生未做的討論
        hasLinebotID, comment_list = comment(linebotID) # 討論 # id parentId posterId postTime length title done
        comment_json = []

        if hasLinebotID: # 有 linebotID
            comment_json.append(
                {
                    "type": "text",
                    "text": "未做的討論："
                }
            )

            for i in range(len(comment_list)):
                comment_json.append(
                    {
                        "type": "text",
                        "text": f"{comment_list.loc[i,'id']} : {comment_list.loc[i,'title']}"
                    }
                )
            
            Flex_message = FlexSendMessage(
                alt_text="未做討論訊息。",
                contents={
                    "type": "bubble",
                    "body": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": comment_json
                    },
                    "footer": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "button",
                                "action": {
                                    "type": "message",
                                    "label": "小幫手",
                                    "text": "小幫手"
                                }
                            }
                        ]
                    }
                }
            )
            
            line_bot_api.reply_message(event.reply_token, Flex_message)

        else:
            Flex_message = FlexSendMessage(
                alt_text="尚未登記訊息。",
                contents={
                    "type": "bubble",
                    "body": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "text",
                                "text": "請先進行'學生登記'，來啟動這項功能。"
                            }
                        ]
                    },
                    "footer": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "button",
                                "action": {
                                    "type": "message",
                                    "label": "學生登記",
                                    "text": "學生登記"
                                }
                            }
                        ]
                    }
                }
            )
            
            line_bot_api.reply_message(event.reply_token, Flex_message)
        
    elif text == "未做作業": # 學生未做的作業
        hasLinebotID, exercise_list = exercise(linebotID) # 作業 # id contentID stat_passIDs stat_passCnt submitCnt allowDelay dueDate title done show
        exercise_json = []

        if hasLinebotID: # 有 linebotID
            exercise_json.append(
                {
                    "type": "text",
                    "text": "未做的作業："
                }
            )

            for i in range(len(exercise_list)):
                exercise_json.append(
                    {
                        "type": "text",
                        "text": f"{i+1} : {exercise_list.loc[i,'title']}"
                    }
                )
            
            Flex_message = FlexSendMessage(
                alt_text="未做作業訊息。",
                contents={
                    "type": "bubble",
                    "body": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": exercise_json
                    },
                    "footer": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "button",
                                "action": {
                                    "type": "message",
                                    "label": "小幫手",
                                    "text": "小幫手"
                                }
                            }
                        ]
                    }
                }
            )
            
            line_bot_api.reply_message(event.reply_token, Flex_message)

        else:
            Flex_message = FlexSendMessage(
                alt_text="尚未登記訊息。",
                contents={
                    "type": "bubble",
                    "body": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "text",
                                "text": "請先進行'學生登記'，來啟動這項功能。"
                            }
                        ]
                    },
                    "footer": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "button",
                                "action": {
                                    "type": "message",
                                    "label": "學生登記",
                                    "text": "學生登記"
                                }
                            }
                        ]
                    }
                }
            )
            
            line_bot_api.reply_message(event.reply_token, Flex_message)

    elif text == "未做測驗": # 學生未做的測驗
        hasLinebotID, exam_list = exam(linebotID) # 測驗 # id examID userID start_date end_date title done
        exam_json = []

        if hasLinebotID: # 有 linebotID
            exam_json.append(
                {
                    "type": "text",
                    "text": "未做的測驗："
                }
            )

            for i in range(len(exam_list)):
                exam_json.append(
                    {
                        "type": "text",
                        "text": f"{i+1} : {exam_list.loc[i,'title']}"
                    }
                )
            
            Flex_message = FlexSendMessage(
                alt_text="未做測驗訊息。",
                contents={
                    "type": "bubble",
                    "body": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": exam_json
                    },
                    "footer": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "button",
                                "action": {
                                    "type": "message",
                                    "label": "小幫手",
                                    "text": "小幫手"
                                }
                            }
                        ]
                    }
                }
            )
            
            line_bot_api.reply_message(event.reply_token, Flex_message)

        else:
            Flex_message = FlexSendMessage(
                alt_text="尚未登記訊息。",
                contents={
                    "type": "bubble",
                    "body": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "text",
                                "text": "請先進行'學生登記'，來啟動這項功能。"
                            }
                        ]
                    },
                    "footer": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "button",
                                "action": {
                                    "type": "message",
                                    "label": "學生登記",
                                    "text": "學生登記"
                                }
                            }
                        ]
                    }
                }
            )
            
            line_bot_api.reply_message(event.reply_token, Flex_message)

    elif text == "課程公告": # C-learning 課程公告
        hasLinebotID, courseID, bulletin_list = bulletin(linebotID) # 課程公告 # id ownerID userID publishFrom publishTo topMost viewCnt title visible
        bulletin_json = []

        if hasLinebotID: # 有 linebotID
            bulletin_json.append(
                {
                    "type": "text",
                    "text": "課程公告："
                }
            )

            for i in range(len(bulletin_list)):
                bulletin_json.append(
                    {
                        "type": "text",
                        "text": f"{bulletin_list.loc[i,'id']} : {bulletin_list.loc[i,'title']}"
                    }
                )
            
            Flex_message = FlexSendMessage(
                alt_text="課程公告訊息。",
                contents={
                    "type": "bubble",
                    "body": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": bulletin_json
                    },
                    "footer": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "button",
                                "action": {
                                    "type": "uri",
                                    "label": "課程網頁",
                                    "uri": f"https://c-learning.cycu.edu.tw/course/{courseID}/section/lecture"
                                }
                            },
                            {
                                "type": "button",
                                "action": {
                                    "type": "message",
                                    "label": "小幫手",
                                    "text": "小幫手"
                                }
                            }
                        ]
                    }
                }
            )
            
            line_bot_api.reply_message(event.reply_token, Flex_message)

        else:
            Flex_message = FlexSendMessage(
                alt_text="尚未登記訊息。",
                contents={
                    "type": "bubble",
                    "body": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "text",
                                "text": "請先進行'學生登記'，來啟動這項功能。"
                            }
                        ]
                    },
                    "footer": {
                        "type": "box",
                        "layout": "vertical",
                        "contents": [
                            {
                                "type": "button",
                                "action": {
                                    "type": "message",
                                    "label": "學生登記",
                                    "text": "學生登記"
                                }
                            }
                        ]
                    }
                }
            )
            
            line_bot_api.reply_message(event.reply_token, Flex_message)

    elif text == "這次的課程提醒對我有幫助" or text == "這次的課程提醒對我沒有幫助" : # 推播回覆
        Flex_message = FlexSendMessage(
            alt_text="推播回覆。",
            contents={
                "type": "bubble",
                "body": {
                    "type": "box",
                    "layout": "vertical",
                    "contents": [
                        {
                            "type": "text",
                            "text": "感謝您的回覆。"
                        }
                    ]
                },
                "footer": {
                    "type": "box",
                    "layout": "vertical",
                    "contents": [
                        {
                            "type": "button",
                            "action": {
                                "type": "message",
                                "label": "小幫手",
                                "text": "小幫手"
                            }
                        }
                    ]
                }
            }
        )


        line_bot_api.reply_message(event.reply_token, Flex_message)
        
        if os.path.isfile(f"./pushreply_log/pushreply_{now_date}.txt"):
            with open(f"./pushreply_log/pushreply_{now_date}.txt", "a", encoding='utf-8') as f:
                f.write("{"+f"\"reply_token\": \"{event.reply_token}\", \"user_id\": \"{event.source.user_id}\", \"now_time\": \"{now_time}\", \"message\": \"{event.message.text}\""+"}\n")
        else:
            with open(f"./pushreply_log/pushreply_{now_date}.txt", "w", encoding='utf-8') as f:
                f.write("{"+f"\"reply_token\": \"{event.reply_token}\", \"user_id\": \"{event.source.user_id}\", \"now_time\": \"{now_time}\", \"message\": \"{event.message.text}\""+"}\n")



if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)
