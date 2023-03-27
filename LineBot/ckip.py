from ckiptagger import construct_dictionary, WS, POS # tensorflow > 1.13 & tensorflow < 2 # I use the 1.15

global ws
global pos
ws = WS("./data")
pos = POS("./data")  
def main():
    text = input("問題 > ")
    ws_list, pos_list = ckip_tagger(text)

    print(text)
    print()
    assert len(ws_list) == len(pos_list)
    for ws, pos in zip(ws_list, pos_list):
        print(f"{ws}({pos})", end="\u3000")
    print()

def ckip_tagger(text):
    text = text_change(text)

    # Load model without GPU
#    ws = WS("./data")
#    pos = POS("./data")

    word_to_weight = {
        "三一微功夫":1,
        "三一功":1,
        "三變":1,
        "硬實力":1,
        "軟實力": 1,
        "職場軟實力": 1,
        "軟功夫": 1,
        "且慢功": 1,
        "探詢功": 1,
        "起步功": 1,
        "出牌功": 1,
        "終極功": 1,
        "終始功": 1,
        "轉身功": 1,
        "一步功": 1,
        "三呆": 1,
    }
    dictionary = construct_dictionary(word_to_weight)

    ws_result = ws([text], recommend_dictionary=dictionary)
    pos_result = pos(ws_result)

    # Release model
#    del ws
#    del pos

    sub_ws_result, sub_pos_result = pos_filter(ws_result[0], pos_result[0])
    
    return sub_ws_result, sub_pos_result

def text_change(text):
    for i in range(len(text)):
        if ord(text[i]) in range(65281, 65374): # 全形轉半形
            uni = ord(text[i])
            uni_change = (chr(uni - 65248).encode("utf-8")).decode('utf-8')
            text = text.replace(text[i], uni_change)
        
        if ord(text[i]) == 12288: # 空格全形轉半形
            uni_change = (chr(32).encode("utf-8")).decode('utf-8')
            text = text.replace(text[i], uni_change)
    
    text = text.lower() # 大寫轉小寫
    return text

def keep_pos(pos):
    """
    A 非謂形容詞 Caa 對等連接詞 Cab 連接詞，如：等等 Cba 連接詞，如：的話 Cbb 關聯連接詞 D 副詞 Da 數量副詞 Dfa 動詞前程度副詞 Dfb 動詞後程度副詞 Di 時態標記 Dk 句副詞 DM 定量式 I 感嘆詞
    Na 普通名詞 Nb 專有名詞 Nc 地方詞 Ncd 位置詞 Nd 時間詞 Nep 指代定詞 Neqa 數量定詞 Neqb 後置數量定詞 Nes 特指定詞 Neu 數詞定詞 Nf 量詞 Ng 後置詞 Nh 代名詞 Nv 名物化動詞
    P 介詞 T 語助詞
    VA 動作不及物動詞 VAC 動作使動動詞 VB 動作類及物動詞 VC 動作及物動詞 VCL 動作接地方賓語動詞 VD 雙賓動詞 VE 動作句賓動詞 VF 動作謂賓動詞 VG 分類動詞 VH 狀態不及物動詞 VHC 狀態使動動詞
    VI 狀態類及物動詞 VJ 狀態及物動詞 VK 狀態句賓動詞 VL 狀態謂賓動詞 V_2 有
    DE 的之得地 SHI 是 FW 外文
    COLONCATEGORY 冒號 COMMACATEGORY 逗號 DASHCATEGORY 破折號 DOTCATEGORY 點號 ETCCATEGORY 刪節號 EXCLAMATIONCATEGORY 驚嘆號 PARENTHESISCATEGORY 括號 PAUSECATEGORY 頓號
    PERIODCATEGORY 句號 QUESTIONCATEGORY 問號 SEMICOLONCATEGORY 分號 SPCHANGECATEGORY 雙直線 WHITESPACE 空白
    """
    if pos == "Na" or pos == "Nb" or pos == "Nc" or pos == "Neqb" or pos == "Nes" or pos == "Nv" or \
       pos == "VA" or pos == "VAC" or pos == "VB" or pos == "VC" or pos == "VCL" or pos == "VD" or pos == "VE" or pos == "VF" or pos == "VG" or pos == "VH" or \
       pos == "VHC" or pos == "VI" or pos == "VJ" or pos == "VK" or pos == "VL":
    # NEP NEU NEQA 被刪掉

        return True
    
    else:
        return False

def pos_filter(ws, pos):
    new_ws, new_pos = [], []

    for i in range(len(ws)):
        if keep_pos(pos[i]):
            new_ws.append(ws[i])
            new_pos.append(pos[i])

        else:
            continue
    
    return new_ws, new_pos

if __name__ == "__main__":
    main()
